#include <Jay/Context.h>

namespace Jay {
	
	Context::Context(TokenList* tokenList) {
		this->tokenList = tokenList;
	}
	
	Context::~Context() {
		// NOTHING
	}
	
	void Context::start() {
		Token* tok;
		
		for (int i = 0; i < this->tokenList->getSize(); i++) {
			tok = this->tokenList->get(i);
			
			if (tok->getType() == TYPE_NAME) {
				// Function Name
				if (tokenList->get(i-1)->getType() == TYPE_KEYWORD &&
					tokenList->get(i-1)->getData() == TOKEN_FUNC &&
					tokenList->get(i+1)->getType() == TYPE_SPECIAL &&
					tokenList->get(i+1)->getData() == TOKEN_LEFT_PAR) {
					tok->setType(TYPE_ID);
				}
				
				// Return Type
				if (tokenList->get(i-1)->getType() == TYPE_SPECIAL &&
					tokenList->get(i-1)->getData() == TOKEN_LEFT_BRACKET &&
					tokenList->get(i+1)->getType() == TYPE_SPECIAL &&
					tokenList->get(i+1)->getData() == TOKEN_RIGHT_BRACKET) {
					tok->setType(TYPE_TYPE);
				}
				
				// Variable Name
				if (tokenList->get(i+1)->getType() == TYPE_SPECIAL &&
					tokenList->get(i+1)->getData() == TOKEN_COLON) {
					tok->setType(TYPE_ID);
				}
				
				// Return Variable
				if (tokenList->get(i-1)->getType() == TYPE_KEYWORD &&
					tokenList->get(i-1)->getData() == TOKEN_RET) {
					tok->setType(TYPE_ID);	
				}
				
				// Variable Type
				if (tokenList->get(i-1)->getType() == TYPE_SPECIAL &&
					tokenList->get(i-1)->getData() == TOKEN_COLON) {
					// Function Variable Type
					if ((tokenList->get(i+1)->getType() == TYPE_SPECIAL &&
						tokenList->get(i+1)->getData() == TOKEN_RIGHT_PAR) ||
						(tokenList->get(i+1)->getType() == TYPE_SPECIAL &&
						tokenList->get(i+1)->getData() == TOKEN_COMMA)) {
						tok->setType(TYPE_TYPE);
					}
				}
			}
		}
	}
	
	void Context::setNameList(List<char*>* nameList) {
		this->nameList = nameList;
	}
	
}