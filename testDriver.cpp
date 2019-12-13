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
		search(seqMain1);
	if (addTest)
		addRecord(seqMain1);
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

void remove(SequencedSet* seqPoint)
{
	string key;
	cout << "please enter a key:";
	cin >> key;
	seqPoint->deleteRecord(key);
}
