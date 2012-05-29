#include "jlCore.h"
#include <cstdlib>

void * jlAlloc (size_t size) {
	return malloc(size);
}

void jlDelete (void *ptr) {
	free(ptr);
}

#if (JL_USE_CUSTOM_MEMORY_ALLOCATORS)
void * operator new (size_t size) {
	return jlAlloc(size);
	//return ::operator new(size, std::nothrow);
}

void operator delete (void *ptr) {
	return jlDelete(ptr);
	//::operator delete(ptr, std::nothrow);
}

void * operator new [] (size_t size) {
	return jlAlloc(size);
	//return ::operator new[](size, std::nothrow);
}

void operator delete [] (void *ptr) {
	return jlDelete(ptr);
	//::operator delete[](ptr, std::nothrow); 
}
#endif

bool8 jlMemoryIsAligned(void *ptr, size_t sz, size_t alignment) {
	return (((uintptr_t)ptr & (alignment - 1)) == 0) && (((uintptr_t)sz & (alignment - 1)) == 0);
}

void * jlAllocAligned(size_t sz, size_t alignment) {
	return _aligned_malloc(sz, alignment);
}

void jlFreeAligned(void *ptr) {
	_aligned_free(ptr);
}
