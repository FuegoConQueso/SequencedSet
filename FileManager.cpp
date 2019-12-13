#include "FileManager.h"
#include "SequencedSet.h"

/** Opens a file for input and output and sets the storage and index file names, with the old conetents of the file immediately removed
@param filename: name of storage file
@param indexfilename: name of index file
*/
void FileManager::create(string filename, string indexfilename) 
{
	 filefile.open(filename, ios::in | ios::out | ios::trunc | ios::binary);
	 this->filefilename = filename;
	 this->indexfilename = indexfilename;
}

/** Opens a file for input and output and sets the storage and index file names
@param filename: name of storage file
@param indexfilename: name of index file
*/
void FileManager::open(string filename, string indexfilename)
{
	 filefile.open(filename, ios::in | ios::out | ios::binary); 
	 this->filefilename = filename;
	 this->indexfilename = indexfilename;
}

/** Returns the name of the sequenced set file
*/
fstream& FileManager::getFile()
{
	return filefile;
}

/**Returns the name of the index file
*/
string FileManager::getIndexFileName()
{
	return indexfilename;
}


/** Returns the name of the storage file
*/
string FileManager::getFileFileName()
{
	return filefilename;
}

/** Returns a block with a given block number from the file.
@param blockNumber: the block number of the block to be retrieved from the file
*/
Block FileManager::getBlock(int blockNumber)
{
	 Header* header = SequencedSet::sHeader();
	 string blockG;
	 int bsize;
	 int position = header -> getHeaderSize();
	 bsize = header -> blockSize();
	 char* buf = new char[bsize+1]; //use header->blockSize
	 position += blockNumber * bsize;
	 filefile.seekg(position);
	 filefile.read(buf, bsize);
	 buf[bsize] = '\0';
	 blockG = string(buf);
	 return BlockBuffer::unpack(blockNumber, blockG);
}

/** Write a block in string format at the position dictated by the block number
@param wBlock: the string-formatted block to be written to the file
@param blockNumber: the block number of the block to be written to the file
*/
void FileManager::writeBlock(string wBlock, int blockNumber)
{
	 Header* header = SequencedSet::sHeader();
	 string blockG;
	 int bsize;
	 int position = header -> getHeaderSize();
	 bsize = header -> blockSize();
	 position += blockNumber * bsize;
	 filefile.seekp(position, ios_base::beg);
	 const char* s = wBlock.c_str();
	 filefile.write(s, bsize);
}

void FileManager::createSpace(int blockNumber)
{
	Header* header = SequencedSet::sHeader();
	int bsize;
	int position = header->getHeaderSize();
	bsize = header->blockSize();
	position += blockNumber * bsize;
	filefile.seekg(position, ios_base::beg);
	const char* output = header->pad("", bsize).c_str();
	filefile.write(output, bsize);
}

/**Returns and index object initialized with the contents of the index file
*/
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

/** Writes the contents of an Index object to an index file
@param ind: the Index object whose contents are to be written to the index file.
*/
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

/** Returns the header object obtained by unpacking the header of the main contents file.
*/
Header FileManager::readHeader()
{

	 return HeaderBuffer::unpack(filefile, "Storage.txt");
}

/** Writes the contents of a header object to the file.
*/
void FileManager::writeHeader(Header* header)
{
	 filefile.seekp(0);
	 string packed = HeaderBuffer::pack(*header);
	 filefile.write(packed.c_str(), packed.size());
}

/** Closes the main file
*/
void FileManager::closeFile()
{
	filefile.close();
}
