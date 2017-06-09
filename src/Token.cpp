#include <Jay/Token.h>

namespace Jay {
	
	//
	//	TOKEN
	//
	
	Token::Token(int type, int data) {
		this->type = type;
		this->data = data;
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
			
			switch (tok->getType()) {
				// KEYWORDS
				case TYPE_KEYWORD: {
					if (tok->getData() == TOKEN_FUNC) {
						std::printf("FUNC\n");
					}
					break;
				}
				
				// SPECIALS
				case  TYPE_SPECIAL: {
					if (tok->getData() == TOKEN_LEFT_PAR) {
						std::printf("(\n");
					} else if (tok->getData()) {
						std::printf(")\n");
					}
					break;
				}
			}
		}
	}
	
}