#pragma once
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

class Record
{
public:
	 //constructors
	 Record(); //default constructor
	 Record(vector<string> packedRecord); //creates a block from the string vector provided (post unbuffering)
	 Record(int zipCode, string placeName, string state, string county, float longitude, float latitude); //initializes the record with the given values

	 //methods
	 vector<string> pack(); /*returns a vector of strings that the buffer class can prep for writing. Output is as follows: [zipCode, placeName, state, county, longitude, latitude] */
	 
private:
	 //data members
	 int zipCode;
	 string placeName;
	 string state;
	 string county;
	 float longitude;
	 float latitude;

	 //methods
	 void unpack(vector<string> packedRecord); //loads the unbuffered string vector into the Record
};

