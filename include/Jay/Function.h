#ifndef JAY_FUNCTION_H
#define JAY_FUNCTION_H

#include <Jay/Common.h>
#include <Jay/Util.h>
#include <Jay/Variable.h>

namespace Jay {
	
	struct Function {
		char* name;
		char* ret;
		int argc;
		Variable** argv;
	};
	
}

#endif // JAY_FUNCTION_H