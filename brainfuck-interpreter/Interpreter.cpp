#include "stdafx.h"
#include "Interpreter.hpp"
#include <assert.h>

Interpreter::Interpreter(): program_(nullptr)
{
}

Interpreter::~Interpreter()
{
}

void Interpreter::setProgram(Program& program)
{
	this->program_ = &program;
}

void Interpreter::compile()
{
	const std::string& source = this->program_->getSource();
	assert(source.length() > 0);

	std::cout << "COMPILING..." << std::endl;
	std::cout << "Input file length: " << source.length() << std::endl;

	// reset program counter
	this->pc_ = 0;

	// clear stack
	this->stack_ = std::stack<unsigned short>();

	for (auto it = source.begin(); it != source.end(); ++it)
	{
		// Parse the current token and "compile" the program by putting operations into an array
		switch (*it) {
			case '>':
				this->compiled_[this->pc_].op = OPERATOR::OP_INCREMENT_PTR;
				break;
			case '<':
				this->compiled_[this->pc_].op = OPERATOR::OP_DECREMENT_PTR;
				break;
			case '+':
				this->compiled_[this->pc_].op = OPERATOR::OP_INCREMENT_VAL;
				break;
			case '-':
				this->compiled_[this->pc_].op = OPERATOR::OP_DECREMENT_VAL;
				break;
			case '.':
				this->compiled_[this->pc_].op = OPERATOR::OP_PUT_CHAR;
				break;
			case ',':
				this->compiled_[this->pc_].op = OPERATOR::OP_GET_CHAR;
				break;
			case '[':
				// add the current program counter to the address and start a while loop
				this->compiled_[this->pc_].op = OPERATOR::OP_START_LOOP;
				this->stack_.push(this->pc_);
				break;
			case ']':
				if (!this->stack_.empty()) {
					// pop the value of the pc before starting the loop from the stack
					this->pcJump_ = this->stack_.top();
					this->stack_.pop();
					// return the program at the last stacked pc and end the loop
					this->compiled_[this->pc_].op = OPERATOR::OP_END_LOOP;
					this->compiled_[this->pc_].operand = this->pcJump_;

					this->compiled_[this->pcJump_].operand = this->pc_;
				}
				break;
			default:
				this->pc_--;
				break;
		}

		this->pc_++;
	}

	// end the program
	this->compiled_[this->pc_].op = OPERATOR::OP_END;
}

void Interpreter::interpret()
{
	this->compile();

	this->ptr_ = 0;
	this->pc_ = 0;
	
	std::cout << "RUNNING..." << std::endl;
	std::cout << "Output:" << std::endl;

	// run "compiled" program
	while (this->compiled_[this->pc_].op != OPERATOR::OP_END) {
		switch (this->compiled_[this->pc_].op) {
			// increment the pointer value
			case OPERATOR::OP_INCREMENT_PTR:
				++this->ptr_;
				break;
			// decrement the pointer value
			case OPERATOR::OP_DECREMENT_PTR:
				--this->ptr_;
				break;
			// increment the cell at the pointers value
			case OPERATOR::OP_INCREMENT_VAL:
				++this->data_[this->ptr_];
				break;
			// decrement the cell at the pointers value
			case OPERATOR::OP_DECREMENT_VAL:
				--this->data_[this->ptr_];
				break;
			// put the char at the current cell to the screen
			case OPERATOR::OP_PUT_CHAR:
				std::cout << this->data_[this->ptr_];
				break;
			// read the current data cell from cin
			case OPERATOR::OP_GET_CHAR:
				this->data_[this->ptr_] = std::cin.get();
				break;
			// branch to the value at the program counter
			case OPERATOR::OP_START_LOOP:
				if (!this->data_[this->ptr_]) {
					this->pc_ = this->compiled_[this->pc_].operand;
				}
				break;
			// branch back
			case OPERATOR::OP_END_LOOP:
				if (this->data_[this->ptr_]) {
					this->pc_ = this->compiled_[this->pc_].operand;
				}
				break;
		}

		this->pc_++;
	}
}