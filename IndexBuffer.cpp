#include "IndexBuffer.h"
#include "SequencedSet.h"

/** Takes a vector of string-integer pairs and a fieldType and places them all into one string
@param indices: the vector of string-integer pairs to be appended to the string
@param fieldType: the string indicating field type to be placed at the beginning of the string
*/
string IndexBuffer::pack(vector<pair<string, int>> indices, string fieldType)
{
	 Header* header = SequencedSet::sHeader();
	 //write the key's fieldType to the packed string
	 string packed = fieldType;
	 //fill the indices
	 for (int i = 0; i < indices.size(); i++) {
		  // extract the name and pad it
		  string name = indices[i].first;
		  name = header->pad(name, header->getFieldSize(0));
		  //extract the blockNum and pad it
		  string blockNum = to_string(indices[i].second);
		  blockNum = header->pad(blockNum, header->nextBlockSize());
		  //add the index to the packed string
		  packed.append("\n" + name + blockNum);
	 }
	 return packed;
}

/** Creates a vector of string-integer pairs from a string containing them in order
@param packed: the string to be split into string-integer pairs
@param fieldType: tests if the fieldType listed in the string is compatible with the testType in the packed string
*/
vector<pair<string, int>> IndexBuffer::unpack(string packed, string fieldType)
{

	 Header* header = SequencedSet::sHeader();

	 vector<pair<string, int>> result = vector<pair<string, int>>();
	 stringstream data = stringstream(packed);
	 string testType;
	 getline(data, testType);
	 if (testType.compare(fieldType) != 0) {
		  throw new exception("Invalid index file");
	 }
	 int keySize = header->getFieldSize(0);
	 for (string line; getline(data, line);) {
		  //get unpadded key
		  string key = line.substr(0, keySize);
		  key = header->unpad(key);
		  //get unpadded blockNum
		  string blockNum = line.substr(keySize, header->blockSize());
		  blockNum = header->unpad(blockNum);
		  //push to result vector
		  result.push_back(make_pair(key, stoi(blockNum)));
	 }
	 return result;
}
