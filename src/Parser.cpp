#include <Jay/Parser.h>

namespace Jay {
	
	Parser::Parser(char* buf) {
		this->buf = buf;
	}
	
	Parser::~Parser() {
		delete[] buf;
	}
	
	void Parser::start() {
		std::cout << buf << std::endl;
	}
	
}