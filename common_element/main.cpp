#include <map>
#include <iostream>
#include <string>
#include <map>
using namespace std;
int main()
{
  int a [] = {1,2,3,5,6,7,8};
  int b [] = {77,88,11,22,33,55,6,1,1,1,1,1,1,1};
  map<int,int> myMap;
  int key,maxKey;
  int max=0;
  for(int i = 0 ; i < sizeof(a)/sizeof(*a); i++)
  {
    key = a[i];
    for(int j = 0 ; j < sizeof(b)/sizeof(*b); j++)
    {
      if (key == b[j])
      {
        myMap[key] = myMap[key]+1;
      }
      if (myMap[key] >max)
      {
        max = myMap[key];
        maxKey = key;
      }
    }
  }
  cout<<"The most common element is "<<maxKey<<endl;
  return 0 ;
}
