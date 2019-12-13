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
	 Block(int blockNumber, int nextBlock, int prevBlock, vector<Record> records); //creates a Block from the given data

	 //methods
	 int recordCount(); //returns the current number of records in the block (aka records.size)
	 int getBlockNumber(); //returns the current block number
	 Record getRecord(int index); 
	 void insertRecord(int index, Record rec);
	 void pushRecord(Record rec); //adds record at end of block
	 int getBlockNextNumber();
	 void setNextBlockNumber(int nextBlock);
	 int getPrevBlockNumber();

	 string getLastKey();

	 void deleteRecord(int rrn);

	 Record pop_first();
	 Record pop_last();
private:
	 //data members
	 int blockNumber; //what relative block position this block is.
	 int nextBlock; //the relative block position of the next block.
	 int prevBlock; //the relative block position of the prev block.
	 vector<Record> records; // a vector of the records contained in this block
};
