#include "stdafx.h"
#include "Program.hpp"
#include <assert.h>

Program::Program()
{
}

///
/// Passes the source of the program as string.
///

Program::Program(const std::string& source) {
	this->source_ = source;
}

Program::~Program()
{

}

///
/// Allows to set the source.
///
void Program::setSource(const std::string& source)
{
	assert(source.length() > 0);

	this->source_ = source;
}

///
/// Loads a text file containing a program and sets it as program source.
///
void Program::loadFromFile(const std::string& file)
{
	std::cout << "Opening file: " << file << std::endl;

	if (file.length() > 0) {
		std::ifstream fileStream;
		fileStream.open(file, std::ifstream::in);

		if (!fileStream.fail() && fileStream.is_open()) {
			std::string input((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
			this->source_ = input;
		}
		else {
			throw std::runtime_error("Could not open file");
		}
	}
	else {
		throw std::runtime_error("No filename given");
	}
}

///
/// Returns the program source.
///
const std::string& Program::getSource() const
{
	return this->source_;
}