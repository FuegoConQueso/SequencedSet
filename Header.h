#pragma once
#include <string>
#include <vector>
#include <tuple>
using namespace std;

class SequencedSet;
class InputFileHeader;

class Header
{

public:
	 //enum
	 enum class FieldType {
		  U_INTEGER,
		  TEXT,
		  FLOAT
	 };

	 //constructor
	 Header();
	 Header(string fileName, string name, vector<tuple<string, int, FieldType>> fieldInfo, int startBlockIndex, int startAvailIndex,
		  int blockCapacity = 4, int blockNumSize = 6, int bhRecordCountSize = 3, int headerSizeSize = 4, string headerSeperators = "\n",
		  string hFieldSeperator = "|", string bhPrefix = "\n", string recordPrefix = "", string padChar = " ");

	 //block size-related methods
	 int blockSize(); //returns the size of a block (in chars)
	 int blockHeaderSize(); // returns the size of the block header(in chars)
	 int blockRecordCountSize(); //returns the size (in chars) of the record count field of the block header
	 int nextBlockSize(); //returns the size (in chars) of the next block pointer in the block header

	 //block-related methods
	 int getBlockCapacity(); //returns the maximum number of records in a block
	 
	 //field-related methods
	 string getFieldName(int index); //gets the name of the field at position index
	 int getFieldSize(int index); //gets the size of the field at position index
	 FieldType getFieldType(int index); //gets the FieldType of the field at position index
	 int getNumOfFields(); //returns the number of fields

	 //header field-related methods
	 string getHFieldSeparator(); //returns the string that is used as a field separator between the header strings

	 //header-related methods
	 int getHeaderSize(); //returns the number of characters in the header
	 string getHeaderSeperator(); //returns the seperator of the header's parts
	 int getHeaderSizeSize(); //returns the size (in chars) of the header's size string
	 int getStartBlock(); //returns the index of the start block
	 int getStartAvail(); //returns the index of the start of the avail list
	 void setStartBlock(int index); //sets the start block index
	 void setStartAvail(int index); //sets the start of the avail list's index
	 
	 //FieldType conversion methods
	 static FieldType toFieldType(string name); //takes a string and converts it to a FieldType
	 static string fieldTypeToString(FieldType type); //takes a FieldType and converts it to a string

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


	 //comparison method
	 static int compare(string a, string b, FieldType f);
private:
	 string name; //name of the sequenced set fill
	 string fileName; //name of the file
	 int startBlock;
	 int startAvail;
	 string indexName;//name of the index file
	 int headerSizeSize; //size (in chars) of the header's size field
	 int blockCapacity; //the maximum number of records in a block
	 int blockNumSize; //size of the next block part of the block header in chars
	 int bhRecordCountSize; //size of the block count part of the block header in chars
	 string bhPrefix; //the prefix of the block header (added for readability, and ability to use getline() )
	 string recordPrefix; //the prefix of the record block (added for readability and ability to use getline() )
	 string headerSeperators; //the seperator of each part of the header header (added for readability and ability to use getline() )
	 string hFieldSeperator; //the seperators of the field metadata in the header (added for readability and ability to use getline() )
	 vector<tuple<std::string, int, Header::FieldType>> fieldInfo; //the field info, in form <name, size(in chars), type>, for each field
	 string padChar; //the character used for padding
	 /* int blockNumSize = 6; 
	 int bhRecordCountSize = 3;
	 string headerSeperators = "\n";
	 string hFieldSeperators = "|"; 
	 string bhPrefix = "\n"; 
	 string recordPrefix = "";
	 string padChar = " "; */
};
