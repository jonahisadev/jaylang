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
		lexi = 0;
		for (int x = 0; x < 256; x++) {
			lex[x] = '\0';
		}
		
		while (!isCharImportant(text[i])) {
			if (text[i] == '\0')				// check for end
				return;
			
			lex[lexi++] = text[i++];
		}
		
		// SPECIALS
		if (lexi == 0) {
			switch (text[i]) {
				case '(': {
					tokenList->add(new Token(TYPE_SPECIAL, TOKEN_LEFT_PAR));
					break;
				}
				case ')': {
					tokenList->add(new Token(TYPE_SPECIAL, TOKEN_RIGHT_PAR));
					break;
				}
				default:
					break;
			}
			
			i++;
			goto end;
		}
		
		// KEYWORDS
		if (Util::strEquals(lex, "func")) {
			tokenList->add(new Token(TYPE_KEYWORD, TOKEN_FUNC));
			goto end;
		}
		
		end:
		if (text[i] == ' ') {
			i++;
		}
		goto resetLex;
	}
	
	bool Parser::isCharImportant(char c) {
		if (c == ' ' ||
			c == '(' ||
			c == ')') {
			return true;
		}
		return false;
	}
	
	void Parser::printTokens() {
		this->tokenList->printList();
	}
	
}