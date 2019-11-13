#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "rbuffer1.h"

using namespace std;

static class BlockBuffer
{
protected:
	 static const int nextBlockSize = 6;
	 static const int recordCountSize = 3;
public:
	 //this works with the hard coded stuff at the moment
	 //I haven't tried it with a block header, though
	 //that probably will not be a problem. you may have to make changes
	 //depending on your code.
	 //printing produces an output with no breaks. no new line after a record
	 static string pack(vector<string> recbloc1, int& place);
	 static string pack(vector<string> recbloc1);

	 static int getBlockHeaderSize();
	 static int getBlockSize();
};
