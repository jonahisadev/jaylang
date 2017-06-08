#ifndef JAY_UTIL_H
#define JAY_UTIL_H

#include <Jay/Common.h>

#include <cstdio>
#include <cstdlib>

namespace Jay {

	class Util {
	public:
		static char* readFile(const char* path);
		static int strLength(const char* str);
		static bool strEquals(const char* a, const char* b);
	};

}

#endif // JAY_UTIL_H