#include "Index.h"
#include "SequencedSet.h"

Index::Index()
{
}

void Index::Create() {
	 Header* header = SequencedSet::sHeader();
	 indices = vector<pair<string, int>>();
	 keyType = header->getFieldType(0);
}

string Index::pack()
{
	 return IndexBuffer::pack(indices,Header::fieldTypeToString(keyType));
}

void Index::addIndex(string key, int blockNum)
{
	 indices.push_back(make_pair(key, blockNum));
}
