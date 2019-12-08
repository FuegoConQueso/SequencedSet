#pragma once
#include <exception>
#include <string>

using namespace std;

class DuplicateRecordException :	 public std::exception
{
	 int duplicateLocation;
	 string _message;

public:
	 DuplicateRecordException(int duplicateLocation, string message = "") {
		  this->duplicateLocation = duplicateLocation;
		  this->_message = message;
	 }

	 int location() { return duplicateLocation; }
	 string message() { return _message; }

	 string to_string() {
		  return "DuplicateRecordException: " + _message + " (duplicate at rrn: " + std::to_string(duplicateLocation) + ")";
	 }
};

class RecordNotFoundException : public std::exception
{
	 int _lastSearchLocation;
	 string _message;

public:
	 RecordNotFoundException(int lastSearchLocation, string message = "") {
		  this->_lastSearchLocation = lastSearchLocation;
		  this->_message = message;
	 }

	 int lastSearchLocation() { return _lastSearchLocation; }
	 string message() { return _message; }

	 string to_string() {
		  string output = "RecordNotFoundException: " + _message;
		  if (_lastSearchLocation != -1) {
				output += " (insertion location: " + std::to_string(_lastSearchLocation) + ")";
		  }
		  return output;
	 }
};