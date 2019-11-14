#pragma once
#include <iterator>
#include <iostream>

using namespace std;

class FileIterator : public iterator<forward_iterator_tag, string, ptrdiff_t, int, string>
{
	 int blockNum;

	 FileIterator(int x) :blockNum(x) {}
	 FileIterator(const FileIterator& other) : blockNum (other.blockNum) {}
	 FileIterator& operator++() { blockNum; return *this; }
	 FileIterator operator++(int) { FileIterator tmp(*this); operator++(); return tmp; }
	 bool operator==(const FileIterator& rhs) const { return blockNum == rhs.blockNum; }
	 bool operator!=(const FileIterator& rhs) const { return blockNum != rhs.blockNum; }
	 int& operator*() { return blockNum; }
};

