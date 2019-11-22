#include "Header.h"
#include "InputFileHeader.h"

using namespace std;

int Header::getRecordSize()
{
	 int size = 0;
	 for (int i = 0; i < fieldInfo.size(); i++) {
		  size += get<1>(fieldInfo[i]);
	 }
	 return size;
}

string Header::getFileName()
{
	 return fileName;
}

string Header::getName()
{
	 return name;
}

string Header::pad(string toPad, int paddedSize)
{
	 for (int c = toPad.size(); c < paddedSize; c++) {
		  toPad.append(" ");
	 }
	 return toPad;
}

string Header::unpad(string padded)
{
	 int erasePos = padded.find_last_not_of(padChar) + 1;
	 int eraseLength = padded.size() - erasePos;
	 padded.erase(erasePos, eraseLength);
	 return padded;
}

string Header::getHFieldSeparator()
{
	 return hFieldSeperator;
}
int Header::getHeaderSize()
{
	 int s = headerSeperators.size();
	 int size = headerSizeSize + s;
	 size += name.size();
	 int fs = hFieldSeperator.size();
	 for (int i = 0; i < getNumOfFields(); i++) {
		  size += s;
		  size += getFieldName(i).size() + fs;
		  size += to_string(getFieldSize(i)).size() + fs;
		  size += fieldTypeToString(getFieldType(i)).size();
	 }
	 return size;
}
string Header::getHeaderSeperator()
{
	 return headerSeperators;
}
int Header::getHeaderSizeSize()
{
	 return headerSizeSize;
}

Header::Header()
{
}

Header::Header(string fileName, string name, vector<tuple<string, int, FieldType>> fieldInfo, SequencedSet* parent, int blockCapacity,
	 int bhNextBlockSize, int bhRecordCountSize, int headerSizeSize, string headerSeperators,
	 string hFieldSeperator, string bhPrefix, string recordPrefix, string padChar)
{
	 this->fileName = fileName;
	 this->name = name;
	 this->fieldInfo = fieldInfo;
	 this->blockCapacity = blockCapacity;
	 this->blockNumSize = bhNextBlockSize;
	 this->bhRecordCountSize = bhRecordCountSize;
	 this->headerSizeSize = headerSizeSize;
	 this->headerSeperators = headerSeperators;
	 this->hFieldSeperator = hFieldSeperator;
	 this->bhPrefix = bhPrefix;
	 this->recordPrefix = recordPrefix;
	 this->padChar = padChar;
	 
}
int Header::blockSize()
{
	 return blockHeaderSize() + (getRecordSize() * getBlockCapacity());
}
int Header::blockHeaderSize()
{
	 return bhPrefix.size() + blockRecordCountSize() + nextBlockSize();
}
int Header::blockRecordCountSize()
{
	 return bhRecordCountSize;
}
int Header::nextBlockSize()
{
	 return blockNumSize;
}
int Header::getBlockCapacity()
{
	 return blockCapacity;
}
string Header::getFieldName(int index)
{
	 return get<0>(fieldInfo[index]);;
}

int Header::getFieldSize(int index)
{
	 return get<1>(fieldInfo[index]);
}

Header::FieldType Header::getFieldType(int index)
{
	 return get<2>(fieldInfo[index]);
}

int Header::getNumOfFields()
{
	 return fieldInfo.size();
}

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

Header::FieldType Header::getKeyType()
{
	 return getFieldType(0);
}

bool Header::isKeyType(FieldType type) {
	 if (type == getKeyType()) {
		  return true;
	 }
	 else {
		  return false;
	 }
}