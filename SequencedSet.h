#ifndef SEQUENCED_SET_H
#define SEQUENCED_SET_H
#include <iostream>
#include <fstream>
#include <iostream>
#include <fstream>
#include <string>
#include "InputFileHeader.h"
#include "Block.h"
#include "Index.h"
#include "IndexBuffer.h"
#include "Record.h"
#include "BlockBuffer.h"
#include "Header.h"
#include "HeaderBuffer.h"
#include "FileManager.h"
#include "SeqSetExceptions.h"
using namespace std;

class SequencedSet{
	private:
		Index index; //the index of blocks
		Record populateRecord(string line);


		FileManager fileManager;
		static Header* activeHeader;
		static SequencedSet* activeSeqSet;
	public:
		SequencedSet();
		SequencedSet(const SequencedSet& other);
		~SequencedSet();
		void populate(string inputFile, string fileName = "Storage.txt", string indexFileName = "Index.txt");
		void load(string fileName = "Storage.txt", string indexFileName = "Index.txt");
		int searchForBlock(string primaryKey); 
		Record searchForRecord(int rbn, string primaryKey, int& rrn); //Searches a block for a record.
		int searchForInsertion(Block toSearch, string keyToInsert);
		void add(Record rec);
		void deleteRecord(string primaryKey);
		void split(Block blk);
		Block getBlockFromFile(int); //takes output of int searchForBlock
		Record specifyRecord(); // allows user to build record
		Record findMost(vector<Record> vecToSearch, int fieldNumber);
		Record findLeast(vector<Record> vecToSearch, int fieldNumber);
		vector<Record> searchMatches(string toSearch, int fieldNum);

		static void updateHeader(); //called by Header methods to automatically update the header file with each change to the header object
		static Header* sHeader();
		static SequencedSet* SeqSet();

		Header header;
};

#endif