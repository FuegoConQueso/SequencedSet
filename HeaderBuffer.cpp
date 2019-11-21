#include "HeaderBuffer.h"

string HeaderBuffer::pack(Header header)
{
	 string s = header.getHeaderSeperator();
	 string output = s;
	 output.append(header.getName());
	 string fs = header.getHFieldSeparator();
	 for (int i = 0; i < header.getNumOfFields(); i++) {
		  output.append(s);
		  output.append(header.getFieldName(i) + fs);
		  output.append(to_string(header.getFieldSize(i)) + fs);
		  output.append(Header::fieldTypeToString(header.getFieldType(i)));
	 }
	 int size = output.size() + header.getHeaderSizeSize();
	 output.insert(0, header.pad(to_string(size), header.getHeaderSizeSize()));
	 return output;
}

Header HeaderBuffer::unpack(fstream mainFile, string fileName, SequencedSet* parent)
{
	 //create variables
	 string headerSizeString;
	 string name;
	 vector<tuple<string, int, Header::FieldType>> fieldInfos = vector<tuple<string,int,Header::FieldType>>();
	 //get headerSize
	 getline(mainFile, headerSizeString);
	 int headerSize = stoi(headerSizeString);
	 //get sequencedSet name
	 getline(mainFile, name);
	 //get info for the fields
	 while (mainFile.tellg() < headerSize) {
		  string field;
		  string fieldName;
		  string fieldSizeString;
		  string fieldTypeString;
		  int fieldSize;
		  Header::FieldType fieldType;
		  //transfer the field info into a seperate stringstream
		  getline(mainFile, field);
		  stringstream fieldstream = stringstream(field);
		  //get the fieldName
		  getline(fieldstream, fieldName, '|');
		  //get the fieldSize
		  getline(fieldstream, fieldSizeString, '|');
		  fieldSize = stoi(fieldSizeString);
		  //get the fieldType
		  getline(fieldstream, fieldTypeString);
		  fieldType = Header::toFieldType(fieldTypeString);
		  //create a fieldInfo tuple
		  tuple<string, int, Header::FieldType> fieldInfo = make_tuple(fieldName, fieldSize, fieldType);
		  //add tuple to the vector
		  fieldInfos.push_back(fieldInfo);

	 }

	 
	 return Header(fileName,name,fieldInfos, parent);
}
