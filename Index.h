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
	 int findIndexByBlockNum(int blockNum); //returns indexNum
	 int findIndexByBlockNum(int blockNum, bool isInsertion);
public:
	 Index();
	 Index(vector<pair<string, int>> indices);
	 Index(string packed);
	 void Create();
	 string pack();

	 void addIndex(string key, int blockNum); //TODO: needs work (find correct spot to insert)
	 void deleteIndex(int indexPosition);
	 void updateIndex(int blockToUpdateNum, string key);

	 pair<string, int> getIndex(int indexPosition);
	 pair<string, int> getLastIndex();
	 vector<int> getSiblings(int indexPosition); //returns the indices of the siblings.
	 int size();
};
