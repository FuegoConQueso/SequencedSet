#pragma once
#include <exception>
#include <string>

using namespace std;

class DuplicateException :	 public std::exception
{
	 int duplicateLocation;
	 string message;

public:
	 DuplicateException(int duplicateLocation, string message = "") {
		  this->duplicateLocation = duplicateLocation;
		  this->message = message;
	 }

	 int getLocation() { return duplicateLocation; }
	 string getMessage() { return message; }

	 string to_string() {
		  return "DuplicateException: " + message + " (duplicate at rrn: " + std::to_string(duplicateLocation) + ")";
	 }
};

