#include "Index.h"
#include "SequencedSet.h"

Index::Index()
{
}

Index::Index(vector<pair<string, int>> indices)
{
	 Header* header = SequencedSet::sHeader();
	 this->indices = indices;
	 keyType = header->getKeyType();
}

Index::Index(string packed)
{
	 Header* header = SequencedSet::sHeader();
	 string headerStr = header->fieldTypeToString(header->getKeyType());
	 *this = Index::Index(IndexBuffer::unpack(packed, headerStr));
}

void Index::Create() {
	 Header* header = SequencedSet::sHeader();
	 indices = vector<pair<string, int>>();
	 keyType = header->getKeyType();
}

string Index::pack()
{
	 return IndexBuffer::pack(indices, Header::fieldTypeToString(keyType));
}

void Index::addIndex(string key, int blockNum)
{
	 indices.push_back(make_pair(key, blockNum));
}

void Index::writeIndex(ofstream& indexOutput)
{
	for (int i = 0; i < indices.size(); i++)
	{
		indexOutput << get<0>(indices[i])<< " " << get<1>(indices[i]) << endl;
	}
	
}
