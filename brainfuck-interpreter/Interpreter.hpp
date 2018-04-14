#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "Program.hpp"
#include <iostream>
#include <string>
#include <stack>
#include <array>

enum OPERATOR {
	OP_INCREMENT_PTR,
	OP_DECREMENT_PTR,
	OP_INCREMENT_VAL,
	OP_DECREMENT_VAL,
	OP_PUT_CHAR,
	OP_GET_CHAR,
	OP_START_LOOP,
	OP_END_LOOP,
	OP_END
};

struct OPCODE {
	unsigned short op;
	unsigned short operand;
};

class Interpreter {
private:
	Program* program_;
	std::array<unsigned char, 65536> data_;
	std::array<OPCODE, 65536> compiled_;
	std::stack<unsigned short> stack_;
	unsigned int ptr_;
	unsigned short pc_;
	unsigned short pcJump_;
	void compile();
public:
	Interpreter();
	~Interpreter();
	void setProgram(Program& program);
	void interpret();
};

#endif