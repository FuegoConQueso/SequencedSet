#include "BlockBuffer.h"

string BlockBuffer::pack(vector<string> recbloc1, int& place) {

	 {
		  string strb;
		  //tell the calling function where this block is located
		  place = stoi(recbloc1[0]);
		  //pad the nextBlock
		  for (int f = recbloc1[1].size(); f < nextBlockSize; f++) {
				recbloc1[1].append(" ");
		  }
		  //pad the recordCount
		  for (int f = recbloc1[2].size(); f < recordCountSize; f++) {
				recbloc1[2].append(" ");
		  }
		  for (int i = 0; i < recbloc1.size(); i++) {
				strb.append(recbloc1[i]);
		  }
		  return strb;
	 }
}

string BlockBuffer::pack(vector<string> recbloc1) {
	 int callback = 0;
	 return pack(recbloc1, callback);
}

/*
int main()
{
	vector<string> rec, rec12, rec13;
	vector<int> fieldSize;
	vector<string> rec1;
	fieldSize.push_back(6);
	fieldSize.push_back(31);
	fieldSize.push_back(2);
	fieldSize.push_back(36);
	fieldSize.push_back(9);
	fieldSize.push_back(10);
	recordBuffer r0;
	BlockBuffer b1;
	string rec2;
	vector<string> vecrec;

	rec.push_back("1001");
	rec.push_back("Agawam");
	rec.push_back("NY");
	rec.push_back("Hamp den");
	rec.push_back("42.0702");
	rec.push_back("-72.6227");

	rec12.push_back("501");
	rec12.push_back("Holtsville");
	rec12.push_back("NY");
	rec12.push_back("Suffolk");
	rec12.push_back("40.8154");
	rec12.push_back("-73.0451");

	rec13.push_back("504");
	rec13.push_back("Holtsville");
	rec13.push_back("NY");
	rec13.push_back("Suffolk");
	rec13.push_back("40.8154");
	rec13.push_back("-73.0451");

	rec2 = r0.pack(rec);
	vecrec.push_back(rec2);
	rec2.clear();

	rec2 = r0.pack(rec12);
	vecrec.push_back(rec2);
	rec2.clear();

	rec2 = r0.pack(rec13);
	vecrec.push_back(rec2);
	rec2.clear();
	rec2 = b1.pack(vecrec, blockNumber);
	cout << rec2;

	rec1 = r0.unpack(fieldSize);

	return 0;
}	*/