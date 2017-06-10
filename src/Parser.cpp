#include <Jay/Parser.h>
#include <Jay/Token.h>

namespace Jay {
	
	Parser::Parser(char* text) {
		this->text = text;
		this->tokenList = new TokenList(1);
		this->nameList = new List<char*>(1);
	}
	
	Parser::~Parser() {
		delete[] text;
		delete tokenList;
		delete nameList;
	}
	
	void Parser::start() {
		//std::printf("%s\n\n", this->text);
		
		char* lex = new char[256];
		int lexi = 0;
		int i = 0;
		int line = 1;
		
		resetLex:
		lexi = 0;
		for (int x = 0; x < 256; x++) {
			lex[x] = '\0';
		}
		
		while (!isCharImportant(text[i])) {
			if (text[i] == '\0')				// Check for end
				break;
			else if (text[i] == '\n')			// Check for new line
				break;
			else if (text[i] == '\t') {			// Ignore tabs
				i++;
				goto resetLex;
			}
			
			lex[lexi++] = text[i++];
		}

		lex[lexi] = '\0';
		
		// SPECIALS
		if (lexi == 0) {
			switch (text[i]) {
				case '(': {
					tokenList->add(new Token(TYPE_SPECIAL, TOKEN_LEFT_PAR, line));
					break;
				}
				case ')': {
					tokenList->add(new Token(TYPE_SPECIAL, TOKEN_RIGHT_PAR, line));
					break;
				}
				case '[': {
					tokenList->add(new Token(TYPE_SPECIAL, TOKEN_LEFT_BRACKET, line));
					break;
				}
				case ']': {
					tokenList->add(new Token(TYPE_SPECIAL, TOKEN_RIGHT_BRACKET, line));
					break;
				}
				case ':': {
					tokenList->add(new Token(TYPE_SPECIAL, TOKEN_COLON, line));
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
			tokenList->add(new Token(TYPE_KEYWORD, TOKEN_FUNC, line));
			goto end;
		} else if (Util::strEquals(lex, "endf")) {
			tokenList->add(new Token(TYPE_KEYWORD, TOKEN_ENDF, line));
			goto end;
		} else if (Util::strEquals(lex, "return")) {
			tokenList->add(new Token(TYPE_KEYWORD, TOKEN_RET, line));
			goto end;
		}
		
		// NUMBERS
		else if (Util::isNumber(lex)) {
			tokenList->add(new Token(TYPE_NUM, Util::convertNum(lex, 10), line));
			goto end;
		}
		
		// NAME
		else {
			nameList->add(Util::strDupFull(lex));
			tokenList->add(new Token(TYPE_NAME, nameList->getPointer()-1, line));
			goto end;
		}
		
		end:
		if (text[i] == ' ') {
			i++;
		} else if (text[i] == '\n') {
			i++;
			line++;
		} else if (text[i] == '\0') {
			return;
		}
		goto resetLex;
	}
	
	bool Parser::isCharImportant(char c) {
		if (c == ' ' ||
			c == '(' ||
			c == ')' ||
			c == '[' ||
			c == ']' ||
			c == ':') {
			return true;
		}
		return false;
	}
	
	void Parser::printTokens() {
		this->tokenList->printList(this->nameList);
	}
	
	Context* Parser::createContext() {
		Context* c = new Context(this->tokenList);
		c->setNameList(this->nameList);
		return c;
	}
	
	Compiler* Parser::createCompiler(const char* path) {
		Compiler* c = new Compiler(path, this->tokenList);
		c->setNameList(this->nameList);
		return c;
	}
	
}