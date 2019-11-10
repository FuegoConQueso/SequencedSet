#include <string>
#include <iostream>
#include <vector>
using namespace std;

class BlockBuffer
{
	protected:
		vector<string> records;
		int recordsize = 94;
	public:
		string pack(vector<string> recbloc1);
		vector<string> unpack(string blocrec1);
};

string BlockBuffer::pack(vector<string> recbloc1)
{
	string strb;
	for(int i = 0; i < recbloc1.size(); i++)
		strb.append(recbloc1[i]);
	return strb;
}

//this works on the hard code without a header.
vector<string> BlockBuffer::unpack(string blocrec1)
{
		vector<string> unpackblock;
		string holdrec;
		//position to start reading in the string
		int startReadPos = 0;
		//number of records
		int numOfRecs = 3;
		//a substring cosisting of one record will be produced from the string containing the block
		//the substring will then be put into the vector
		//the read position will then be updated and he substring cleared
		for(int y = 0; y < numOfRecs; y++)
		{
			holdrec = blocrec1.substr(startReadPos, recordsize);
			unpackblock.push_back(holdrec);
			startReadPos += recordsize;
			holdrec.clear();	
		}
		return unpackblock;
}
