#ifndef HEADER_FILE_H
#define HEADER_FILE_H
#include <iostream>
#include <vector>
#include <fstream>
#include "InputFileHeader.h"
using namespace std;

class HeaderFile(){
	private:
		int headerSize;
		int recordSize;
		vector<int> fieldSizes;
		vector<string> fieldTypes;
		vector<string> fieldNames;
	public: 
		HeaderFile();
		int getHeaderSize(){return headerSize;}
		int getRecordSize(){return recordSize;}
		int getNumFields(){return numFields;}
		int compare(string a, string b, FieldType f);
		void loadInputHeader;
	
};

#endif
