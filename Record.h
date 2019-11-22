#pragma once
#include <cstdlib>
#include <string>
#include <vector>
#include <tuple>
#include "Header.h"

using namespace std;

class Record
{
public:
	 //constructors
	 Record(); //default constructor
	 Record(vector<string> fields); //creates a block from the string vector provided (post unbuffering)

	 //methods
	 vector<string> pack(); /*returns a vector of strings that the buffer class can prep for writing. */
	 string getField(int index); //returns the value of a specific field
	 
private:
	 //data members
	 vector<string> fields; //the vector of fields in this record, stored as strings

	 //methods
};

