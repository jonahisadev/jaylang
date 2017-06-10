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
		
		Parser* p = new Parser(Util::strDupFull(buf));
		p->start();
		
		Context* c = p->createContext();
		c->start();
		p->printTokens();
		
		delete c;
		delete p;
	} else {
		help();
	}
	
	return 0;
}