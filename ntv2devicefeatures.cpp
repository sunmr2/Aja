/**
	@file		ntv2devicefeatures.cpp
	@brief		Implementations of non-auto-generated device capability functions.
	@copyright	(C) 2004-2017 AJA Video Systems, Inc.	Proprietary and confidential information.
	@note		The functions in this module are those that aren't auto-generated by a Python script from CSV
				files that were exported from a spreadsheet. The mechanically-generated functions are placed
				in the 'ntv2devicefeatures.hpp' file that's included below. See the README in 'ntv2projects/sdkgen'
				for more details.
**/

#include "ntv2devicefeatures.h"

//	Most of the device features functions are generated using a Python script from '.csv' files exported from a spreadsheet.
//	The script writes the declarations into 'ntv2devicefeatures.hh', and implementations into 'ntv2devicefeatures.hpp'...
#include "ntv2devicefeatures.hpp"
#include "xpt_c44.h"
#include "xpt_c88.h"
#include "xpt_kona4_ufc.h"
#include "xpt_kona4.h"
#include "xpt_io4k.h"
#include "xpt_io4k_ufc.h"
#include "xpt_kip_4rxtx.h"
#include "xpt_kip_2p2rxtc.h"
#include "xpt_kip_j2k1rxt.h"
#include "xpt_kip_j2k2tx.h"
#include "xpt_kip_2100_4tx.h"
#include "xpt_kip_2100_1rxtx,h"




//	The rest of the non-auto-generated function implementations follow...


bool NTV2DeviceCanDoFormat(NTV2DeviceID		boardID,
						  NTV2FrameRate		inFrameRate,
  			              NTV2FrameGeometry inFrameGeometry,
						  NTV2Standard		inStandard)
{
	switch (boardID)
	{
	case DEVICE_ID_CORVID22:
	case DEVICE_ID_CORVID3G:
	case DEVICE_ID_LHI:
	case DEVICE_ID_KONALHIDVI:
	#if !defined (NTV2_DEPRECATE)
	//case BOARD_ID_LHI_DVI:
	case BOARD_ID_LHI_T:
	#endif	//	!defined (NTV2_DEPRECATE)
		switch (inStandard)
		{
		case NTV2_STANDARD_1080p:
			switch (inFrameRate)
			{
			case NTV2_FRAMERATE_6000:
			case NTV2_FRAMERATE_5994:
			case NTV2_FRAMERATE_5000:
			case NTV2_FRAMERATE_3000:
			case NTV2_FRAMERATE_2997:
			case NTV2_FRAMERATE_2500:
			case NTV2_FRAMERATE_2400:
			case NTV2_FRAMERATE_2398:	
				return (inFrameGeometry == NTV2_FG_1920x1080 || inFrameGeometry == NTV2_FG_1920x1112 ||
						inFrameGeometry == NTV2_FG_2048x1080 || inFrameGeometry == NTV2_FG_2048x1112);
			default:					
				return false;
			}
		case NTV2_STANDARD_1080:
			switch (inFrameRate)
			{
			case NTV2_FRAMERATE_3000:
			case NTV2_FRAMERATE_2997:
			case NTV2_FRAMERATE_2500:
			case NTV2_FRAMERATE_2400:
			case NTV2_FRAMERATE_2398:	
				return (inFrameGeometry == NTV2_FG_1920x1080 || inFrameGeometry == NTV2_FG_1920x1112 ||
						inFrameGeometry == NTV2_FG_2048x1080 || inFrameGeometry == NTV2_FG_2048x1112);
			default:					
				return false;
			}
		case NTV2_STANDARD_720:
			switch (inFrameRate)
			{
			case NTV2_FRAMERATE_6000:
			case NTV2_FRAMERATE_5994:
			case NTV2_FRAMERATE_5000:
			case NTV2_FRAMERATE_2500:
			case NTV2_FRAMERATE_2398:
				return (inFrameGeometry == NTV2_FG_1280x720 || inFrameGeometry == NTV2_FG_1280x740);
			default:
				return false;
			}
		case NTV2_STANDARD_525:
			switch (inFrameRate)
			{
			case NTV2_FRAMERATE_2997:
				return (inFrameGeometry == NTV2_FG_720x486 || inFrameGeometry == NTV2_FG_720x508 || inFrameGeometry == NTV2_FG_720x514);
			default:
				return false;
			}
		case NTV2_STANDARD_625:
			switch (inFrameRate)
			{
			case NTV2_FRAMERATE_2500:
				return (inFrameGeometry == NTV2_FG_720x576 || inFrameGeometry == NTV2_FG_720x598 || inFrameGeometry == NTV2_FG_720x612);
			default:
				return false;
			}
		default:
			return false;
		}
		
	case DEVICE_ID_LHE_PLUS:
		switch (inStandard)
		{
		case NTV2_STANDARD_1080p:
			switch (inFrameRate)
			{
			case NTV2_FRAMERATE_3000:
			case NTV2_FRAMERATE_2997:
			case NTV2_FRAMERATE_2500:
			case NTV2_FRAMERATE_2400:
			case NTV2_FRAMERATE_2398:	
				return (inFrameGeometry == NTV2_FG_1920x1080 || inFrameGeometry == NTV2_FG_1920x1112 ||
						inFrameGeometry == NTV2_FG_2048x1080 || inFrameGeometry == NTV2_FG_2048x1112);
			default:					
				return false;
			}
		case NTV2_STANDARD_1080:
			switch (inFrameRate)
			{
			case NTV2_FRAMERATE_3000:
			case NTV2_FRAMERATE_2997:
			case NTV2_FRAMERATE_2500:
			case NTV2_FRAMERATE_2400:
			case NTV2_FRAMERATE_2398:	
				return (inFrameGeometry == NTV2_FG_1920x1080 || inFrameGeometry == NTV2_FG_1920x1112 ||
						inFrameGeometry == NTV2_FG_2048x1080 || inFrameGeometry == NTV2_FG_2048x1112);
			default:					
				return false;
			}
		case NTV2_STANDARD_720:
			switch (inFrameRate)
			{
			case NTV2_FRAMERATE_6000:
			case NTV2_FRAMERATE_5994:
			case NTV2_FRAMERATE_5000:
				return (inFrameGeometry == NTV2_FG_1280x720 || inFrameGeometry == NTV2_FG_1280x740);
			default:
				return false;
			}
		case NTV2_STANDARD_525:
			switch (inFrameRate)
			{
			case NTV2_FRAMERATE_2997:
				return (inFrameGeometry == NTV2_FG_720x486 || inFrameGeometry == NTV2_FG_720x508 || inFrameGeometry == NTV2_FG_720x514);
			default:
				return false;
			}
		case NTV2_STANDARD_625:
			switch (inFrameRate)
			{
			case NTV2_FRAMERATE_2500:
				return (inFrameGeometry == NTV2_FG_720x576 || inFrameGeometry == NTV2_FG_720x598 || inFrameGeometry == NTV2_FG_720x612);
			default:
				return false;
			}
		default:
			return false;
		}
		
	case DEVICE_ID_IOEXPRESS:
	case DEVICE_ID_CORVID1:
	case DEVICE_ID_TTAP:
		switch (inStandard)
		{
		case NTV2_STANDARD_1080p:
		case NTV2_STANDARD_1080:
			switch (inFrameRate)
			{
			case NTV2_FRAMERATE_3000:
			case NTV2_FRAMERATE_2997:
			case NTV2_FRAMERATE_2500:
			case NTV2_FRAMERATE_2400:
			case NTV2_FRAMERATE_2398:	
				return (inFrameGeometry == NTV2_FG_1920x1080 || inFrameGeometry == NTV2_FG_1920x1112 ||
						inFrameGeometry == NTV2_FG_2048x1080 || inFrameGeometry == NTV2_FG_2048x1112);
			default:					
				return false;
			}
		case NTV2_STANDARD_720:
			switch (inFrameRate)
			{
			case NTV2_FRAMERATE_6000:
			case NTV2_FRAMERATE_5994:
			case NTV2_FRAMERATE_5000:
				return (inFrameGeometry == NTV2_FG_1280x720 || inFrameGeometry == NTV2_FG_1280x740);
			default:
				return false;
			}
		case NTV2_STANDARD_525:
			switch (inFrameRate)
			{
			case NTV2_FRAMERATE_2997:
				return (inFrameGeometry == NTV2_FG_720x486 || inFrameGeometry == NTV2_FG_720x508 || inFrameGeometry == NTV2_FG_720x514);
			default:
				return false;
			}
		case NTV2_STANDARD_625:
			switch (inFrameRate)
			{
			case NTV2_FRAMERATE_2500:
				return (inFrameGeometry == NTV2_FG_720x576 || inFrameGeometry == NTV2_FG_720x598 || inFrameGeometry == NTV2_FG_720x612);
			default:
				return false;
			}
		default:
			return false;
		}

	#if !defined (NTV2_DEPRECATE)
	case BOARD_ID_XENA2:	// defined by what it can't do for now
		switch (inStandard)
		{
		case NTV2_STANDARD_1080p:
			switch (inFrameRate)
			{
			case NTV2_FRAMERATE_6000:	// can't do 1080p60 "a" formats
			case NTV2_FRAMERATE_5994:
			case NTV2_FRAMERATE_5000:
				return false;
			default:					
				return true;
			}
		default:
			return true;
		}
	#endif	//	!defined (NTV2_DEPRECATE)

	case DEVICE_ID_KONA3G:
		switch (inFrameGeometry)
		{
		case NTV2_FG_4x1920x1080:
		case NTV2_FG_4x2048x1080:
			return false;
		default:
			return true;
		}

	case DEVICE_ID_IOXT:
	case DEVICE_ID_IO4KUFC:
	case DEVICE_ID_KONA4UFC:
		switch (inFrameGeometry)
		{
		case NTV2_FG_4x1920x1080:
		case NTV2_FG_4x2048x1080:
		case NTV2_FG_2048x1556:
		case NTV2_FG_2048x1588:
			return false;
		default:
			return true;
		}

	case DEVICE_ID_KONA3GQUAD:
	case DEVICE_ID_CORVID24:
	case DEVICE_ID_IO4K:
	case DEVICE_ID_KONA4:
	case DEVICE_ID_CORVID88:
	case DEVICE_ID_CORVID44:
	case DEVICE_ID_CORVIDHEVC:
	case DEVICE_ID_CORVIDHBR:
	case DEVICE_ID_IO4KPLUS:
	case DEVICE_ID_IO4KIP:
		switch (inStandard)
		{
		case NTV2_STANDARD_525:
			return (inFrameRate != NTV2_FRAMERATE_2398 && inFrameRate != NTV2_FRAMERATE_2400);	// eg NTV2_FORMAT_525_2398 requires conversion which is not available
		case NTV2_STANDARD_720:
			return (inFrameRate != NTV2_FRAMERATE_2398 && inFrameRate != NTV2_FRAMERATE_2500);	// eg NTV2_FORMAT_720p_2398 requires conversion which is not available
		default:
			return true;		// pretty much everything else
		}
		
	case DEVICE_ID_KONAIP_4CH_1SFP:
	case DEVICE_ID_KONAIP_4CH_2SFP:
	case DEVICE_ID_KONAIP_1RX_1TX_1SFP_J2K:
	case DEVICE_ID_KONAIP_2TX_1SFP_J2K:
	case DEVICE_ID_KONAIP_1RX_1TX_2110:
	case DEVICE_ID_KONAIP_4TX_2110:
		switch (inStandard)
		{
		case NTV2_STANDARD_525:
			return (inFrameRate != NTV2_FRAMERATE_2398 && inFrameRate != NTV2_FRAMERATE_2400);	// eg NTV2_FORMAT_525_2398 requires conversion which is not available
		case NTV2_STANDARD_720:
			return (inFrameRate != NTV2_FRAMERATE_2398 && inFrameRate != NTV2_FRAMERATE_2500);	// eg NTV2_FORMAT_720p_2398 requires conversion which is not available
		case NTV2_STANDARD_3840x2160p:
		case NTV2_STANDARD_4096x2160p:
		case NTV2_STANDARD_3840HFR:
		case NTV2_STANDARD_4096HFR:
			return false;		//	No 4K/UHD
		default:
			return true;		// pretty much everything else
		}

	default:
		return false;
	}
}

bool NTV2DeviceCanDo3GOut (NTV2DeviceID boardID, UWord index0)
{
	switch (index0)
	{
	case 0:
		return NTV2DeviceCanDoWidget(boardID, NTV2_Wgt3GSDIOut1);
	case 1:
		return NTV2DeviceCanDoWidget(boardID, NTV2_Wgt3GSDIOut2);
	case 2:
		return NTV2DeviceCanDoWidget(boardID, NTV2_Wgt3GSDIOut3);
	case 3:
		return NTV2DeviceCanDoWidget(boardID, NTV2_Wgt3GSDIOut4);
	case 4:
		return NTV2DeviceCanDoWidget(boardID, NTV2_Wgt3GSDIOut5);
	case 5:
		return NTV2DeviceCanDoWidget(boardID, NTV2_Wgt3GSDIOut6);
	case 6:
		return NTV2DeviceCanDoWidget(boardID, NTV2_Wgt3GSDIOut7);
	case 7:
		return NTV2DeviceCanDoWidget(boardID, NTV2_Wgt3GSDIOut8);
	default:
		return false;
	}
}	//	NTV2DeviceCanDo3GOut

bool NTV2DeviceCanDo12GOut(NTV2DeviceID boardID, UWord index0)
{
	switch (index0)
	{
	case 0:
		return NTV2DeviceCanDoWidget(boardID, NTV2_Wgt12GSDIOut1);
	case 1:
		return NTV2DeviceCanDoWidget(boardID, NTV2_Wgt12GSDIOut2);
	case 2:
		return NTV2DeviceCanDoWidget(boardID, NTV2_Wgt12GSDIOut3);
	case 3:
		return NTV2DeviceCanDoWidget(boardID, NTV2_Wgt12GSDIOut4);
	default:
		return false;
	}
}	//	NTV2DeviceCanDo3GOut


bool NTV2DeviceCanDoLTCEmbeddedN (NTV2DeviceID boardID, UWord index0)
{
	switch (index0)
	{
	case 0:
		return (NTV2DeviceCanDoWidget(boardID, NTV2_Wgt3GSDIIn1) || NTV2DeviceCanDoWidget(boardID, NTV2_WgtSDIIn1) || NTV2DeviceCanDoWidget(boardID, NTV2_Wgt12GSDIIn1));
	case 1:
		return (NTV2DeviceCanDoWidget(boardID, NTV2_Wgt3GSDIIn2) || NTV2DeviceCanDoWidget(boardID, NTV2_WgtSDIIn2) || NTV2DeviceCanDoWidget(boardID, NTV2_Wgt12GSDIIn2));
	case 2:
		return (NTV2DeviceCanDoWidget(boardID, NTV2_Wgt3GSDIIn3) || NTV2DeviceCanDoWidget(boardID, NTV2_Wgt12GSDIIn3));
	case 3:
		return (NTV2DeviceCanDoWidget(boardID, NTV2_Wgt3GSDIIn4) || NTV2DeviceCanDoWidget(boardID, NTV2_Wgt12GSDIIn4));
	case 4:
		return NTV2DeviceCanDoWidget(boardID, NTV2_Wgt3GSDIIn5);
	case 5:
		return NTV2DeviceCanDoWidget(boardID, NTV2_Wgt3GSDIIn6);
	case 6:
		return NTV2DeviceCanDoWidget(boardID, NTV2_Wgt3GSDIIn7);
	case 7:
		return NTV2DeviceCanDoWidget(boardID, NTV2_Wgt3GSDIIn8);
	default:
		return false;
	}
}	//	NTV2DeviceCanDoLTCEmbeddedN


// Overloading not supported by the ANSI C compiler used for Linux drivers.
#if defined(__CPLUSPLUS__) || defined(__cplusplus)
ULWord NTV2DeviceGetFrameBufferSize(NTV2DeviceID boardID)
#else
ULWord NTV2DeviceGetFrameBufferSize_Ex(NTV2DeviceID boardID)
#endif
{
	ULWord frameBufferSize = 0;
	switch (boardID)
	{
	#if !defined (NTV2_DEPRECATE)
	case BOARD_ID_XENA2:
	//case BOARD_ID_LHI_DVI:
	case BOARD_ID_LHI_T:
	#endif	//	!defined (NTV2_DEPRECATE)
	case DEVICE_ID_KONALHIDVI:
	case DEVICE_ID_LHI:
	case DEVICE_ID_IOEXPRESS:
	case DEVICE_ID_CORVID1:
	case DEVICE_ID_CORVID22:
	case DEVICE_ID_CORVID3G:
	case DEVICE_ID_KONA3G:
	case DEVICE_ID_KONA3GQUAD:
	case DEVICE_ID_LHE_PLUS:
	case DEVICE_ID_IOXT:
	case DEVICE_ID_CORVID24:
	case DEVICE_ID_TTAP:
	case DEVICE_ID_IO4K:
	case DEVICE_ID_IO4KUFC:
	case DEVICE_ID_KONA4:
	case DEVICE_ID_KONA4UFC:
	case DEVICE_ID_CORVID88:
	case DEVICE_ID_CORVID44:
    case DEVICE_ID_CORVIDHEVC:
	case DEVICE_ID_KONAIP_4CH_1SFP:
	case DEVICE_ID_KONAIP_4CH_2SFP:
	case DEVICE_ID_KONAIP_1RX_1TX_1SFP_J2K:
	case DEVICE_ID_KONAIP_2TX_1SFP_J2K:
	case DEVICE_ID_CORVIDHBR:
	case DEVICE_ID_KONAIP_1RX_1TX_2110:
	case DEVICE_ID_IO4KPLUS:
	case DEVICE_ID_IO4KIP:
	case DEVICE_ID_KONAIP_4TX_2110:
        frameBufferSize = XENA2_FRAMEBUFFER_SIZE;
		break;
	default:
		frameBufferSize = 0;
		break;
	}
	
	return frameBufferSize;
}


ULWord NTV2DeviceGetFrameBufferSize (NTV2DeviceID boardID, NTV2FrameGeometry inFrameGeometry, NTV2FrameBufferFormat frameFormat)
{
	ULWord multiplier = 1; // default

	switch (boardID)
	{
	// based on FrameGeometry
	#if !defined (NTV2_DEPRECATE)
	case BOARD_ID_XENA2:
	//case BOARD_ID_LHI_DVI:
	case BOARD_ID_LHI_T:
	#endif	//	!defined (NTV2_DEPRECATE)
	case DEVICE_ID_KONALHIDVI:
	case DEVICE_ID_LHI:
	case DEVICE_ID_LHE_PLUS:
	case DEVICE_ID_IOEXPRESS:
	case DEVICE_ID_CORVID1:
	case DEVICE_ID_CORVID22:
	case DEVICE_ID_CORVID3G:
	case DEVICE_ID_IOXT:
	case DEVICE_ID_TTAP:
		switch (inFrameGeometry)
		{
		case NTV2_FG_2048x1080:
		case NTV2_FG_2048x1556:
		case NTV2_FG_2048x1588:
		case NTV2_FG_1920x1112:
		case NTV2_FG_2048x1112:
			multiplier = 2;
			break;
		default:
			break;
		}
		break;
	case DEVICE_ID_KONA3G:
	case DEVICE_ID_KONA3GQUAD:
	case DEVICE_ID_CORVID24:
	case DEVICE_ID_IO4K:
	case DEVICE_ID_IO4KUFC:
	case DEVICE_ID_KONA4:
	case DEVICE_ID_KONA4UFC:
	case DEVICE_ID_CORVID88:
	case DEVICE_ID_CORVID44:
    case DEVICE_ID_CORVIDHEVC:
	case DEVICE_ID_CORVIDHBR:
	case DEVICE_ID_KONAIP_4CH_1SFP:
	case DEVICE_ID_KONAIP_4CH_2SFP:
	case DEVICE_ID_KONAIP_1RX_1TX_1SFP_J2K:
	case DEVICE_ID_KONAIP_2TX_1SFP_J2K:
	case DEVICE_ID_KONAIP_1RX_1TX_2110:
	case DEVICE_ID_IO4KPLUS:
	case DEVICE_ID_IO4KIP:
	case DEVICE_ID_KONAIP_4TX_2110:
        switch (inFrameGeometry)
		{
		case NTV2_FG_4x1920x1080:
			if(frameFormat == NTV2_FBF_48BIT_RGB || frameFormat == NTV2_FBF_10BIT_ARGB)
				multiplier = 8;
			else
				multiplier = 4;
			break;
		case NTV2_FG_1920x1080:
			if(	frameFormat == NTV2_FBF_10BIT_ARGB || 
				frameFormat == NTV2_FBF_16BIT_ARGB ||
				frameFormat == NTV2_FBF_48BIT_RGB)
				multiplier = 2;
			break;
		case NTV2_FG_4x2048x1080:
			switch(frameFormat)
			{
			case NTV2_FBF_48BIT_RGB:
			case NTV2_FBF_10BIT_ARGB:
			case NTV2_FBF_ARGB:
			case NTV2_FBF_RGBA:
			case NTV2_FBF_10BIT_RGB:
			case NTV2_FBF_ABGR:
			case NTV2_FBF_10BIT_DPX:
			case NTV2_FBF_10BIT_DPX_LITTLEENDIAN:
				multiplier = 8;
				break;
			default:
				multiplier = 4;
				break;
			}
			break;
		case NTV2_FG_2048x1080:
		case NTV2_FG_2048x1556:
		case NTV2_FG_2048x1588:
		case NTV2_FG_1920x1112:
		case NTV2_FG_1920x1114:
		case NTV2_FG_2048x1112:
		case NTV2_FG_2048x1114:
			if(frameFormat == NTV2_FBF_16BIT_ARGB)
				multiplier = 4;
			else
				multiplier = 2;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

#if defined(__CPLUSPLUS__) || defined(__cplusplus)
	return (NTV2DeviceGetFrameBufferSize(boardID)* multiplier);
#else
	return (NTV2DeviceGetFrameBufferSize_Ex(boardID)* multiplier);
#endif
}


#if defined(__CPLUSPLUS__) || defined(__cplusplus)
ULWord NTV2DeviceGetNumberFrameBuffers(NTV2DeviceID boardID)
#else
ULWord NTV2DeviceGetNumberFrameBuffers_Ex(NTV2DeviceID boardID)
#endif
{
	switch (boardID)
	{
	case DEVICE_ID_IOEXPRESS:
	case DEVICE_ID_LHE_PLUS:
	case DEVICE_ID_TTAP:
		return 16;
	#if !defined (NTV2_DEPRECATE)
	case BOARD_ID_XENA2:
	//case BOARD_ID_LHI_DVI:
	case BOARD_ID_LHI_T:
	#endif	//	!defined (NTV2_DEPRECATE)
	case DEVICE_ID_KONALHIDVI:
	case DEVICE_ID_LHI:
	case DEVICE_ID_CORVID1:
	case DEVICE_ID_CORVID3G:
		return 32;
	case DEVICE_ID_IOXT:
		return 24;
	case DEVICE_ID_CORVID22:
	case DEVICE_ID_KONA3GQUAD: //Took this from below quad has no ufc but it still reserves 8 buffers for 3D feature.
	case DEVICE_ID_CORVID24:
		return 64;
	case DEVICE_ID_IO4K:
	case DEVICE_ID_IO4KUFC:
	case DEVICE_ID_KONA4:
	case DEVICE_ID_KONA4UFC:
	case DEVICE_ID_CORVID88:
	case DEVICE_ID_CORVID44:
    case DEVICE_ID_CORVIDHEVC:
	case DEVICE_ID_KONAIP_4CH_1SFP:
	case DEVICE_ID_KONAIP_4CH_2SFP:
	case DEVICE_ID_KONAIP_1RX_1TX_1SFP_J2K:
	case DEVICE_ID_KONAIP_2TX_1SFP_J2K:
	case DEVICE_ID_KONAIP_1RX_1TX_2110:
	case DEVICE_ID_IO4KPLUS:
	case DEVICE_ID_IO4KIP:
	case DEVICE_ID_KONAIP_4TX_2110:
        return 111;
	case DEVICE_ID_KONA3G:
		return 56; // ufc uses 8 
	case DEVICE_ID_CORVIDHBR:
		return 56;
	default:
		return 0;
	}
}


ULWord NTV2DeviceGetNumberFrameBuffers (NTV2DeviceID boardID, NTV2FrameGeometry inFrameGeometry, NTV2FrameBufferFormat frameFormat)
{
	ULWord divisor = 1; // default
	switch (boardID)
	{
		// based on FrameGeometry
	#if !defined (NTV2_DEPRECATE)
	case BOARD_ID_XENA2:
	case BOARD_ID_LHI_T:
	#endif	//	!defined (NTV2_DEPRECATE)
	case DEVICE_ID_KONALHIDVI:
	case DEVICE_ID_LHI:
	case DEVICE_ID_LHE_PLUS:
	case DEVICE_ID_IOEXPRESS:
	case DEVICE_ID_CORVID1:
	case DEVICE_ID_CORVID22:
	case DEVICE_ID_CORVID3G:
	case DEVICE_ID_IOXT:
	case DEVICE_ID_TTAP:
		switch (inFrameGeometry)
		{
		case NTV2_FG_2048x1080:
		case NTV2_FG_2048x1556:
		case NTV2_FG_2048x1588:
		case NTV2_FG_1920x1112:
		case NTV2_FG_2048x1112:
			divisor = 2;
			break;
		default:
			break;
		}
		break;
	case DEVICE_ID_KONA3G:
	case DEVICE_ID_KONA3GQUAD:
	case DEVICE_ID_CORVID24:
	case DEVICE_ID_IO4K:
	case DEVICE_ID_IO4KUFC:
	case DEVICE_ID_KONA4:
	case DEVICE_ID_KONA4UFC:
	case DEVICE_ID_CORVID88:
	case DEVICE_ID_CORVID44:
    case DEVICE_ID_CORVIDHEVC:
	case DEVICE_ID_KONAIP_4CH_1SFP:
	case DEVICE_ID_KONAIP_4CH_2SFP:
	case DEVICE_ID_KONAIP_1RX_1TX_1SFP_J2K:
	case DEVICE_ID_KONAIP_2TX_1SFP_J2K:
	case DEVICE_ID_CORVIDHBR:
	case DEVICE_ID_KONAIP_1RX_1TX_2110:
	case DEVICE_ID_IO4KPLUS:
	case DEVICE_ID_IO4KIP:
	case DEVICE_ID_KONAIP_4TX_2110:
        switch (inFrameGeometry)
		{
		case NTV2_FG_4x1920x1080:
		case NTV2_FG_1920x1080:
			if(frameFormat == NTV2_FBF_10BIT_ARGB || frameFormat == NTV2_FBF_16BIT_ARGB
				|| frameFormat == NTV2_FBF_48BIT_RGB)
				divisor = 2;
			break;
		case NTV2_FG_4x2048x1080:
		case NTV2_FG_2048x1080:
		case NTV2_FG_2048x1556:
		case NTV2_FG_2048x1588:
		case NTV2_FG_1920x1112:
		case NTV2_FG_1920x1114:
		case NTV2_FG_2048x1112:
		case NTV2_FG_2048x1114:
			if(frameFormat == NTV2_FBF_16BIT_ARGB)
				divisor = 4;
			else
				divisor = 2;
			break;
		default:
			break;
		}
		if(inFrameGeometry == NTV2_FG_4x1920x1080 || inFrameGeometry == NTV2_FG_4x2048x1080)
			divisor *= 4;
		break;
	default:
		break;
	}

	if ( frameFormat == NTV2_FBF_48BIT_RGB )
	{
		divisor *= 2;
	}

#if defined(__CPLUSPLUS__) || defined(__cplusplus)
	return (NTV2DeviceGetNumberFrameBuffers(boardID)/divisor);
#else
	return (NTV2DeviceGetNumberFrameBuffers_Ex(boardID)/divisor);
#endif
}


#if defined(__CPLUSPLUS__) || defined(__cplusplus)
ULWord NTV2DeviceGetAudioFrameBuffer(NTV2DeviceID boardID)
#else
ULWord NTV2DeviceGetAudioFrameBuffer_Ex(NTV2DeviceID boardID)
#endif
{
#if defined(__CPLUSPLUS__) || defined(__cplusplus)

	return (NTV2DeviceGetNumberFrameBuffers(boardID) - NTV2DeviceGetNumAudioSystems(boardID));		// audio base is 2 MB buffer at top - 2MB (16 - 1 for 2 MB buffers)

#else		// #if defined(__CPLUSPLUS__) || defined(__cplusplus)

	return (NTV2DeviceGetNumberFrameBuffers_Ex(boardID) - NTV2DeviceGetNumAudioSystems(boardID));		// audio base is 2 MB buffer at top - 2MB (16 - 1 for 2 MB buffers)

#endif		// #if defined(__CPLUSPLUS__) || defined(__cplusplus)
}


#if defined(__CPLUSPLUS__) || defined(__cplusplus)
ULWord NTV2DeviceGetAudioFrameBuffer2(NTV2DeviceID boardID)
#else
ULWord NTV2DeviceGetAudioFrameBuffer2_Ex(NTV2DeviceID boardID)
#endif
{
#if defined(__CPLUSPLUS__) || defined(__cplusplus)
	return (NTV2DeviceGetNumberFrameBuffers(boardID)-2);

#else		// #if defined(__CPLUSPLUS__) || defined(__cplusplus)
	return (NTV2DeviceGetNumberFrameBuffers_Ex(boardID)-2);

#endif		// #if defined(__CPLUSPLUS__) || defined(__cplusplus)
}


ULWord NTV2DeviceGetAudioFrameBuffer (NTV2DeviceID boardID, NTV2FrameGeometry inFrameGeometry, NTV2FrameBufferFormat frameFormat)
{
	return (NTV2DeviceGetNumberFrameBuffers (boardID, inFrameGeometry, frameFormat) - 1);	// audio base is 2 MB buffer at top  -2MB (16-1 for 2MB buffers)
}


ULWord NTV2DeviceGetAudioFrameBuffer2 (NTV2DeviceID boardID, NTV2FrameGeometry inFrameGeometry, NTV2FrameBufferFormat frameFormat)
{
	return (NTV2DeviceGetNumberFrameBuffers (boardID, inFrameGeometry, frameFormat) - 2);
}


AJAExport bool NTV2DeviceGetVideoFormatFromState (	NTV2VideoFormat *		pOutValue,
													const NTV2FrameRate		inFrameRate,
													const NTV2FrameGeometry	inFrameGeometry,
													const NTV2Standard		inStandard,
													const ULWord			inIsSMPTE372Enabled)
{
	return NTV2DeviceGetVideoFormatFromState_Ex (pOutValue, inFrameRate, inFrameGeometry, inStandard, inIsSMPTE372Enabled, false);
}


bool NTV2DeviceGetVideoFormatFromState_Ex(	NTV2VideoFormat *		pOutValue,
											const NTV2FrameRate		inFrameRate,
											const NTV2FrameGeometry	inFrameGeometry,
											const NTV2Standard		inStandard,
											const ULWord			inIsSMPTE372Enabled,
											const bool				inIsProgressivePicture)
{
	if (!pOutValue)
		return false;

	*pOutValue = NTV2_FORMAT_UNKNOWN;

	switch (inStandard)
	{
	case NTV2_STANDARD_1080:
		switch (inFrameRate)
		{
		case NTV2_FRAMERATE_3000:
			if (inIsSMPTE372Enabled)
			{
				if (inFrameGeometry == NTV2_FG_2048x1080)
					*pOutValue = NTV2_FORMAT_1080p_2K_6000_B;
				else
					*pOutValue = NTV2_FORMAT_1080p_6000_B;
			}
			else if (inFrameGeometry == NTV2_FG_4x1920x1080)
				*pOutValue = NTV2_FORMAT_4x1920x1080psf_3000;
			else if (inFrameGeometry == NTV2_FG_4x2048x1080)
				*pOutValue = NTV2_FORMAT_4x2048x1080psf_3000;
			else
				*pOutValue = inIsProgressivePicture ? NTV2_FORMAT_1080psf_3000_2 : NTV2_FORMAT_1080i_6000;
			break;
		case NTV2_FRAMERATE_2997:
			if (inIsSMPTE372Enabled)
			{
				if (inFrameGeometry == NTV2_FG_2048x1080)
					*pOutValue = NTV2_FORMAT_1080p_2K_5994_B;
				else
					*pOutValue = NTV2_FORMAT_1080p_5994_B;
			}
			else if (inFrameGeometry == NTV2_FG_4x1920x1080)
				*pOutValue = NTV2_FORMAT_4x1920x1080psf_2997;
			else if (inFrameGeometry == NTV2_FG_4x2048x1080)
				*pOutValue = NTV2_FORMAT_4x2048x1080psf_2997;
			else
				*pOutValue = inIsProgressivePicture ? NTV2_FORMAT_1080psf_2997_2: NTV2_FORMAT_1080i_5994;
			break;
		case NTV2_FRAMERATE_2500:
			if (inIsSMPTE372Enabled)
			{
				if (inFrameGeometry == NTV2_FG_2048x1080)
					*pOutValue = NTV2_FORMAT_1080p_2K_5000_B;
				else
					*pOutValue = NTV2_FORMAT_1080p_5000_B;
			}
			else if (inFrameGeometry == NTV2_FG_2048x1080 || inFrameGeometry == NTV2_FG_2048x1112 || inFrameGeometry == NTV2_FG_2048x1114)
				*pOutValue = NTV2_FORMAT_1080psf_2K_2500;
			else if (inFrameGeometry == NTV2_FG_4x1920x1080)
				*pOutValue = NTV2_FORMAT_4x1920x1080psf_2500;
			else if (inFrameGeometry == NTV2_FG_4x2048x1080)
				*pOutValue = NTV2_FORMAT_4x2048x1080psf_2500;
			else
				*pOutValue = inIsProgressivePicture ? NTV2_FORMAT_1080psf_2500_2 : NTV2_FORMAT_1080i_5000;
			break;
		case NTV2_FRAMERATE_2400:
			if (inIsSMPTE372Enabled)
				*pOutValue = NTV2_FORMAT_1080p_2K_4800_B;
			else if ( inFrameGeometry == NTV2_FG_2048x1080 || inFrameGeometry == NTV2_FG_2048x1112 || inFrameGeometry == NTV2_FG_2048x1114)
				*pOutValue = NTV2_FORMAT_1080psf_2K_2400;
			else if (inFrameGeometry == NTV2_FG_4x1920x1080)
				*pOutValue = NTV2_FORMAT_4x1920x1080psf_2400;
			else if (inFrameGeometry == NTV2_FG_4x2048x1080)
				*pOutValue = NTV2_FORMAT_4x2048x1080psf_2400;
			else
				*pOutValue = NTV2_FORMAT_1080psf_2400;
			break;
		case NTV2_FRAMERATE_2398:
			if (inIsSMPTE372Enabled)
				*pOutValue = NTV2_FORMAT_1080p_2K_4795_B;
			else if ( inFrameGeometry == NTV2_FG_2048x1080 || inFrameGeometry == NTV2_FG_2048x1112 || inFrameGeometry == NTV2_FG_2048x1114)
				*pOutValue = NTV2_FORMAT_1080psf_2K_2398;
			else if (inFrameGeometry == NTV2_FG_4x1920x1080)
				*pOutValue = NTV2_FORMAT_4x1920x1080psf_2398;
			else if (inFrameGeometry == NTV2_FG_4x2048x1080)
				*pOutValue = NTV2_FORMAT_4x2048x1080psf_2398;
			else
				*pOutValue = NTV2_FORMAT_1080psf_2398;
			break;
		default:
			return false;
		}
		break;
		
	case NTV2_STANDARD_1080p:
		switch (inFrameRate)
		{
		case NTV2_FRAMERATE_3000:
			if ( inFrameGeometry == NTV2_FG_2048x1080 || inFrameGeometry == NTV2_FG_2048x1112 || inFrameGeometry == NTV2_FG_2048x1114)
				*pOutValue = NTV2_FORMAT_1080p_2K_3000;
			else if (inFrameGeometry == NTV2_FG_4x1920x1080)
				*pOutValue = NTV2_FORMAT_4x1920x1080p_3000;
			else if (inFrameGeometry == NTV2_FG_4x2048x1080)
				*pOutValue = NTV2_FORMAT_4x2048x1080p_3000;
			else
				*pOutValue = NTV2_FORMAT_1080p_3000;
			break;
		case NTV2_FRAMERATE_2997:
			if ( inFrameGeometry == NTV2_FG_2048x1080 || inFrameGeometry == NTV2_FG_2048x1112 || inFrameGeometry == NTV2_FG_2048x1114)
				*pOutValue = NTV2_FORMAT_1080p_2K_2997;
			else if (inFrameGeometry == NTV2_FG_4x1920x1080)
				*pOutValue = NTV2_FORMAT_4x1920x1080p_2997;
			else if (inFrameGeometry == NTV2_FG_4x2048x1080)
				*pOutValue = NTV2_FORMAT_4x2048x1080p_2997;
			else
				*pOutValue = NTV2_FORMAT_1080p_2997;
			break;
		case NTV2_FRAMERATE_2500:
			if ( inFrameGeometry == NTV2_FG_2048x1080 || inFrameGeometry == NTV2_FG_2048x1112 || inFrameGeometry == NTV2_FG_2048x1114)
				*pOutValue = NTV2_FORMAT_1080p_2K_2500;
			else if (inFrameGeometry == NTV2_FG_4x1920x1080)
				*pOutValue = NTV2_FORMAT_4x1920x1080p_2500;
			else if (inFrameGeometry == NTV2_FG_4x2048x1080)
				*pOutValue = NTV2_FORMAT_4x2048x1080p_2500;
			else
				*pOutValue = NTV2_FORMAT_1080p_2500;
			break;
		case NTV2_FRAMERATE_2400:
			if ( inFrameGeometry == NTV2_FG_2048x1080 || inFrameGeometry == NTV2_FG_2048x1112 || inFrameGeometry == NTV2_FG_2048x1114)
				*pOutValue = NTV2_FORMAT_1080p_2K_2400;
			else if (inFrameGeometry == NTV2_FG_4x1920x1080)
				*pOutValue = NTV2_FORMAT_4x1920x1080p_2400;
			else if (inFrameGeometry == NTV2_FG_4x2048x1080)
				*pOutValue = NTV2_FORMAT_4x2048x1080p_2400;
			else
				*pOutValue = NTV2_FORMAT_1080p_2400;
			break;
		case NTV2_FRAMERATE_2398:
			if ( inFrameGeometry == NTV2_FG_2048x1080 || inFrameGeometry == NTV2_FG_2048x1112 || inFrameGeometry == NTV2_FG_2048x1114)
				*pOutValue = NTV2_FORMAT_1080p_2K_2398;
			else if (inFrameGeometry == NTV2_FG_4x1920x1080)
				*pOutValue = NTV2_FORMAT_4x1920x1080p_2398;
			else if (inFrameGeometry == NTV2_FG_4x2048x1080)
				*pOutValue = NTV2_FORMAT_4x2048x1080p_2398;
			else
				*pOutValue = NTV2_FORMAT_1080p_2398;
			break;
		case NTV2_FRAMERATE_4795:
			if ( inFrameGeometry == NTV2_FG_4x2048x1080 )
				*pOutValue = NTV2_FORMAT_4x2048x1080p_4795;
			else
				*pOutValue = NTV2_FORMAT_1080p_2K_4795;
			break;
		case NTV2_FRAMERATE_4800:
			if ( inFrameGeometry == NTV2_FG_4x2048x1080 )
				*pOutValue = NTV2_FORMAT_4x2048x1080p_4800;
			else
				*pOutValue = NTV2_FORMAT_1080p_2K_4800;
			break;
		case NTV2_FRAMERATE_5000:
			if ( inFrameGeometry == NTV2_FG_4x1920x1080 )
				*pOutValue = NTV2_FORMAT_4x1920x1080p_5000;
			else if ( inFrameGeometry == NTV2_FG_4x2048x1080 )
				*pOutValue = NTV2_FORMAT_4x2048x1080p_5000;
			else if ( inFrameGeometry == NTV2_FG_2048x1080 || inFrameGeometry == NTV2_FG_2048x1112 || inFrameGeometry == NTV2_FG_2048x1114)
				*pOutValue = NTV2_FORMAT_1080p_2K_5000;
			else
				*pOutValue = NTV2_FORMAT_1080p_5000_A;
			break;
		case NTV2_FRAMERATE_5994:
			if ( inFrameGeometry == NTV2_FG_4x1920x1080 )
				*pOutValue = NTV2_FORMAT_4x1920x1080p_5994;
			else if ( inFrameGeometry == NTV2_FG_4x2048x1080 )
				*pOutValue = NTV2_FORMAT_4x2048x1080p_5994;
			else if ( inFrameGeometry == NTV2_FG_2048x1080 || inFrameGeometry == NTV2_FG_2048x1112 || inFrameGeometry == NTV2_FG_2048x1114)
				*pOutValue = NTV2_FORMAT_1080p_2K_5994;
			else
				*pOutValue = NTV2_FORMAT_1080p_5994_A;
			break;
		case NTV2_FRAMERATE_6000:
			if ( inFrameGeometry == NTV2_FG_4x1920x1080 )
				*pOutValue = NTV2_FORMAT_4x1920x1080p_6000;
			else if ( inFrameGeometry == NTV2_FG_4x2048x1080 )
				*pOutValue = NTV2_FORMAT_4x2048x1080p_6000;
			else if ( inFrameGeometry == NTV2_FG_2048x1080 || inFrameGeometry == NTV2_FG_2048x1112 || inFrameGeometry == NTV2_FG_2048x1114)
				*pOutValue = NTV2_FORMAT_1080p_2K_6000;
			else
				*pOutValue = NTV2_FORMAT_1080p_6000_A;
			break;
		case NTV2_FRAMERATE_11988:
			if ( inFrameGeometry == NTV2_FG_4x2048x1080 )
				*pOutValue = NTV2_FORMAT_4x2048x1080p_11988;
			break;
		case NTV2_FRAMERATE_12000:
			if ( inFrameGeometry == NTV2_FG_4x2048x1080 )
				*pOutValue = NTV2_FORMAT_4x2048x1080p_12000;
			break;
		default:
			return false;
		}
		break;
		
	case NTV2_STANDARD_720:
		switch (inFrameRate)
		{
		case NTV2_FRAMERATE_6000:
			*pOutValue = NTV2_FORMAT_720p_6000;
			break;
		case NTV2_FRAMERATE_5994:
			*pOutValue = NTV2_FORMAT_720p_5994;
			break;
		case NTV2_FRAMERATE_5000:
			*pOutValue = NTV2_FORMAT_720p_5000;
			break;
		case NTV2_FRAMERATE_2500:
			*pOutValue = NTV2_FORMAT_720p_2500;
			break;            
		case NTV2_FRAMERATE_2398:
			*pOutValue = NTV2_FORMAT_720p_2398;
			break;
		default:
			return false;
		}
		break;
		
	case NTV2_STANDARD_525:
		switch (inFrameRate)
		{
		case NTV2_FRAMERATE_2997:
			*pOutValue = inIsProgressivePicture ? NTV2_FORMAT_525psf_2997 : NTV2_FORMAT_525_5994;
			break;
		case NTV2_FRAMERATE_2400:
			*pOutValue = NTV2_FORMAT_525_2400;
			break;
		case NTV2_FRAMERATE_2398:
			*pOutValue = NTV2_FORMAT_525_2398;
			break;

		default:
			return false;
		}
		break;
		
	case NTV2_STANDARD_625:
		*pOutValue = inIsProgressivePicture ? NTV2_FORMAT_625psf_2500 : NTV2_FORMAT_625_5000;
		break;
	case NTV2_STANDARD_2K:
		switch (inFrameRate)
		{
		case NTV2_FRAMERATE_1498:
			*pOutValue = NTV2_FORMAT_2K_1498;
			break;
		case NTV2_FRAMERATE_1500:
			*pOutValue = NTV2_FORMAT_2K_1500;
			break;
		case NTV2_FRAMERATE_2398:
			*pOutValue = NTV2_FORMAT_2K_2398;
			break;
		case NTV2_FRAMERATE_2400:
			*pOutValue = NTV2_FORMAT_2K_2400;
			break;
		case NTV2_FRAMERATE_2500:
			*pOutValue = NTV2_FORMAT_2K_2500;
			break;

		default:
			return false;
		}
		break;

	default: 
		return false;
	}

	return true;
}


bool NTV2DeviceCanConnect (const NTV2DeviceID inDeviceID, const NTV2InputCrosspointID inInputXpt, const NTV2OutputCrosspointID inOutputXpt)
{
	//	FUTURE:	THIS MAY BE IMPLEMENTED IN A SEPARATE .hpp FILE GENERATED BY A SCRIPT THAT PARSES
	//			THE SAME CROSSPOINT .csv TABLE THAT ALSO GENERATES THE CROSSPOINT CONNECTION VERILOG SOURCE
	(void) inDeviceID;
	(void) inInputXpt;
	(void) inOutputXpt;
    switch(inDeviceID)
    {
        case DEVICE_ID_CORVID44:
            return xpt_c44MatrixYCbCr[inInputXpt][inOutputXpt];
            break;
        case DEVICE_ID_CORVID88:
            return xpt_c88MatrixYCbCr[inInputXpt][inOutputXpt];
            break;
        default:
            return false;

    }
}


#define	MAX_OF(__a__,__b__)		((__a__) > (__b__) ? (__a__) : (__b__))

bool NTV2DeviceCanDoTCIndex (const NTV2DeviceID inDeviceID, const NTV2TCIndex inTCIndex)
{
	UWord	maxNumLTCs	= MAX_OF(NTV2DeviceGetNumLTCInputs(inDeviceID), NTV2DeviceGetNumLTCOutputs(inDeviceID));
	UWord	maxNumSDIs	= MAX_OF(NTV2DeviceGetNumVideoInputs(inDeviceID), NTV2DeviceGetNumVideoOutputs(inDeviceID));

	if (NTV2_IS_ATC_VITC2_TIMECODE_INDEX(inTCIndex)  &&  !NTV2DeviceCanDoVITC2(inDeviceID))
		return false;	//	Can't do VITC2

	switch (inTCIndex)
	{
		case NTV2_TCINDEX_DEFAULT:		return true;	//	All devices support this index

		case NTV2_TCINDEX_LTC1:			return maxNumLTCs > 0;
		case NTV2_TCINDEX_LTC2:			return maxNumLTCs > 1;

		case NTV2_TCINDEX_SDI1:
		case NTV2_TCINDEX_SDI1_LTC:
		case NTV2_TCINDEX_SDI1_2:		return maxNumSDIs > 0;

		case NTV2_TCINDEX_SDI2:
		case NTV2_TCINDEX_SDI2_LTC:
		case NTV2_TCINDEX_SDI2_2:		return maxNumSDIs > 1;

		case NTV2_TCINDEX_SDI3:
		case NTV2_TCINDEX_SDI3_LTC:
		case NTV2_TCINDEX_SDI3_2:		return maxNumSDIs > 2;

		case NTV2_TCINDEX_SDI4:
		case NTV2_TCINDEX_SDI4_LTC:
		case NTV2_TCINDEX_SDI4_2:		return maxNumSDIs > 3;

		case NTV2_TCINDEX_SDI5:
		case NTV2_TCINDEX_SDI5_LTC:
		case NTV2_TCINDEX_SDI5_2:		return maxNumSDIs > 4;

		case NTV2_TCINDEX_SDI6:
		case NTV2_TCINDEX_SDI6_LTC:
		case NTV2_TCINDEX_SDI6_2:
		case NTV2_TCINDEX_SDI7:
		case NTV2_TCINDEX_SDI7_LTC:
		case NTV2_TCINDEX_SDI7_2:
		case NTV2_TCINDEX_SDI8:
		case NTV2_TCINDEX_SDI8_LTC:
		case NTV2_TCINDEX_SDI8_2:		return maxNumSDIs > 5;

		default:						break;
	}
	return false;
}


bool NTV2DeviceCanDoLTCInN (NTV2DeviceID boardID, UWord index0)
{
	return index0 < NTV2DeviceGetNumLTCInputs (boardID);

}	//	NTV2DeviceCanDoLTCInN


bool NTV2DeviceCanDoLTCOutN(NTV2DeviceID boardID, UWord index0)
{
	return index0 < NTV2DeviceGetNumLTCOutputs (boardID);
}	//	NTV2DeviceCanDoLTCOutN


bool NTV2DeviceCanDoAudioN (NTV2DeviceID boardID, UWord index0)
{
	return index0 < NTV2DeviceGetNumAudioSystems (boardID);

}	//	NTV2DeviceCanDoAudioN

UWord NTV2DeviceGetNumAudioStreams (NTV2DeviceID boardID)
{
	return NTV2DeviceGetNumAudioSystems (boardID);
}

bool NTV2DeviceCanDoRS422N (const NTV2DeviceID inDeviceID, const NTV2Channel inChannel)
{
	return inChannel < NTV2DeviceGetNumSerialPorts (inDeviceID);
}

NTV2AudioSystem NTV2DeviceGetAudioMixerSystem(const NTV2DeviceID inDeviceID)
{
	if (inDeviceID == DEVICE_ID_IO4KPLUS  ||  inDeviceID == DEVICE_ID_IO4K)
		return NTV2AudioSystem(NTV2DeviceGetNumAudioSystems(inDeviceID) + 1);
	return NTV2_AUDIOSYSTEM_INVALID;
}

#if !defined (NTV2_DEPRECATE)
	bool NTV2DeviceCanDoProAudio(NTV2DeviceID boardID)
	{
		(void) boardID;
		return false;
	}

	bool NTV2DeviceCanDoUARTN (NTV2DeviceID boardID, UWord index0)
	{
		return NTV2DeviceCanDoRS422N (boardID, (NTV2Channel) index0);
	}

	bool NTV2BoardCanDoProcAmp(NTV2DeviceID boardID)
	{
		(void) boardID;
		return false;
	}

	bool NTV2BoardCanDoBrightnessAdjustment(NTV2DeviceID boardID, NTV2LSVideoADCMode videoADCMode)
	{
		(void) boardID;
		(void) videoADCMode;
		return false;
	}

	bool NTV2BoardCanDoContrastAdjustment(NTV2DeviceID boardID, NTV2LSVideoADCMode videoADCMode)
	{
		(void) boardID;
		(void) videoADCMode;
		return false;
	}

	bool NTV2BoardCanDoSaturationAdjustment(NTV2DeviceID boardID, NTV2LSVideoADCMode videoADCMode)
	{
		(void) boardID;
		(void) videoADCMode;
		return false;
	}

	bool NTV2BoardCanDoHueAdjustment(NTV2DeviceID boardID, NTV2LSVideoADCMode videoADCMode)
	{
		(void) boardID;
		(void) videoADCMode;
		return false;
	}

	bool NTV2BoardCanDoAudio		(NTV2DeviceID boardID)		{	return NTV2DeviceCanDoAudioN		(boardID, 0);	}
	bool NTV2BoardCanDoAudio2		(NTV2DeviceID boardID)		{	return NTV2DeviceCanDoAudioN		(boardID, 1);	}
	bool NTV2BoardCanDoAudio3		(NTV2DeviceID boardID)		{	return NTV2DeviceCanDoAudioN		(boardID, 2);	}
	bool NTV2BoardCanDoAudio4		(NTV2DeviceID boardID)		{	return NTV2DeviceCanDoAudioN		(boardID, 3);	}
	bool NTV2BoardCanDoAudio5		(NTV2DeviceID boardID)		{	return NTV2DeviceCanDoAudioN		(boardID, 4);	}
	bool NTV2BoardCanDoAudio6		(NTV2DeviceID boardID)		{	return NTV2DeviceCanDoAudioN		(boardID, 5);	}
	bool NTV2BoardCanDoAudio7		(NTV2DeviceID boardID)		{	return NTV2DeviceCanDoAudioN		(boardID, 6);	}
	bool NTV2BoardCanDoAudio8		(NTV2DeviceID boardID)		{	return NTV2DeviceCanDoAudioN		(boardID, 7);	}
	bool NTV2BoardCanDoMixer2		(NTV2DeviceID boardID)		{	return NTV2DeviceGetNumMixers		(boardID) >= 2;	}
	bool NTV2BoardCanDoMixer3		(NTV2DeviceID boardID)		{	return NTV2DeviceGetNumMixers		(boardID) >= 3;	}
	bool NTV2BoardCanDoMixer4		(NTV2DeviceID boardID)		{	return NTV2DeviceGetNumMixers		(boardID) >= 4;	}
	bool NTV2BoardCanDoUART			(NTV2DeviceID boardID)		{	return NTV2DeviceCanDoUARTN			(boardID, 0);	}
	bool NTV2BoardCanDoUART2		(NTV2DeviceID boardID)		{	return NTV2DeviceCanDoUARTN			(boardID, 1);	}
	bool NTV2BoardCanDoLTCEmbedded	(NTV2DeviceID boardID)		{	return NTV2DeviceCanDoLTCEmbeddedN	(boardID, 0);	}
	bool NTV2BoardCanDoLTCEmbedded2	(NTV2DeviceID boardID)		{	return NTV2DeviceCanDoLTCEmbeddedN	(boardID, 1);	}
	bool NTV2BoardCanDoLTCEmbedded3	(NTV2DeviceID boardID)		{	return NTV2DeviceCanDoLTCEmbeddedN	(boardID, 2);	}
	bool NTV2BoardCanDoLTCEmbedded4	(NTV2DeviceID boardID)		{	return NTV2DeviceCanDoLTCEmbeddedN	(boardID, 3);	}
	bool NTV2BoardCanDoLTCEmbedded5	(NTV2DeviceID boardID)		{	return NTV2DeviceCanDoLTCEmbeddedN	(boardID, 4);	}
	bool NTV2BoardCanDoLTCEmbedded6	(NTV2DeviceID boardID)		{	return NTV2DeviceCanDoLTCEmbeddedN	(boardID, 5);	}
	bool NTV2BoardCanDoLTCEmbedded7	(NTV2DeviceID boardID)		{	return NTV2DeviceCanDoLTCEmbeddedN	(boardID, 6);	}
	bool NTV2BoardCanDoLTCEmbedded8	(NTV2DeviceID boardID)		{	return NTV2DeviceCanDoLTCEmbeddedN	(boardID, 7);	}
	bool NTV2BoardCanDo3G			(NTV2DeviceID boardID)		{	return NTV2DeviceCanDo3GOut			(boardID, 0);	}
	bool NTV2BoardCanDo3GOut2		(NTV2DeviceID boardID)		{	return NTV2DeviceCanDo3GOut			(boardID, 1);	}
	bool NTV2BoardCanDo3GOut3		(NTV2DeviceID boardID)		{	return NTV2DeviceCanDo3GOut			(boardID, 2);	}
	bool NTV2BoardCanDo3GOut4		(NTV2DeviceID boardID)		{	return NTV2DeviceCanDo3GOut			(boardID, 3);	}
	bool NTV2BoardCanDo3GOut5		(NTV2DeviceID boardID)		{	return NTV2DeviceCanDo3GOut			(boardID, 4);	}
	bool NTV2BoardCanDo3GOut6		(NTV2DeviceID boardID)		{	return NTV2DeviceCanDo3GOut			(boardID, 5);	}
	bool NTV2BoardCanDo3GOut7		(NTV2DeviceID boardID)		{	return NTV2DeviceCanDo3GOut			(boardID, 6);	}
	bool NTV2BoardCanDo3GOut8		(NTV2DeviceID boardID)		{	return NTV2DeviceCanDo3GOut			(boardID, 7);	}
	bool NTV2BoardCanDoLTCIn		(NTV2DeviceID boardID)		{	return NTV2DeviceCanDoLTCInN		(boardID, 0);	}
	bool NTV2BoardCanDoLTCIn2		(NTV2DeviceID boardID)		{	return NTV2DeviceCanDoLTCInN		(boardID, 1);	}
	bool NTV2BoardCanDoLTCOut		(NTV2DeviceID boardID)		{	return NTV2DeviceCanDoLTCOutN		(boardID, 0);	}
	bool NTV2BoardCanDoLTCOut2		(NTV2DeviceID boardID)		{	return NTV2DeviceCanDoLTCOutN		(boardID, 1);	}
#endif	//	NTV2_DEPRECATE
