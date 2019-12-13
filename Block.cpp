#include "Block.h"
#include "SequencedSet.h"


Block::Block() {
	 records = vector<Record>();
}

Block::Block(int blockNumber, int nextBlock, int prevBlock, vector<Record> records)
{
	 this->blockNumber = blockNumber;
	 this->nextBlock = nextBlock;
	 this->prevBlock = prevBlock;
	 this->records = records;
}


/** Returns the size of the records object in the block.
*/
int Block::recordCount() {
	 return records.size();
}

/** Returns the block number of the block.
*/
int Block::getBlockNumber()
{
	 return blockNumber;
}

/** Returns the record located at a given index.
@param index: the index within the block where the record is located
*/
Record Block::getRecord(int index) {
	 return records[index];
}

/** Returns the block number of the block after the current block.
*/
int Block::getBlockNextNumber()
{
	 return nextBlock;
}

void Block::setNextBlockNumber(int nextBlock)
{
	 this->nextBlock = nextBlock;
}

int Block::getPrevBlockNumber()
{
	 return prevBlock;
}

string Block::getLastKey()
{
	 return records.back().getField(0);
}


void Block::deleteRecord(int rrn) {
	 records.erase(records.begin() + rrn);
}
/**
Returns the first record of the block while erasing it.
*/
Record Block::pop_first()
{
	 Record output = records.front();
	 records.erase(records.begin());
	 return output;
}

/** Returns the last record of the block while erasing it.
*/
Record Block::pop_last()
{
	 Record output = records.back();
	 records.pop_back();
	 return output;
}

/** Inserts a record at a given index
@param index: position at which the record is to be inserted.
@param rec: the record which is to be inserted into the block.
*/
void Block::insertRecord(int index, Record rec)
{
	records.insert(records.begin() + index, rec);
}

/**Appends a record onto the end of the block's record vector
@param rec: the record which is to be appended to the block.
*/
void Block::pushRecord(Record rec)
{
	 records.push_back(rec);
}

