#include "BlockBuffer.h"
#include "SequencedSet.h"

/** Given a vector of strings containing the records of a block, returns a single string with 
all relevant information.
@param recbloc1: the vector of strings containing the block information.
*/
string BlockBuffer::pack(vector<string> recbloc1, int& place) {

	 {
		  string strb = "\n"; //new block starts with a newline
		  //tell the calling function where this block is located
		  place = stoi(recbloc1[0]);
		  Header* header = SequencedSet::sHeader();
		  //pad the nextBlock
		  recbloc1[1] = header->pad(recbloc1[1], header->nextBlockSize());
		  //pad the recordCount
		  int recordCount = stoi(recbloc1[2]);
		  recbloc1[2] = header->pad(recbloc1[2], header->blockRecordCountSize());

		  // fill in the block with the nextblock, count, and records
		  for (int i = 1; i < recbloc1.size(); i++) {
				strb.append(recbloc1[i]);
		  }

		  //add blank records up to capacity
		  for (int i = recordCount; i < header->getBlockCapacity(); i++) {
				strb.append(header->pad("", header->getRecordSize()));
		  }
		  return strb;
	 }
}

/** Packs the input vector of strings with place parameter zero.
@param recbloc1: the vector of strings to be packed
*/
string BlockBuffer::pack(vector<string> recbloc1) {
	 int callback = 0;
	 return pack(recbloc1, callback);
}

/** Returns a block with a given block number and records as defined in a string.
@param blocknum: the block number
@param blocrec1: the records of the block in string format.
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
	 return Block(blockNum, nextBlock, records);
}
