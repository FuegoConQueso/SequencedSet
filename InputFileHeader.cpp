#include "InputFileHeader.h"
using namespace std;

InputFileHeader::InputFileHeader()
{
	headerSize = 0;
	recordSize = 0;
	filename = " ";
}

vector<tuple<string, int, Header::FieldType>> InputFileHeader::makeTuples() {
	 vector<tuple<string, int, Header::FieldType>> fieldInfo = vector<tuple<string, int, Header::FieldType>>();
	 for (int i = 0; i < recordFields.size(); i++)
	 {
		  fieldInfo.push_back(make_tuple(getFieldName(i), getFieldSize(i), getFieldType(i)));
	 }
	 return fieldInfo;
}

void InputFileHeader::readHeader(ifstream &inputFile){
	char dummyChar;
	char* buf = new char[128];
	string name;
	string headerSizeString;
	string recordSizeString;
	string s1, s2;
	int num1;
	int num2;
	//get name of SequencedSet
	inputFile.getline(buf, 128);
	name = string(buf);
	//get headersize of SequencedSet
	inputFile.getline(buf, 128);
	headerSizeString = string(buf);
	int pos = headerSizeString.find_first_of(':') + 2;
	headerSizeString = headerSizeString.substr(pos, headerSizeString.size() - pos);
	//get recordSize of SequencedSet
	inputFile.getline(buf, 128);
	recordSizeString = string(buf);
	pos = recordSizeString.find_first_of(':') + 2;
	recordSizeString = recordSizeString.substr(pos, recordSizeString.size() - pos);
	//convert both to ints
	recordSize = stoi(recordSizeString);
	headerSize = stoi(headerSizeString); // should probably catch exception OR make sure only int values are read.
	//throw away extra line
	inputFile.getline(buf, 128);
	//While loop for reading ANY subsequent fields
	int count = 0;
	while(inputFile.tellg() <= headerSize)
	{
		inputFile >> s1;
		fieldNames.push_back(s1);
		//inputFile.seekg(-1, ios_base::cur);
		inputFile >> dummyChar;
		inputFile >> num1;
		inputFile >> dummyChar;
		inputFile >> num2;
		inputFile >> dummyChar;
		inputFile >> s2;
		fieldTypes.push_back(s2);
		fieldSizes.push_back(num2-num1+1);
		tuple<string, int, Header::FieldType> fieldInfo = make_tuple(s1, num2 - num1 + 1, Header::toFieldType(s2));
		recordFields.push_back(fieldInfo);
		count++; 
	}
	//Record::setFieldInfo(recordFields);
}

string InputFileHeader::getFieldName(int i)
{
	return get<0>(recordFields[i]);
}

int InputFileHeader::getFieldSize(int i)
{
	 return fieldSizes[i];
}

Header::FieldType InputFileHeader::getFieldType(int i)
{
	return Header::toFieldType(fieldTypes[i]);
}