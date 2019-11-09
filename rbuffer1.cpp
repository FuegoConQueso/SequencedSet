#include "rbuffer1.h"

/*f1 is a vector containing the fields in the order of zip, placename, state, county, latitude, and longitude.
fs in a vector containing the maximum size of each field in the same order as f1*/
string recordBuffer::pack(vector<string> f1)
{
	string f2;
	for(int index = 0; index < f1.size(); index++)
	{
		f2.clear();
		f2 = f1[index];		//the field in the vector is copied to string f2
		if(f2.size() < Record::getFieldSize(index))
		{
			int fieldS1 = f2.size();
			int fieldMS = Record::getFieldSize(index);
			/* obtain the difference between the size of the field 
			and the maximum size of the field*/
			fieldMS -= fieldS1;
			f2.clear();
			/* if the field is zip, latitude or longitude
			the field will be right justified. Otherwise, the padding 
			will be added after the field is put into f2*/
			if(index == 0 || index == 4 || index == 5)
			{
				for(int f = 0; f < fieldMS; f++)
					f2.append(" ");
				f2.append(f1[index]);
			}
			else
			{
				f2.append(f1[index]);
				for(int indj = 0; indj < fieldMS; indj++)
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
	int position = 0;
	int erasePos = 0;
	vector<string> recFields2;
	for(int i = 0; i < Record::getNumOfFields(); i++)
	{
			string subs1, subs2;
			int beginPos = 0;
			subs1 = record.substr(position, Record::getFieldSize(i));
			if(i == 0 || i == 4 || i == 5)
			{
				erasePos = subs1.find_first_not_of(" ");
				subs1.erase(beginPos, erasePos);
				recFields2.push_back(subs1);
			}
			else if(i == 2)
				recFields2.push_back(subs1);		
			else
			{
				erasePos = subs1.find_last_not_of(" ");
				int fieSize = Record::getFieldSize(i);
				int endRead = erasePos - fieSize;
				erasePos += 1;
				subs1.erase(erasePos, endRead);	
				recFields2.push_back(subs1);
			}
			subs1.clear();
			position = Record::getFieldSize(i);
	}
	 return recFields2;
}
