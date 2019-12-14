#include "Index.h"
#include "SequencedSet.h"

int Index::findIndex(string key) {
	 return findIndex(key, false);
}

int Index::findIndex(string key, bool isInsertion)
{
	 Header* header = SequencedSet::sHeader();
	 int midpoint = 0, r, l, compnum = -1;
	 string compstring;
	 r = indices.size() - 1;
	 l = 0;
	 while (l <= r)
	 {
		  midpoint = l + (r - l) / 2;
		  compstring = indices[midpoint].key;
		  compnum = header->compare(key, compstring, header->getKeyType());
		  if (compnum == 0)
		  {
				if (!isInsertion) {
					 return midpoint;
				}
				else {
					 throw new DuplicateIndexException(midpoint, "Thrown in findIndexByBlockNum()");
				}
		  }
		  else if (compnum == -1)
				r = midpoint - 1;
		  else
				l = midpoint + 1;
	 }
	 if (!isInsertion) {
		  return -1;
	 }
	 else {
		  if (compnum == 1) {
				midpoint += 1;
		  }
			return midpoint;
	 }
}

Index::Index()
{
}

Index::Index(vector<IndexRecord> indices)
{
	 Header* header = SequencedSet::sHeader();
	 this->indices = indices;
	 keyType = header->getKeyType();
}

Index::Index(string packed)
{
	 Header* header = SequencedSet::sHeader();
	 string headerStr = header->fieldTypeToString(header->getKeyType());
	 *this = Index(IndexBuffer::unpack(packed, headerStr));
}

void Index::Create() {
	 Header* header = SequencedSet::sHeader();
	 indices = vector<IndexRecord>();
	 keyType = header->getKeyType();
}

string Index::pack()
{
	 return IndexBuffer::pack(indices, Header::fieldTypeToString(keyType));
}

void Index::addIndex(string key, int blockNum)
{
	 int location = findIndex(key, true);
	 indices.insert(indices.begin() + location, IndexRecord(key, blockNum));
}

IndexRecord Index::getIndex(int indexPosition)
{
	 return indices[indexPosition];
}

IndexRecord Index::getLastIndex()
{
	 IndexRecord output = IndexRecord(indices.back());
	 return output;
}

vector<IndexRecord> Index::getSiblings(int indexPosition)
{
	 vector<IndexRecord> siblings = vector<IndexRecord>();
	 if (indexPosition > 0) {
		  siblings.push_back(getIndex(indexPosition - 1));
	 }
	 if (indexPosition < indices.size() - 2) {
		  siblings.push_back(getIndex(indexPosition + 1));
	 }
	 return siblings;
}

void Index::deleteIndex(string key)
{
	 indices.erase(indices.begin() + findIndex(key));
}

void Index::updateIndex(string oldkey, string newkey)
{
	 if (oldkey.compare(newkey) != 0) {
		  int targetIndex = findIndex(oldkey);
		  indices[targetIndex].key = newkey;
	 }
}

int Index::size()
{
	 return indices.size();
}

