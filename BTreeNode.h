#pragma once
#include <vector>
#include "Header.h"
#include "IndexRecord.h"

class BTreeNode {

public:
	BTreeNode();
	int getNumKeys() { return numKeys; }
	int getMinDegree() { return minDegree; }
	IndexRecord getKey(int index) { return keyList[index]; }
	bool getLeaf() { return leaf; }
private:
	int numKeys;
	int minDegree;
	vector<IndexRecord> keyList;
	vector<BTreeNode*> children;
	bool leaf;
};
