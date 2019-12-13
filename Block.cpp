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


int Block::recordCount() {
	 return records.size();
}

int Block::getBlockNumber()
{
	 return blockNumber;
}

Record Block::getRecord(int index) {
	 return records[index];
}

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

Record Block::pop_first()
{
	 Record output = records.front();
	 records.erase(records.begin());
	 return output;
}

Record Block::pop_last()
{
	 Record output = records.back();
	 records.pop_back();
	 return output;
}

void Block::insertRecord(int index, Record rec)
{
	records.insert(records.begin() + index, rec);
}

void Block::pushRecord(Record rec)
{
	 records.push_back(rec);
}

