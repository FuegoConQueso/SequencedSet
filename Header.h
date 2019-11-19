#pragma once
#include <string>
#include <vector>
#include <tuple>
#include "InputFileHeader.h"
using namespace std;

class Header
{

public:
	 //enum
	 enum class FieldType {
		  U_INTEGER,
		  TEXT,
		  FLOAT
	 };

	 //default constructor
	 Header(){;};
	 //constructor
	 Header(string fileName, string name, vector<tuple<string, int, FieldType>> fieldInfo);

	 //block size-related methods
	 int blockSize(); //returns the size of a block (in chars)
	 int blockHeaderSize(); // returns the size of the block header(in chars)
	 
	 //field-related methods
	 string getFieldName(int index); //gets the name of the field at position index
	 int getFieldSize(int index); //gets the size of the field at position index
	 FieldType getFieldType(int index); //gets the FieldType of the field at position index
	 int getNumOfFields(); //returns the number of fields

	 //header field-related methods
	 string getFieldSeparator(); //returns the string that is used as a field separator
	 
	 //FieldType conversion methods
	 FieldType toFieldType(string name); //takes a string and converts it to a FieldType
	 string fieldTypeToString(FieldType); //takes a FieldType and converts it to a string

	 //key related methods
	 FieldType getKeyType(); //returns the type of the primary key field
	 bool isKeyType(FieldType); //returns whether the primary key is of the given FieldType

	 //record size-related methods
	 int getRecordSize(); //returns the size of a single record

	 //file-related methods
	 string getFileName(); //returns the file's name

	 //name-related methods
	 string getName(); //returns the name of the set

	 //padding and unpadding methods
	 string pad(string toPad, int paddedSize); //pads a string toPad (on the right), using padChar, to make it size paddedSize
	 string unpad(string padded); //unpads a string on both left and right, removing padChar

	 //load the input file header
	 void loadInput(InputFileHeader ifh); //loads information from the input file header
private:
	 string name; //name of the sequenced set fill
	 string fileName; //name of the file
	 int bhNextBlockSize; //size of the next block part of the block header in chars
	 int bhRecordCountSize; //size of the block count part of the block header in chars
	 string bhPrefix; //the prefix of the block header (added for readability, and ability to use getline() )
	 string recordPrefix; //the prefix of the record block (added for readability and ability to use getline() )
	 string headerSeperators; //the seperator of each part of the header header (added for readability and ability to use getline() )
	 string hFieldSeperator; //the seperators of the field metadata in the header (added for readability and ability to use getline() )
	 vector<tuple<std::string, int, Record::FieldType>> fieldInfo; //the field info, in form <name, size(in chars), type>, for each field
	 string padChar; //the character used for padding
	 /* int bhNextBlockSize = 6; 
	 int bhRecordCountSize = 3;
	 string headerSeperators = "\n";
	 string hFieldSeperators = "|"; 
	 string bhPrefix = "\n"; 
	 string recordPrefix = "";
	 string padChar = " "; */
};

#include "Header.cpp"
