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
using namespace std;

class SequencedSet{
	private:
		Index index; //the index of blocks
		Record populateRecord(string line);

		FileManager fileManager;
		static Header* activeHeader;
	public:
		SequencedSet();
		SequencedSet(const SequencedSet& other);
		~SequencedSet();
		void populate(string inputFile, string fileName = "Storage.txt", string indexFileName = "Index.txt");
		void load(string fileName = "Storage.txt", string indexFileName = "Index.txt");
		int searchForBlock(string primaryKey); 
		Record searchForRecord(int rbn, string primaryKey);
		int searchForInsertion(Block toSearch, string keyToInsert);
		void add(string primaryKey);
		Block getBlockFromFile(int); //takes output of int searchForBlock

		static Header* sHeader();

		Header header;
};

#endif