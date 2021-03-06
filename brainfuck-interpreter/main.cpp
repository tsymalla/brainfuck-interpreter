#include "stdafx.h"
#include <iostream>
#include <string>
#include "Interpreter.hpp"
#include "Program.hpp"

int main(int argc, char* argv[])
{
	// Reads the first command line argument and uses it as input file.
	if (argc < 2) {
		std::cout << "Usage: " << argv[0] << " filename.bf" << std::endl;
		return 1;
	}

	Program program;
	program.loadFromFile(argv[1]);
	Interpreter interpreter;
	interpreter.setProgram(program);

	interpreter.interpret();

    return 0;
}

