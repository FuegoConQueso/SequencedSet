#include "FileManager.h"
#include "SequencedSet.h"
/*
void FileManager::create(string filename, string indexfilename) 
{
	 filefile.open(filename, ios::in | ios::out | ios::trunc); 
	 this->indexfilename = indexfilename;
}

void FileManager::open(string filename, string indexfilename)
{
	 filefile.open(filename, ios::in | ios::out); 
	 this->indexfilename = indexfilename;
}

fstream FileManager::getFile()
{
	return filefile;
}

fstream FileManager::getIndexFile()
{
	return indexfile;
}

//I used an array is an intermediate step as I am unsure if i can use the write function with a string.
string FileManager::getBlock(int blockNumber)
{
	 Header* header = SequencedSet::sHeader();
	 string blockG;
	 int bsize;
	 int position = header -> getHeaderSize();
	 char* buf = new char[header -> blockSize()]; //use header->blockSize
	 bsize = header -> blockSize();
	 position += blockNumber * bsize;
	 filefile.seekg(position, ios_base::beg);
	 filefile.read(buf, bsize);
		blockG = string(buf);
	 return blockG;
}

void FileManager::writeBlock(string wBlock, int blockNumber)
{
	 Header* header = SequencedSet::sHeader();
	 string blockG;
	 int bsize;
	 int position = header -> getHeaderSize();
	 bsize = header -> blockSize();
	 position += blockNumber * bsize;
	 filefile.seekp(position, ios_base::beg);
	 filefile.write(wBlock, bsize);
}

Index FileManager::readIndexFile()
{
	fstream index1;
	string indexPass;
	index1.open(indexfilename, ios::in);
	index1.seekg(0, index1.end);
	int indexSize = index1.tellg();
	index1.seekg(0, index.beg);
	index1.read(indexPass, indexSize);
	return Index(indexPass);
}

void FileManager::writeIndexFile(Index* ind)
{
	fstream indexfile;
	string inda;
	inda = ind -> pack();
	indexfile.open(indexfilename, ios::in | ios::out | ios::trunc);
	indexfile.write(inda, inda.size());
	indexfile.close();
	
}

*/
