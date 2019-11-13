#pragma once
#include <cstdlib>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

class Record
{
public:
	 //enum
	 enum class FieldType {
		  U_INTEGER,
		  TEXT,
		  FLOAT
	 };

	 //static methods
	 static void setFieldInfo(vector<tuple<string, int, FieldType>> fieldInfo); //sets the info for each field
	 static string getFieldName(int index); //gets the name of the field at position index
	 static int getFieldSize(int index); //gets the size of the field at position index
	 static FieldType getFieldType(int index); //gets the FieldType of the field at position index
	 static int getNumOfFields(); //returns the number of fields
	 static FieldType toFieldType(string name); //takes a string and converts it to a FieldType
	 static string fieldTypeToString(FieldType); //takes a FieldType and converts it to a string
	 static int getRecordSize(); //returns the size of a single Record (in chars)

	 //constructors
	 Record(); //default constructor
	 Record(vector<string> fields); //creates a block from the string vector provided (post unbuffering)

	 //methods
	 vector<string> pack(); /*returns a vector of strings that the buffer class can prep for writing. */
	 
	 
private:
	 //static data members
	 static vector<tuple<string, int, FieldType>> fieldInfo; //the vector of information for each field

	 //data members
	 vector<string> fields; //the vector of fields in this record, stored as strings

	 //methods
};

