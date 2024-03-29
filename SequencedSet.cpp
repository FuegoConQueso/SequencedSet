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
@pre: A set of input file names
@post: A set of files in our file storage format.
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
	 //write the header to the file
	 fileManager.writeHeader(&header);
	 //create the Index
	 index = Index();
	 index.Create();
	 //variables used for the loop
	 int recordCount = 0;
	 int blockCount = -1;
	 int prevBlock = -1;
	 int blockMinSize = header.getBlockMinSize();
	 int blockCapacity = header.getBlockCapacity();
	 int blockInitialSize = blockMinSize + (blockCapacity - blockMinSize) / 2;
	 Block tempBlock;
	 Block tempPrevBlock;
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
				if (blockCount == -1)
				{
					 blockCount = header.getStartBlock();
					 tempPrevBlock = Block(blockCount, -1, -1, tempRecords);
					 prevBlock = blockCount;
					 fileManager.createSpace(blockCount);
					 header.setStartBlock(blockCount + 1, false);
					 recordCount = 0;
					 tempRecords.clear();
				}
				else {
					 //create a block, which will be block number blockCount, with a pointer to Block blockCount+1
					 blockCount = header.getStartBlock();
					 tempPrevBlock.setNextBlockNumber(blockCount);
					 fileManager.writeBlock(BlockBuffer::pack(&tempPrevBlock), prevBlock);
					 fileManager.createSpace(blockCount);
					 header.setStartBlock(blockCount + 1, false);
					 tempBlock = Block(blockCount, -1, prevBlock, tempRecords);
					 prevBlock = blockCount;
					 // create the index entry
					 string indexKey = tempPrevBlock.getLastKey();
					 int indexBlockNum = tempPrevBlock.getBlockNumber();
					 index.addIndex(indexKey, indexBlockNum);
					 tempPrevBlock = tempBlock;
					 //reset recordCount
					 recordCount = 0;
					 tempRecords.clear();
				}
		  }
	 }
	 //if additional records, create final block
	 if (recordCount > 0) {
		  blockCount = header.getStartBlock();
		  tempPrevBlock.setNextBlockNumber(blockCount);
		  fileManager.writeBlock(BlockBuffer::pack(&tempPrevBlock), tempPrevBlock.getBlockNumber());
		  fileManager.createSpace(blockCount);
		  header.setStartBlock(blockCount + 1, false);
		  tempBlock = Block(blockCount, -1, prevBlock, tempRecords);
		  // create the index entry
		  string indexKey = tempPrevBlock.getLastKey();
		  int indexBlockNum = tempPrevBlock.getBlockNumber();
		  index.addIndex(indexKey, indexBlockNum);
		  tempPrevBlock = tempBlock;
		  prevBlock = blockCount;
	 }

	 fileManager.writeBlock(BlockBuffer::pack(&tempPrevBlock), tempPrevBlock.getBlockNumber());
	 // create the index entry
	 string indexKey = tempPrevBlock.getLastKey();
	 int indexBlockNum = tempPrevBlock.getBlockNumber();
	 index.addIndex(indexKey, indexBlockNum);
	 header.setStartBlock(0, false);
	 fileManager.writeHeader(&header);
	 fileManager.writeIndexFile(&index);
}

/** Opens the storage file and the index file
@param fileName: name of the storage file
@param indexFileName: name of the index file
@pre: The storage file namea nd index file name
@post: The index and storage files are opened for writing
*/
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
@param[in] primaryKey The primary key of the record we are searching for.
@param[out] indexLocation The index number for the block.
@pre: A prinary key and an index location
@post: the rbn of the block that could contain that primary key.
@throws BeyondLastBlockException if key is greater than the last index key.
*/
int SequencedSet::searchForBlock(string primaryKey, int& indexLocation)
{

	cout << "Searching for " << primaryKey << "...\n"; string compstring;
	int midpoint = -1, r, l, compnum = 0;
	r = index.size() - 1;
	l = 0;
	while (l <= r)
	{
		 midpoint = l + (r - l) / 2;
		 compstring.clear();
		 compstring = index.getIndex(midpoint).key;
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
	if (midpoint == index.size()) {
		 throw BeyondLastBlockException("Thrown in SearchForBlock()");
	}
	indexLocation = midpoint;
	return index.getIndex(midpoint).blockNum;
	
}

/** Searches the index for the rbn (relative block number) of a block that
should contain a record with the primary key (if such a record exists).
@param primaryKey The primary key of the record we are searching for.
@pre: A primary key string
@post: the rbn of the block that could contain that primary key.

@throws BeyondLastBlockException if key is greater than the last index key.
*/
int SequencedSet::searchForBlock(string primaryKey) {
	 int throwaway = -1;
	 return SequencedSet::searchForBlock(primaryKey, throwaway);
}

/** Searches a block for a record.
@param[in] rbn The rbn (relative block number) of the block we want to search.
@param[in] primaryKey The key to search for.
@param[out] rrn The relative record number of the record that is returned.
@pre: A block pointer and a primary key string
@post: The record, if found.

@throws RecordNotFoundException() if no record matching the search key is found.
*/
Record SequencedSet::searchRecordInBlock(Block* blk, string primaryKey, int& rrn) {

	 string compstring;
	 int midpoint, r, l, compnum;
	 r = blk->recordCount() - 1;
	 l = 0;
	 while (l <= r)
	 {
		  midpoint = l + (r - l) / 2;
		  compstring.clear();
		  compstring = blk->getRecord(midpoint).getField(0);
		  compnum = header.compare(primaryKey, compstring, header.getKeyType());
		  cout << "Compstring: " << compstring << endl;
		  cout << "CompNum: " << compnum << endl;
		  cout << "primaryKey: " << primaryKey << endl;
		  if (compnum == 0)
		  {
				rrn = midpoint;
				return blk->getRecord(midpoint);
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
	 throw new RecordNotFoundException(midpoint, "Thrown in searchRecordInBlock()");
}

/** Opens a block and searches it for a record.
@param[in] rbn The rbn (relative block number) of the block we want to search.
@param[in] primaryKey The key to search for.
@param[out] rrn The relative record number of the record that is returned.
@pre: A relative block number and a primary key string with a relative record number
@post: The record, if found.
@throws RecordNotFoundException() if no record matching the search key is found.
*/
Record SequencedSet::searchForRecord(int rbn, string primaryKey, int& rrn)
{
	Block block;
	block = fileManager.getBlock(rbn);
	return searchRecordInBlock(&block, primaryKey, rrn);
}

/** Searches a block for an insertion point for an input key
@param toSearch: the block to be searched
@param keyToInsert: the key to be inserted into the block
@pre: none
@post: An integer returning the insertion point of the key into the block
*/
int SequencedSet::searchForInsertion(Block* toSearch, string keyToInsert)
{
	int insertionPoint = 0;
	bool inserted = false;
	while ((!inserted) && (insertionPoint < toSearch->recordCount()))
	{
		Record curRec = toSearch->getRecord(insertionPoint);
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

/* Adds a record to the sequenced set in the appropriate block, in the appropriate position
Merges and splits blocks as necessary
@param rec: the record to be inserted into the sequenced set
@pre: a Record to be added to the sequenced set
@post: The record is added, if possible, to the Sequenced set
@throws duplicateRecordException if a record with the same primary key is already in the sequenced set
*/
void SequencedSet::add(Record rec)
{
	 string primaryKey = rec.getField(0);
	 int indexNum = -1;
	 int blockNum = -1;
	 Block insertionBlock;
	 try {
		  blockNum = searchForBlock(primaryKey, indexNum);
		  insertionBlock = getBlockFromFile(blockNum);
	 }
	 catch (BeyondLastBlockException * e) {
		  indexNum = index.size() - 1;
		  blockNum = index.getLastIndex().blockNum;
		  insertionBlock = getBlockFromFile(blockNum);
	 }
	 string startKey = insertionBlock.getLastKey();
	 try {
		  int insertPoint = searchForInsertion(&insertionBlock, primaryKey);
		  insertionBlock.insertRecord(insertPoint, rec);
		  index.updateIndex(startKey, insertionBlock.getLastKey());
		  cout << primaryKey << " inserted into block " << blockNum << " at position " << insertPoint << endl;

		  if (insertionBlock.recordCount() > header.getBlockCapacity())
		  {
				//attempts to redistribute; if it can not, it calls the split function
				redistributeAdd(&insertionBlock, indexNum);
		  }
		  else {
				fileManager.writeBlock(BlockBuffer::pack(&insertionBlock), blockNum);
		  }
		  fileManager.writeIndexFile(&index);
	 }
	 catch (DuplicateRecordException* e) {
		  cout << e->to_string() << endl;
	 }
	// These two lines essentially "save" the changes made to the file by closing the file and reopening.
}

/** Deletes a primary key from the sequenced set if the key is found.  Merges and redistributes blocks as necessary
@param primaryKey: the primaryKey to be removed
@pre: a primary key string
@post: The record containing that primary key is deleted from the sequenced set
@throws RecordNotFoundException if there is no record with the primary key argument to delete
*/
void SequencedSet::deleteRecord(string primaryKey)
{
	 try {
		  int blockNum;
		  int indexNum;
		  try {
				blockNum = searchForBlock(primaryKey, indexNum)-1;
		  }
		  catch (BeyondLastBlockException * e) {
				throw new RecordNotFoundException(-1, "searchForBlock() failed in deleteRecord()");
		  }
		  int rrn = -1;
		  Block recordBlock = fileManager.getBlock(blockNum);
		  string prevKey = recordBlock.getLastKey();
		  searchRecordInBlock(&recordBlock, primaryKey, rrn);
		  recordBlock.deleteRecord(rrn);
		  index.updateIndex(prevKey, recordBlock.getLastKey());
		  if (recordBlock.recordCount() < header.getBlockMinSize()) {
				redistributeRemove(&recordBlock, indexNum);
		  }
		  else {
				fileManager.writeBlock(BlockBuffer::pack(&recordBlock), recordBlock.getBlockNumber());
		  }
		  
	 }
	 catch (RecordNotFoundException* e) {
		  cout << "Record not found." << endl;
	 }
}

/** Attempts to redistribute a block at a given index number, if it fails, it calls merge
@param blk: the block whose contents are to be redistributed
@param indexNum: the index number of the block whose contents are to be redistributed
@pre: a block pointer and an index number
@post: the elements of the block at the given index number are redistributed.
*/
void SequencedSet::redistributeRemove(Block* blk, int indexNum) {
	 bool resolved = false;
	 //last record's key in the overfull block
	 string lastKey = index.getIndex(indexNum).key;
	 // get the index entries
	 vector<IndexRecord> siblings = index.getSiblings(indexNum);
	 //load blocks 1 at a time.
	 vector<Block> loadedSiblings = vector<Block>();
	 for (int i = 0; i < siblings.size(); i++) {
		  int blockNum = siblings[i].blockNum;
		  loadedSiblings.push_back(fileManager.getBlock(blockNum));
		  int siblingSize = loadedSiblings[i].recordCount();
		  //if there's room in this sibling
		  if (siblingSize > header.getBlockMinSize()) {

				//if this sibling comes before the block
				if (header.compare(siblings[i].key, lastKey, header.getKeyType()) == -1) {
					 //save the index key of this block
					 string prevKey = loadedSiblings[i].getLastKey();
					 //move the last record of sibling to the start of this block
					 blk->insertRecord(0, loadedSiblings[i].pop_last());
					 //update index
					 index.updateIndex(prevKey, loadedSiblings[i].getLastKey());
					 //update sibling block in file
					 fileManager.writeBlock(BlockBuffer::pack(&loadedSiblings[i]), loadedSiblings[i].getBlockNumber());
				}

				//if this sibling comes after the block
				else {
					 //move the first record of sibling to the end of this block
					 blk->pushRecord(loadedSiblings[i].pop_first());
					 //update index
					 index.updateIndex(lastKey, blk->getLastKey());
					 //update sibling block in file
					 fileManager.writeBlock(BlockBuffer::pack(&loadedSiblings[i]), loadedSiblings[i].getBlockNumber());
				}

				//update blk block in file
				fileManager.writeBlock(BlockBuffer::pack(blk), blk->getBlockNumber());
				resolved = true;
				break;
		  }
	 }
	 if (!resolved) {
		  // in this case, all siblings are full (or there are no siblings). Split this block
		  // (sibling passed to enable conversion to B+ Tree later)
		  merge(blk, &loadedSiblings[0]);
	 }
}

/** Examines the siblings of the current block to see if redistribution is possible. If it is, redistribute, if it isn't call 
a split function.
@param blk: the block whose records are to be redistributed
@param indexNum: the index number of the block
@pre: a block pointer and an index number
@post: the records of the blocks are redistributed 
*/
void SequencedSet::redistributeAdd(Block* blk, int indexNum) {
	 bool resolved = false;
	 //last record's key in the overfull block
	 string lastKey = blk->getLastKey();
	 // get the index entries
	 vector<IndexRecord> siblings = index.getSiblings(indexNum);
	 //load blocks 1 at a time.
	 vector<Block> loadedSiblings = vector<Block>();
	 for (int i = 0; i < siblings.size(); i++) {
		  int blockNum = siblings[i].blockNum;
		  loadedSiblings.push_back(fileManager.getBlock(blockNum));
		  int siblingSize = loadedSiblings[i].recordCount();
		  //if there's room in this sibling
		  if (siblingSize < header.getBlockCapacity()) {

				//if this sibling comes before the block
				if (header.compare(siblings[i].key, lastKey, header.getKeyType()) == -1) {
					 //save the index key of this block
					 string prevKey = loadedSiblings[i].getLastKey();
					 //move the first record of blk to the end of this sibling
					 loadedSiblings[i].pushRecord(blk->pop_first());
					 //update index
					 index.updateIndex(prevKey, loadedSiblings[i].getLastKey());
					 //update sibling block in file
					 fileManager.writeBlock(BlockBuffer::pack(&loadedSiblings[i]), loadedSiblings[i].getBlockNumber());
				}

				//if this sibling comes after the block
				else {
					 //move the last record of block to the start of this sibling
					 loadedSiblings[i].insertRecord(0, blk->pop_last());
					 //update index
					 index.updateIndex(lastKey, blk->getLastKey());
					 //update sibling block in file
					 fileManager.writeBlock(BlockBuffer::pack(&loadedSiblings[i]), loadedSiblings[i].getBlockNumber());
				}

				//update blk block in file
				fileManager.writeBlock(BlockBuffer::pack(blk), blk->getBlockNumber());
				resolved = true;
				break;
		  }
	 }
	 if (!resolved) {
		  // in this case, all siblings are full (or there are no siblings). Split this block
		  // (sibling passed to enable conversion to B+ Tree later)
		  split(blk, &loadedSiblings[0]);
	 }
}

/** Splits the contents of a block amongst itself and it's sibling
@param blk: the block to be split
@param sibling: the sibling of the block to be split
@pre: A pointer to a block and a pointer to it's sibling
@post: the contents of the block are split between itselfa nd it's sibling
*/
void SequencedSet::split(Block* blk, Block* sibling)
{
	 bool availAtEnd = false;
	 string prevKey = blk->getLastKey();
	 int newBlockPosition = header.getStartAvail();
	 if (newBlockPosition == -1) {
		  availAtEnd = true;
		  newBlockPosition = index.size();
	 }
	 else {
		  header.setStartAvail(getBlockFromFile(header.getStartAvail()).getBlockNextNumber());
	 }
	 vector<Record> newRecords;
	 vector<Record> newRecords2;
	 for (int i = 0; i < blk->recordCount(); i++)
	 {
		  if (i <= blk->recordCount() / 2)
		  {
				newRecords.push_back(blk->getRecord(i));
		  }
		  else
				newRecords2.push_back(blk->getRecord(i));
	 }
	 //create new blocks
	 Block newBlock(newBlockPosition, blk->getBlockNextNumber(), blk->getBlockNumber(), newRecords2);
	 blk = new Block(blk->getBlockNumber(), newBlockPosition, blk->getPrevBlockNumber(), newRecords);
	 //write blocks
	 fileManager.writeBlock(BlockBuffer::pack(blk), blk->getBlockNumber());
	 fileManager.writeBlock(BlockBuffer::pack(&newBlock), newBlock.getBlockNumber());
	 //update index
	 index.updateIndex(prevKey, blk->getLastKey());
	 index.addIndex(newBlock.getLastKey(), newBlock.getBlockNumber());
	 //write changes to header
	 fileManager.writeHeader(&header);
}

/** Merges the contents of a block and it's sibling
@param blk: the block to be merged with it's sibling
@param sibling: the sibling that the block is to be merged with
@pre: two pointers to blocks
@post: the contents of the two blocks are merged into one block
*/
void SequencedSet::merge(Block* blk, Block* sibling) {
	 int compNum = Header::compare(blk->getLastKey(), sibling->getLastKey(), header.getKeyType());
	 //if blk comes before sibling
	 if (compNum == -1) {
		  string prevKey = blk->getLastKey();
		  index.deleteIndex(sibling->getLastKey());
		  while (sibling->recordCount() > 0) {
				blk->pushRecord(sibling->pop_first());
		  }
		  blk->setNextBlockNumber(sibling->getBlockNextNumber());
		  fileManager.writeBlock(BlockBuffer::pack(blk), blk->getBlockNumber());
		  fileManager.writeBlock(BlockBuffer::createAvail(sibling), sibling->getBlockNumber());
		  index.updateIndex(prevKey, blk->getLastKey());
	 }
	 //if sibling comes before blk
	 else {
		  string prevKey = sibling->getLastKey();
		  index.deleteIndex(blk->getLastKey());
		  while (blk->recordCount() > 0) {
				sibling->pushRecord(blk->pop_first());
		  }
		  sibling->setNextBlockNumber(blk->getBlockNextNumber());
		  fileManager.writeBlock(BlockBuffer::pack(sibling), sibling->getBlockNumber());
		  fileManager.writeBlock(BlockBuffer::createAvail(blk), blk->getBlockNumber());
		  index.updateIndex(prevKey, sibling->getLastKey());
	 }
}

/** Updates the header file with new information such as next block and avail list pointers
@pre: none
@post: the header file is updated
*/
void SequencedSet::updateHeader()
{
	 activeSeqSet->fileManager.writeHeader(&(activeSeqSet->header));
}

/* Returns a pointer to the header of the active sequenced set
@pre: none
@post: pointer to header of active sequenced set
*/
Header* SequencedSet::sHeader()
{
	 return &(activeSeqSet->header);
}

/* Returns the active sequenced set pointer
*/
SequencedSet* SequencedSet::SeqSet()
{
	 return activeSeqSet;
}

/** Populates a record with a string
@param line: the string used to populate the record
@pre: a line string
@post: A Record object with the contents of the string input
*/
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

/** Returns the vector of all records in the sequenced set whose fields with index fieldNum match the search string
@param toSearch: the string being searched for amongst field at index fieldNum
@param fieldNum: the index of the field being searched within the records
@pre: a search string and a field number
@post: a vector of records whose fields at the input field number index contain
the search string
*/
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

/** Gets a block object from the file manager using the block number
@param blkNum: the block number of the block to be retrieved from the file manager
@pre: a block number
@post: a Block object from the block number in the file
*/
Block SequencedSet::getBlockFromFile(int blkNum)
{
	 return fileManager.getBlock(blkNum);
}

/** Returns the record with the highest value of a given field in a vector of records
@param vecToSearch: the vector of records whose field value is to be searched
@param fieldNumber: the field number of the field that is getting compared between vectors
@pre: a vector of records and a field number
@post: the Record with the highest value of the indicated field number in the input vector of records
*/
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

/** Returns the record with the lowest value of a given field in a vector of records
@param vecToSearch: the vector of records whose field value is to be searched
@param fieldNumber: the field number of the field that is getting compared between vectors
@pre: a vector of records and a field number
@post: the Record with the lowest value of the indicated field number in the input vector of records*/
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

/* Returns a record whose fields are individually specified by a user
@pre: none
@post: A record specified by the user
*/
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

