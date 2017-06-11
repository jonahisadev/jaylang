#include <Jay/Common.h>
#include <Jay/Util.h>
#include <Jay/Parser.h>
#include <Jay/Context.h>

void help() {
	std::cout << "== Jay Help ==" << std::endl;
	std::cout << "\tjay -c [file]: Compile file" << std::endl;
	std::exit(1);
}

int main(int argc, char** argv) {
	if (argc < 3) {
		help();
	}
	
	using namespace Jay;
	
	if (Util::strEquals(argv[1], "-c")) {
		char* buf = Util::readFile(argv[2]);
		
		// Parse for tokens
		Parser* p = new Parser(Util::strDupFull(buf));
		p->start();
		
		// Fill in the gaps
		Context* context = p->createContext();
		context->start();
		p->printTokens();
		delete context;
		
		// Build necessary structures
		p->buildFunctions();
		
		// Compile to SpaceVM
		Compiler* c = p->createCompiler("test.vm");
		c->start();
		
		delete c;
		delete p;
	} else {
		help();
	}
	
	return 0;
}