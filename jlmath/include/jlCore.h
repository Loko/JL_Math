/// @file jlCore.h
/// @authors Jeff Lansing
/// Basic root include file

#ifndef JL_CORE_H
#define JL_CORE_H

/// PLATFORMS
#define JL_PLATFORM_WINDOWS 1
#define JL_PLATFORM_XBOX_360 2

/// DETECT PLATFORM
#if defined(_WIN32) || defined(_WIN64)
#	define JL_PLATFORM JL_PLATFORM_WINDOWS // only confirmed supported platform
#elif defined(__XBOX__)
#	define JL_PLATFORM JL_PLATFORM_XBOX_360
#else
#	error Unsupported platform, define a new one in jlCore.h if you need to
#endif

/// COMPILERS
#define JL_COMPILER_MSVC 1	// microsoft visual c++
#define JL_COMPILER_GCC 2	// g++ or its mingw variant

/// DETECT COMPILER
#if defined(_MSC_VER)
#	define JL_COMPILER JL_COMPILER_MSVC
#elif defined(__GNUC__)
#	define JL_COMPILER JL_COMPILER_GCC
#else
#	error Unknown compiler, define a new one in jlCore.h
#endif

/// ENDIANNESS
#define JL_BIG_ENDIAN 1
#define JL_LITTLE_ENDIAN 2

/// ARCHITECTURES
#define JL_ARCH_X86 1

/// DETECT ARCHITECTURE/ENDIANNESS
#if defined(__i386__) || defined(_M_IX86)
#	define JL_ARCH JL_ARCH_X86
#	define JL_ENDIANNESS JL_LITTLE_ENDIAN
#	define JL_SUPPORTS_INTRINSICS 1
#	define JL_PLATFORM_USE_DEFAULT_BOOLEANS
#else
#	error Unknown architecture, define a new one in jlCore.h
#endif

/// COMPILER SPECIFIC KEYWORDS/MACROS
#if JL_COMPILER == JL_COMPILER_MSVC
#	define JL_INLINE inline
#	define JL_FORCE_INLINE __forceinline
#	define JL_ALIGN(ALIGNMENT) __declspec(align(ALIGNMENT))
#	define JL_ALIGN_16 __declspec(align(16))
#	define JL_RESTRICT __restrict
#else // JL_COMPILER_GCC
#	define JL_INLINE inline
#	define JL_FORCE_INLINE inline
#	define JL_ALIGN(ALIGNMENT) __attribute__ ((aligned (ALIGNMENT)))
#	define JL_ALIGN_16 __attribute__ ((aligned (16)))
#	define JL_RESTRICT __restrict__
#endif

// DETERMINE TYPES
#include "util/jlTypes.h"

// CUSTOM MEMORY ALLOCATORS
#include "util/jlMemory.h"

// DEBUG MODE
#if (_DEBUG)
#	define JL_DEBUG
#	define JL_ASSERTIONS_ENABLED
#endif

// MISCELLANOUS
#define JL_UNREFERENCED(p) (p)
#define JL_JOIN(X, Y) JL_DO_JOIN(X, Y)
#define JL_DO_JOIN(X, Y) JL_DO_JOIN2(X,Y)
#define JL_DO_JOIN2(X, Y) X##Y
#define JL_SAFE_DELETE(ptr) if (ptr) { delete ptr;  ptr = JL_NULL; }
#define JL_SAFE_DELETE_ARRAY(aptr) if (aptr) { delete [] aptr; aptr = JL_NULL; }
#ifdef _UNICODE
#	define JL_WIDEN(STR) JL_JOIN(L, STR)
#else
#	define JL_WIDEN(STR) STR
#endif
#define JL_DISALLOW_COPY_AND_ASSIGN(TYPE) \
	TYPE(const TYPE&);   \
	void operator=(const TYPE&)


// ENABLE/DISABLE ASSERTIONS
#ifdef JL_ASSERTIONS_ENABLED
#	define JL_SLOW_ASSERTIONS_ENABLED
#else
#	if JL_SLOW_ASSERTIONS_ENABLED
#		pragma message("JL_SLOW_ASSERT cannot be enabled if JL_ASSERT is disabled")
#	endif
#	undef JL_SLOW_ASSERTIONS_ENABLED
#endif

// ASSERTION BEHAVOIRS
#define JL_HALT() __debugbreak()
#define JL_UNUSED(x) do { (void)sizeof(x); } while(0)

#define JL_ON_ASSERT_EXIT 1
#define JL_ON_ASSERT_HALT 2

#ifdef JL_DEBUG
#	define JL_DEFAULT_ON_ASSERT JL_ON_ASSERT_HALT
#else
#	define JL_DEFAULT_ON_ASSERT JL_ON_ASSERT_EXIT
#endif

/// ASSERTION HANDLING
enum jlAssertionBehavoir {
	BEHAVOIR_EXIT = 0,
	BEHAVOIR_HALT = 1
};

typedef jlAssertionBehavoir (*jlAssertionHandler) (const char8 *cond, const char8 *msg, const char8 *file, int32 line);

void jlSetAssertionHandler(jlAssertionHandler handler);
jlAssertionHandler jlGetAssertionHandler();
jlAssertionBehavoir jlReportAssertion(const char8 *cond, const char8 *file, int32 line, const char8 *msg, ...);

/// @see http://cnicholson.net/2009/03/stupid-c-tricks-dowhile0-and-c4127/
/// It removes the annoying warning in a reusable way that doesn't require the user 
/// to remember the warning number every time they come across this problem
/// Yes I know it's ugly, but all your assert macros will whine otherwise
#define JL_MULTILINE_MACRO_END \
	__pragma(warning(push)) \
	__pragma(warning(disable:4127)) \
	} while(0) \
	__pragma(warning(pop))

// ASSERTIONS
#if defined(JL_ASSERTIONS_ENABLED)
#	define JL_ASSERT(cond) \
	do \
	{ \
		if (!(cond)) \
		{ \
			if (jlReportAssertion(#cond, __FILE__, __LINE__, 0) == BEHAVOIR_HALT) \
				JL_HALT(); \
		} \
	JL_MULTILINE_MACRO_END
#	define JL_ASSERT_MSG(cond, msg, ...) \
	do \
	{ \
		if (!(cond)) \
		{ \
			if (jlReportAssertion(#cond, __FILE__, __LINE__, (msg), __VA_ARGS__) == BEHAVOIR_HALT) \
				JL_HALT(); \
		} \
	JL_MULTILINE_MACRO_END
#	define JL_ASSERT_NO_LOG(cond) \
	do \
	{ \
		if (!(cond)) \
		{ \
			if (JL_ON_ASSERT_HALT) \
				JL_HALT(); \
			else \
				abort(); \
		} \
	JL_MULTILINE_MACRO_END

	// used for static asserts to force early compile time errors
	template<bool> class jlCompileTimeCheck {
	public:
		jlCompileTimeCheck(...) {}
	};
	template<> class jlCompileTimeCheck<false> { };

#	define JL_DO_STATIC_ASSERT(test, errorStructName) \
	struct errorStructName {}; 	\
	typedef jlCompileTimeCheck< (test) != 0 > tmplimpl; \
	tmplimpl aTemp = tmplimpl(errorStructName()); \
	sizeof(aTemp)

#	define JL_STATIC_ASSERT(test)  \
	do { \
		JL_DO_STATIC_ASSERT((test), JL_JOIN(ERROR_STATIC_ASSERT_, __COUNTER__)); \
	JL_MULTILINE_MACRO_END
#	define JL_STATIC_ASSERT_FAIL() \
	do { \
		JL_DO_STATIC_ASSERT(0, JL_JOIN(ERROR_STATIC_ASSERT_, __COUNTER__)); \
	JL_MULTILINE_MACRO_END
#else
#	define JL_ASSERT(cond) \
		do { JL_UNUSED(cond); } while(0)
#	define JL_ASSERT_MSG(cond, msg, ...) \
		do { JL_UNUSED(cond); } while(0)
#	define JL_ASSERT_NO_LOG(cond) \
		do { JL_UNUSED(cond); } while(0)
#	define JL_STATIC_ASSERT(cond) \
		do { JL_UNUSED(cond); } while(0)
#	define JL_STATIC_ASSERT_FAIL() \
		do { JL_UNUSED(cond); } while(0)
#endif

// SLOW ASSERT (if assert conditions are too expensive in debug builds)
#if defined(JL_SLOW_ASSERTIONS_ENABLED)
#	define JL_SLOW_ASSERT(cond) \
	do \
	{ \
		if (!(cond)) \
		{ \
			if (jlReportAssertion(#cond, __FILE__, __LINE__, 0) == BEHAVOIR_HALT) \
				JL_HALT(); \
		} \
	JL_MULTILINE_MACRO_END
#	define JL_SLOW_ASSERT_MSG(cond, msg, ...) \
	do \
	{ \
		if (!(cond)) \
		{ \
			if (jlReportAssertion(#cond, __FILE__, __LINE__, (msg), __VA_ARGS__) == BEHAVOIR_HALT) \
				JL_HALT(); \
		} \
	JL_MULTILINE_MACRO_END
#else
#	define JL_SLOW_ASSERT(cond) \
		do { JL_UNUSED(cond); } while(0)
#	define JL_SLOW_ASSERT_MSG(cond, msg, ...) \
		do { JL_UNUSED(cond); } while(0)
#endif

template <typename T> 
JL_FORCE_INLINE void jlSwap(T& a, T& b) {
	T tmp = a;
	a = b;
	b = tmp;
}

#endif // JL_CORE_H
