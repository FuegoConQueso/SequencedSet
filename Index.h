#pragma once
#include <vector>
#include <tuple>
#include <string>
#include <fstream>
#include "Record.h"
#include "IndexBuffer.h"
#include "Header.h"
#include "BTreeNode.h"

using namespace std;

class Index
{
private:
	 Header::FieldType keyType;
	 vector<IndexRecord> indices;
	 BTreeNode* rootNode = new BTreeNode(minDegree);
	 int minDegree;
	 string outputFileName;
	 int findIndex(string key); //returns indexNum
	 int findIndex(string key, bool isInsertion);
public:
	 Index();
	 Index(vector<IndexRecord> indices);
	 Index(string packed);
	 void Create();
	 string pack();

	 void addIndex(string key, int blockNum);
	 void deleteIndex(string oldkey);
	 void updateIndex(string oldkey, string newkey);

	 IndexRecord getIndex(int indexPosition);
	 IndexRecord getLastIndex();
	 vector<IndexRecord> getSiblings(int indexPosition); //returns the indices of the siblings.
	 void BTreeSplitChild(BTreeNode x, int i);
	 void BTreeInsertNonFull(BTreeNode x, string k);
	 int size();
};
