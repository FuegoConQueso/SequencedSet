#include "Block.h"

int Block::size;

int Block::getSize()
{
	 return size;
}

void Block::setSize(int size)
{
	 Block::size = size;
}

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
		  recordBuffer rb = recordBuffer();
		  packed.push_back(rb.pack(records[i].pack()));
	 }
	 return packed;
}

int Block::recordCount() {
	 return records.size();
}

void Block::unpack(vector<string> packedBlock)
{
	 int size = packedBlock.size();
	 blockNumber = stoi(packedBlock[0]);
	 nextBlock = stoi(packedBlock[1]);
	 //skips reading size
	 for (int i = 3; i < size; i++) {
		  recordBuffer rb = recordBuffer();
		  //unbuffers, and then uses that to construct a new record which is placed at the end
		  //records.emplace_back(rb.unpack(packedBlock[i]));
	 }
}
