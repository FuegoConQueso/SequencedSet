//Test driver for SequencedSet
#include <iostream>
#include "InputFileHeader.h"
#include <fstream>
#include <tuple>
#include "SequencedSet.h"
#include "Record.h"
#include "Block.h"

using namespace std;

SequencedSet* populate(string);
SequencedSet* populate(string, string);
SequencedSet* load(string);
void search(SequencedSet*);
void addRecord(SequencedSet*);
void remove(SequencedSet*);

/** Test Driver: contains flags for testing the sequenced set
@param argc: the number of string arguments taken at the command prompt
@param argv: A two-dimensional array of the characters in the command arguments
@pre: none
@post: Testing of various aspects of the Sequenced set
*/
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
	SequencedSet* seqMain1 = new SequencedSet;
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
	if (loadTest)
		seqMain1 = load(inputFile);
	if (populateTest)
	{
		if (i <= argc)
		{
			i++;
			string inputFile2(argv[i]);
			seqMain1 = populate(inputFile, inputFile2);
		}
		else
			seqMain1 = populate(inputFile);
	}
	if (searchTest)
		search(seqMain1);
	if (addTest)
		addRecord(seqMain1);
	if (removeTest)
		remove(seqMain1);
	cin.get();
	return 0;
}

/** Tests the populate function with default output file name
@param inputFile: the name of the input file
@pre: none
@post: Returns a sequenced set pointer populated with the input file
*/
SequencedSet* populate(string inputFile)
{
	SequencedSet* seqPoint;
	seqPoint = new SequencedSet();
	seqPoint->populate(inputFile);
	return seqPoint;
}

/** Tests the populate function with specified output file name
@param inputFile: the name of the input file
@pre: none
@post: Returns a sequenced set pointer populated with the input file
*/
SequencedSet* populate(string inputFile, string outputFile)
{
	SequencedSet* seqPoint;
	seqPoint = new SequencedSet();
	seqPoint->populate(inputFile, outputFile);
	return seqPoint;
}

/** Tests the load function of the sequenced set
@param inputFile: the input file the sequenced set is loading
@pre: none
@post: the sequenced set loads the input file and is returned
*/
SequencedSet* load(string inputFile)
{
	SequencedSet* seqLoad;
	seqLoad = new SequencedSet();
	seqLoad->load(inputFile);
	return seqLoad;
}

/** Tests the search functionality of the sequenced set
@param seqSearch: the sequenced set being searched
@pre: none
@post: The user is prompted for a search key, and the key is searched for.
*/
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

/** Tests the ability to add a record to the sequenced set
@param seqAddPoint: the sequenced set to which a record is to be added
@pre: none
@post: A record is added to the sequenced set
*/
void addRecord(SequencedSet* seqAddPoint)
{
	Record addRec;
	addRec = seqAddPoint->specifyRecord();
	seqAddPoint->add(addRec);
}

/** Test the ability to remove a record from the sequenced set
@param seqPoint: the sequenced set from which the point is to be removed
@pre: none
@post: The user is prompted for a key and a record with that key is 
attempted to be removed.
*/
void remove(SequencedSet* seqPoint)
{
	string key;
	cout << "please enter a key:";
	cin >> key;
	seqPoint->deleteRecord(key);
}
