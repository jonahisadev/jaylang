#include <Jay/Compiler.h>

namespace Jay {
	
	Compiler::Compiler(const char* path, TokenList* tokenList) {
		this->tokenList = tokenList;
		this->fout = fopen(path, "w");
	}
	
	Compiler::~Compiler() {
		// NOTHING
	}
	
	void Compiler::start() {
		Token* tok;
		for (int i = 0; i < tokenList->getSize(); i++) {
			tok = tokenList->get(i);
			
			// Functions
			if (tok->getType() == TYPE_KEYWORD &&
				tok->getData() == TOKEN_FUNC) {
				std::fprintf(fout, VMTemplate::LABEL, nameList->get(tokenList->get(i+1)->getData()));
			}
			
			// Return
			else if (tok->getType() == TYPE_KEYWORD &&
				tok->getData() == TOKEN_RET) {
				// Return literal
				if (tokenList->get(i+1)->getType() == TYPE_NUM) {
					std::fprintf(fout, VMTemplate::RET_NUM, tokenList->get(i+1)->getData());
				}
			}
		}
	}
	
	void Compiler::setNameList(List<char*>* nameList) {
		this->nameList = nameList;
	}
	
	//
	// VMTemplate
	//
	
	const char* VMTemplate::LABEL = "%s:\n";
	const char* VMTemplate::RET_NUM = "\tmov %%dx $%d\n\tret\n\n";
	
}