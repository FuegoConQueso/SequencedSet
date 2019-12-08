//Test driver for SequencedSet
#include <iostream>
#include "InputFileHeader.h"
#include <fstream>
#include <tuple>
#include "SequencedSet.h"
#include "Record.h"
#include "Block.h"

using namespace std;

void InputFileHeaderReadTest(string);
void BlockStructureTest();
void FileManagerTest();
void searchTestFunction();
void addTestFunction();

int main(int argc, char *argv[])
{
	//ifstream inputFile("us_postal_codes.txt");
	bool createCheck = false;
	bool blockStructTest = false;
	bool fileManagerTest = false;
	bool searchTest = false;
	bool addTest = false;
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
			case 's':
				{
					searchTest = true;
				}
			case 'a':
				{
					addTest = true;
				}
			default:
				{
					break;
				}
		}
		i++;
	}
	string inputFile(argv[i]);
	
	if (createCheck == true)
	{
		InputFileHeaderReadTest(inputFile);
	}
	if (blockStructTest == true)
		BlockStructureTest();
	if (fileManagerTest) {
		 FileManagerTest();
	}
	if (searchTest)
		searchTestFunction();
	if (addTest)
		addTestFunction();
	cin.get();
	return 0;
}

void InputFileHeaderReadTest(string inputFile)
{
	SequencedSet seqSet = SequencedSet();
	cout << "populating...\n";
	seqSet.populate(inputFile);
	cout << "done";
	string primaryKey;
	cout << "\nSearch test is on.\n";
	cout << "What zip code would you like to search for? > ";
	cin >> primaryKey;
	int blockNum = seqSet.searchForBlock(primaryKey);
	if (blockNum == -1) {
		 cout << "Key not found\n";
	}
	else
	{
		 cout << primaryKey << " should be located in block " << blockNum << endl;
		 int rrn = 0;
		 Record record = seqSet.searchForRecord(blockNum, primaryKey, rrn);
		 cout << endl << "Record:\n" << recordBuffer::pack(record.pack()) << endl; //code terminates here if block found but record not found within block.
	}

}

void FileManagerTest() {

}

void searchTestFunction()
{
	 SequencedSet seqSet = SequencedSet();
	 cout << "loading...\n";
	 seqSet.load();
	 cout << "done";
	 string primaryKey;
	 cout << "\nSearch test is on.\n";
	 cout << "What zip code would you like to search for? > ";
	 cin >> primaryKey;
	 int blockNum = seqSet.searchForBlock(primaryKey);
	 if (blockNum == -1) {
		  cout << "Key not found\n";
	 }
	 else
	 {
		  cout << primaryKey << " should be located in block " << blockNum << endl;
		  int rrn = -1;
		  Record record = seqSet.searchForRecord(blockNum, primaryKey, rrn);
		  cout << endl << "Record:\n" << recordBuffer::pack(record.pack()) << endl;
	 }

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

void addTestFunction()
{
	SequencedSet seqSet = SequencedSet();
	seqSet.load();
	Block blk = seqSet.getBlockFromFile(455);
	for (int i = 0; i < blk.pack().size(); i++)
		cout << blk.pack()[i];
	string searchTerm;
	cout << "What record would you like to insert into the above block? > ";
	cin >> searchTerm;
	try {
		 int insertPoint = seqSet.searchForInsertion(blk, searchTerm);
		 cout << "Term can be inserted at position " << insertPoint << endl;
	}
	catch (DuplicateException* e){
		 cout << e->to_string() << endl;
	}
	Record rec = seqSet.specifyRecord();
	seqSet.add(rec);
	Record rec2 = seqSet.specifyRecord();
	seqSet.add(rec2);

	//Testing delete
	cout << "Enter a record's primary key and the record will be removed. > ";
	string primaryKey;
	cin >> primaryKey;
	seqSet.deleteRecord(primaryKey);
}

