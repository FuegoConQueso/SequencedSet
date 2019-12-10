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

/** Returns a vector of strings containing the block number, next block, size, and records (in order)
of the block object.
*/
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

/** Returns the primary key of the final record of the block.
*/
string Block::getLastKey()
{
	 return records.back().getField(0);
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

/** Takes a block in the form of a vector of strings and converts it to a block object
@param packedBlock: the vector of strings with the block information to be converted
into a block object.
*/
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
