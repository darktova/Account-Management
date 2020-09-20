#include "FileError.h"

FileError::FileError(const std::string& file) : 
	filename(file) { }


std::string FileError::getName() const { return filename; }