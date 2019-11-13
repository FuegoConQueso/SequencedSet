#include "IndexBuffer.h"

string IndexBuffer::pack(vector<pair<string, int>> indices, string fieldType)
{
	 string packed = fieldType;
	 for (int i = 0; i < indices.size; i++) {
		  string name = indices[i].first;
		  for (int c = name.size; c < Record::getFieldSize(0); c++) {
				name.append(" ");
		  }
		  string blockNum = to_string(indices[i].second);
		  for (int c = blockNum.size; c < blockNumSize; c++) {
				blockNum.append(" ");
		  }
		  packed.append("\n" + name + blockNum);
	 }
}
