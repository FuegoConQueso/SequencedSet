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
using namespace std;

class SequencedSet{
	private:
		int blockCapacity; //maximum number of records in a block
		int blockInitialSize; //initial number of records in a block
		int headerSize; //size of the header in characters
		Index index; //the index of blocks

		Record populateRecord(string line);
	public:
		SequencedSet();
		~SequencedSet();
		void create(ifstream& inputFile);
		void populate(ifstream& inputFile);

		Header header;
		Record search(string key);
};

#endif
