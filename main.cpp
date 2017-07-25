/* strtok example */
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>
using namespace std;

void  token(string &target,string &key,string &value)
{
  vector<string> tokens;

  char * str = (char*)target.c_str();

  char * pch;

  pch = strtok (str," 8'bx");

  while (pch != NULL)

  {

      tokens.push_back(pch);

      pch = strtok (NULL, " 8'bx");

  }

  for(unsigned int i = 0; i< tokens.size(); i++)
  {
        key = tokens[1];
        value = tokens[2];
  }
  str = (char*)value.c_str();
  pch = strtok (str,"_");
  value = pch;
}
int main ()
{   string key,value;
    string target="`define IN1A     8'bx000_0001  //  8'h0e";
    token(target,key,value);
    cout<<key<<" "<<value<<endl;
}
