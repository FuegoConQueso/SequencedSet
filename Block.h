#pragma once

#include <cstdlib>
#include <vector>
#include <string>
#include "Record.h"
#include "rbuffer1.h"

using namespace std;

class Block
{
public:
	 //constructors
	 Block(); //creates empty block, with records vector initialized (but empty).
	 Block(vector<string> packedBlock); //creates a block from the string vector provided (post unbuffering)
	 Block(int blockNumber, int nextBlock, vector<Record> records); //creates a Block from the given data

	 //methods
	 vector<string> pack(); /*returns a vector of strings that the buffer class can prep for writing. Output is as follows: [blockNumber, nextBlock, blockSize, {Each record as a single string}] */
	 int recordCount(); //returns the current number of records in the block (aka records.size)
	 int getBlockNumber(); //returns the current block number
	 Record getRecord(int index); 
	 void insertRecord(int index, Record rec);
	 void pushRecord(Record rec); //adds record at end of block
	 int getBlockNextNumber();
	 string getLastKey();

	 void deleteRecord(int rrn);

	 Record pop_first();
	 Record pop_last();
private:
	 //data members
	 int blockNumber; //what relative block position this block is.
	 int nextBlock; //the relative block position of the next block.
	 vector<Record> records; // a vector of the records contained in this block

	 //methods
	 void unpack(vector<string> packedBlock); //loads the unbuffered string vector into the block
};
