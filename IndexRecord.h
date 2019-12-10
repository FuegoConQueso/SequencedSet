#pragma once
#include <string>

using namespace std;

class IndexRecord
{
public:
	 string key;
	 int blockNum;
	 IndexRecord(string key, int blockNum);
};

