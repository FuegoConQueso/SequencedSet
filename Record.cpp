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

int Record::getNumOfFields()
{
	 return fieldInfo.size();
}

Record::FieldType Record::toFieldType(string name)
{
	 if (name == "text") {
		  return FieldType::TEXT;
	 }
	 else if (name == "u_integer") {
		  return FieldType::U_INTEGER;
	 }
	 else if (name == "float") {
		  return FieldType::FLOAT;
	 }
	 else {
		  return FieldType();
	 }
}

string Record::fieldTypeToString(FieldType type)
{
	 if (type == FieldType::TEXT) {
		  return "text";
	 }
	 else if (type == FieldType::U_INTEGER) {
		  return "u_integer";
	 }
	 else if (type == FieldType::FLOAT) {
		  return "float";
	 }
	 else {
		  return string();
	 }
}

Record::FieldType Record::getKeyType()
{
	 return getFieldType(0);
}

int Record::getRecordSize()
{
	 int size = 0;
	 for (int i = 0; i < fieldInfo.size(); i++) {
		  size += get<1>(fieldInfo[i]);
	 }
	 return size;
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

string Record::getField(int index)
{
	 return fields[index];
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
