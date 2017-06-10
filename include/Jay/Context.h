#ifndef JAY_CONTEXT_H
#define JAY_CONTEXT_H

#include <Jay/Common.h>
#include <Jay/Token.h>
#include <Jay/List.h>

namespace Jay {
	
	class Context {
	private:
		TokenList* tokenList;
		List<char*>* nameList;
		
	public:
		Context(TokenList* tokenList);
		~Context();
		
		void start();
		
		void setNameList(List<char*>* nameList);
	};
	
}

#endif // JAY_CONTEXT_H