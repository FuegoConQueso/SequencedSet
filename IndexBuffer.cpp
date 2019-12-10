#include "IndexBuffer.h"
#include "SequencedSet.h"


/** Takes a vector of Index Records and a fieldType and places them all into one string
@param indices: the vector of index records to be appended to the string
@param fieldType: the string indicating field type to be placed at the beginning of the string
*/
string IndexBuffer::pack(vector<IndexRecord> indices, string fieldType)
{
	 Header* header = SequencedSet::sHeader();
	 //write the key's fieldType to the packed string
	 string packed = fieldType;
	 //fill the indices
	 for (int i = 0; i < indices.size(); i++) {
		  string packedIRecord = IndexRecordBuffer::pack(indices[i]);
		  //add the index to the packed string
		  packed.append("\n" + packedIRecord);
	 }
	 return packed;
}


/** Creates a vector of Index Records from a string containing them in order
@param packed: the string to be split into string-integer pairs
@param fieldType: tests if the fieldType listed in the string is compatible with the testType in the packed string
*/
vector<IndexRecord> IndexBuffer::unpack(string packed, string fieldType)
{

	 Header* header = SequencedSet::sHeader();

	 vector<IndexRecord> result = vector<IndexRecord>();
	 stringstream data = stringstream(packed);
	 string testType;
	 getline(data, testType);
	 if (testType.compare(fieldType) != 0) {
		  throw new exception("Invalid index file");
	 }
	 int keySize = header->getFieldSize(0);
	 for (string line; getline(data, line);) {

		  result.push_back(IndexRecordBuffer::unpack(line));
	 }
	 return result;
}
