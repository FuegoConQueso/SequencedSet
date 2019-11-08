#include <iostream>
#include <fstream> 
#include "InputFileHeader.h"
using namespace std;

SequencedSet::SequencedSet(){
}

SequencedSet::~SequencedSet(){
}

void SequencedSet::create(ifstream & inputFile){
	InputFileHeader hfile;
	hfile.readHeader(inputFile);
}

