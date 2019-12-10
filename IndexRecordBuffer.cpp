#include "IndexRecordBuffer.h"
#include "SequencedSet.h"

string IndexRecordBuffer::pack(IndexRecord topack)
{
	 Header* header = SequencedSet::sHeader();

	 // extract the name and pad it
	 string key = topack.key;
	 key = header->pad(key, header->getFieldSize(0));
	 //extract the blockNum and pad it
	 string blockNum = to_string(topack.blockNum);
	 blockNum = header->pad(blockNum, header->nextBlockSize());
	 //add the index to the packed string
	 return (key + blockNum);
}

IndexRecord IndexRecordBuffer::unpack(string packed)
{
	 Header* header = SequencedSet::sHeader();

	 int keySize = header->getFieldSize(0);
	 //get unpadded key
	 string key = packed.substr(0, keySize);
	 key = header->unpad(key);
	 //get unpadded blockNum
	 string blockNum = packed.substr(keySize, header->blockSize());
	 blockNum = header->unpad(blockNum);
	 return IndexRecord(key, stoi(blockNum));
}
