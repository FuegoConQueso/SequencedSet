#include "SqSetFileManager.h"

SqSetFileManager::SqSetFileManager(string fileName)
{
	 file = fstream(fileName);
}
