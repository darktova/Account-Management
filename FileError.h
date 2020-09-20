#pragma once
#include <iostream>

class FileError
{
private:
	std::string filename;
public:
	FileError(const std::string&);
	std::string getName() const;
};
