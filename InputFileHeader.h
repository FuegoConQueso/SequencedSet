#ifndef INPUT_FILE_HEADER_H
#define INPUT_FILE_HEADER_H
#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>
#include <string>
#include "Header.h"
using namespace std;

class InputFileHeader {
	private:
		int headerSize;
		int recordSize;
		string filename;
		vector<int> fieldSizes;
		vector<string> fieldTypes;
		vector<string> fieldNames;
	public:
		InputFileHeader();
		void readHeader(ifstream &inputFile);
		int getHeaderSize(){return headerSize;}
		int getRecordSize(){return recordSize;}
		void setFileName(string fn){filename = fn;}
		string getFieldName(int i);
		int getFieldSize(int i);
		Header::FieldType getFieldType(int i);
		vector<tuple<string, int, Header::FieldType>> recordFields;
		vector<tuple<string, int, Header::FieldType>> makeTuples();
};


#endif 