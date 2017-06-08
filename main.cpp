#include <Jay/Common.h>
#include <Jay/Util.h>

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
		std::cout << buf << std::endl;
	} else {
		help();
	}
	
	return 0;
}