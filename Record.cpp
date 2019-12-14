#include "Record.h"
#include "SequencedSet.h"

/** The default constructor of the Record class.
*/
Record::Record()
{
	 fields = vector<string>();
}

/** The constructor of the Record object which intitializes the fields vector
*/
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
@pre: an integer index
@post: a string with the field located at the index
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
