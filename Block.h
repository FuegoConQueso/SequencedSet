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
	 //static methods
	 static int getSize(); //returns the size (in characters) of a block
	 static void setSize(int size); //sets the size (in characters) of a block

	 //constructors
	 Block(); //creates empty block, with records vector initialized (but empty).
	 Block(vector<string> packedBlock); //creates a block from the string vector provided (post unbuffering)
	 Block(int blockNumber, int nextBlock, vector<Record> records); //creates a Block from the given data

	 //methods
	 vector<string> pack(); /*returns a vector of strings that the buffer class can prep for writing. Output is as follows: [blockNumber, nextBlock, blockSize, {Each record as a single string}] */
	 int recordCount(); //returns the current number of records in the block (aka records.size)
	 int getBlockNumber(); //returns the current block number
private:
	 //data members
	 static int size; //the size (in number of characters) of a block 
	 int blockNumber; //what relative block position this block is.
	 int nextBlock; //the relative block position of the next block.
	 vector<Record> records; // a vector of the records contained in this block

	 //methods
	 void unpack(vector<string> packedBlock); //loads the unbuffered string vector into the block
};

