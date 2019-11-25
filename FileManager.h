#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include "Index.h"
#include "Block.h"
using namespace std;

class SequencedSet;

class FileManager
{
	protected:
		fstream filefile;
		string indexfilename;
	public:
		void create(string filename, string indexfilename);
		fstream& getFile();
		void open(string filname, string indfilname);
		string getIndexFileName();

		Index readIndexFile();
		void writeIndexFile(Index* ind);
		Header readHeader();
		Block getBlock(int blockNumber);
		void writeBlock(string wBlock, int blockNumber);
};
