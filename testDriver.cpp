//Test driver for SequencedSet
#include <iostream>
#include "InputFileHeader.h"
#include <fstream>
using namespace std;

void InputFileHeaderReadTest(ifstream&);

int main(int argc, char *argv[])
{
	//ifstream inputFile("us_postal_codes.txt");
	bool createCheck;
	int i = 1;
	while((i < argc) && (argv[i][0] == '-'))
	{
		char c = argv[i][1];
		switch(c)
		{
			case 'c':
				{
					createCheck = true;
					break;
				}
			default:
				{
					break;
				}
		}
		i++;
	}
	ifstream inputFile(argv[i]);
	
	if (createCheck == true)
	{
		InputFileHeaderReadTest(inputFile);
	}
	return 0;
}

void InputFileHeaderReadTest(ifstream &inputFile)
{
	InputFileHeader header1;	
	header1.readHeader(inputFile);
	cout << "Header size is: " << header1.getHeaderSize() << endl;
	cout << "Record size is: " << header1.getRecordSize() << endl;

}
