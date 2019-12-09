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
		 cout << "Key not located in any blocks\n";
	}
	else
	{
		 cout << primaryKey << " should be located in block " << blockNum << endl;
		 int rrn = 0;
		 try {
			  Record record = seqSet.searchForRecord(blockNum, primaryKey, rrn);
			  cout << endl << "Record:\n" << recordBuffer::pack(record.pack()) << endl;
		 }
		 catch (RecordNotFoundException * e) {
			  cout << "No matching record found in block " + to_string(blockNum) << "; record does not exist." <<endl;
		 }
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
		  cout << "Key not located in any blocks\n";
	 }
	 else
	 {
		  cout << primaryKey << " should be located in block " << blockNum << endl;
		  int rrn = 0;
		  try {
				Record record = seqSet.searchForRecord(blockNum, primaryKey, rrn);
				cout << endl << "Record:\n" << recordBuffer::pack(record.pack()) << endl;
		  }
		  catch (RecordNotFoundException * e) {
				cout << "No matching record found in block " + to_string(blockNum) << "; record does not exist." << endl;
		  }
	 }

}

void BlockStructureTest() {
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
	catch (DuplicateRecordException* e){
		 cout << e->to_string() << endl;
	}
	for (int i = 0; i < 20; i++) {
		 int location = 400 + i;
		 string locS = to_string(location);
		 Record rec = Record(vector<string>{locS, "Hope" + locS, "IT", "Works", locS, "-" + locS});
		 seqSet.add(rec);
	}

	//Testing delete
	cout << "Enter a record's primary key and the record will be removed. > ";
	string primaryKey;
	cin >> primaryKey;
	seqSet.deleteRecord(primaryKey);
}

