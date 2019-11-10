#ifndef SEQUENCED_SET_H
#define SEQUENCED_SET_H
#include <iostream>
#include <fstream>
using namespace std;

class SequencedSet{
	private:
		 int blockCapacity;
		 int blockInitialSize;
		int headerSize;
	public:
		SequencedSet();
		~SequencedSet();
		void create(ifstream& inputFile);
		void populate(ifstream& inputFile);

};

#endif
