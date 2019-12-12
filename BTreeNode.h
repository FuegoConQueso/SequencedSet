#pragma once
#include <vector>
#include "Header.h"
#include "IndexRecord.h"

class BTreeNode {

public:
	BTreeNode();
	BTreeNode(int md);
	int getNumKeys() { return numKeys; }
	int getMinDegree() { return minDegree; }
	IndexRecord getKey(int index) { return keyList[index]; }
	bool getLeaf() { return leaf; }
	BTreeNode* getChild(int i) { return children[i]; }
	void setLeaf(bool leafValue) { leaf = leafValue; }
	void setNumKeys(int nk) { numKeys = nk; }
	void addKey(IndexRecord ir) { keyList.push_back(ir); }
	void addChild(BTreeNode* btn) { children.push_back(btn); }
	void setChild(BTreeNode* btn, int i) { children[i] = btn; }
	void setKey(IndexRecord ir, int i) { keyList[i] = ir; }
private:
	int numKeys;
	int minDegree;
	vector<IndexRecord> keyList;
	vector<BTreeNode*> children;
	bool leaf;
};
