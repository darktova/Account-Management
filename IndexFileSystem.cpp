#include "IndexFileSystem.h"

IndexFileSystem::IndexFileSystem(const std::string s)
	: AccFile(s + ".prim"), IndexFile(s + ".ind")
{
	name = s;
}

void IndexFileSystem::insert(Account& acc)
{ 
	// No multiple entries:
	if (search(acc.getNr()) == -1)
	{
		long pos = append(acc); // Insert in primary file
		if (pos != -1) // Insert in
			IndexFile::insert(acc.getNr(), pos); // index file.
	}
}

Account* IndexFileSystem::retrieve(long key)
{
	long pos = search(key); // Get the record address:
	if (pos == -1) // Account number found?
		return NULL;
	else
	{
		IndexEntry entry; // Read the index entry:
		IndexFile::retrieve(entry, pos);
		// Read from primary file:
		return(AccFile::retrieve(entry.getPos()));
	}
}
