//Test driver for SequencedSet
#include <iostream>
#include "InputFileHeader.h"
#include <fstream>
#include <tuple>
#include "SequencedSet.h"
#include "Record.h"
#include "Block.h"

using namespace std;

void InputFileHeaderReadTest(ifstream&);
void BlockStructureTest();

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
	BlockStructureTest();
	cin.get();
	return 0;
}

void InputFileHeaderReadTest(ifstream &inputFile)
{
	InputFileHeader header1;	
	header1.readHeader(inputFile);
	cout << "Header size is: " << header1.getHeaderSize() << endl;
	cout << "Record size is: " << header1.getRecordSize() << endl;
	SequencedSet seqSet = SequencedSet();
	seqSet.populate(inputFile);

}

void BlockStructureTest() {

	 //set up the record sizes
	 vector<tuple<string, int, Record::FieldType>> fieldInfos = vector<tuple<string, int, Record::FieldType>>();
	 fieldInfos.push_back(make_tuple<string, int, Record::FieldType>("ZIP", 6, Record::FieldType::U_INTEGER));
	 fieldInfos.push_back(make_tuple<string, int, Record::FieldType>("Place", 31, Record::FieldType::TEXT));
	 fieldInfos.push_back(make_tuple<string, int, Record::FieldType>("State", 2, Record::FieldType::TEXT));
	 fieldInfos.push_back(make_tuple<string, int, Record::FieldType>("County", 36, Record::FieldType::TEXT));
	 fieldInfos.push_back(make_tuple<string, int, Record::FieldType>("Latitude", 9, Record::FieldType::FLOAT));
	 fieldInfos.push_back(make_tuple<string, int, Record::FieldType>("Longitude", 10, Record::FieldType::FLOAT));
	 Record::setFieldInfo(fieldInfos);

	 //create the record buffer, test said buffer
	 vector<string> rec;
	 recordBuffer r0;
	 string rec2;
	 rec.push_back("1001");
	 rec.push_back("Agawam");
	 rec.push_back("NY");
	 rec.push_back("Hampden");
	 rec.push_back("42.0702");
	 rec.push_back("-72.6227");
	 rec2 = r0.pack(rec);
	 cout << rec2;
}