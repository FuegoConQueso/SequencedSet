#ifndef INPUT_FILE_HEADER_H
#define INPUT_FILE_HEADER_H
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class InputFileHeader {
	private:
		int headerSize;
		int recordSize;
		vector<int> fieldSizes;
		vector<string> fieldTypes;
		vector<string> fieldNames;
	public:
		InputFileHeader();
		void readHeader(ifstream &inputFile);
		int getHeaderSize(){return headerSize;}
		int getRecordSize(){return recordSize;}
};

#endif 
