/* strtok example */
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <math.h>
using namespace std;

void  token(string &target,string &key,int &num)
{
  vector<string> tokens;

  char * str = (char*)target.c_str();

  char * pch;

  pch = strtok (str," ");

  string value;

  while (pch != NULL)

  {

      tokens.push_back(pch);

      pch = strtok (NULL, " ");

  }

  for(unsigned int i = 0; i< tokens.size(); i++)
  {
       if(tokens[i].find("`"))
       {
        key = tokens[i+1];
      }
        value = tokens[2];
  }
  value.erase(remove(value.begin(),value.end(),'_'),value.end());
  cout<<value<<endl;
  for(unsigned int i = 0; i<value.length();i++)
  {
    if(value[i]=='1')
    {
      num +=pow(2,(value.length()-i-1));
    }
  }
}
int main ()
{
    string key;
    int num = 0;
    string target="`define IN1A     8'bx000_0001  //  8'h0e";
    token(target,key,num);
    cout<<key<<" "<<num<<endl;
}
