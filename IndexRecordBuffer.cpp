#include "IndexRecordBuffer.h"
#include "SequencedSet.h"

/** Takes an Index Record object and places it's information into a string
@param topack: the Index Record object that is to be packed into a string
@pre: an Index Record
@post: a string containing th einformation of the input index record
*/
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

/* Takes a string and outputs a corresponding Index Record object
@param packed: the string whose information is to be put into an index record object
@pre: a string
@post: an IndexRecord with the information conveyed by the string
*/
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
