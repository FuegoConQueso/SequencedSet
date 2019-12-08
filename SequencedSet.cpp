#include "SequencedSet.h"
#include <string>

Header* SequencedSet::activeHeader;
SequencedSet* SequencedSet::activeSeqSet;

SequencedSet::SequencedSet(){
}

SequencedSet::~SequencedSet(){
}

/** Converts an input file into our file storage format, saving it as a storage file and index.

@param inputFileName The name of the file you want to input. Must be located in the SequencedSet directory.
@param fileName The name of the file that will be used to store the SequencedSet data. Defaults to "Storage.txt"
@param indexFileName The name of the file that will be used to store the index. Defaults to "Index.txt"
*/
void SequencedSet::populate(string inputFileName, string fileName, string indexFileName) {
	 ifstream inputFile = ifstream(inputFileName);
	 //initialize filemanager
	 fileManager = FileManager();
	 fileManager.create(fileName, indexFileName);
	 //header loading
	 InputFileHeader hfile;
	 hfile.readHeader(inputFile);
	 header = Header(fileName, hfile.getFileName(), hfile.makeTuples(), 0, -1);
	 activeSeqSet = this;
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
	 //Create empty block at current avail;
	 vector<Record> lastBlockRecords;
	 Block lastBlock(header.getStartAvail(), header.getStartAvail() + 1, lastBlockRecords);
	 fileManager.writeBlock(BlockBuffer::pack(lastBlock.pack()), header.getStartAvail());
}

void SequencedSet::load(string fileName, string indexFileName)
{
	 //start filemanager
	 fileManager = FileManager();
	 fileManager.open(fileName, indexFileName);
	 //load header object
	 header = fileManager.readHeader();
	 activeSeqSet = this;
	 //load index file
	 index = fileManager.readIndexFile();
}
/** Searches the index for the rbn (relative block number) of a block that
should contain a record with the primary key (if such a record exists).

@param primaryKey The primary key of the record we are searching for.

@returns the rbn of the block that could contain that primary key, or -1 if not found.
*/
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

/** Searches a block for a record.

@param[in] rbn The rbn (relative block number) of the block we want to search.
@param[in] primaryKey The key to search for.
@param[out] rrn The relative record number of the record that is returned.

@returns The record, if found.

@throws RecordNotFoundException() if no record matching the search key is found.
*/
Record SequencedSet::searchForRecord(int rbn, string primaryKey, int& rrn)
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
		{
			rrn = midpoint;
			return block.getRecord(midpoint);
		}
		else if (compnum == -1)
		  r = midpoint - 1;
		else
		  l = midpoint + 1;
	}
	//if it isn't found
	if (compnum == 1) {
		 midpoint += 1;
	}
	throw new RecordNotFoundException(midpoint, "Thrown in searchForRecord()");
}

int SequencedSet::searchForInsertion(Block toSearch, string keyToInsert)
{
	int insertionPoint = 0;
	bool inserted = false;
	while ((!inserted) && (insertionPoint < toSearch.recordCount()))
	{
		Record curRec = toSearch.getRecord(insertionPoint);
		int compareVal = Header::compare(curRec.getField(0), keyToInsert, header.getFieldType(0));
		if (compareVal == 0) {
			 throw new DuplicateRecordException(insertionPoint, "Thrown in searchForInsertion()");
		}
		if (compareVal == 1) {
			 break;
		}
		insertionPoint++;
	}
	return insertionPoint;
}

void SequencedSet::add(Record rec)
{
	string primaryKey = rec.getField(0);
	int blockNum = searchForBlock(primaryKey);
	Block insertionBlock = getBlockFromFile(blockNum);
	bool duplicate = false;
	 try {
		  int insertPoint = searchForInsertion(insertionBlock, primaryKey);
		  insertionBlock.insertRecord(insertPoint, rec);
		  cout << primaryKey << " inserted into block " << blockNum << " at position " << insertPoint << endl;
		  fileManager.writeBlock(BlockBuffer::pack(insertionBlock.pack()), blockNum);
		  if (insertionBlock.recordCount() > header.getBlockCapacity())
		  {
				split(insertionBlock);
		  }

	 }
	 catch (DuplicateRecordException* e) {
		  cout << e->to_string() << endl;
	 }
	// These two lines essentially "save" the changes made to the file by closing the file and reopening.
	fileManager.closeFile();
	fileManager.open(fileManager.getFileFileName(), fileManager.getIndexFileName()); 
}

void SequencedSet::deleteRecord(string primaryKey)
{
	 try {
		  int recordBlock = searchForBlock(primaryKey);

		  int rrn = -1;
		  if (recordBlock == -1) {
				throw new RecordNotFoundException(-1, "searchForBlock() failed in deleteRecord()");
		  }

		  Record foundRecord = searchForRecord(recordBlock, primaryKey, rrn);

		  Block blk = fileManager.getBlock(recordBlock);
	 }
	 catch (RecordNotFoundException* e) {
		  cout << "Record not found." << endl;
	 }
}

void SequencedSet::split(Block blk)
{
	int newBlockPosition = header.getStartAvail();
	int newBlockNext = getBlockFromFile(header.getStartAvail()).getBlockNextNumber();
	vector<Record> newRecords;
	vector<Record> newRecords2;
	for (int i = 0; i < blk.recordCount(); i++)
	{
		if (i <= blk.recordCount() / 2)
		{
			newRecords.push_back(blk.getRecord(i));
		}
		else
			newRecords2.push_back(blk.getRecord(i));
	}
	Block newBlock(blk.getBlockNumber(), blk.getBlockNextNumber(), newRecords);
	Block newBlock2(newBlockPosition, newBlockNext, newRecords2);
	fileManager.writeBlock(BlockBuffer::pack(newBlock.pack()), newBlock.getBlockNumber());
	fileManager.writeBlock(BlockBuffer::pack(newBlock2.pack()), newBlock2.getBlockNumber());
	header.setStartAvail(newBlock2.getBlockNextNumber());
	index.addIndex(newBlock.getRecord(newBlock.recordCount() - 1).getField(0), newBlock.getBlockNumber());
	index.addIndex(newBlock.getRecord(newBlock2.recordCount() - 1).getField(0), newBlock2.getBlockNumber());
	fileManager.writeHeader(&header);
	fileManager.writeIndexFile(&index);
}

void SequencedSet::updateHeader()
{
	 activeSeqSet->fileManager.writeHeader(&(activeSeqSet->header));
}

Header* SequencedSet::sHeader()
{
	 return &(activeSeqSet->header);
}

SequencedSet* SequencedSet::SeqSet()
{
	 return activeSeqSet;
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
	 return fileManager.getBlock(blkNum);
}

Record SequencedSet::findMost(vector<Record> vecToSearch, int fieldNumber)
{
	int highest = 0;
	string comp1, comp2;
	for (int i = 1; i < vecToSearch.size(); i++)
	{
		comp1 = vecToSearch[highest].getField(fieldNumber);;
		comp2 = vecToSearch[i].getField(fieldNumber);
		Header::compare(comp1, comp2, header.getFieldType(fieldNumber));
		if (comp2 > comp1)
			highest = i;
	}
	return vecToSearch[highest];
}

Record SequencedSet::findLeast(vector<Record> vecToSearch, int fieldNumber)
{
	int lowest = 0;
	string comp1, comp2;
	for (int i = 1; i < vecToSearch.size(); i++)
	{
		comp1 = vecToSearch[lowest].getField(fieldNumber);
		comp2 = vecToSearch[i].getField(fieldNumber);
		Header::compare(comp1, comp2, header.getFieldType(fieldNumber));
		if (comp2 < comp1)
			lowest = i;
	}
	return vecToSearch[lowest];
}
Record SequencedSet::specifyRecord()
{
	vector<string> customFields;
	string currentString;
	for (int i = 0; i < header.getNumOfFields(); i++)
	{
		cout << "Enter " << header.getFieldName(i) << ": ";
		cin >> currentString;
		customFields.push_back(currentString);
	}
	return Record(customFields);
}

