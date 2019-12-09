#include "rbuffer1.h"
#include "SequencedSet.h"

/*f1 is a vector containing the fields in the order of zip, placename, state, county, latitude, and longitude.
fs in a vector containing the maximum size of each field in the same order as f1*/
string recordBuffer::pack(Record packed)
{
	Header* header = SequencedSet::sHeader();
	string field;
	string record;
	for(int index = 0; index < header->getNumOfFields(); index++)
	{
		field = packed.getField(index);		//the field in the vector is copied to string f2
		field = header->pad(field, header->getFieldSize(index));
		record.append(field);	//the field with padding is appended to string Record
	}
	return record;
}

//I havent tested this with the rest of the sequence set code
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
