#pragma once
#include <iostream>
#include <iomanip>

enum TypeId { ACCOUNT, DEP_ACC, SAV_ACC };

class Account
{
private:
	std::string name; 
	unsigned long nr; 
	double balance;

public:
	Account(const std::string& = "X", unsigned long = 1111111L, double = 0.0);
	const std::string& getName() const;
	void setName(const std::string&);
	unsigned long getNr() const;
	void setNr(unsigned long);
	double getBalance() const;
	void setBalance(double);
	void display();
	virtual TypeId getTypeId() const;
	virtual std::ostream& write(std::ostream& fs) const;
	virtual std::istream& read(std::istream& fs);

};

