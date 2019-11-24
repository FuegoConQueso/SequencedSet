#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <tuple>
#include <sstream>
#include "Header.h"

using namespace std;

class HeaderBuffer
{
public:
	 static string pack(Header& header);

	 static Header unpack(fstream& mainFile, string fileName);
};

