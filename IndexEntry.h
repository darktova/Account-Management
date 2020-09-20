#pragma once
#include <iostream>
#include <fstream>

class IndexEntry
{
private:
	long key; // Key
	long recNr; // Offset

public:
	IndexEntry();
	IndexEntry(long, long);
	long getKey() const;
	long getPos() const;
	void setKey(long);
	void setPos(long);
	// Access methods ... and:
	int recordSize() const;
	std::fstream& write(std::fstream& ind) const;
	std::fstream& read(std::fstream& ind);
	std::fstream& write_at(std::fstream& ind, long pos) const;
	std::fstream& read_at(std::fstream& ind, long pos);
};
