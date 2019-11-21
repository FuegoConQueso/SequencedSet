#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Record.h"
using namespace std;


static class recordBuffer
{
public:
	 static string pack(vector<string> f1, SequencedSet* parent);
	 static vector<string> unpack(string record, SequencedSet* parent);
};