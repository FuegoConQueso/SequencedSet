#include "Header.h"
#include "InputFileHeader.h"
#include "HeaderBuffer.h"
#include "SequencedSet.h"

using namespace std;

/** Returns the record size by summing the sizes of the individual fields of the record
*/
int Header::getRecordSize()
{
	 int size = 0;
	 for (int i = 0; i < fieldInfo.size(); i++) {
		  size += get<1>(fieldInfo[i]);
	 }
	 return size;
}

/** returns the file name in the header
*/
string Header::getFileName()
{
	 return fileName;
}

/** Returns the name of the sequenced set
*/
string Header::getName()
{
	 return name;
}

/** Pads an input string with white space to a given size
@param toPad: string to be padded
@param paddedeSize: size the string is to be padded out to using white space
*/
string Header::pad(string toPad, int paddedSize)
{
	 int padLength = paddedSize - toPad.size();
	 string pad = string(padLength, ' ');
	 toPad.append(pad);
	 return toPad;
}

/** Takes a padded string and removes extra white space
@param padded: string for which the extra white space is to be removed
*/
string Header::unpad(string padded)
{
	 int erasePos = padded.find_last_not_of(padChar) + 1;
	 int eraseLength = padded.size() - erasePos;
	 padded.erase(erasePos, eraseLength);
	 return padded;
}

/** Compares two strings according to the FieldType object that the strings represent
@param a, b: The strings to be compared
@param f: The fieldtype that the strings represent (integer, float, or string).
*/
int Header::compare(string a, string b, FieldType f)
{
	switch (f) 
	{
	case FieldType::U_INTEGER:
	{
		if (stoi(a) < stoi(b))
			return -1;
		else if (stoi(a) > stoi(b))
			return 1;
		else
			return 0;
		break;
	}
	case FieldType::FLOAT:
	{	
		if (stof(a) < stof(b))
			return -1;
		else if (stof(a) > stof(b))
			return 1;
		else
			return 0;
		break;
	}
	case FieldType::TEXT:
	{
		if (a.compare(b) < 0)
			return -1;
		else if (a.compare(b) > 0)
			return 1;
		else
			return 0;
		break;
	}
	default:
	{
		break;
	}
	}

	return 0;
}

/** Returns the header's field separator string
*/
string Header::getHFieldSeparator()
{
	 return hFieldSeperator;
}

/** Returns the size of the header by packing the header into a string and reading it's size
*/
int Header::getHeaderSize()
{
	 int size = HeaderBuffer::pack(*this).size();
	 return size;
}

/** returns the header separator string
*/
string Header::getHeaderSeperator()
{
	 return headerSeperators;
}

/**Returns the size of the header size
*/
int Header::getHeaderSizeSize()
{
	 return headerSizeSize;
}

/** Returns the starting block number in the header
*/
int Header::getStartBlock()
{
	 return startBlock;
}

/** Returns the block number at the start of the avail list
*/
int Header::getStartAvail()
{
	 return startAvail;
}

/** Sets the start block number to a given index parameter and updates the header of the sequenced set (rewriting header to file)
@param index: the value that the start block number is to be set to
*/
void Header::setStartBlock(int index, bool updateFile)
{
	 startBlock = index;
	 if (updateFile) {
		  SequencedSet::updateHeader();
	 }
}

/** Sets the start of the avail list to a given block number and updates the header of the sequenced set (rewriting header to file)
@param index: the value that the avail list start number is to be set to.
*/
void Header::setStartAvail(int index, bool updateFile)
{
	 startAvail = index;
	 if (updateFile) {
		  SequencedSet::updateHeader();
	 }
}

Header::Header()
{
}

Header::Header(string fileName, string name, vector<tuple<string, int, FieldType>> fieldInfo, int startBlockIndex,
	 int startAvailIndex, int blockCapacity, int blockMinSize, int bhNextBlockSize, int bhRecordCountSize, int headerSizeSize,
	 string headerSeperators, string hFieldSeperator, string bhPrefix, string recordPrefix, string padChar)
{
	 this->fileName = fileName;
	 this->name = name; 
	 this->fieldInfo = fieldInfo;
	 this->startBlock = startBlockIndex;
	 this->startAvail = startAvailIndex;
	 this->blockCapacity = blockCapacity;
	 this->blockMinSize = blockMinSize;
	 this->blockNumSize = bhNextBlockSize;
	 this->bhRecordCountSize = bhRecordCountSize;
	 this->headerSizeSize = headerSizeSize;
	 this->headerSeperators = headerSeperators;
	 this->hFieldSeperator = hFieldSeperator;
	 this->bhPrefix = bhPrefix;
	 this->recordPrefix = recordPrefix;
	 this->padChar = padChar;
	 this->indexName = indexName;
}

/* Returns the block size in bytes by calculating the sum of the block header and product of record size and block capacity
*/
int Header::blockSize()
{
	 return blockHeaderSize() + (getRecordSize() * getBlockCapacity());
}

/** Returns the block header size in bytes by calculating the sum of the block header prefix, block record count size, and next block size
*/
int Header::blockHeaderSize()
{
	 return bhPrefix.size() + blockRecordCountSize() + nextBlockSize();
}

/** Returns the block record count size
*/
int Header::blockRecordCountSize()
{
	 return bhRecordCountSize;
}

/* Returns the next block size in bytes
*/
int Header::nextBlockSize()
{
	 return blockNumSize;
}

/* Returns the block capacity in bytes
*/
int Header::getBlockCapacity()
{
	 return blockCapacity;
}

/** Returns the minimum block size
*/
int Header::getBlockMinSize()
{
	 return blockMinSize;
}

/** Returns the field name of the field at a given index
@param index: the index where the field is located in the record
*/
string Header::getFieldName(int index)
{
	 return get<0>(fieldInfo[index]);;
}

/** Returns the field size of the field at a given index
@param index: the index where the field is located in the record
*/
int Header::getFieldSize(int index)
{
	 return get<1>(fieldInfo[index]);
}

/** Returns the field type of the field at a given index
@param index: the index where the field is located in the record
*/
Header::FieldType Header::getFieldType(int index)
{
	 return get<2>(fieldInfo[index]);
}

/** Returns the number of fields in a record
*/
int Header::getNumOfFields()
{
	 return fieldInfo.size();
}

/** Converts a string to an enumerated object of type FieldType (defined in Header class)
@param name: the string to be converted into a FieldType enumerated class object
*/
Header::FieldType Header::toFieldType(string name)
{
	 if (name == "text") {
		  return FieldType::TEXT;
	 }
	 else if (name == "u_integer") {
		  return FieldType::U_INTEGER;
	 }
	 else if (name == "float") {
		  return FieldType::FLOAT;
	 }
	 else {
		  return FieldType();
	 }
}

/** Converts a FieldType (defined in Header class) object to a string
@param type: the FieldType to be converted to a string
*/
string Header::fieldTypeToString(FieldType type)
{
	 if (type == FieldType::TEXT) {
		  return "text";
	 }
	 else if (type == FieldType::U_INTEGER) {
		  return "u_integer";
	 }
	 else if (type == FieldType::FLOAT) {
		  return "float";
	 }
	 else {
		  return string();
	 }
}

/** Returns the type of the primary key of the records
*/
Header::FieldType Header::getKeyType()
{
	 return getFieldType(0);
}

/** Returns a boolean variable indicated whether an input FieldType is the same as the type of the primary key
@param type: the FieldType to be compared with the primary key's FieldType
*/
bool Header::isKeyType(FieldType type) {
	 if (type == getKeyType()) {
		  return true;
	 }
	 else {
		  return false;
	 }
}