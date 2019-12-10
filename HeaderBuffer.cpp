#include "HeaderBuffer.h"

/** Takes a header object and converts it into a single string
@param header: The header object to be packed into a string
*/
string HeaderBuffer::pack(Header& header)
{
	 string s = header.getHeaderSeperator();
	 string output = s;
	 output.append(header.getName());
	 output.append(s + header.pad(to_string(header.getStartBlock()), header.nextBlockSize()));
	 output.append(s + header.pad(to_string(header.getStartAvail()), header.nextBlockSize()));
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

/** Converts the header of a file into a Header object in memory
@param mainFile: the filestream object whose header is to be read
@param fileName: the name of the file whose header is to be read into a Header object
*/
Header HeaderBuffer::unpack(fstream& mainFile, string fileName)
{
	 //create variables
	 string headerSizeString;
	 string name;
	 string startBlockStr;
	 string startAvailStr;
	 string indexName;
	 vector<tuple<string, int, Header::FieldType>> fieldInfos = vector<tuple<string,int,Header::FieldType>>();
	 //get headerSize
	 getline(mainFile, headerSizeString);
	 int headerSize = stoi(headerSizeString);
	 //get sequencedSet name
	 getline(mainFile, name);
	 //get startBlock;
	 getline(mainFile, startBlockStr);
	 int startBlock = stoi(startBlockStr);
	 //get startAvail
	 getline(mainFile, startAvailStr);
	 int startAvail = stoi(startAvailStr);
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

	 
	 return Header(fileName,name,fieldInfos,startBlock,startAvail);
}
