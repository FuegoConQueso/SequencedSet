#include "IndexBuffer.h"

string IndexBuffer::pack(vector<pair<string, int>> indices, string fieldType)
{
	 string packed = fieldType;
	 for (int i = 0; i < indices.size(); i++) {
		  string name = indices[i].first;
		  for (int c = name.size(); c < Record::getFieldSize(0); c++) {
				name.append(" ");
		  }
		  string blockNum = to_string(indices[i].second);
		  for (int c = blockNum.size(); c < blockNumSize; c++) {
				blockNum.append(" ");
		  }
		  packed.append("\n" + name + blockNum);
	 }
	 return packed;
}

vector<pair<string, int>> IndexBuffer::unpack(string packed, string fieldType)
{
	 vector<pair<string, int>> result = vector<pair<string, int>>();
	 stringstream data = stringstream(packed);
	 string testType;
	 getline(data, testType);
	 if (testType.compare(fieldType) != 0) {
		  throw new exception("Invalid index file");
	 }
	 int keySize = Record::getFieldSize(0);
	 for (string line; getline(data, line);) {
		  //get unpadded key
		  string key = line.substr(0, keySize);
		  int erasePos = key.find_last_not_of(" ") + 1;
		  int eraseLength = key.size() - erasePos;
		  key.erase(erasePos, eraseLength);
		  //get unpadded blockNum
		  string blockNum = line.substr(keySize, blockNumSize);
		  erasePos = blockNum.find_last_not_of(" ") + 1;
		  eraseLength = blockNum.size() - erasePos;
		  blockNum.erase(erasePos, eraseLength);
		  //push to result vector
		  result.push_back(make_pair(key, stoi(blockNum)));
	 }
	 return result;
}
