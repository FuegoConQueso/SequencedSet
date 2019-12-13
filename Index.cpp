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
	 *this = Index::Index(IndexBuffer::unpack(packed, headerStr));
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

void Index::BTreeSplitChild(BTreeNode x, int i)
{
	BTreeNode* z = new BTreeNode(minDegree);
	BTreeNode* y;
	y = x.getChild(i);
	z->setLeaf(y->getLeaf());
	z->setNumKeys(minDegree - 1);
	for (int j = 0; j < minDegree - 1; j++)
	{
		z->addKey(y->getKey(j + minDegree));
	}
	if (!y->getLeaf())
	{
		for (int j = 0; j < minDegree; j++)
		{
			z->addChild(y->getChild(j + minDegree));
		}
	}
	y->setNumKeys(minDegree - 1);
	BTreeNode* dummyNode;
	x.addChild(dummyNode);
	for (int j = x.getNumKeys(); j > (i); j--)
	{
		x.setChild(x.getChild(j - 1), j);
	}
	x.setChild(z, i);
	IndexRecord dummyRecord(0,0);
	x.addKey(dummyRecord);
	for (int j = x.getNumKeys - 1; j > (i - 1); j--)
	{
		x.setKey(x.getKey(j-1), j);
	}
	x.setKey(y->getKey(minDegree - 1), i - 1);
	x.setNumKeys(x.getNumKeys() + 1);
}

void Index::BTreeInsertNonFull(BTreeNode x, string k)
{
	Header* header = SequencedSet::sHeader();
	int i = x.getNumKeys();
	IndexRecord dummyRecord(0,0);
	x.addKey(dummyRecord);
	if (x.getLeaf())
	{
		while ((i >= 0) && (header->compare(k, x.getKey(i-1).key, header->getKeyType())) == -1)
		{
			x.setKey(x.getKey(i-1), i);
			i--;
		}
		IndexRecord addedRecord(k, 0); //How to compute block number for key?
		x.setKey(addedRecord, i+1);
		x.setNumKeys(x.getNumKeys() + 1);
	}
	else
	{
		while ((i >= 0) && (header->compare(k, x.getKey(i - 1).key, header->getKeyType())) == -1)
		{
			i--;
		}
		if (x.getChild(i - 1)->getNumKeys() == 2 * minDegree - 1)
		{
			BTreeSplitChild(x, i);
			if (header->compare(k, x.getKey(i - 1).key, header->getKeyType()) == 1)
				i++;
		}
		BTreeInsertNonFull(*(x.getChild(i-1)), k);
	}
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

