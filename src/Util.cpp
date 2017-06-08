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
	
}