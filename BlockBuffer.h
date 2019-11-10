#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "rbuffer1.h"

using namespace std;

class BlockBuffer
{
protected:
	 const int nextBlockSize = 3;
	 const int recordCountSize = 3;
	 vector<string> records;
	 int recordsize;
public:
	 //this works with the hard coded stuff at the moment
	 //I haven't tried it with a block header, though
	 //that probably will not be a problem. you may have to make changes
	 //depending on your code.
	 //printing produces an output with no breaks. no new line after a record
	 string pack(vector<string> recbloc1, int& place);
};
