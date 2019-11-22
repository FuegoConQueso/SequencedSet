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
	string headerSizeString;
	string recordSizeString;
	string s1, s2;
	int num1;
	int num2;
	//inputFile.seekg(27, ios_base::beg);
	for (int i = 0; i < 24; i++)
	{
		inputFile >> dummyChar;
	}
	inputFile >> headerSizeString;
	//inputFile.seekg(10, ios_base::cur);
	for (int i = 0; i < 11; i++)
	{
		inputFile >> dummyChar;
	}
	inputFile >> recordSizeString;
	//inputFile.seekg(36, ios_base::cur);
	for (int i = 0; i < 26; i++)
	{
		inputFile >> dummyChar;
	}
	cout << "Header size string output: " << headerSizeString << endl;
	cout << "Record size string output: " << recordSizeString << endl;
	recordSize = stoi(recordSizeString);
	headerSize = stoi(headerSizeString);
	
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
		cout << fieldNames[count] << "|" << fieldTypes[count]<< "|" << fieldSizes[count] << endl;
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