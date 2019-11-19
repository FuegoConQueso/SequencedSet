#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class FileManager
{
	protected:
		fstream indexfile;
		fstream filefile;
		SequencedSet *ptrSeqSet;
	public:
		void create(string filename, string indexfilename);
		void open(string filname, indfilname);
		fstream getFileIndex();
		string getBlock(int blockNumber);
};

void FileManager::create(string filename, string indexfilename);
{
	filefile.open(filename, ios::in | ios::app | ios::trunc);
	indexfile.open(indexfilename, ios::in | ios::app | ios::trunc);
}

void FileManager::open(string filname, string indfilname)
{
	filefile.open(filename, ios::in | ios::trunc);
	indexfile.open(indexfilename, ios::in | ios::trunc);
}

fstream FileManager:: getFileIndex();
{
	
}

//I used an array is an intermediate step as I am unsure if i can use the write function with a string.
string FileManager::getBlock(int blockNumber)
{
	string blockG;
	int position = headersize;
	char * buf = new char[blocksize];
	position += blockNumber * blocksize;
	filefile.seekp(position, ios_base::beg);
	filefile.write(buf, blocksize);
	for(int i = 0; i < blocksize; i++)
		blockG += buf[i];
	return blockG;
}
