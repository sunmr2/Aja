#include "xpt.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <map>
#include <list>
#include <algorithm>
#include "ntv2enums.h"
#include "ntv2signalrouter.h"
#include "ntv2devicefeatures.h"
#include <assert.h>
#include "memory.h"
#include <time.h>
#include <stdlib.h>

using namespace std;

sBoardInfo boardInfo[] =
{
    "xpt_c44",              DEVICE_ID_CORVID44,   "xpt_c44",
    "xpt_dax",              DEVICE_ID_CORVID88,   "xpt_c88",
    "xpt_kona_4",           DEVICE_ID_KONA4,      "xpt_kona_4",
    "xpt_kona_4_ufc",       DEVICE_ID_KONA4UFC,   "xpt_kona4_ufc",
    "xpt_io_xt_4k",         DEVICE_ID_IO4K,       "xpt_io4k",
    "xpt_io_xt_4k_ufc",     DEVICE_ID_IO4KUFC,    "xpt_io4k_ufc",
    "xpt_c44",              DEVICE_ID_KONAIP_4CH_1SFP, "xpt_kip_4rxtx",
    "xpt_c44",              DEVICE_ID_KONAIP_4CH_2SFP, "xpt_kip_2p2rxtc",
    "xpt_c44",              DEVICE_ID_KONAIP_1RX_1TX_1SFP_J2K, "xpt_kip_j2k1rxtx",
    "xpt_c44",              DEVICE_ID_KONAIP_2TX_1SFP_J2K, "xpt_kip_j2k2tx",
    "xpt_c44",              DEVICE_ID_KONAIP_4TX_2110, "xpt_kip_2100_4tx",
    "xpt_c44",              DEVICE_ID_KONAIP_1RX_1TX_2110, "xpt_kip_2100_1rxtx"
};

#define boardInfoSize (sizeof(boardInfo)/sizeof(sBoardInfo))

/*
Brief: Constructor to initialize the filename.
Input: Filename to parse.
Output:
*/
XpointValidationGenerator::XpointValidationGenerator(string file)
{
    rawInputFilename = file;
    inputFilename    = file;

    // Initialize 2D array of possible firmware widget routes to all false
    for(unsigned int i= 0; i < NTV2_LAST_INPUT_CROSSPOINT; i++)
    {
        for(unsigned int j= 0; j < NTV2_LAST_OUTPUT_CROSSPOINT; j++)
        {
            matrixYCbCr[i][j] = false;
            matrixRGB[i][j] = false;
        }
    }

    // Initialize maps needed for parsing and conversions
    createInputCrosspointID();
}

/*
Brief: Opens the files in read mode, creates the maps we need
to parse and convert names from the verilog file. This functions
also does error checking to ensure there wont be any errors.
Input:
Output: True if no errors occured, otherwise false.
*/
bool XpointValidationGenerator::process()
{
    cout << "Parsing: " << inputFilename << endl;

    // Error checking to make sure the file is going to open correctly
    vi_file.open(rawInputFilename);
    if (!vi_file)
    {
        cerr << "Could not open: " << inputFilename << endl;
        return false;
    }
    vi_file.close();

    // Parse file for output crosspoint ID's
    if (!createOutputCrosspointID())
    {
        cerr << "createOutputCrosspointID - failed " << endl;
        return false;
    }

    // Clean up filename so that it doesnt contain the path or the extension of the file
    while(inputFilename.find("/") != std::string::npos)
    {
        if(inputFilename.find("/") == 0)
        {
            inputFilename.erase(0, 1);
            continue;
        }
        inputFilename.erase(0, inputFilename.find("/") + 1);
    }

    inputFilename.erase(inputFilename.find(".v"), 2);
    assert(inputFilename.size() < 256);

    // Initialize these temporary variables
    bool found = false;
    NTV2DeviceID deviceId = DEVICE_ID_NOTFOUND;
    string outname;

    // Loop through entire list of boards because some boards use the same verilog file
    for (unsigned int i=0; i < boardInfoSize; i++)
    {
        // Parse for every board that uses the verilog file that was the command line argument
        if (boardInfo[i].inputFilename == inputFilename)
        {
            vi_file.open(rawInputFilename);
            if (!vi_file)
            {
                cerr << "Could not open: " << inputFilename << endl;
                return false;
            }

            // Set your deviceID so you can prune your routes with the can do function
            deviceId = boardInfo[i].deviceId;
            // Set your output filename so you can make header files with a name related to the device
            outname  = boardInfo[i].outputFilname;
            found = true;

            parse(deviceId);
            writeHeader(outname);

            vi_file.close();
        }
    }
    // Make sure the device type (filename) exists within the predefinied map
    if (!found)
    {
        cerr << "Device not found: " << inputFilename <<endl;
        return false;
    }

    return true;
}

/*
Brief: Removes any sort of white spaces in a string.
Input: String that you want to clean up.
Output: String without ANY form of spaces.
*/
string XpointValidationGenerator::whiteSpace(string buffer)
{
    buffer.erase(remove(buffer.begin(), buffer.end(), ' '), buffer.end());
    buffer.erase(remove(buffer.begin(), buffer.end(), '\t'), buffer.end());
    buffer.erase(remove(buffer.begin(), buffer.end(), '\n'), buffer.end());
    buffer.erase(remove(buffer.begin(), buffer.end(), '\v'), buffer.end());
    buffer.erase(remove(buffer.begin(), buffer.end(), '\f'), buffer.end());
    buffer.erase(remove(buffer.begin(), buffer.end(), '\r'), buffer.end());
    return buffer;
}

/*
Brief: Removes parenthesis within a string.
Input: String that you want to clean up.
Output: String without parenthesis.
*/
string XpointValidationGenerator::removeParenthesis(string buffer)
{
    buffer.erase(remove(buffer.begin(), buffer.end(), '('), buffer.end());
    buffer.erase(remove(buffer.begin(), buffer.end(), ')'), buffer.end());
    return buffer;
}

/*
Brief: This function parses the file passed in and creates a static map
with the key value being the name of the output port in verilog
and the value being the number it is defined as in the verilog file.
Input: Instance of the file to parse.
Output:
*/
bool XpointValidationGenerator::createOutputCrosspointID()
{
    ifstream nameToHex;
    nameToHex.open(inputFilename);

    if (!nameToHex)
    {
        return false;
    }

    string buffer, value, key;
    list<unsigned int> myList;


    while (getline(nameToHex, buffer))
    {
        // Erase all white space and check for a define statement that is not commented
        buffer = whiteSpace(buffer);
        if (buffer.find("//`define") != std::string::npos)
           continue;
        else if (buffer.find("`define") != std::string::npos)
        {
            // Tokenize the define statement to seperate your key and the hex value corresponding to the key
            buffer.erase(buffer.find("`define"),sizeof("`define")-1);
            key =  buffer.substr(0, buffer.find("8'b"));
            value = buffer.substr(buffer.find("8'b"), sizeof("8'bxxxx_xxxx")-1);
            //buffer.erase(buffer.find("8'b"),sizeof("8'bxxxx_xxxx")-1);
            //key = buffer.substr(0, buffer.find("//"));
            //buffer.erase(0,(buffer.find("8'h")+3));
            //value = buffer.substr(0,2);

            // Convert the string representing the hex value to an integer and
            OutputCrosspointID[key] = (NTV2OutputCrosspointID)binaryConversion(value);
        }
    }

    return true;
}

/*
Brief: This function creates a static map that allows you to index
with the parsed string, and convert to the NTV2InputCrosspointID
enumeration value listed in NTV2enums.h. Basically how to convert
from the verilog version of the port to the c++ version of the port.
Input:
Output:
*/
void XpointValidationGenerator::createInputCrosspointID()
{

    /*------------------ANALOG OUT---------------*/
    InputCrosspointID["avid_c_in_r" ] = NTV2_XptAnalogOutInput;
    InputCrosspointID["avid_r_in_r" ] = NTV2_XptAnalogOutInput;

    /*------------------SDI OUT---------------*/
    InputCrosspointID["out1a_c_in_r" ] = NTV2_XptSDIOut1Input;
    InputCrosspointID["out1b_c_in_r" ] = NTV2_XptSDIOut1InputDS2;
    InputCrosspointID["out2a_c_in_r" ] = NTV2_XptSDIOut2Input;
    InputCrosspointID["out2b_c_in_r" ] = NTV2_XptSDIOut2InputDS2;
    InputCrosspointID["out3a_c_in_r" ] = NTV2_XptSDIOut3Input;
    InputCrosspointID["out3b_c_in_r" ] = NTV2_XptSDIOut3InputDS2;
    InputCrosspointID["out4a_c_in_r" ] = NTV2_XptSDIOut4Input;
    InputCrosspointID["out4b_c_in_r" ] = NTV2_XptSDIOut4InputDS2;
    InputCrosspointID["out5a_c_in_r" ] = NTV2_XptSDIOut5Input;
    InputCrosspointID["out5b_c_in_r" ] = NTV2_XptSDIOut5InputDS2;
    InputCrosspointID["out6a_c_in_r" ] = NTV2_XptSDIOut6Input;
    InputCrosspointID["out6b_c_in_r" ] = NTV2_XptSDIOut6InputDS2;
    InputCrosspointID["out7a_c_in_r" ] = NTV2_XptSDIOut7Input;
    InputCrosspointID["out7b_c_in_r" ] = NTV2_XptSDIOut7InputDS2;
    InputCrosspointID["out8a_c_in_r" ] = NTV2_XptSDIOut8Input;
    InputCrosspointID["out8b_c_in_r" ] = NTV2_XptSDIOut8InputDS2;

    /*------------------Frame Buffer---------------*/
    InputCrosspointID["fb1_c_in_r" ] = NTV2_XptFrameBuffer1Input;
    InputCrosspointID["fb1_r_in_r" ] = NTV2_XptFrameBuffer1Input;
    InputCrosspointID["fb1_c2_in_r" ] = NTV2_XptFrameBuffer1BInput;
    InputCrosspointID["fb1_r2_in_r" ] = NTV2_XptFrameBuffer1BInput;
    InputCrosspointID["fb2_c_in_r" ] = NTV2_XptFrameBuffer2Input;
    InputCrosspointID["fb2_r_in_r" ] = NTV2_XptFrameBuffer2Input;
    InputCrosspointID["fb2_c2_in_r" ] = NTV2_XptFrameBuffer2BInput;
    InputCrosspointID["fb2_r2_in_r" ] = NTV2_XptFrameBuffer2BInput;
    InputCrosspointID["fb3_c_in_r" ] = NTV2_XptFrameBuffer3Input;
    InputCrosspointID["fb3_r_in_r" ] = NTV2_XptFrameBuffer3Input;
    InputCrosspointID["fb3_c2_in_r" ] = NTV2_XptFrameBuffer3BInput;
    InputCrosspointID["fb3_r2_in_r" ] = NTV2_XptFrameBuffer3BInput;
    InputCrosspointID["fb4_c_in_r" ] = NTV2_XptFrameBuffer4Input;
    InputCrosspointID["fb4_r_in_r" ] = NTV2_XptFrameBuffer4Input;
    InputCrosspointID["fb4_c2_in_r" ] = NTV2_XptFrameBuffer4BInput;
    InputCrosspointID["fb4_r2_in_r" ] = NTV2_XptFrameBuffer4BInput;
    InputCrosspointID["fb5_c_in_r" ] = NTV2_XptFrameBuffer5Input;
    InputCrosspointID["fb5_r_in_r" ] = NTV2_XptFrameBuffer5Input;
    InputCrosspointID["fb5_c2_in_r" ] = NTV2_XptFrameBuffer5BInput;
    InputCrosspointID["fb5_r2_in_r" ] = NTV2_XptFrameBuffer5BInput;
    InputCrosspointID["fb6_c_in_r" ] = NTV2_XptFrameBuffer6Input;
    InputCrosspointID["fb6_r_in_r" ] = NTV2_XptFrameBuffer6Input;
    InputCrosspointID["fb6_c2_in_r" ] = NTV2_XptFrameBuffer6BInput;
    InputCrosspointID["fb6_r2_in_r" ] = NTV2_XptFrameBuffer6BInput;
    InputCrosspointID["fb7_c_in_r" ] = NTV2_XptFrameBuffer7Input;
    InputCrosspointID["fb7_r_in_r" ] = NTV2_XptFrameBuffer7Input;
    InputCrosspointID["fb7_c2_in_r" ] = NTV2_XptFrameBuffer7BInput;
    InputCrosspointID["fb7_r2_in_r" ] = NTV2_XptFrameBuffer7BInput;
    InputCrosspointID["fb8_c_in_r" ] = NTV2_XptFrameBuffer8Input;
    InputCrosspointID["fb8_r_in_r" ] = NTV2_XptFrameBuffer8Input;
    InputCrosspointID["fb8_c2_in_r" ] = NTV2_XptFrameBuffer8BInput;
    InputCrosspointID["fb8_r2_in_r" ] = NTV2_XptFrameBuffer8BInput;

    /*-------------------Color Space Converter-------------------*/
    InputCrosspointID["csc1_c_in_r" ] = NTV2_XptCSC1VidInput;
    InputCrosspointID["csc1_r_in_r" ] = NTV2_XptCSC1VidInput;
    InputCrosspointID["csc1_k_in_r" ] = NTV2_XptCSC1KeyInput;
    InputCrosspointID["csc2_c_in_r" ] = NTV2_XptCSC2VidInput;
    InputCrosspointID["csc2_r_in_r" ] = NTV2_XptCSC2VidInput;
    InputCrosspointID["csc2_k_in_r" ] = NTV2_XptCSC2KeyInput;
    InputCrosspointID["csc3_c_in_r" ] = NTV2_XptCSC3VidInput;
    InputCrosspointID["csc3_r_in_r" ] = NTV2_XptCSC3VidInput;
    InputCrosspointID["csc3_k_in_r" ] = NTV2_XptCSC3KeyInput;
    InputCrosspointID["csc4_c_in_r" ] = NTV2_XptCSC4VidInput;
    InputCrosspointID["csc4_r_in_r" ] = NTV2_XptCSC4VidInput;
    InputCrosspointID["csc4_k_in_r" ] = NTV2_XptCSC4KeyInput;
    InputCrosspointID["csc5_c_in_r" ] = NTV2_XptCSC5VidInput;
    InputCrosspointID["csc5_r_in_r" ] = NTV2_XptCSC5VidInput;
    InputCrosspointID["csc5_k_in_r" ] = NTV2_XptCSC5KeyInput;
    InputCrosspointID["csc6_c_in_r" ] = NTV2_XptCSC6VidInput;
    InputCrosspointID["csc6_r_in_r" ] = NTV2_XptCSC6VidInput;
    InputCrosspointID["csc6_k_in_r" ] = NTV2_XptCSC6KeyInput;
    InputCrosspointID["csc7_c_in_r" ] = NTV2_XptCSC7VidInput;
    InputCrosspointID["csc7_r_in_r" ] = NTV2_XptCSC7VidInput;
    InputCrosspointID["csc7_k_in_r" ] = NTV2_XptCSC7KeyInput;
    InputCrosspointID["csc8_c_in_r" ] = NTV2_XptCSC8VidInput;
    InputCrosspointID["csc8_r_in_r" ] = NTV2_XptCSC8VidInput;
    InputCrosspointID["csc8_k_in_r" ] = NTV2_XptCSC8KeyInput;

    /*-------------------LUTS-------------------*/
    InputCrosspointID["lut1_r_in_r" ] = NTV2_XptLUT1Input;
    InputCrosspointID["lut2_r_in_r" ] = NTV2_XptLUT2Input;
    InputCrosspointID["lut3_r_in_r" ] = NTV2_XptLUT3Input;
    InputCrosspointID["lut4_r_in_r" ] = NTV2_XptLUT4Input;
    InputCrosspointID["lut5_r_in_r" ] = NTV2_XptLUT5Input;
    InputCrosspointID["lut6_r_in_r" ] = NTV2_XptLUT6Input;
    InputCrosspointID["lut7_r_in_r" ] = NTV2_XptLUT7Input;
    InputCrosspointID["lut8_r_in_r" ] = NTV2_XptLUT8Input;

    /*-------------------4K to 2K INPUT-------------------*/
    InputCrosspointID["conv2a_c_in_r" ] = NTV2_Xpt4KDCQ1Input;
    InputCrosspointID["conv2a_r_in_r" ] = NTV2_Xpt4KDCQ1Input;
    InputCrosspointID["conv2b_c_in_r" ] = NTV2_Xpt4KDCQ2Input;
    InputCrosspointID["conv2b_r_in_r" ] = NTV2_Xpt4KDCQ2Input;
    InputCrosspointID["conv2c_c_in_r" ] = NTV2_Xpt4KDCQ3Input;
    InputCrosspointID["conv2c_r_in_r" ] = NTV2_Xpt4KDCQ3Input;
    InputCrosspointID["conv2d_c_in_r" ] = NTV2_Xpt4KDCQ4Input;
    InputCrosspointID["conv2d_r_in_r" ] = NTV2_Xpt4KDCQ4Input;

    /*--------------------DUAL LINK OUTPUT-------------------*/
    InputCrosspointID["dlo1_r_in_r" ] = NTV2_XptDualLinkOut1Input;
    InputCrosspointID["dlo2_r_in_r" ] = NTV2_XptDualLinkOut2Input;
    InputCrosspointID["dlo3_r_in_r" ] = NTV2_XptDualLinkOut3Input;
    InputCrosspointID["dlo4_r_in_r" ] = NTV2_XptDualLinkOut4Input;
    InputCrosspointID["dlo5_r_in_r" ] = NTV2_XptDualLinkOut5Input;
    InputCrosspointID["dlo6_r_in_r" ] = NTV2_XptDualLinkOut6Input;
    InputCrosspointID["dlo7_r_in_r" ] = NTV2_XptDualLinkOut7Input;
    InputCrosspointID["dlo8_r_in_r" ] = NTV2_XptDualLinkOut8Input;

    InputCrosspointID["comp_c_in_r" ] = NTV2_XptCompressionModInput;
    InputCrosspointID["conv_c_in_r" ] = NTV2_XptConversionModInput;

    /*--------------------MIXERS-------------------*/
    InputCrosspointID["mix1_fgc_in_r" ] = NTV2_XptMixer1FGVidInput;
    InputCrosspointID["mix1_fgk_in_r" ] = NTV2_XptMixer1FGKeyInput;
    InputCrosspointID["mix1_bgc_in_r" ] = NTV2_XptMixer1BGVidInput;
    InputCrosspointID["mix1_bgk_in_r" ] = NTV2_XptMixer1BGKeyInput;
    InputCrosspointID["mix2_fgc_in_r" ] = NTV2_XptMixer2FGVidInput;
    InputCrosspointID["mix2_fgk_in_r" ] = NTV2_XptMixer2FGKeyInput;
    InputCrosspointID["mix2_bgc_in_r" ] = NTV2_XptMixer2BGVidInput;
    InputCrosspointID["mix2_bgk_in_r" ] = NTV2_XptMixer2BGKeyInput;
    InputCrosspointID["mix3_fgc_in_r" ] = NTV2_XptMixer3FGVidInput;
    InputCrosspointID["mix3_fgk_in_r" ] = NTV2_XptMixer3FGKeyInput;
    InputCrosspointID["mix3_bgc_in_r" ] = NTV2_XptMixer3BGVidInput;
    InputCrosspointID["mix3_bgk_in_r" ] = NTV2_XptMixer3BGKeyInput;
    InputCrosspointID["mix4_fgc_in_r" ] = NTV2_XptMixer4FGVidInput;
    InputCrosspointID["mix4_fgk_in_r" ] = NTV2_XptMixer4FGKeyInput;
    InputCrosspointID["mix4_bgc_in_r" ] = NTV2_XptMixer4BGVidInput;
    InputCrosspointID["mix4_bgk_in_r" ] = NTV2_XptMixer4BGKeyInput;

    /*--------------------DUAL LINK Input-------------------*/
    InputCrosspointID["dual_link_in_r_1_stream_c1" ] = NTV2_XptDualLinkIn1Input;
    InputCrosspointID["dual_link_in_r_1_stream_c2" ] = NTV2_XptDualLinkIn1DSInput;
    InputCrosspointID["dual_link_in_r_2_stream_c1" ] = NTV2_XptDualLinkIn2Input;
    InputCrosspointID["dual_link_in_r_2_stream_c2" ] = NTV2_XptDualLinkIn2DSInput;
    InputCrosspointID["dual_link_in_r_3_stream_c1" ] = NTV2_XptDualLinkIn3Input;
    InputCrosspointID["dual_link_in_r_3_stream_c2" ] = NTV2_XptDualLinkIn3DSInput;
    InputCrosspointID["dual_link_in_r_4_stream_c1" ] = NTV2_XptDualLinkIn4Input;
    InputCrosspointID["dual_link_in_r_4_stream_c2" ] = NTV2_XptDualLinkIn4DSInput;
    InputCrosspointID["dual_link_in_r_5_stream_c1" ] = NTV2_XptDualLinkIn5Input;
    InputCrosspointID["dual_link_in_r_5_stream_c2" ] = NTV2_XptDualLinkIn5DSInput;
    InputCrosspointID["dual_link_in_r_6_stream_c1" ] = NTV2_XptDualLinkIn6Input;
    InputCrosspointID["dual_link_in_r_6_stream_c2" ] = NTV2_XptDualLinkIn6DSInput;
    InputCrosspointID["dual_link_in_r_7_stream_c1" ] = NTV2_XptDualLinkIn7Input;
    InputCrosspointID["dual_link_in_r_7_stream_c2" ] = NTV2_XptDualLinkIn7DSInput;
    InputCrosspointID["dual_link_in_r_8_stream_c1" ] = NTV2_XptDualLinkIn8Input;
    InputCrosspointID["dual_link_in_r_8_stream_c2" ] = NTV2_XptDualLinkIn8DSInput;

    /*---------------------QUADRANT RASTER CONVERT---------------------*/
    InputCrosspointID["qrc_c1_in_r" ] = NTV2_XptHDMIOutInput;
    InputCrosspointID["qrc_r1_in_r" ] = NTV2_XptHDMIOutInput;
    InputCrosspointID["qrc_c2_in_r" ] = NTV2_XptHDMIOutQ2Input;
    InputCrosspointID["qrc_r2_in_r" ] = NTV2_XptHDMIOutQ2Input;
    InputCrosspointID["qrc_c3_in_r" ] = NTV2_XptHDMIOutQ3Input;
    InputCrosspointID["qrc_r3_in_r" ] = NTV2_XptHDMIOutQ3Input;
    InputCrosspointID["qrc_c4_in_r" ] = NTV2_XptHDMIOutQ4Input;
    InputCrosspointID["qrc_r4_in_r" ] = NTV2_XptHDMIOutQ4Input;

    /*---------------------MULTIPLEXERS---------------------*/
    InputCrosspointID["mux1_c1_in_r" ] = NTV2_Xpt425Mux1AInput;
    InputCrosspointID["mux1_r1_in_r" ] = NTV2_Xpt425Mux1AInput;
    InputCrosspointID["mux1_c2_in_r" ] = NTV2_Xpt425Mux1BInput;
    InputCrosspointID["mux1_r2_in_r" ] = NTV2_Xpt425Mux1BInput;
    InputCrosspointID["mux2_c1_in_r" ] = NTV2_Xpt425Mux2AInput;
    InputCrosspointID["mux2_r1_in_r" ] = NTV2_Xpt425Mux2AInput;
    InputCrosspointID["mux2_c2_in_r" ] = NTV2_Xpt425Mux2BInput;
    InputCrosspointID["mux2_r2_in_r" ] = NTV2_Xpt425Mux2BInput;
    InputCrosspointID["mux3_c1_in_r" ] = NTV2_Xpt425Mux3AInput;
    InputCrosspointID["mux3_r1_in_r" ] = NTV2_Xpt425Mux3AInput;
    InputCrosspointID["mux3_c2_in_r" ] = NTV2_Xpt425Mux3BInput;
    InputCrosspointID["mux3_r2_in_r" ] = NTV2_Xpt425Mux3BInput;
    InputCrosspointID["mux4_c1_in_r" ] = NTV2_Xpt425Mux4AInput;
    InputCrosspointID["mux4_r1_in_r" ] = NTV2_Xpt425Mux4AInput;
    InputCrosspointID["mux4_c2_in_r" ] = NTV2_Xpt425Mux4BInput;
    InputCrosspointID["mux4_r2_in_r" ] = NTV2_Xpt425Mux4BInput;
}

/*
Brief: This function parses the verilog file, and creates a 2 dimensional
array for all the valid routes between firmware widegets in both the YUV
and RGB colorspaces.
Input:
Output:
*/
void XpointValidationGenerator::parse(NTV2DeviceID deviceId)
{
    string buffer, key, value;
    bool iterate = false;
    bool ignore  = false;

    InputXpt2WidgetID & inputToWidget = CNTV2SignalRouter::gInputXpt2WidgetID;
    OutputXpt2WidgetID & outToWidget  = CNTV2SignalRouter::gOutputXpt2WidgetID;

    NTV2InputCrosspointID xptInId;
    NTV2OutputCrosspointID xptOutId;

    list<unsigned int> myList;

    // Reading the verilog file and parsing the strings
    while (getline(vi_file, buffer))
    {
        if (buffer.find("casex") != std::string::npos)
        {
            buffer = whiteSpace(buffer);
            // Ignore if casex is commented out
            if (buffer.find("//") == std::string::npos)
                    iterate = true;

            while (iterate == true)
            {
                getline(vi_file, buffer, ':');
                buffer = whiteSpace(buffer);

                // If the value is default you have recorded all the possible values (stop iterating)
                if (buffer.find("default") != std::string::npos)
                    iterate = false;

                // If line is commented dont add it to the list
                if (buffer.find("//`") != std::string::npos)
                {
                    ignore = false;
                    getline(vi_file, buffer, ';');
                }
                else
                {
                    ignore = true;
                    value = buffer;
                }

                if(ignore != false && iterate != false)
                {
                    // Get the input crosspoint ID from the verilog file and clean up the string
                    getline(vi_file, buffer, '[');
                    buffer = whiteSpace(buffer);
                    key = buffer;
                    value.erase(remove(value.begin(), value.end(), '`'), value.end());

                    if(key.find("_g") != std::string::npos || key.find("_b") != std::string::npos
                    || key.find("_y") != std::string::npos || key.find("_a") != std::string::npos
                    || key.find("_t") != std::string::npos)
                    {
                        // for C or R value add to vector, ignore all other possible keys
                        iterate = false;
                        ignore = false;
                    }
                    else if(key.find("_f") != std::string::npos && key.find("y_") != std::string::npos)
                    {
                        // Special Case for mixers
                        iterate = false;
                        ignore = false;
                    }
                    else if(key.find("_b") != std::string::npos && key.find("y_") != std::string::npos)
                    {
                        // Another Special Case for mixers
                        iterate = false;
                        ignore = false;
                    }
                    else
                    {
                        // Add the output crosspoint to the list

                        // Error checking to make sure Output Crosspoint ID exists in the map
                        if(OutputCrosspointID.find(value) == OutputCrosspointID.end() )
                            cerr << "Output Crosspoint ID not found: " << value <<endl;

                        // Checking if the output ID has a widget id then add the input to the list
                        xptOutId = OutputCrosspointID[value];
                        if(outToWidget.find(xptOutId) != outToWidget.end() )
                        {
                            // Check if the device can support this widget
                            if(NTV2DeviceCanDoWidget(deviceId, outToWidget[xptOutId]) == true)
                            {
                                myList.push_back(OutputCrosspointID[value]);
                            }
                        }
                    }
                    // Read in until the end of the line and throw away the string
                    getline(vi_file, buffer);
                }
            }

            // Add the list to the map
            if (ignore != false)
            {
                // Error checking to make sure Input Crosspoint ID exists in the map
                if(InputCrosspointID.find(key) == InputCrosspointID.end() )
                    cerr << "Input Crosspoint ID not found: " << key <<endl;

                // Checking if the input ID has a widget id then add the input to the map
                xptInId = InputCrosspointID[key];
                if(inputToWidget.find(xptInId) != inputToWidget.end())
                {
                    if(NTV2DeviceCanDoWidget(deviceId, inputToWidget[xptInId]) == true)
                    {
                        // Add to YCbCr Map if the key contians "_c"
                        if(key.find("_c") != std::string::npos)
                        {
                            parsingMapYCbCr[InputCrosspointID[key]] = myList;
                        }
                        else if(key.find("_f") != std::string::npos || key.find("_b") != std::string::npos)
                        {
                            parsingMapRGB[InputCrosspointID[key]] = myList;
                            parsingMapYCbCr[InputCrosspointID[key]] = myList;
                        }
                        else
                        {
                            parsingMapRGB[InputCrosspointID[key]] = myList;
                        }
                    }
                }
            }

            // Clear the list for next iteration
            myList.clear();
        }
    }

    // Make all valid routes true in the YCbCr matrix
    int numYUVConnections = 0;
    map<unsigned int, list<unsigned int> >::const_iterator iter;
    list<unsigned int>::const_iterator list_iter;
    for (iter = parsingMapYCbCr.begin(); iter != parsingMapYCbCr.end(); iter++)
    {
        for (list_iter = iter->second.begin(); list_iter != iter->second.end(); list_iter++)
        {
            matrixYCbCr[iter->first][(*list_iter)] = true;
            numYUVConnections++;
        }
    }
    cout << "Number of YUV connections: " << numYUVConnections << endl;

    // Make all valid routes true in the RGB matrix
    int numRGBConnections = 0;
    for (iter = parsingMapRGB.begin(); iter != parsingMapRGB.end(); iter++)
    {
        for (list_iter = iter->second.begin(); list_iter != iter->second.end(); list_iter++)
        {
            matrixRGB[iter->first][(*list_iter)] = true;
            numRGBConnections++;
        }
    }
    cout << "Number of RGB connections: " << numRGBConnections << endl;

}

/*
Brief: This function creates a header file for the AJA device that
can be used to see if valid routes between firmmware widgets exist.
Input:
Output:
*/
void XpointValidationGenerator::writeHeader(string outname)
{
    time_t curT;
    time(&curT);

    // Convert the filename to a clean output name for the header file
    string outputFilename = outname;

    // Need the filename to be uppercase for the #define statement
    string headerName;
    for(unsigned int k = 0; k < outputFilename.length(); k++)
    {
        headerName += toupper(outputFilename[k]);
    }

    // Create output header file where the matrices will be initialized
    ofstream matrixfile((outputFilename + ".h"), ios::out);
    matrixfile << "#ifndef __" + headerName + "_H_INCLUDED" << endl;
    matrixfile << "#define __" + headerName  + "_H_INCLUDED" << endl;
    matrixfile << "#include \"ntv2enum2.h\"" << endl;
    matrixfile << "// date created: " << ctime(&curT) << endl;
    matrixfile << "bool " + outputFilename + "MatrixRGB[NTV2_LAST_INPUT_CROSSPOINT][NTV2_LAST_OUTPUT_CROSSPOINT] = {";

    // Iterate through the matrices and print out all the boolean values into the RGB matrix
    for(unsigned int i=0; i < NTV2_LAST_INPUT_CROSSPOINT; i++)
    {
        matrixfile << "{";

        for(unsigned int j=0; j < NTV2_LAST_OUTPUT_CROSSPOINT; j++)
        {
            if(j == 0)
                matrixfile << matrixRGB[i][j];
            else
                matrixfile << ", " << matrixRGB[i][j];
        }

        if(i < NTV2_LAST_OUTPUT_CROSSPOINT)
            matrixfile << "},\n ";
        else
            matrixfile << "}";
    }
    matrixfile << "} \n \n" << endl;

    // Iterate through the matrices and print out all the boolean values into the YCbCr matrix
    matrixfile << "bool " + outputFilename + "MatrixYCbCr[NTV2_LAST_INPUT_CROSSPOINT][NTV2_LAST_OUTPUT_CROSSPOINT] = {";
    for(unsigned int i=0; i < NTV2_LAST_INPUT_CROSSPOINT; i++)
    {
        matrixfile << "{";
        for(unsigned int j=0; j < NTV2_LAST_OUTPUT_CROSSPOINT; j++)
        {
            if(j == 0)
                matrixfile << matrixYCbCr[i][j];
            else
                matrixfile << ", " << matrixYCbCr[i][j];
        }
        if(i < NTV2_LAST_OUTPUT_CROSSPOINT)
            matrixfile << "},\n ";
        else
            matrixfile << "}";
    }
    matrixfile << "}" << endl;
    matrixfile << "#endif" << endl;

    cout << "Created: " << outputFilename << ".h" << endl;
}

int XpointValidationGenerator::binaryConversion(string token)
{
   token.erase(remove(token.begin(), token.end(), '_'), token.end());

   int value = 0;
   for(unsigned int i = 0; i < token.length(); i++)
   {
     if(token[i] == '1')
       value += pow(2, (token.length()-i-1));
   }
  return value;
 }
