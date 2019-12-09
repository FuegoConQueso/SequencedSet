#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Record.h"
using namespace std;


class recordBuffer
{
public:
	 static string pack(Record f1);
	 static vector<string> unpack(string record);
};

