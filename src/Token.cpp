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
			this->data = (Token**) realloc(this->data, this->alloc_size);
		}
		
		this->data[this->ptr++] = tok;
	}
	
	Token* TokenList::get(int ptr) {
		return this->data[ptr];
	}
	
	void TokenList::printList() {
		for (int i = 0; i < getSize(); i++) {
			if (data[i]->getType() == TYPE_KEYWORD) {
				if (data[i]->getData() == TOKEN_FUNC) {
					std::printf("FUNC\n");
				}
			}
		}
	}
	
}