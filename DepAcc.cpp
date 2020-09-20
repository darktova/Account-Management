#include "DepAcc.h"

DepAcc::DepAcc(const std::string s,
	unsigned long n,
	double bal,
	double li,
	double ir)
	: Account(s, n, bal), limit(li), interest(ir)
{ }

std::ostream& DepAcc::write(std::ostream& os) const
{
	if (!Account::write(os))
		return os;
	os.write((char*)&limit, sizeof(limit));
	os.write((char*)&interest, sizeof(interest));
	return os;
}

std::istream& DepAcc::read(std::istream& is)
{
	if (!Account::read(is))
		return is;
	is.read((char*)&limit, sizeof(limit));
	is.read((char*)&interest, sizeof(interest));
	return is;
}