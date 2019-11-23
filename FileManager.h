#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class SequencedSet;

class FileManager
{
	protected:
		fstream indexfile;
		fstream filefile;
		SequencedSet *ptrSeqSet; //SequencedSet not included
	public:
		void create(string filename, string indexfilename);
		//void open(string filname, indfilname); //string
		fstream getFileIndex();
		string getBlock(int blockNumber);
};
