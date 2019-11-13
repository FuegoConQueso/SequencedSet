#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "InputFileHeader.h"
using namespace std;

InputFileHeader::InputFileHeader()
{
	headerSize = 0;
	recordSize = 0;
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
	cout << inputFile.tellg() << endl;
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
		cout << fieldNames[count] << "|" << fieldTypes[count]<< "|" << fieldSizes[count] << endl;
		count++; 
	}
}
