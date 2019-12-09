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
	 void addIndex2(string key, int blockNum);
	 pair<string, int> getIndex(int indexPosition);
	 void deleteIndex(int indexPosition);
	 int size();
	 void writeIndex(ofstream& indexOutput);
	 
};
