#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int binaryConversion(string token);

int main(void)
{
  string binaryWord ="8'bx010_1100";
  cout << binaryConversion(binaryWord) << endl;
  return 0;
}

int binaryConversion(string token)
{
  token.erase(remove(token.begin(), token.end(), '_'), token.end());

  int value = 0;
  for(int i = 0; i < token.length(); i++)
  {
    if(token[i] == '1')
      value += pow(2, (token.length()-i-1));
  }
  return value;
}
