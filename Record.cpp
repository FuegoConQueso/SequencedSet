#include "Record.h"
#include "SequencedSet.h"

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
