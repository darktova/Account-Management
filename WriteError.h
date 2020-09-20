#pragma once
#include <iostream>
#include "FileError.h"

class WriteError : public FileError
{
public:
	WriteError(const std::string&);
};

