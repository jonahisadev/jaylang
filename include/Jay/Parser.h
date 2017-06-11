#ifndef JAY_PARSER_H
#define JAY_PARSER_H

#include <Jay/Common.h>
#include <Jay/Util.h>
#include <Jay/Token.h>
#include <Jay/List.h>
#include <Jay/Context.h>
#include <Jay/Compiler.h>
#include <Jay/Function.h>
#include <Jay/Variable.h>

namespace Jay {
	
	enum  {
		VAR_TYPE_ARG,
	};
	
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
		Variable* buildVariable(int* index, int type);
		
		void printTokens();
		Context* createContext();
		Compiler* createCompiler(const char* path);
	};
	
}

#endif // JAY_PARSER_H