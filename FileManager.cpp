#include "FileManager.h"
#include "SequencedSet.h"
/*
void FileManager::create(string filename, string indexfilename); //remove semicolon
{
	 filefile.open(filename, ios::in | ios::app | ios::trunc); //ios::out not ios::app
	 indexfile.open(indexfilename, ios::in | ios::app | ios::trunc); //ios::out not ios::app
}

void FileManager::open(string filname, string indfilname)
{
	 filefile.open(filename, ios::in | ios::trunc); //different var name (filename vs filname) //don't truncate //add ios::out
	 indexfile.open(indexfilename, ios::in | ios::trunc); //different var name (indexfilename vs indfilname) //don't truncate //add ios::out
}

fstream FileManager::getFileIndex(); //change name to getIndexFile for clarity // remove semicolon
{

}

//I used an array is an intermediate step as I am unsure if i can use the write function with a string.
string FileManager::getBlock(int blockNumber)
{
	 Header* header = SequencedSet::sHeader();
	 string blockG;
	 int position = headersize; //use header->getHeaderSize
	 char* buf = new char[blocksize]; //use header->blockSize
	 position += blockNumber * blocksize;
	 filefile.seekp(position, ios_base::beg);
	 filefile.write(buf, blocksize);
	 for (int i = 0; i < blocksize; i++)
		  blockG += buf[i];
	 return blockG;
}*/
