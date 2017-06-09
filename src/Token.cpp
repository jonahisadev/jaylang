#include <Jay/Token.h>

namespace Jay {
	
	//
	//	TOKEN
	//
	
	Token::Token(int type, int data, int line) {
		this->type = type;
		this->data = data;
		this->line = line;
	}
	
	Token::~Token() {
		// NOTHING
	}
	
	//
	//	TOKEN LIST
	//
	
	TokenList::TokenList(int size) {
		this->data = (Token**) malloc(sizeof(Token*) * size);
		this->alloc_size = size;
		this->ptr = 0;
	}
	
	TokenList::~TokenList() {
		free(this->data);
	}
	
	void TokenList::add(Token* tok) {
		if (getSize() >= getAllocatedSize()) {
			this->alloc_size *= 2;
			this->data = (Token**) realloc(this->data, sizeof(Token*) * this->alloc_size);
		}
		
		this->data[this->ptr++] = tok;
	}
	
	Token* TokenList::get(int ptr) {
		return this->data[ptr];
	}
	
	void TokenList::printList() {
		Token* tok;
		for (int i = 0; i < getSize(); i++) {
			tok = data[i];
			std::printf("%03d: ", tok->getLine());
			
			switch (tok->getType()) {
				// KEYWORDS
				case TYPE_KEYWORD: {
					if (tok->getData() == TOKEN_FUNC)
						std::printf("FUNC\n");
					else if (tok->getData() == TOKEN_ENDF)
						std::printf("ENDF\n");
					else if (tok->getData() == TOKEN_RET)
						std::printf("RETURN\n");
					break;
				}
				
				// SPECIALS
				case  TYPE_SPECIAL: {
					if (tok->getData() == TOKEN_LEFT_PAR)
						std::printf("(\n");
					else if (tok->getData() == TOKEN_RIGHT_PAR)
						std::printf(")\n");
					else if (tok->getData() == TOKEN_LEFT_BRACKET)
						std::printf("[\n");
					else if (tok->getData() == TOKEN_RIGHT_BRACKET)
						std::printf("]\n");
					else if (tok->getData() == TOKEN_COLON)
						std::printf(":\n");
					break;
				}
				
				// NUMBERS
				case TYPE_NUM: {
					std::printf("%d\n", tok->getData());
					break;
				}
			}
		}
	}
	
}