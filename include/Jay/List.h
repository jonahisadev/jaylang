#ifndef JAY_LIST_H
#define JAY_LIST_H

#include <Jay/Function.h>

namespace Jay {
	
	template <class T>
	class List {
	private:
		T* data;
		int alloc_size;
		int ptr;
		
	public:
		List(int size);
		~List();
		
		void add(T data);
		T get(int ptr) const { return data[ptr]; }
		void set(int ptr, T data);
		
		inline int getPointer() const { return ptr; }
		inline int getSize() const { return ptr; }
		inline int getAllocatedSize() const { return alloc_size; }
	};
	
	template class List<char*>;
	template class List<int>;
	template class List<Function*>;
	
	template <class T>
	List<T>::List(int size) {
		this->data = (T*) malloc(sizeof(T) * size);
		this->alloc_size = size;
		this->ptr = 0;
	}
	
	template <class T>
	List<T>::~List() {
		free(this->data);
	}
	
	template <class T>
	void List<T>::add(T data) {
		if (getSize() >= getAllocatedSize()) {
			this->alloc_size *= 2;
			this->data = (T*) realloc(this->data, sizeof(T) * this->alloc_size);
		}
		
		this->data[this->ptr++] = data;
	}
	
	template <class T>
	void List<T>::set(int ptr, T data) {
		this->data[ptr] = data;
	}
	
}

#endif // JAY_LIST_H