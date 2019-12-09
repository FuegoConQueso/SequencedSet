#include "Index.h"
#include "SequencedSet.h"

int Index::findIndexByBlockNum(int blockNum) {
	 return findIndexByBlockNum(blockNum, false);
}

int Index::findIndexByBlockNum(int blockNum, bool isInsertion)
{
	 int midpoint = -1, r, l, compnum = -1;
	 r = indices.size() - 1;
	 l = 0;
	 while (l <= r)
	 {
		  midpoint = l + (r - l) / 2;
		  compnum = indices[midpoint].second;
		  if (blockNum == compnum)
		  {
				if (!isInsertion) {
					 return midpoint;
				}
				else {
					 throw new DuplicateIndexException(midpoint, "Thrown in findIndexByBlockNum()");
				}
		  }
		  else if (blockNum < compnum)
				r = midpoint - 1;
		  else
				l = midpoint + 1;
	 }
	 if (!isInsertion) {
		  return -1;
	 }
	 else {
		  if (blockNum > compnum) {
				midpoint += 1;
		  }
				return midpoint;
	 }
}

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
	 int location = findIndexByBlockNum(blockNum, true);
	 indices.insert(indices.begin() + location, make_pair(key, blockNum));
}

pair<string, int> Index::getIndex(int indexPosition)
{
	 return indices[indexPosition];
}

pair<string, int> Index::getLastIndex()
{
	 pair<string, int> output = pair<string, int>(indices.back());
	 return output;
}

vector<int> Index::getSiblings(int indexPosition)
{
	 vector<int> siblings = vector<int>();
	 if (indexPosition > 0) {
		  siblings.push_back(indexPosition - 1);
	 }
	 if (indexPosition < indices.size() - 2) {
		  siblings.push_back(indexPosition + 1);
	 }
	 return siblings;
}

void Index::deleteIndex(int indexPosition)
{
	 indices.erase(indices.begin() + indexPosition);
}

void Index::updateIndex(int blockToUpdateNum, string key)
{
	 int targetIndex = findIndexByBlockNum(blockToUpdateNum);
	 indices[targetIndex].first = key;
}

int Index::size()
{
	 return indices.size();
}

