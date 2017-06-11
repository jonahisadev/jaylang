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
				this->functionScope = Util::strDupFull(nameList->get(tokenList->get(i+1)->getData()));
			}
			
			// Return
			else if (tok->getType() == TYPE_KEYWORD &&
				tok->getData() == TOKEN_RET) {
				// Return literal
				if (tokenList->get(i+1)->getType() == TYPE_NUM) {
					std::fprintf(fout, VMTemplate::RET_INT, tokenList->get(i+1)->getData());
				}
				
				// Return void
				else if (tokenList->get(i+1)->getType() == TYPE_KEYWORD &&
						tokenList->get(i+1)->getData() == TOKEN_ENDF) {
					std::fprintf(fout, "%s", VMTemplate::RET_VOID);		
				}
				
				// Return variable
				else if (tokenList->get(i+1)->getType() == TYPE_ID) {
					tok = tokenList->get(i+1);
					bool found = false;
					for (int x = 0; x < funcList->getSize(); x++) {
						// Find the function in the list
						if (Util::strEquals(funcList->get(x)->name, this->functionScope)) {
							Function* func = funcList->get(x);
							for (int y = 0; y < func->argc; y++) {
								// Find the variable in the arguments
								if (Util::strEquals(func->argv[y]->name, nameList->get(tok->getData()))) {
									std::fprintf(fout, VMTemplate::RET_ARG, y + 1);
									found = true;
									break;
								}
							}
							break;
						}
					}
					
					if (!found) {
						serror("No variable found", tok->getLine());
					}
				}
			}
		}
	}
	
	void Compiler::setNameList(List<char*>* nameList) {
		this->nameList = nameList;
	}
	
	void Compiler::setFunctionList(List<Function*>* funcList) {
		this->funcList = funcList;
	}
	
	//
	// VMTemplate
	//
	
	const char* VMTemplate::LABEL = "%s:\n";
	const char* VMTemplate::RET_INT = "\tmovw %%dx $%d\n\tret\n\n";
	const char* VMTemplate::RET_VOID = "\tret\n\n";
	const char* VMTemplate::RET_ARG = "\targ %%dx $%d\n\tret\n\n";
	
}