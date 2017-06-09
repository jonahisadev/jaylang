#include <Jay/Parser.h>
#include <Jay/Token.h>

namespace Jay {
	
	Parser::Parser(char* text) {
		this->text = text;
		this->tokenList = new TokenList(1);
	}
	
	Parser::~Parser() {
		delete[] text;
	}
	
	void Parser::start() {
		char* lex = new char[256];
		int lexi = 0;
		int i = 0;
		
		resetLex:
		for (int x = 0; x < 256; x++) {
			lex[x] = '\0';
		}
		
		while (!isCharImportant(text[i])) {
			if (text[i] == '\0')				// check for end
				return;
			
			lex[lexi++] = text[i++];
		}
		
		// KEYWORDS
		if (Util::strEquals(lex, "func")) {
			tokenList->add(new Token(TYPE_KEYWORD, TOKEN_FUNC));
		}
		
		i++;
		goto resetLex;
	}
	
	bool Parser::isCharImportant(char c) {
		if (c == ' ') {
			return true;
		}
		return false;
	}
	
	void Parser::printTokens() {
		this->tokenList->printList();
	}
	
}