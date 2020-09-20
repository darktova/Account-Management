#include "IndexFile.h"

IndexFile::IndexFile(const std::string s) throw(OpenError)
{
	std::ios::openmode mode = std::ios::in | std::ios::out
		| std::ios::binary;
	index.open(s.c_str(), mode);

	if (!index) // If the file does not exist
	{
		index.clear();
		mode |= std::ios::trunc;
		index.open(s.c_str(), mode);
	
		if (!index)
			throw OpenError(s);
	}
	else
		name = s;
}

void IndexFile::insert(long k, long n)
	throw(ReadError, WriteError)
{
	IndexEntry entry;
	int size = entry.recordSize(); // Length of an
	// index entry.
	index.clear();
	index.seekg(0, std::ios::end);
	long nr = index.tellg(); // Get file length
	// 0, if file is empty.
	if (!index) throw ReadError(name);
	nr -= size; // Last entry.
	bool found = false;
	while (nr >= 0 && !found) // Search for position
	{ // to insert
		if (!entry.read_at(index, nr))
			throw ReadError(name);
		if (k < entry.getKey()) // To shift.
		{
			entry.write_at(index, nr + size);
			nr -= size;
		}
		else
		{
			found = true;
		}
	}
	entry.setKey(k); entry.setPos(n); // insert
	entry.write_at(index, nr + size);
	if (!index)
		throw WriteError(name);
}

long IndexFile::search(long key) throw(ReadError)
{
	IndexEntry entry;

	// Length of an index entry.
	int size = entry.recordSize();

	index.clear();
	index.seekg(0, std::ios::end);
	
	// Get file length 0, if file is empty
	long nr = index.tellg(); 
	if (!index) 
		throw ReadError(name);
	
	// Last entry
	nr -= size; 
	bool found = false;
	
	// Search for position to insert
	while (nr && !found)
	{
		// Exception Handling
		if (!entry.read_at(index, nr))
			throw ReadError(name);

		// Found
		if (key == entry.getKey())
			return key;
		else
			nr -= size;
	}
	return -1;
}

void IndexFile::retrieve(IndexEntry& entry, long pos) throw(ReadError)
{
	if (!index.good() || pos == -1)
		return;

	index.clear();
	entry.read_at(index, pos);
}