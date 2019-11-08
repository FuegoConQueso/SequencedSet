#include "Record.h"

vector<tuple<string, int, Record::FieldType>> Record::fieldInfo;

void Record::setFieldInfo(vector<tuple<string, int, Record::FieldType>> fieldInfo)
{
	 Record::fieldInfo = vector<tuple< string, int, Record::FieldType>>(fieldInfo);
}

string Record::getFieldName(int index)
{
	 return get<0>(fieldInfo[index]);;
}

int Record::getFieldSize(int index)
{
	 return get<1>(fieldInfo[index]);
}

Record::FieldType Record::getFieldType(int index)
{
	 return get<2>(fieldInfo[index]);
}

int Record::getNumOfFields(int index)
{
	 return fieldInfo.size();
}


Record::Record()
{
	 fields = vector<string>();
}

Record::Record(vector<string> fields)
{
	 this->fields = fields;
}

vector<string> Record::pack()
{
	 return fields;
}

/* code we might need to use? not sure
	 switch (get<2>(fieldInfo[index])) {
		  case U_INTEGER:
				stoi(fields[index]);
				break;
		  case FLOAT:
				stof(fields[index]);
				break;
		  case TEXT:
				fields[index];
				break;
	 }*/
