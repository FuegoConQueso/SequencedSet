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

void Index::addIndex2(string key, int blockNum)
{
	cout << "In addIndex2 function.\n";
	cout << "Key: " << key << endl;
	cout << "Block Number: " << blockNum << endl;
	cout << "Indices vector size: " << indices.size() << endl;
	for (int i = 0; i < indices.size(); i++)
	{
		if (stoi(get<0>(indices[i])) >= stoi(key))
		{
			indices.insert(indices.begin() + i, make_pair(key, blockNum));
			if (stoi(get<0>(indices[i + 1])) == stoi(key))
				indices.erase(indices.begin() + (i + 1));
			break;
		}
	}
}

pair<string, int> Index::getIndex(int indexPosition)
{
	 return indices[indexPosition];
}

void Index::deleteIndex(int indexPosition)
{
	 indices.erase(indices.begin() + indexPosition);
}

int Index::size()
{
	 return indices.size();
}

void Index::writeIndex(ofstream& indexOutput)
{
	for (int i = 0; i < indices.size(); i++)
	{
		indexOutput << get<0>(indices[i])<< " " << get<1>(indices[i]) << endl;
	}
	
}
