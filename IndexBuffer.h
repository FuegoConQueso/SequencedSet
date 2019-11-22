#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "Header.h"

using namespace std;

class IndexBuffer
{
public:
	 static string pack(vector<pair<string, int>> indices, string fieldType);
	 static vector<pair<string, int>> unpack(string packed, string fieldType);
};

