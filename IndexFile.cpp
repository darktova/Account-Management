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

long IndexFile::search(long k) throw(ReadError)
{
	IndexEntry entry;

	/* Found indx.
	* Position markers.
	* Number of file records.
	* Length of an index entry (in bytes). */
	long key,
		mid, begin = 0,
		end; 
	int size = entry.recordSize();

	// Resetting file stream mode
	// Changing position of get ptr
	index.clear();
	index.seekg(0L, std::ios::end);

	// Number of records
	end = index.tellg() / size;

	// File stream failed
	if (!index)
		throw ReadError(name);

	// No records to serach
	if (end == 0)
		return -1;

	// Position of the last entry
	end -= 1;

	// Binary search
	while (begin < end)
	{
		mid = (begin + end + 1) / 2;

		// Read current entry
		entry.read_at(index, mid * size);
		
		// Is File stream ok?
		if (!index)
			throw ReadError(name);
	
		/* Compare two indx
		* found key and actual one */
		key = entry.getKey();

		/* Changing position of borders
		* left or right */
		if (k < key)
			end = mid - 1;
		else
			begin = mid;
	}

	// Reading remaining entry
	entry.read_at(index, begin * size);
	
	// Reading was ok?
	if (!index)
		throw ReadError(name);

	// Key found?
	return ((k == entry.getKey()) ? (begin * size) : -1);
}

void IndexFile::retrieve(IndexEntry& entry, long pos) throw(ReadError)
{
	// Resetting stream status mode
	index.clear();

	/* BAD:
	File stream  
	either position bad 
	or reading from file bad */
	if (!index.good() || pos == -1 
		|| !entry.read_at(index, pos))
		throw ReadError(name);
}

void IndexFile::display() throw(ReadError)
{
	long pos = 0L;

	while (!index.eof())
	{
		IndexEntry* entry = new IndexEntry();
		index.seekg(pos);

		if (!index)
			throw ReadError("IndexFile: Setting the get pointer");
	
		std::cout << "\nThe Index: " << pos << "\n";
		
		if (!entry->read(index))
			throw ReadError(name);
		
		entry->display();
		pos += entry->recordSize();
	}

	index.clear();
}