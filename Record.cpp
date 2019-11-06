#include "Record.h"

Record::Record(vector<string> packedRecord)
{
	 unpack(packedRecord);
}

Record::Record(int zipCode, string placeName, string state, string county, float longitude, float latitude)
{
	 this->zipCode = zipCode;
	 this->placeName = placeName;
	 this->state = state;
	 this->county = county;
	 this->longitude = longitude;
	 this->latitude = latitude;
}

vector<string> Record::pack()
{
	 vector<string> packed = vector<string>();
	 packed.push_back(to_string(zipCode));
	 packed.push_back(placeName);
	 packed.push_back(state);
	 packed.push_back(county);
	 packed.push_back(to_string(longitude));
	 packed.push_back(to_string(latitude));
	 return packed;
}

void Record::unpack(vector<string> packedRecord)
{
	 zipCode = stoi(packedRecord[0]);
	 placeName = packedRecord[1];
	 state = packedRecord[2];
	 county = packedRecord[3];
	 longitude = stof(packedRecord[4]);
	 latitude = stof(packedRecord[5]);
}
