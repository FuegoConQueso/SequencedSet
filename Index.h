#pragma once
#include <vector>
#include <tuple>
#include <string>
#include <fstream>
#include "Record.h"
#include "IndexBuffer.h"
#include "Header.h"

using namespace std;

class Index
{
private:
	 Header::FieldType keyType;
	 vector<pair<string, int>> indices;
	 string outputFileName;
public:
	 Index();
	 Index(vector<pair<string, int>> indices);
	 Index(string packed);
	 void Create();
	 string pack();
	 void addIndex(string key, int blockNum);
	 void writeIndex(ofstream& indexOutput);
};
