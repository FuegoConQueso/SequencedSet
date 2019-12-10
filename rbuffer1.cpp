#include "rbuffer1.h"
#include "SequencedSet.h"

/** takes a vector of strings representing the fields of a record and places it into one string
@param packed: the vector of strings which is to be converted into one string
*/
string recordBuffer::pack(vector<string> packed)
{
	Header* header = SequencedSet::sHeader();
	string field;
	string record;
	for(int index = 0; index < packed.size(); index++)
	{
		field = packed[index];		//the field in the vector is copied to string f2
		field = header->pad(field, header->getFieldSize(index));
		record.append(field);	//the field with padding is appended to string Record
	}
	return record;
}

/** takes a string representing an entire record and places it into a vector of strings indicating the fields
@param record: the string to be split into vector elements (fields)
*/
vector<string> recordBuffer::unpack(string record)
{
	Header* header = SequencedSet::sHeader();
	int position = 0;
	vector<string> recFields2;
	for(int i = 0; i < header->getNumOfFields(); i++)
	{
			string field = record.substr(position, header->getFieldSize(i));
			field = header->unpad(field);
			recFields2.push_back(field);
			position += header->getFieldSize(i);
	}
	 return recFields2;
}
