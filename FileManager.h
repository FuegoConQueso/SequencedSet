#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include "Index.h"
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
		Block getBlock(int blockNumber);
		void writeBlock(string wBlock, int blockNumber);
};
