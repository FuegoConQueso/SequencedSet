#include "SequencedSet.h"

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
	header = Header("Storage.txt", "Doesn't Read in File Name Yet", hfile.makeTuples(), this);
	activeHeader = &header;
}

void SequencedSet::populate(ifstream& inputFile) {
	 ofstream outputFile(header.getFileName(), ofstream::trunc | ofstream::out);
	 outputFile << HeaderBuffer::pack(header);
	 int recordCount = 0;
	 int blockCount = 0;
	 index = Index();
	 Block tempBlock;
	 vector<Record> tempRecords = vector<Record>();
	 string etc;
	 //deal with garbage
	 getline(inputFile, etc);
	 getline(inputFile, etc);
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
	 outputFile.close();
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

