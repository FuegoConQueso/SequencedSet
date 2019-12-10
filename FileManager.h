#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include "Index.h"
#include <sstream>
#include "Block.h"
using namespace std;

class SequencedSet;

class FileManager
{
	protected:
		fstream filefile;
		string filefilename;
		string indexfilename;
	public:
		void create(string filename, string indexfilename);
		fstream& getFile();
		void open(string filname, string indfilname);
		void closeFile();
		string getIndexFileName();
		string getFileFileName();

		Index readIndexFile();
		void writeIndexFile(Index* ind);
		Header readHeader();
		void writeHeader(Header* header);
		Block getBlock(int blockNumber);
		void writeBlock(string wBlock, int blockNumber);
		void createSpace(int blockNumber);
};
