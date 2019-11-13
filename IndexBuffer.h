#pragma once
#include "Index.h"
#include <string>
#include <vector>
#include "Record.h"
#include "BlockBuffer.h"

using namespace std;

class IndexBuffer
{
protected:
	 static const int blockNumSize = 6;
public:
	 static string pack(vector<pair<string, int>> indices, string fieldType);
};

