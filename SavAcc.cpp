#include "SavAcc.h"

SavAcc::SavAcc(const std::string s,
	unsigned long n,
	double bal,
	double ir)
	: Account(s, n, bal), interest(ir)
{ }

std::ostream& SavAcc::write(std::ostream& fs) const
{
    // TODO: insert return statement here
	return fs;
}

std::istream& SavAcc::read(std::istream& fs)
{
    // TODO: insert return statement here
	return fs;
}
