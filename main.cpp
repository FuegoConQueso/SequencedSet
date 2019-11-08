#include <string>
#include <iostream>
#include <vector>
#include "rbuffer1.h"

int main()
{
	 //set up the record sizes
	 vector<tuple<string, int, Record::FieldType>> fieldInfos = vector<tuple<string, int, Record::FieldType>>();
	 fieldInfos.push_back(make_tuple<string, int, Record::FieldType>("ZIP", 6, Record::FieldType::U_INTEGER));
	 fieldInfos.push_back(make_tuple<string, int, Record::FieldType>("Place", 31, Record::FieldType::TEXT));
	 fieldInfos.push_back(make_tuple<string, int, Record::FieldType>("State", 2, Record::FieldType::TEXT));
	 fieldInfos.push_back(make_tuple<string, int, Record::FieldType>("County", 36, Record::FieldType::TEXT));
	 fieldInfos.push_back(make_tuple<string, int, Record::FieldType>("Latitude", 9, Record::FieldType::FLOAT));
	 fieldInfos.push_back(make_tuple<string, int, Record::FieldType>("Longitude", 10, Record::FieldType::FLOAT));
	 Record::setFieldInfo(fieldInfos);

	 //create the record buffer, test said buffer
	 vector<string> rec;
	 recordBuffer r0;
	 string rec2;
	 rec.push_back("1001");
	 rec.push_back("Agawam");
	 rec.push_back("NY");
	 rec.push_back("Hampden");
	 rec.push_back("42.0702");
	 rec.push_back("-72.6227");
	 rec2 = r0.pack(rec);
	 cout << rec2;
	 return 0;
}