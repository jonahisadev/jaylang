#include <Jay/Parser.h>

namespace Jay {
	
	Parser::Parser(char* text) {
		this->text = text;
		this->tokenList = new TokenList(1);
		this->nameList = new List<char*>(1);
		this->funcList = new List<Function*>(1);
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
				case ',': {
					tokenList->add(new Token(TYPE_SPECIAL, TOKEN_COMMA, line));
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
			c == ':' ||
			c == ',') {
			return true;
		}
		return false;
	}
	
	void Parser::buildFunctions() {
		Token* tok;
		int offset = 0;
		
		for (int i = 0; i < tokenList->getSize(); i++) {
			tok = tokenList->get(i);
			
			if (tok->getType() == TYPE_KEYWORD &&
				tok->getData() == TOKEN_FUNC) {
				Function* func = new Function();
				i++;
				tok = tokenList->get(i);
				
				// Name
				
				if (tok->getType() == TYPE_ID) {
					func->name = Util::strDupFull(nameList->get(tok->getData()));
					//std::cout << "Function name: " << func->name << std::endl;
				} else {
					serror("No function name found", tok->getLine());
				}
				i++;
				tok = tokenList->get(i);
				
				// Arguments
				
				int argc = 0;
				List<Variable*>* argv = new List<Variable*>(1);
				if (tok->getType() == TYPE_SPECIAL &&
					tok->getData() == TOKEN_LEFT_PAR) {
					i++;
					tok = tokenList->get(i);
					while (tok->getType() != TYPE_SPECIAL &&
							tok->getData() != TOKEN_RIGHT_PAR) {
						Variable* var = buildVariable(&i, VAR_TYPE_ARG);
						//std::cout << "Variable " << var->name << " of type " << var->type << std::endl;
						argv->add(var);
						argc++;
						i++;
						tok = tokenList->get(i);
					}
				} else {
					serror("No left paranthesis after function name", tok->getLine());
				}
				func->argc = argc;
				func->argv = argv->getRawData();
				
				funcList->add(func);
			}
		}
	}
	
	Variable* Parser::buildVariable(int* index, int type) {
		Variable* var = new Variable();
		Token* tok = tokenList->get(*index);
		
		// Name
		if (tok->getType() == TYPE_ID) {
			var->name = Util::strDupFull(nameList->get(tok->getData()));
			*index = *index + 1;
		} else {
			delete var;
			serror("Variable must have identifier", tok->getLine());
		}
		
		// Colon
		tok = tokenList->get(*index);
		if (tok->getType() == TYPE_SPECIAL &&
			tok->getData() == TOKEN_COLON) {
			*index = *index + 1;	
		} else {
			delete var;
			serror("Variable missing ':'", tok->getLine());
		}
		
		// Type
		tok = tokenList->get(*index);
		if (tok->getType() == TYPE_TYPE) {
			var->type = Util::strDupFull(nameList->get(tok->getData()));
			*index = *index + 1;
		} else {
			delete var;
			serror("Variable must have a type", tok->getLine());
		}
		
		if (type != VAR_TYPE_ARG) {
			// TODO: Parse for data
		} else {
			var->data = 0;
		}
		
		return var;
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
		c->setFunctionList(this->funcList);
		return c;
	}
	
}