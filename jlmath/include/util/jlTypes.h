/// @file jlTypes.h
/// @authors Jeff Lansing
/// Custom platform independent typedefs

#ifndef JL_TYPES_H
#define JL_TYPES_H

#include <cfloat>
#include <limits>
//#include <string>

/// STATUS/ERROR CODES
enum jlResult {
	JL_FILE_NOT_FOUND = -2,
	JL_BAD_ALLOC = -1,
	JL_ERROR = 0,
	JL_OK = 1
};

#define JL_FAILED(sr) (((jlResult)sr) <= JL_ERROR)

/// PLATFORM INDEPENDENT TYPEDEFS
typedef char char8;
typedef unsigned char uchar8;
typedef signed char int8;
typedef uchar8 uint8;
typedef short int int16;
typedef unsigned short int uint16;
typedef signed int int32;
typedef signed int bool32;
typedef unsigned int uint32;
typedef long long int int64;
typedef unsigned long long int uint64;
typedef float float32;
typedef double float64;

/// NULL EQUIVALENT
const int32 JL_NULL = 0;

// NUMERIC TYPE LIMITS/RANGES
const char8 CHAR8_MIN = CHAR_MIN;
const char8 CHAR8_MAX = CHAR_MAX;
const int8 INT8_MIN = SCHAR_MIN;
const int8 INT8_MAX = SCHAR_MAX;
const uchar8 UCHAR8_MAX = UCHAR_MAX;
const uint8 UINT8_MAX = UCHAR_MAX;

const int16 INT16_MIN = SHRT_MIN;
const int16 INT16_MAX = SHRT_MAX;
const uint16 UINT16_MAX = USHRT_MAX;

const int32 INT32_MIN = INT_MIN;
const int32 INT32_MAX = INT_MAX;
const uint32 UINT32_MAX = UINT_MAX;
const bool32 BOOL32_TRUE = 1;
const bool32 BOOL32_FALSE = 0;

const int64 INT64_MIN = LLONG_MIN;
const int64 INT64_MAX = LLONG_MAX;
const uint64 UINT64_MAX = ULLONG_MAX;

const float32 FLOAT32_MIN = FLT_MIN;
const float32 FLOAT32_MAX = FLT_MAX;
const float32 FLOAT32_EPSILON = FLT_EPSILON;
const float32 FLOAT32_INFINITY = std::numeric_limits<float32>::infinity();
const float32 FLOAT32_NEG_INFINITY = -FLOAT32_INFINITY;

const float64 FLOAT64_MIN = DBL_MIN;
const float64 FLOAT64_MAX = DBL_MAX;
const float64 FLOAT64_EPSILON = DBL_EPSILON;
const float64 FLOAT64_INFINITY = std::numeric_limits<float64>::infinity();
const float64 FLOAT64_NEG_INFINITY = -FLOAT64_INFINITY;

#ifdef JL_PLATFORM_USE_DEFAULT_BOOLEANS
typedef bool bool8;
#else
/// Forces booleans to be represented by an 8 bit value
/// Regardless of compilers/architectures that make C++'s 
/// bool type a greater size
class bool8 {
public:
	JL_FORCE_INLINE bool8() { }
	
	JL_FORCE_INLINE bool8(bool cb) {
		b = static_cast<uint8>(cb);
	}

	JL_FORCE_INLINE operator bool() const {
		return b != 0;
	}

	JL_FORCE_INLINE operator bool8() const { 
		return bool8(b != 0); 
	}

	JL_FORCE_INLINE bool8& operator =(bool cb) {
		b = static_cast<uint8>(cb);
		return *this;
	}

	JL_FORCE_INLINE bool8 operator ==(bool cb) const {
		(b != 0) == cb;
	}

	JL_FORCE_INLINE bool8 operator !=(bool cb) const {
		return (b != 0) != cb;
	}
private:
	uint8 b;
};
#endif


// INTRINSICS SUPPORTED?
#ifndef JL_SIMD_ENABLED
#	ifdef JL_SUPPORTS_INTRINSICS
#		define JL_SIMD_ENABLED 1
#	else
#		define JL_SIMD_ENABLED 0
#	endif
#else
#	ifndef JL_SUPPORTS_INTRINSICS
#		error You cannot enable SIMD on a platform that doesn't support it
#	endif
#endif

// INTRINSICS TYPE quad128/quadint128
// For platform independence, struct with the same name is provided 
// which uses floats/ints
#if (JL_SIMD_ENABLED && JL_PLATFORM == JL_PLATFORM_WINDOWS)
	#include <xmmintrin.h>
	#include <emmintrin.h>	

	typedef __m128 quad128; // used by jlVector4
	typedef __m128i quadint128; // used by random number generators
	typedef quad128 jlSimdInternalFloat; // used by jlSimdFloat
	typedef quad128 jlCompMask; // used by jlComp

	const quad128 QUAD_ZERO = _mm_setzero_ps();
	const quad128 QUAD_MIN = _mm_set_ps1(FLOAT32_MIN);
	const quad128 QUAD_MAX = _mm_set_ps1(FLOAT32_MAX);
	const quad128 QUAD_ONE = _mm_set_ps1(1.0f);
	const quad128 QUAD_TWO = _mm_set_ps1(2.0f);
	const quad128 QUAD_THREE = _mm_set_ps1(3.0f);
	const quad128 QUAD_FOUR = _mm_set_ps1(4.0f);
	const quad128 QUAD_INV_TWO = _mm_set_ps1(0.5f);
	const quad128 QUAD_INV_THREE = _mm_set_ps1(1.0f / 3.0f);
	const quad128 QUAD_INV_FOUR = _mm_set_ps1(0.25f);
	const quad128 QUAD_SINGLE_ZERO = _mm_set_ss(0.0f);
	const quad128 QUAD_SINGLE_ONE = _mm_set_ss(1.0f);
	const quad128 QUAD_SINGLE_TWO = _mm_set_ss(2.0f);
	const quad128 QUAD_SINGLE_THREE = _mm_set_ss(3.0f);
	const quad128 QUAD_SINGLE_FOUR = _mm_set_ss(4.0f);
	const quad128 QUAD_SINGLE_INV_TWO = _mm_set_ss(0.5f);
	const quad128 QUAD_SINGLE_INV_THREE = _mm_set_ss(1.0f / 3.0f);
	const quad128 QUAD_SINGLE_INV_FOUR = _mm_set_ss(1.0f / 4.0f);
#else
	struct quad128 {
	public:
		JL_ALIGN_16 float32 v[4];
		
		quad128() { }

		quad128(float32 x, float32 y, float32 z, float32 w) {
			v[0] = x;
			v[1] = y;
			v[2] = z;
			v[3] = w;
		}

		quad128(const float32 *arr) { 
			v[0] = arr[0];
			v[1] = arr[1];
			v[2] = arr[2];
			v[3] = arr[3];
		}
	};

	struct quadint128 {
	public:
		JL_ALIGN_16 uint32 v[4];
		
		quadint128() { }

		quadint128(uint32 x, uint32 y, uint32 z, uint32 w) {
			v[0] = x;
			v[1] = y;
			v[2] = z;
			v[3] = w;
		}

		quadint128(const uint32 *arr) { 
			v[0] = arr[0];
			v[1] = arr[1];
			v[2] = arr[2];
			v[3] = arr[3];
		}
	};
	
	typedef float32 jlSimdInternalFloat; // used by jlSimdFloat
	typedef int32 jlCompMask; // used by jlComp

	const quad128 QUAD_ZERO(0.0f, 0.0f, 0.0f, 0.0f);
	const quad128 QUAD_MIN(FLOAT32_MIN, FLOAT32_MIN, FLOAT32_MIN, FLOAT32_MIN);
	const quad128 QUAD_MAX(FLOAT32_MAX, FLOAT32_MAX, FLOAT32_MAX, FLOAT32_MAX);
	const quad128 QUAD_ONE(1.0f, 1.0f, 1.0f, 1.0f);
	const quad128 QUAD_TWO(2.0f, 2.0f, 2.0f, 2.0f);
	const quad128 QUAD_THREE(3.0f, 3.0f, 3.0f, 3.0f);
	const quad128 QUAD_FOUR(4.0f, 4.0f, 4.0f, 4.0f);
	const quad128 QUAD_INV_TWO(0.5f, 0.5f, 0.5f, 0.5f);
	const quad128 QUAD_INV_THREE(1.0f / 3.0f, 1.0f / 3.0f, 1.0f / 3.0f, 1.0f / 3.0f);
	const quad128 QUAD_INV_FOUR(0.25f, 0.25f, 0.25f, 0.25f);
	const quad128 QUAD_SINGLE_ZERO(0.0f, 0.0f, 0.0f, 0.0f);
	const quad128 QUAD_SINGLE_ONE(1.0f, 0.0f, 0.0f, 0.0f);
	const quad128 QUAD_SINGLE_TWO(2.0f, 0.0f, 0.0f, 0.0f);
	const quad128 QUAD_SINGLE_THREE(3.0f, 0.0f, 0.0f, 0.0f);
	const quad128 QUAD_SINGLE_FOUR(4.0f, 0.0f, 0.0f, 0.0f);
	const quad128 QUAD_SINGLE_INV_TWO(0.5f, 0.0f, 0.0f, 0.0f);
	const quad128 QUAD_SINGLE_INV_THREE(1.0f / 3.0f, 0.0f, 0.0f, 0.0f);
	const quad128 QUAD_SINGLE_INV_FOUR(1.0f / 4.0f, 0.0f, 0.0f, 0.0f);
#endif

#endif // JL_TYPES_H
