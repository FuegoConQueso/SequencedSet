#pragma once
#include "IndexRecord.h"
#include "Header.h"
#include <string>

using namespace std;

class IndexRecordBuffer
{
public:
	 static string pack(IndexRecord topack);
	 static IndexRecord unpack(string packed);

};

