#include "Header.h"
#include "InputFileHeader.h"
using namespace std;


Header::Header(string fileName, string name, vector<tuple<string, int, FieldType>> fieldInfo)
{

}

void Header::loadInput(InputFileHeader ifh)
{
    for (int i = 0; i < ifh.recordFields.get_size())
    {
        fieldInfo.push_back(make_tuple(getFieldName(i),getFieldName(i),getFieldName(i)));
    }
}
