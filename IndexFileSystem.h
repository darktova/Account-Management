#pragma once
#include "AccFile.h"
#include "IndexFile.h"

class IndexFileSystem : 
	public AccFile, public IndexFile
{
private:
	std::string name;

public:
	IndexFileSystem(const std::string);

	void insert(Account& acc);
	Account* retrieve(long key);
};

