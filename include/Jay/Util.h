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
		static void strCopy(const char* src, char* dest, int start, int end);
		static void strCopyFull(const char* src, char* dest);
		static char* strDup(const char* src, int start, int end);
		static char* strDupFull(const char* src);
		static bool isNumber(const char* str);
		static int convertNum(char* str, int base);
	};

}

#endif // JAY_UTIL_H