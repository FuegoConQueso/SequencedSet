#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "Header.h"
#include "IndexRecordBuffer.h"

using namespace std;

class IndexBuffer
{
public:
	 static string pack(vector<IndexRecord> indices, string fieldType);
	 static vector<IndexRecord> unpack(string packed, string fieldType);
};