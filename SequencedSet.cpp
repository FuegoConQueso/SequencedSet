#include "SequencedSet.h"
#include <string>

Header* SequencedSet::activeHeader;

SequencedSet::SequencedSet(){

	 blockCapacity = 4;
	 blockInitialSize = blockCapacity * 3 / 4;
}

SequencedSet::~SequencedSet(){
}

void SequencedSet::create(ifstream & inputFile){
	InputFileHeader hfile;
	hfile.readHeader(inputFile);
	header = Header("Storage.txt", "Doesn't Read in File Name Yet", hfile.makeTuples(), 0, -1);
	activeHeader = &header;
}

void SequencedSet::populate(ifstream& inputFile) {
	 //initialize filemanager
	 fileManager = FileManager();
	 fileManager.create("Storage.txt", "Index.txt");
	 //get the filestream to use for the main file
	 fstream& outputFile = fileManager.getFile();
	 //write the header to the file
	 outputFile << HeaderBuffer::pack(header);
	 //create the Index
	 index = Index();
	 index.Create();
	 //variables used for the loop
	 int recordCount = 0;
	 int blockCount = 0;
	 Block tempBlock;
	 vector<Record> tempRecords = vector<Record>();
	 //deal with extra newline character
	 string garbage;
	 getline(inputFile, garbage);
	 //loop to read remaining file
	 for (std::string line; getline(inputFile, line); )
	 {
		  //decompose into a record, create Record
		  tempRecords.push_back(populateRecord(line));
		  recordCount++;
		  //if we have reached the desired number of records in the block, create the block
		  if (recordCount == blockInitialSize) {
				//create a block, which will be block number blockCount, with a pointer to Block blockCount+1
				tempBlock = Block(blockCount, blockCount + 1, tempRecords);
				blockCount++;
				//pack the block for output
				string output = BlockBuffer::pack(tempBlock.pack());
				outputFile << output;
				// create the index entry for this block
				string indexKey = tempRecords.back().getField(0);
				int indexBlockNum = tempBlock.getBlockNumber();
				index.addIndex(indexKey, indexBlockNum);
				//reset recordCount
				recordCount = 0;
				tempRecords.clear();
		  }
	 }
	 //if additional records, create final block
	 if (recordCount > 0) {
		  tempBlock = Block(blockCount, blockCount + 1, tempRecords);
		  string output = BlockBuffer::pack(tempBlock.pack());
		  outputFile << output;
		  // create the index entry for this block
		  string indexKey = tempRecords.back().getField(0);
		  int indexBlockNum = tempBlock.getBlockNumber();
		  index.addIndex(indexKey, indexBlockNum);
		  blockCount++;
	 }
	 //update the header's Avail pointer
	 header.setStartAvail(blockCount);
	 //TODO: add Filemanager "update avail start" function call

	 fileManager.writeIndexFile(&index);
}

void SequencedSet::load(string fileName, string indexFileName)
{
	 fileManager = FileManager();
	 fileManager.open(fileName, indexFileName);
}

int SequencedSet::searchForBlock(string primaryKey, ifstream& indexFile)
{

	cout << "Searching for " << primaryKey << "...\n";
	int returnValue = -1;
	bool found = 0;
	string testString = "";
	string garbage = "";
	getline(indexFile, garbage); // get the garbage
	while (!indexFile.eof() && !found)
	{
		getline(indexFile, testString);
		stringstream line = stringstream(testString);
		string primKeyString;
		string blkNumString;
		line >> primKeyString;
		line >> blkNumString;
		Header::FieldType keyFieldType = header.getKeyType();
		if (Header::compare(primKeyString, primaryKey, keyFieldType) == 1 || Header::compare(primKeyString, primaryKey, keyFieldType) == 0)
		{
			returnValue = stoi(blkNumString);
			found = true;
		}
	}
	return returnValue;
}

int SequencedSet::searchForRecord(int rbn, string primaryKey)
{
	Block block;
	string compstring;
	block = fileManager.getBlock(rbn);
	int midpoint, r, l, compnum;
	r = block.recordCount() - 1;
	l = 0;
	while (l <= r)
	{
		midpoint = l + (r - l) / 2;
		compstring.clear();
		compstring = block.getRecord(midpoint).getField(0);
		compnum = header.compare(primaryKey, compstring, header.getKeyType());
			if (compnum == 0)
				return midpoint;
			else if (compnum == -1)
				r = midpoint - 1;
			else
				l = midpoint + 1;
	}
	return -1;
}

Header* SequencedSet::sHeader()
{
	 return activeHeader;
}

Record SequencedSet::populateRecord(string line) {
	 int position = 0;
	 int erasePos = 0;
	 vector<string> recFields2;
	 for (int i = 0; i < header.getNumOfFields(); i++)
	 {
		  string subs1, subs2;
		  int beginPos = 0;
		  subs1 = line.substr(position, header.getFieldSize(i));
		  //erase leading whitespace
		  erasePos = subs1.find_first_not_of(" ");
		  subs1.erase(beginPos, erasePos);
		  //erase trailing whitespace
		  erasePos = subs1.find_last_not_of(" ");
		  int fieSize = header.getFieldSize(i);
		  int endRead = erasePos - fieSize;
		  erasePos += 1;
		  subs1.erase(erasePos, endRead);
		  //add field to the record
		  recFields2.push_back(subs1);
		  //positions pointer for next call
		  position += header.getFieldSize(i);
	 }
	 return Record(recFields2);
}

