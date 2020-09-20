#pragma once
#include <fstream>
#include "exceptio.h"
#include "IndexEntry.h"
#include "Account.h"

class IndexFile
{
private:
	std::fstream index;
	std::string name; // Filename of the index

public:
	IndexFile(const std::string s) throw(OpenError);
	~IndexFile() { index.close(); }

	void insert(long key, long pos)
		throw(ReadError, WriteError);
	long search(long key) throw(ReadError);
	void retrieve(IndexEntry& entry, long pos)
		throw(ReadError);
	void display() throw(ReadError);
};

