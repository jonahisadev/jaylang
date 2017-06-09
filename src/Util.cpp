#include <Jay/Util.h>

namespace Jay {
	
	char* Util::readFile(const char* path) {
		FILE* file = fopen(path, "r");
		ASSERT(file, "Could not read file");
		
		fseek(file, 0, SEEK_END);
		int size = ftell(file);
		fseek(file, 0, SEEK_SET);
		
		char* buf = new char[size];
		ASSERT(buf, "Could not allocate memory");
		
		fread(buf, 1, size, file);
		fclose(file);
		buf[size] = '\0';
		
		return buf;
	}
	
	int Util::strLength(const char* str) {
		int len = 0;
		while (str[len] != '\0')
			len++;
		return len;
	}
	
	bool Util::strEquals(const char* a, const char* b) {
		int aLen = strLength(a);
		int bLen = strLength(b);
		
		if (aLen != bLen) {
			return false;
		}
		
		for (int i = 0; i < aLen; i++) {
			if (a[i] != b[i])
				return false;
		}
		
		return true;
	}
	
	void Util::strCopy(const char* src, char* dest, int start, int end) {
		int x = 0;
		for (int i = start; i < end; i++) {
			dest[x] = src[i];
			x++;
		}
	}
	
	void Util::strCopyFull(const char* src, char* dest) {
		int len = strLength(src);
		strCopy(src, dest, 0, len);
	}
	
	char* Util::strDup(const char* src, int start, int end) {
		char* dest = new char[(end-start)+1];
        ASSERT(dest, "strDup allocation failure");

        strCopy(src, dest, start, end+1);
		dest[end] = '\0';
        return dest;
	}
	
	char* Util::strDupFull(const char* src) {
		return strDup(src, 0, strLength(src)+1);
	}
	
	bool Util::isNumber(const char* str) {
		int len = strLength(str);
		
		for (int i = 0; i < len; i++) {
			if (str[i] <= '0' || str[i] >= '9')
				return false;
		}
		
		return true;
	}
	
	int Util::convertNum(char* str, int base) {
	    int x = (int) strtol(str, (char**)NULL, base);
	    return x;
	}
	
}