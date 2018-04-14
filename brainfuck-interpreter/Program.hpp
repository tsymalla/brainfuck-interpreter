#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <string>
#include <memory>
#include <iostream>
#include <fstream>

class Program {
private:
	std::string source_;
public:
	Program();
	Program(const std::string& source);
	~Program();
	void setSource(const std::string& source);
	void loadFromFile(const std::string& file);
	const std::string& getSource() const;
};

#endif