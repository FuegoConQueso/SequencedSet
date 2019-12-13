#pragma once
#include "Header.h"
#include <string>
#include <iostream>
#include <vector>
#include "rbuffer1.h"
#include "Block.h"
#include "Record.h"

using namespace std;

class BlockBuffer
{
public:
	 //this works with the hard coded stuff at the moment
	 //I haven't tried it with a block header, though
	 //that probably will not be a problem. you may have to make changes
	 //depending on your code.
	 //printing produces an output with no breaks. no new line after a record
	 static string pack(Block* topack, int& place);
	 static string pack(Block* topack);
	 static Block unpack(int blockNum, string blocrec1);
	 static string createAvail(Block* block);
};
