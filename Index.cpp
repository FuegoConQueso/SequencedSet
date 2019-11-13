#include "Index.h"

Index::Index()
{
	 indices = vector<pair<string, int>>();
	 keyType = Record::getFieldType(0);
}

string Index::pack()
{
	 return IndexBuffer::pack(indices,Record::fieldTypeToString(keyType));
}

void Index::addIndex(string key, int blockNum)
{
	 indices.push_back(make_pair(key, blockNum));
}
