#pragma once
#include <vector>
#include <tuple>
#include <string>
#include "Record.h"
#include "IndexBuffer.h"
#include "Header.h"

using namespace std;

class Index
{
private:
	 Header::FieldType keyType;
	 vector<pair<string, int>> indices;
public:
	 Index();
	 void Create();
	 string pack();
	 void addIndex(string key, int blockNum);
};

