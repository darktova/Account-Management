#include "Account.h"

Account::Account(const std::string& s, unsigned long n, double st)
	: name(s), nr(n), balance(st)
{ }

const std::string& Account::getName() const { return name; }

void Account::setName(const std::string& n) { name = n; }

unsigned long Account::getNr() const { return nr; }

void Account::setNr(unsigned long n) { nr = n; }

double Account::getBalance() const { return balance; }

void Account::setBalance(double st) { balance = st; }

void Account::display()
{
	std::cout << std::fixed << std::setprecision(2)
	<< "----------------------------------------"
	<< "\nAccount holder: " << name
	<< "\nAccount number: " << nr
	<< "\nBalance of the account:" << balance << '\n';
}

TypeId Account::getTypeId() const { return ACCOUNT; }

std::ostream& Account::write(std::ostream& fs) const
{
	if (!fs.good())
		return fs;
	fs.write((char*)&nr, sizeof(nr));
	fs.write((char*)&name, sizeof(name));
	fs.write((char*)&balance, sizeof(balance));
	return fs;
}

std::istream& Account::read(std::istream& fs)
{
	if (!fs.good())
		return fs;
	fs.read((char*)&nr, sizeof(nr));
	fs.read((char*)&name, sizeof(name));
	fs.read((char*)&balance, sizeof(balance));
	return fs;
}
