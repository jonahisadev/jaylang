#ifndef JAY_PARSER_H
#define JAY_PARSER_H

#include <Jay/Common.h>

namespace Jay {
	
	class Parser {
	private:
		char* buf;
		
	public:
		Parser(char* buf);
		~Parser();
		
		void start();
	};
	
}

#endif // JAY_PARSER_H