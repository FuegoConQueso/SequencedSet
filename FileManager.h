#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class SequencedSet;

class FileManager
{
	protected:
		fstream filefile;
		string indexfilename;
	public:
		void create(string filename, string indexfilename);
		//void open(string filname, indfilname); //string
		fstream getFileIndex();
		string getBlock(int blockNumber);
};
