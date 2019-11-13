#pragma once
#include <vector>
#include <tuple>
#include <string>
#include "Record.h"
using namespace std;

class Index
{
private:
	 Record::FieldType keyType;
	 vector<pair<string, int>> indices;
public:
	 Index();
	 void addIndex(string key, int blockNum);
};

