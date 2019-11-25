#include "rbuffer1.h"
#include "SequencedSet.h"

/*f1 is a vector containing the fields in the order of zip, placename, state, county, latitude, and longitude.
fs in a vector containing the maximum size of each field in the same order as f1*/
string recordBuffer::pack(vector<string> f1)
{
	Header* header = SequencedSet::sHeader();
	string f2;
	string record;
	for(int index = 0; index < f1.size(); index++)
	{
		f2.clear();
		f2 = f1[index];		//the field in the vector is copied to string f2
		if(f2.size() < header->getFieldSize(index))
		{
			int fieldS1 = f2.size();
			int fieldMS = header->getFieldSize(index);
			/* obtain the difference between the size of the field 
			and the maximum size of the field*/
			fieldMS -= fieldS1;
			f2.clear();
			f2.append(f1[index]);
			for (int f = 0; f < fieldMS; f++) {
				 f2.append(" ");
			}
		}
		record.append(f2);	//the field with padding is appended to string Record
	}
	f2.clear();
	f1.clear();
	return record;
}

//I havent tested this with the rest of the sequence set code
vector<string> recordBuffer::unpack(string record)
{
	Header* header = SequencedSet::sHeader();
	int position = 0;
	int erasePos = 0;
	vector<string> recFields2;
	for(int i = 0; i < header->getNumOfFields(); i++)
	{
			string subs1, subs2;
			int beginPos = 0;
			subs1 = record.substr(position, header->getFieldSize(i));
			subs1 = header->unpad(subs1);
			recFields2.push_back(subs1);
			position = header->getFieldSize(i);
	}
	 return recFields2;
}
