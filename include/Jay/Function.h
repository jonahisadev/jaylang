#ifndef JAY_FUNCTION_H
#define JAY_FUNCTION_H

#include <Jay/Common.h>
#include <Jay/Util.h>

namespace Jay {
	
	struct Function {
		char* name;
		char* ret;
		int argc;
		int* argv;
		
		//Function(char* name, char* ret, int argc, int* argv);
		//~Function();
	};
	
}

#endif // JAY_FUNCTION_H