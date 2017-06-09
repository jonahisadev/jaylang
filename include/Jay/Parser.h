#ifndef JAY_PARSER_H
#define JAY_PARSER_H

#include <Jay/Common.h>
#include <Jay/Util.h>
#include <Jay/Token.h>

namespace Jay {
	
	class Parser {
	private:
		char* text;
		TokenList* tokenList;
		
	public:
		Parser(char* text);
		~Parser();
		
		void start();
		bool isCharImportant(char c);
		
		void printTokens();
	};
	
}

#endif // JAY_PARSER_H