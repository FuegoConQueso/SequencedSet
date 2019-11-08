#include <string>
#include <iostream>
#include <vector>
#include "Record.h"
using namespace std;

class recordBuffer
{
	protected:
		string record;
	public:
		recordBuffer(){};
		string pack(vector<string> f1, vector<int> fs);
};

/*f1 is a vector containing the fields in the order of zip, placename, state, county, latitude, and longitude.
fs in a vector containing the maximum size of each field in the same order as f1*/
string recordBuffer::pack(vector<string> f1, vector<int> fs)
{
	string f2;
	for(int index = 0; index < f1.size(); index++)
	{
		f2.clear();
		f2 = f1[index];		//the field in the vector is copied to string f2
		if(f2.size() < fs[index])	
		{
			int fieldS1 = f2.size();
			int fieldMS = Record.;
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

int main()
{
	vector<string> rec;
	vector<int> fieldSize;
	fieldSize.push_back(6);
	fieldSize.push_back(31);
	fieldSize.push_back(2);
	fieldSize.push_back(36);
	fieldSize.push_back(9);
	fieldSize.push_back(10);
	recordBuffer r0;
	string rec2;
	rec.push_back("1001");
	rec.push_back("Agawam");
	rec.push_back("NY");
	rec.push_back("Hampden");
	rec.push_back("42.0702");
	rec.push_back("-72.6227");
	rec2 = r0.pack(rec, fieldSize);
	cout << rec2;
	return 0;
}	