#include "Index.h"

Index::Index()
{
	 indices = vector<pair<string, int>>();
	 keyType = Record::getFieldType(0);
}

void Index::addIndex(string key, int blockNum)
{
	 indices.push_back(make_pair(key, blockNum));
}
