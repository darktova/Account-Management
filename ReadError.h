#pragma once
#include <iostream>
#include "FileError.h"

class ReadError : public FileError
{
public:
	ReadError(const std::string&);
};
