#include "Block.h"
#include "SequencedSet.h"


Block::Block() {
	 records = vector<Record>();
}

Block::Block(vector<string> packedBlock)
{
	 records = vector<Record>();
	 unpack(packedBlock);
}

Block::Block(int blockNumber, int nextBlock, vector<Record> records)
{
	 this->blockNumber = blockNumber;
	 this->nextBlock = nextBlock;
	 this->records = records;
}

vector<string> Block::pack() {
	 vector<string> packed = vector<string>();
	 packed.push_back(to_string(blockNumber));
	 packed.push_back(to_string(nextBlock));
	 int size = recordCount();
	 packed.push_back(to_string(size));

	 for (int i = 0; i < size; i++) {
		  packed.push_back(recordBuffer::pack(records[i].pack()));
	 }
	 return packed;
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

void Block::unpack(vector<string> packedBlock)
{
	 int size = packedBlock.size();
	 blockNumber = stoi(packedBlock[0]);
	 nextBlock = stoi(packedBlock[1]);
	 //skips reading size
	 for (int i = 3; i < size; i++) {
		  //unbuffers, and then uses that to construct a new record which is placed at the end
		  records.emplace_back(recordBuffer::unpack(packedBlock[i]));
	 }
}
