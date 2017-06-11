#ifndef JAY_PARSER_H
#define JAY_PARSER_H

#include <Jay/Common.h>
#include <Jay/Util.h>
#include <Jay/Token.h>
#include <Jay/List.h>
#include <Jay/Context.h>
#include <Jay/Compiler.h>
#include <Jay/Function.h>

namespace Jay {
	
	class Parser {
	private:
		char* text;
		
		TokenList* tokenList;
		List<char*>* nameList;
		List<Function*>* funcList;
		
	public:
		Parser(char* text);
		~Parser();
		
		void start();
		bool isCharImportant(char c);
		
		void buildFunctions();
		
		void printTokens();
		Context* createContext();
		Compiler* createCompiler(const char* path);
	};
	
}

#endif // JAY_PARSER_H