#pragma once
#include <iostream>
#include "FileError.h"

class OpenError : public FileError
{
public:
	OpenError(const std::string&);
};