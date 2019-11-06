#pragma once

#include "Record.h"
#include <cstdlib>
#include <vector>
#include <string>

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
	 int blockSize(); //returns the current number of records in the block (aka records.size)

private:
	 //data members
	 int blockNumber; //what relative block position this block is.
	 int nextBlock; //the relative block position of the next block.
	 vector<Record> records; // a vector of the records contained in this block

	 //methods
	 void unpack(vector<string> packedBlock); //loads the unbuffered string vector into the block
};

