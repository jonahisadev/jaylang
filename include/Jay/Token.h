#ifndef JAY_TOKEN_H
#define JAY_TOKEN_H

#include <cstdlib>
#include <cstdio>

namespace Jay {
	
	// TOKENS
	enum {
		TOKEN_FUNC,
		TOKEN_ENDF,
		TOKEN_RET,
		
		TOKEN_LEFT_PAR,
		TOKEN_RIGHT_PAR,
		TOKEN_LEFT_BRACKET,
		TOKEN_RIGHT_BRACKET,
		TOKEN_COLON,
	};
	
	// TOKEN TYPES
	enum {
		TYPE_KEYWORD,
		TYPE_SPECIAL,
		TYPE_NUM,
	};
	
	class Token {
	private:
		int type;
		int data;
		int line;
		
	public:
		Token(int type, int data, int line);
		~Token();
		
		inline int getType() const { return type; }
		inline int getData() const { return data; }
		inline int getLine() const { return line; }
	};
	
	class TokenList {
	private:
		Token** data;
		int alloc_size;
		int ptr;
		
	public:
		TokenList(int size);
		~TokenList();
		
		void add(Token* tok);
		Token* get(int ptr);
		void printList();
		
		inline int getPointer() const { return ptr; }
		inline int getSize() const { return ptr; }
		inline int getAllocatedSize() const { return alloc_size; }
	};
	
}

#endif // JAY_TOKEN_H