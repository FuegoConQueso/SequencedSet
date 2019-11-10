#ifndef SEQUENCED_SET_H
#define SEQUENCED_SET_H
#include <iostream>
#include <fstream>
#include <iostream>
#include <fstream>
#include <string>
#include "InputFileHeader.h"
#include "Block.h"
#include "Record.h"
#include "BlockBuffer.h"
using namespace std;

class SequencedSet{
	private:
		 int blockCapacity;
		 int blockInitialSize;
		int headerSize;

		Record populateRecord(string line);
	public:
		SequencedSet();
		~SequencedSet();
		void create(ifstream& inputFile);
		void populate(ifstream& inputFile);


};

#endif
