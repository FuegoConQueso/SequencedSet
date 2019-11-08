#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Record.h"
using namespace std;

class recordBuffer
{
protected:
	 string record;
	int something;
public:
	 recordBuffer() {};
	 string pack(vector<string> f1);
};