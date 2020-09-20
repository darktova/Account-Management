#pragma once
#include "Account.h"
class DepAcc :
    public Account
{
private:
    double limit; // Overdrawn limit
    double interest; // Interest rate

public:
    DepAcc(const std::string = "X",
        unsigned long = 1111111L,
        double = 0.0,
        double = 0.0,
        double = 0.0);
    // Access methods:
    // . . .
    // The other methods are implicit virtual:
    TypeId getTypeId() const { return DEP_ACC; }
    std::ostream& write(std::ostream& fs) const;
    std::istream& read(std::istream& fs);
};

