#ifndef JAY_COMPILER_H
#define JAY_COMPILER_H

#include <Jay/Common.h>
#include <Jay/Token.h>
#include <Jay/List.h>

#include <cstdio>

namespace Jay {
	
	class Compiler {
	private:
		FILE* fout;
		
		TokenList* tokenList;
		List<char*>* nameList;
		
	public:
		Compiler(const char* path, TokenList* tokenList);
		~Compiler();
		
		void start();
		
		void setNameList(List<char*>* nameList);
	};
	
	class VMTemplate {
	public:
		static const char* LABEL;
		static const char* RET_INT;
		static const char* RET_VOID;
	};
	
}

#endif // JAY_COMPILER_H