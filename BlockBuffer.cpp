#include "BlockBuffer.h"
#include "SequencedSet.h"

/** Given a vector of strings containing the records of a block, returns a single string with 
all relevant information.
@param topack: the block to be packed
@param place: an integer which gets the block number of topack
@pre: a block pointer and a place
@post: a string containing the information of the block at block number place
*/
string BlockBuffer::pack(Block* topack, int& place) {
	 {
		  Header* header = SequencedSet::sHeader();

		  string strb = "\n"; //new block starts with a newline
		  //tell the calling function where this block is located
		  place = topack->getBlockNumber();
		  //pad the nextBlock
		  int nextBlock = topack->getBlockNextNumber();
		  strb += header->pad(to_string(nextBlock), header->nextBlockSize());
		  //pad the prevBlock
		  int prevBlock = topack->getPrevBlockNumber();
		  strb += header->pad(to_string(prevBlock), header->nextBlockSize());
		  //pad the recordCount
		  int recordCount = topack->recordCount();
		  strb += header->pad(to_string(recordCount), header->blockRecordCountSize());
		  // fill in the block with the nextblock, count, and records
		  for (int i = 0; i < topack->recordCount(); i++) {
				strb.append(recordBuffer::pack(topack->getRecord(i)));
		  }

		  //add blank records up to capacity
		  for (int i = recordCount; i < header->getBlockCapacity(); i++) {
				strb.append(header->pad("", header->getRecordSize()));
		  }
		  return strb;
	 }
}

/** Packs the input vector of strings with place parameter zero.
@param topack: the block to be packed
@pre: a pointer to a block
@post: a string with the information in the block
*/
string BlockBuffer::pack(Block* topack) {
	 int callback = 0;
	 return pack(topack, callback);
}

/** Returns a block with a given block number and records as defined in a string.
@param blocknum: the block number
@param blocrec1: the records of the block in string format.
@pre: a block number less than the size of the blocks in the sequenced set
@post: a block with records as defined in the string
*/
Block BlockBuffer::unpack(int blockNum, string blocrec1)
{
	 Header* header = SequencedSet::sHeader();
	 vector<Record> records;
	 string holdrec;
	 //position to start reading in the string
	 int startReadPos = 1;
	 //read next block
	 string nextBlockStr = blocrec1.substr(startReadPos, header->nextBlockSize());
	 int nextBlock = stoi(header->unpad(nextBlockStr));
	 startReadPos += header->nextBlockSize();
	 //read prev block
	 string prevBlockStr = blocrec1.substr(startReadPos, header->nextBlockSize());
	 int prevBlock = stoi(header->unpad(prevBlockStr));
	 startReadPos += header->nextBlockSize();
	 //read number of records
	 string recordCountStr = blocrec1.substr(startReadPos, header->blockRecordCountSize());
	 int recordCount = stoi(header->unpad(recordCountStr));
	 startReadPos += header->blockRecordCountSize();
	 //a substring cosisting of one record will be produced from the string containing the block
	 //the substring will then be put into the vector
	 //the read position will then be updated and he substring cleared
	 for (int y = 0; y < recordCount; y++)
	 {
		  holdrec = blocrec1.substr(startReadPos, header->getRecordSize());
		  records.emplace_back(recordBuffer::unpack(holdrec));
		  startReadPos += header->getRecordSize();
		  holdrec.clear();
	 }
	 return Block(blockNum, nextBlock, prevBlock, records);
}

/** Creates an empty block at the avail spot
@param block: a pointer to the block to be placed at the avail list spot
@pre: none
@post: an empty block at the next avail list spot in the storage file
*/
string BlockBuffer::createAvail(Block* block)
{
	 Header* header = SequencedSet::sHeader();
	 block = new Block(block->getBlockNumber(), header->getStartAvail(), -2, vector<Record>());
	 header->setStartAvail(block->getBlockNumber());
	 return BlockBuffer::pack(block);
}
