#ifndef JAY_PARSER_H
#define JAY_PARSER_H

#include <Jay/Common.h>
#include <Jay/Util.h>
#include <Jay/Token.h>
#include <Jay/List.h>

namespace Jay {
	
	class Parser {
	private:
		char* text;
		TokenList* tokenList;
		List<char*>* nameList;
		
	public:
		Parser(char* text);
		~Parser();
		
		void start();
		bool isCharImportant(char c);
		
		void printTokens();
	};
	
}

#endif // JAY_PARSER_H