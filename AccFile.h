#pragma once
#include <fstream>
#include "Account.h"
#include "DepAcc.h"
#include "SavAcc.h"
#include "exceptio.h"

class AccFile
{
private:
	std::fstream f;
	std::string name; // Filename of primary file

public:
	AccFile(const std::string s) throw(OpenError);
	~AccFile() { f.close(); }

	long append(Account& acc) throw(WriteError);
	Account* retrieve(long pos) throw(ReadError);
	void display() throw(ReadError);
};