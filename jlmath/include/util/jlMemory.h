/// @file jlMemory.h
/// @authors Jeff Lansing
/// Handles all custom memory allocation
/// Overrides of the new/delete operator

#ifndef JL_MEMORY_H
#define JL_MEMORY_H

/// Called by new/delete operators
/// for default alloc/delete
void * jlAlloc(size_t size);
void jlDelete(void *ptr);

/// global new/delete if needed
#if (JL_USE_CUSTOM_MEMORY_ALLOCATORS)
void * operator new (size_t size);
void operator delete (void *ptr);
void * operator new [] (size_t size);
void operator delete [] (void *ptr);
#endif

/// Checks power of 2 memory alignment
bool8 jlMemoryIsAligned(void *ptr, size_t sz, size_t alignment);

/// Ensures a memory alignment which new/malloc do not guarantee
/// Use for SIMD types and others that require aligned access
void * jlAllocAligned(size_t sz, size_t alignment);

/// Frees a block of memory aligned with jlAllocAligned
void jlFreeAligned(void *ptr);

/// A simple macro that easily lets classes override new/delete 
/// to work with AllocAligned and FreeAligned to a given alignment
#define JL_DECLARE_ALIGNED_ALLOC_OBJECT(ALIGNMENT) \
	static void * operator new(size_t sz) { \
		return jlAllocAligned(sz, (ALIGNMENT)); \
	} \
	\
	static void * operator new[](size_t sz) { \
		return jlAllocAligned(sz, (ALIGNMENT)); \
	} \
	\
	static void operator delete(void *ptr) { \
		jlFreeAligned(ptr); \
	} \
	\
	static void operator delete[](void *ptr) { \
		jlFreeAligned(ptr); \
	}

/// Use if you explictly don't want aligned allocations
/// Or if for some reason, a base class needs it and it doesn't/can't
/// This should be **very** rare
#define JL_DECLARE_UNALIGNED_ALLOC_OBJECT \
	static void * operator new(size_t sz) { \
		return jlAlloc(sz); \
	} \
	\
	static void * operator new[](size_t sz) { \
		return jlAlloc(sz); \
	} \
	\
	static void operator delete(void *ptr) { \
		jlDelete(ptr); \
	} \
	\
	static void operator delete[](void *ptr) { \
		jlDelete(ptr); \
	}

#endif // JL_MEMORY_H
