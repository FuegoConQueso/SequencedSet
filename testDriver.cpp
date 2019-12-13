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
	bool loadTest = false;
	bool populateTest = false;
	bool removeTest = false;
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
					break;
				}
			case 'a':
				{
					addTest = true;
					break;
				}

			case 'p':
				{
				populateTest = true;
				break;
				}

			case 'l':
			{
				loadTest = true;
				break;
			}

			case 'r':
			{
				removeTest = true;
				break;
			}

			case 'm':
			{

			}

			default:
				{
					break;
				}
		}
		i++;
	}
	if (i > argc)
	{
			int end2;
			cout << "error: file not provided" << '\n';
			cout << "Please enter any key to terminate ";
			cin >> end2;
			return 0;
	}
	string inputFile(argv[i]);
	SequencedSet* seqMain1;
	if(populateTest && loadTest)
	{
		int end;
		cout << "error: cannot have the populate flag and load flag true at same time" << '\n';
		cout << "Please enter any key to terminate ";
		cin >> end;
		return 0;
	}
	if (!populateTest && !loadTest)
	{
		int end1;
		cout << "error: the populate flag or the load flag must be true" << '\n';
		cout << "Please enter any key to terminate ";
		cin >> end1;
		return 0;
	}
	if (createCheck == true)
	{
		InputFileHeaderReadTest(inputFile);
	}
	if (blockStructTest == true)
		BlockStructureTest();
	if (fileManagerTest) {
		 FileManagerTest();
	}
	if (loadTest)
		seqMain1 = load(inputFile);
	if (populateTest)
		seqMain1 = populate(inputFile);
	if (searchTest)
		searchTestFunction();
	if (addTest)
		addTestFunction();
	if (removeTest)
		remove(seqMain1);
	cin.get();
	return 0;
}

SequencedSet* populate(string inputFile)
{
	SequencedSet* seqPoint;
	seqPoint = new SequencedSet();
	seqPoint->populate(inputFile);
	return seqPoint;
}

SequencedSet* populate(string inputFile, string outputFile)
{
	SequencedSet* seqPoint;
	seqPoint = new SequencedSet();
	seqPoint->populate(inputFile, outputFile);
	return seqPoint;
}

SequencedSet* load(string inputFile)
{
	SequencedSet* seqLoad;
	seqLoad = new SequencedSet();
	seqLoad->load(inputFile);
	return seqLoad;
}

void search(SequencedSet* seqSearch)
{
	string primaryKey;
	cout << "\nSearch test is on.\n";
	cout << "What zip code would you like to search for? > ";
	cin >> primaryKey;
	int blockNum = seqSearch->searchForBlock(primaryKey);
	if (blockNum == -1) {
		cout << "Key not located in any blocks\n";
	}
	else
	{
		cout << primaryKey << " should be located in block " << blockNum << endl;
		int rrn = 0;
		try {
			Record record = seqSearch->searchForRecord(blockNum, primaryKey, rrn);
			cout << endl << "Record:\n" << recordBuffer::pack(record.pack()) << endl;
		}
		catch (RecordNotFoundException * e) {
			cout << "No matching record found in block " + to_string(blockNum) << "; record does not exist." << endl;
		}
	}
}

void addRecord(SequencedSet* seqAddPoint)
{
	Record addRec;
	addRec = seqAddPoint->specifyRecord();
	seqAddPoint->add(addRec);
}

void addMany(SequencedSet* manySeq, int howMany)
{
	int key;
	cout << "Enter a key to insert the duplicates:";
	cin >> key;
	for (int i = 0; i < howMany; i++)
	{

		string keyS = to_string(key + i);
		Record manyRec = Record(vector<string>{keyS, "ManyAddTest", "ST", "County", "10.01", "-10.01"});
		manySeq->add(manyRec);
	}
}

void remove(SequencedSet* seqPoint)
{
	string key;
	cout << "please enter a key:";
	cin >> key;
	seqPoint->deleteRecord(key);
}

void removeMany(SequencedSet* seqPoint, int howMany)
{
	int key;
	cout << "please enter a key:";
	cin >> key;
	for (int i = 0; i < howMany; i++)
	{
		string keyS = to_string(key + i);
		seqPoint->deleteRecord(keyS);
	}

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
	cout << "FileManagerTest" << endl;
	SequencedSet p;
	p.load();
	Header* header = p.sHeader();
	vector<Record> hello;
	int tests = 2;
	hello = p.searchMatches("MN", tests);
	cout << hello.size();
	for (int i = 0; i < hello.size(); i++) {
		for (int j = 0; j < header->getNumOfFields(); j++) {
			cout << hello[i].getField(i) << ' ';
		}
		cout << "\n";
	}

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
	cout << "Loading..." << endl;
	seqSet.load();
	cout << "done." << endl;
	cout << "Multi-insertion test active." << endl;
	cout << "Enter a zipcode to display the corresponding block for insertion: > ";
	string zipToSearch;
	cin >> zipToSearch;
	Block blk = seqSet.getBlockFromFile(seqSet.searchForBlock(zipToSearch));
	for (int i = 0; i < BlockBuffer::pack(&blk).size(); i++)
		cout << BlockBuffer::pack(&blk)[i];
	cout << endl;
	string searchTerm;
	cout << "What record would you like to insert? > ";
	cin >> searchTerm;
	try {
		 int insertPoint = seqSet.searchForInsertion(&blk, searchTerm);
		 cout << "Term can be inserted at position " << insertPoint << endl;
	}
	catch (DuplicateRecordException* e){
		 cout << e->to_string() << endl;
	}
	for (int i = 0; i < 20; i++) {
		 int location =stoi(searchTerm) + i;
		 string locS = to_string(location);
		 Record rec = Record(vector<string>{locS, "Hope" + locS, "IT", "Works", locS, "-" + locS});
		 seqSet.add(rec);
	}

	//Testing delete
	cout << "Deletion test active." << endl;
	cout << "Enter a zipcode to display the corresponding block for deletion: > ";
	string zipToSearch2;
	cin >> zipToSearch2;
	Block blk2 = seqSet.getBlockFromFile(seqSet.searchForBlock(zipToSearch2));
	for (int i = 0; i < BlockBuffer::pack(&blk).size(); i++)
		 cout << BlockBuffer::pack(&blk)[i];
	cout << endl;
	cout << "Enter a record's primary key and the record will be removed. > ";
	string primaryKey;
	cin >> primaryKey;
	seqSet.deleteRecord(primaryKey);

}

