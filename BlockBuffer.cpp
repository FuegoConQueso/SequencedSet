#include "BlockBuffer.h"
#include "SequencedSet.h"


string BlockBuffer::pack(Block* topack, int& place) {
	 {
		  Header* header = SequencedSet::sHeader();

		  string strb = "\n"; //new block starts with a newline
		  //tell the calling function where this block is located
		  place = topack->getBlockNumber();
		  //pad the nextBlock
		  int nextBlock = topack->getBlockNextNumber();
		  strb += header->pad(to_string(nextBlock), header->nextBlockSize());
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

string BlockBuffer::pack(Block* topack) {
	 int callback = 0;
	 return pack(topack, callback);
}

// this works on the hard code without a header.
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
