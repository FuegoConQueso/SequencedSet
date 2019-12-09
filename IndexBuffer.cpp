#include "IndexBuffer.h"
#include "SequencedSet.h"

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
