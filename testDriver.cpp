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
void FileManagerTest();

int main(int argc, char *argv[])
{
	//ifstream inputFile("us_postal_codes.txt");
	bool createCheck = false;
	bool blockStructTest = false;
	bool fileManagerTest = false;
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
			case 'b':
				{
					blockStructTest = true;
					break;
				}
			case 'f':
	 			{
				 fileManagerTest = true;
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
	if (blockStructTest == true)
		BlockStructureTest();
	if (fileManagerTest) {
		 FileManagerTest();
	}
	cin.get();
	return 0;
}

void InputFileHeaderReadTest(ifstream &inputFile)
{
	InputFileHeader* header1 = new InputFileHeader;	
	SequencedSet seqSet = SequencedSet();
	seqSet.create(inputFile);
	cout << "Header size is: " << header1->getHeaderSize() << endl;
	cout << "Record size is: " << header1->getRecordSize() << endl;
	seqSet.populate(inputFile);

}

void FileManagerTest() {

}

void BlockStructureTest() {
	 /*
	 //set up the record sizes
	 vector<tuple<string, int, Header::FieldType>> fieldInfos = vector<tuple<string, int, Header::FieldType>>();
	 fieldInfos.push_back(make_tuple<string, int, Header::FieldType>("ZIP", 6, Header::FieldType::U_INTEGER));
	 fieldInfos.push_back(make_tuple<string, int, Header::FieldType>("Place", 31, Header::FieldType::TEXT));
	 fieldInfos.push_back(make_tuple<string, int, Header::FieldType>("State", 2, Header::FieldType::TEXT));
	 fieldInfos.push_back(make_tuple<string, int, Header::FieldType>("County", 36, Header::FieldType::TEXT));
	 fieldInfos.push_back(make_tuple<string, int, Header::FieldType>("Latitude", 9, Header::FieldType::FLOAT));
	 fieldInfos.push_back(make_tuple<string, int, Header::FieldType>("Longitude", 10, Header::FieldType::FLOAT));
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
	 */
}
