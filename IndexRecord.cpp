#include "IndexRecord.h"

/** The constructor of the Index Record class.
@param key: the key that the record is to contain
@param blockNum: the block number of the index record object
@pre: none
@post: an Index Record object with key and block number initialized
*/
IndexRecord::IndexRecord(string key, int blockNum)
{
	 this->key = key;
	 this->blockNum = blockNum;

}
