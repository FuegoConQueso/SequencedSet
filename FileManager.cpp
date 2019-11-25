#include "FileManager.h"
#include "SequencedSet.h"

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

fstream& FileManager::getFile()
{
	return filefile;
}

string FileManager::getIndexFileName()
{
	return indexfilename;
}

//I used an array is an intermediate step as I am unsure if i can use the write function with a string.
Block FileManager::getBlock(int blockNumber)
{
	 Header* header = SequencedSet::sHeader();
	 string blockG;
	 int bsize;
	 int position = header -> getHeaderSize();
	 char* buf = new char[header -> blockSize()+1]; //use header->blockSize
	 bsize = header -> blockSize();
	 position += blockNumber * bsize;
	 filefile.seekg(position, ios_base::beg);
	 filefile.read(buf, bsize);
		blockG = string(buf);
	 return BlockBuffer::unpack(blockNumber, blockG);
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
	 char* s = new char(*wBlock.c_str());
	 filefile.write(s, bsize);
}

Index FileManager::readIndexFile()
{
	fstream index1;
	string indexPass;
	index1.open(indexfilename, ios::in);
	index1.seekg(0, index1.end);
	int indexSize = index1.tellg();
	index1.seekg(0, ios::beg);
	char* s = new char[indexSize+1];
	index1.read(s, indexSize);
	indexPass = string(s);
	return Index(indexPass);
}

void FileManager::writeIndexFile(Index* ind)
{
	fstream indexfile;
	string inda;
	inda = ind -> pack();
	indexfile.open(indexfilename, ios::in | ios::out | ios::trunc);
	const char* s = inda.c_str();
	indexfile.write(s, inda.size());
	indexfile.close();
	
}

Header FileManager::readHeader()
{

	 return HeaderBuffer::unpack(filefile, "Storage.txt");
}
