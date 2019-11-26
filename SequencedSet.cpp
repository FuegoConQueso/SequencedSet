#include "SequencedSet.h"
#include <string>

Header* SequencedSet::activeHeader;

SequencedSet::SequencedSet(){
}

SequencedSet::~SequencedSet(){
}

void SequencedSet::populate(string inputFileName, string fileName, string indexFileName) {
	 ifstream inputFile = ifstream(inputFileName);
	 //initialize filemanager
	 fileManager = FileManager();
	 fileManager.create(fileName, indexFileName);
	 //header loading
	 InputFileHeader hfile;
	 hfile.readHeader(inputFile);
	 header = Header(fileName, hfile.getFileName(), hfile.makeTuples(), 0, -1);
	 activeHeader = &header;
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
	 int blockMinSize = header.getBlockMinSize();
	 int blockCapacity = header.getBlockCapacity();
	 int blockInitialSize = blockMinSize + (blockCapacity - blockMinSize) / 2;
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
	 //rewrites the header with the new Avail pointer
	 //TODO: change to Filemanager "update avail start" function call
	 fileManager.writeHeader(&header);
	 fileManager.writeIndexFile(&index);
}

void SequencedSet::load(string fileName, string indexFileName)
{
	 //start filemanager
	 fileManager = FileManager();
	 fileManager.open(fileName, indexFileName);
	 //load header object
	 header = fileManager.readHeader();
	 activeHeader = &header;
	 //load index file
	 index = fileManager.readIndexFile();
}

int SequencedSet::searchForBlock(string primaryKey)
{

	cout << "Searching for " << primaryKey << "...\n"; string compstring;
	int midpoint = -1, r, l, compnum = 0;
	r = index.size() - 1;
	l = 0;
	while (l <= r)
	{
		 midpoint = l + (r - l) / 2;
		 compstring.clear();
		 compstring = index.getIndex(midpoint).first;
		 compnum = header.compare(primaryKey, compstring, header.getKeyType());
		 if (compnum == 0)
			  return midpoint;
		 else if (compnum == -1)
			  r = midpoint - 1;
		 else
			  l = midpoint + 1;
	}
	if (compnum == 1) {
		 midpoint += 1;
	}
	return midpoint;
	
}

Record SequencedSet::searchForRecord(int rbn, string primaryKey)
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
		cout << "Compstring: " << compstring << endl;
		cout << "CompNum: " << compnum <<endl;
		cout << "primaryKey: " << primaryKey << endl;
		if (compnum == 0)
		  return block.getRecord(midpoint);
		else if (compnum == -1)
		  r = midpoint - 1;
		else
		  l = midpoint + 1;
	}
	return Record();
}

int SequencedSet::searchForInsertion(Block toSearch, string keyToInsert)
{
	int insertionPoint = 0;
	bool inserted = false;
	while ((!inserted) && (insertionPoint < toSearch.recordCount()))
	{
		Record curRec = toSearch.getRecord(insertionPoint);
		if (Header::compare(curRec.getField(0), keyToInsert, header.getFieldType(0)) == 1)
			break;
		insertionPoint++;
	}
	return insertionPoint;
}

void SequencedSet::add(string primaryKey)
{
	int blockNum = searchForBlock(primaryKey);
	Block insertionBlock = getBlockFromFile(blockNum);
	int insertPoint = searchForInsertion(insertionBlock, primaryKey);
	cout << primaryKey << " inserted into block " << blockNum << " at position " << insertPoint << endl;
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

vector<Record> SequencedSet::searchMatches(string toSearch, int fieldNum)
{
	vector<Record> matches;
	int matchNum;
	int startTrav;
	Block curBlock;
	Record currentRec;
	startTrav = header.getStartBlock();
	while (startTrav != header.getStartAvail())
	{
		curBlock = fileManager.getBlock(startTrav);
		string compRecStr;
		for (int recNum = 0; recNum < curBlock.recordCount(); recNum++)
		{
			currentRec = curBlock.getRecord(recNum);
			compRecStr = currentRec.getField(fieldNum);
			matchNum = Header::compare(compRecStr, toSearch, header.getFieldType(fieldNum));
			if (matchNum == 0)
				matches.push_back(currentRec);
			compRecStr.clear();
		}
		startTrav = curBlock.getBlockNextNumber();
	}
	return matches;
}
Block SequencedSet::getBlockFromFile(int blkNum)
{
	Block blk;
	ifstream iFile(fileManager.getFileFileName()); 
	cout << "In getBlockFromFile!\n";
	string rec = "";
	//Get rid of header in indexFile
	for (int i = 0; i < 10; i++) //Any way to get 11 from the program itself instead of magic number?
	{
		getline(iFile, rec);
	}
	for (int i = 0; i < blkNum; i++)
	{
		getline(iFile, rec);
	}
	string blockString;
	getline(iFile, blockString);
	BlockBuffer blbuff;
	blk = blbuff.unpack(blkNum, blockString);
	return blk;
}

