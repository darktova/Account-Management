#include "IndexEntry.h"

IndexEntry::IndexEntry() {}

IndexEntry::IndexEntry(long k = 0L, long n = 0L)
	: key(k), recNr(n) {}

long IndexEntry::getKey() const { return key; }

long IndexEntry::getPos() const { return recNr; }

void IndexEntry::setKey(long k) { key = k; }

void IndexEntry::setPos(long n) { recNr = n; }

int IndexEntry::recordSize() const
{
	return sizeof(key) + sizeof(recNr);
}

std::fstream& IndexEntry::write(std::fstream& ind) const
{
	ind.write((char*)&key, sizeof(key));
	ind.write((char*)&recNr, sizeof(recNr));
	return ind;
}

std::fstream& IndexEntry::read(std::fstream& ind)
{
	ind.read((char*)&key, sizeof(key));
	ind.read((char*)&recNr, sizeof(recNr));
	return ind;
}

std::fstream& IndexEntry::write_at(std::fstream& ind, long pos)
const
{
	ind.seekp(pos);
	ind.write((char*)&key, sizeof(key));
	ind.write((char*)&recNr, sizeof(recNr));
	return ind;
}

std::fstream& IndexEntry::read_at(std::fstream& ind, long pos)
{
	ind.seekg(pos);
	ind.read((char*)&key, sizeof(key));
	ind.read((char*)&recNr, sizeof(recNr));
	return ind;
}

void IndexEntry::display() const
{
	std::cout << "Account Nr: " << key
		<< " Position: " << recNr << '\n';
}