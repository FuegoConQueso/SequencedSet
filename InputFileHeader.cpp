#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

InputFileHeader::InputFileHeader()
{
	headerSize = 0;
	recordSize = 0;
}


void InputFileHeader::readHeader(ifstream &inputFile){
	string headerSizeString;
	string recordSizeString;
	string s1, s2;
	int num1, num2;
	inputFile.seekg(27, ios_base::beg);
	inputFile >> headerSizeString;
	headerSize = stoi(headerSizeString);
	inputFile.seekg(13, ios_base::cur);
	inputFile >> recordSizeString;
	recordSize = stoi(recordSizeString);
	inputFile.seekg(41, ios_base::cur);
	
	//While loop for reading ANY subsequent fields
	char dummyChar;
	int count = 0;
	while(inputFile >> dummyChar && inputFile.tellg() <= headerSize)
	{
		inputFile.seekg(-1, ios_base::cur);	
		inputFile >> s1;
		fieldNames.push_back(s1);
		inputFile.seekg(2, ios_base::cur);
		inputFile >> num1;
		inputFile.seekg(1, ios_base::cur);
		inputFile >> num2;
		inputFile.seekg(2, ios_base::cur);
		inputFile >> s2;
		fieldTypes.push_back(s2);
		fieldSizes.push_back(num2-num1+1);
		cout << fieldNames[count] << "|" << fieldTypes[count]<< "|" << fieldSizes[count] << endl;
		count++; 
	}
}
