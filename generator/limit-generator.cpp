/*
LimitsGenerator - the part of GenTesc generator.
Copyright (C) 2015 Ivan Yakimov, e-mail: ivan.yakimov.sibfu@yandex.ru

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

# include "limit-generator.hh"
# include <iostream>
using namespace std;

LimitGenerator::LimitGenerator()
{
  
}

void LimitGenerator::Run(int n)
{
  vector<string> grayCode = GenerateGrayArr(n);

  for (vector<string>::iterator s = grayCode.begin();
       s != grayCode.end(); s++)
    {
      for (int j = 0; j < s->length(); j++)
	{
	  if ((*s)[j] == '0')
	    cout << "$min";
	  else
	    cout << "$max";
	  if (j < s->length()-1)
	    cout << ", ";
	}
      cout << " => ?;" << endl;
    }
}

/*
Following code is taken from:
http://www.geeksforgeeks.org/given-a-number-n-generate-bit-patterns-from-0-to-2n-1-so-that-successive-patterns-differ-by-one-bit/
*/
// C++ program to generate n-bit Gray codes
// This function generates all n bit Gray codes and prints the
// generated codes
// modified by: Ivan Yakimov
vector<string> LimitGenerator::GenerateGrayArr(int n)
{
  // base case
  if (n <= 0)
    return vector<string>();
 
  // 'arr' will store all generated codes
  vector<string> arr;
 
  // start with one-bit pattern
  arr.push_back("0");
  arr.push_back("1");
 
  // Every iteration of this loop generates 2*i codes from previously
  // generated i codes.
  int i, j;
  for (i = 2; i < (1<<n); i = i<<1)
    {
      // Enter the prviously generated codes again in arr[] in reverse
      // order. Nor arr[] has double number of codes.
      for (j = i-1 ; j >= 0 ; j--)
	arr.push_back(arr[j]);
 
      // append 0 to the first half
      for (j = 0 ; j < i ; j++)
	arr[j] = "0" + arr[j];
 
      // append 1 to the second half
      for (j = i ; j < 2*i ; j++)
	arr[j] = "1" + arr[j];
    }

  return arr;
}
