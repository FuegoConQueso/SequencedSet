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

/*Returns the fields of the Record object
*/
vector<string> Record::pack()
{
	 return fields;
}

/* Returns the field at a given index of the record object
@param index: the index of the field to be retrieved
*/
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
