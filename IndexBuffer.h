#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "Record.h"
#include "BlockBuffer.h"

using namespace std;

class IndexBuffer
{
protected:
	 static const int blockNumSize = 6;
public:
	 static string pack(vector<pair<string, int>> indices, string fieldType);
	 static vector<pair<string, int>> unpack(string packed, string fieldType);
};

