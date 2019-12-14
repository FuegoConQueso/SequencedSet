#include "Index.h"
#include "SequencedSet.h"

/** Calls the findIndex function with insertion flag set to false
@param key: the key whose index is to be retrieved
@pre: A key string
@post: An integer containing the location of the key in the index.
*/
int Index::findIndex(string key) {
	 return findIndex(key, false);
}

/* Finds the location of the key in the index depending upon whether it is
an insertion or not
@pre: A key and a boolean flag indicating whether or not it is an insertion.
@post: An integer indicating the position of the key.
*/
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

/** Initializes some member variables of the Index class
@pre: none
@post: header, indices, and keyType for the class are set
*/
void Index::Create() {
	 Header* header = SequencedSet::sHeader();
	 indices = vector<IndexRecord>();
	 keyType = header->getKeyType();
}

/** Returns a string which has packed a vector of indices into a string.
@pre: none
@post: a string containing the information of the vector of indices
*/
string Index::pack()
{
	 return IndexBuffer::pack(indices, Header::fieldTypeToString(keyType));
}

/** Finds the location of the key and then inserts the index from that location
in the index record into the indices vector
@param key: the key to be added
@param blockNum: the block number in the index record of the key to be added
@pre: A key and block number
@post: The Index object now contains the index which was located at the index record location
*/
void Index::addIndex(string key, int blockNum)
{
	 int location = findIndex(key, true);
	 indices.insert(indices.begin() + location, IndexRecord(key, blockNum));
}

/*Gets the index at a given position
@param indexPosition: the position of the index record to be located
@pre: an index position
@post: an IndexRecord object located at the index position
*/
IndexRecord Index::getIndex(int indexPosition)
{
	 return indices[indexPosition];
}

/** Gets the Index Record at the final position of the indices array
@pre: none
@post: The final index record of the indices array
*/
IndexRecord Index::getLastIndex()
{
	 IndexRecord output = IndexRecord(indices.back());
	 return output;
}

/** Gets the siblings of an index at a given position and places them in a vector
@param indexPosition: The position of the index whose siblings are sought
@pre: an index position
@post: a vector of the siblings of the Index object in question.
*/
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

/** Deletes the Index object with a given key
@param key: the key of the index object to be deleted
@pre: a key string
@post: The Index with the key is deleted from the array of indices
*/
void Index::deleteIndex(string key)
{
	 indices.erase(indices.begin() + findIndex(key));
}

/* Updates the key of an Index object
@param oldkey: the previous key of the Index object to be changed
@param newkey: the new key of that the Index object will adopt
@pre: An old key and a new key
@post: the Index with the key value of the old key now has the key value of the new key
*/
void Index::updateIndex(string oldkey, string newkey)
{
	 if (oldkey.compare(newkey) != 0) {
		  int targetIndex = findIndex(oldkey);
		  indices[targetIndex].key = newkey;
	 }
}

/**Returns the size of the indices array
*/
int Index::size()
{
	 return indices.size();
}

