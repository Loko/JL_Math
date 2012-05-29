/// @file jlMath.h
/// @author Jeff Lansing

#ifndef JL_MATH_H
#define JL_MATH_H

#include "jlCore.h"
#include "math/jlSimdFloat.h"
#include <cmath>

/// Custom math functions for more control and optimization opportunities
/// Gives scope to custom math calls and support for our custom typedefs
/// Gives us the possibility to implement platform specific instructions and 
/// things like bitshifting to avoid branches when deemed necessary
/// Caches frequently used variables (e.g. LOG2) and lookup tables for trig functions
class jlMath {
public:
	static const float32 PI;
	static const float32 TWO_PI;
	static const float32 PI_OVER_TWO;
	static const float32 PI_OVER_FOUR;
	static const float32 ONE_OVER_PI;
	static const float32 ONE_OVER_TWO_PI;
	static const float32 DEG2RAD;
	static const float32 RAD2DEG;
	static const float32 LOG2;
	static const int32 DEFAULT_TRIG_TABLE_SIZE;

	// trig functions
	static float32 Cos(float32 x);
	static jlSimdFloat FastCos(const jlSimdFloat& x);
	static float32 Sin(float32 x);
	static jlSimdFloat FastSin(const jlSimdFloat& x);
	static float32 Tan(float32 x);
	static float32 ASin(float32 x);
	static float32 ACos(float32 x);
	static float32 ATan(float32 x);
	static float32 ATan2(float32 y, float32 x);
	static float32 DegreesToRadians(float32 deg);
	static float32 RadiansToDegrees(float32 rad);
	static float32 WrapAngle(float32 x);

	// trig lookup tables
	static jlResult SetupTrigTables(int32 tableSize = DEFAULT_TRIG_TABLE_SIZE);
	static jlResult UnloadTrigTables();
	static float32 Cos(float32 x, bool8 useTable);
	static float32 Sin(float32 x, bool8 useTable);
	static float32 Tan(float32 x, bool8 useTable);

	// numerical robustness
	static bool32 FloatEquals(float32 x, float32 y, float32 absTolerance);
	static bool32 FloatEquals(float32 x, float32 y, float32 absTolerance, float32 relTolerance);
	static bool32 IsNaN(float32 x);

	// abs, min, max, clamp, sign
	static float32 Abs(float32 x);
	static jlSimdFloat Abs(const jlSimdFloat& x);
	static int32 IAbs(int32 x);
	static float32 Clamp(float32 x, float32 min, float32 max);
	static jlSimdFloat Clamp(const jlSimdFloat& x, const jlSimdFloat& min, const jlSimdFloat& max);
	static int32 IClamp(int32 x, int32 min, int32 max);
	template<typename T> static T Clamp(T x, T min, T max);
	static float32 Floor(float32 x);
	static float32 Ceil(float32 x);
	static float32 Min(float32 x, float32 y);
	static jlSimdFloat Min(const jlSimdFloat& x, const jlSimdFloat& y);
	static int32 IMin(int32 x, int32 y);
	template<typename T> static T Min(T x, T y);
	static float32 Max(float32 x, float32 y);
	static jlSimdFloat Max(const jlSimdFloat& x, const jlSimdFloat& y);
	static int32 IMax(int32 x, int32 y);
	template<typename T> static T Max(T x, T y);
	static float32 Sign(float32 x);
	static int32 ISign(int32 x);
	static float32 IsPositive(float32 x);
	static float32 IsNegative(float32 x);

	// pow, sqrt, log
	static float32 Pow(float32 x, float32 power);
	static float32 Pow(float32 x, int32 power);
	static bool32 IsPowerOf2(int32 x);
	static int32 NearestPowerOf2(int32 x);
	static float32 Sqrt(float32 x);
	static jlSimdFloat Sqrt(const jlSimdFloat& x);
	static float32 InvSqrt(float32 x);
	static jlSimdFloat InvSqrt(const jlSimdFloat& x);
	static float32 FastInvSqrt(float32 x);
	static float32 Log(float32 x);
	static float32 Log2(float32 x);
	static float32 LogN(float32 x, float32 n);

	// interpolation
	static float32 Saturate(float32 x);
	static jlSimdFloat Saturate(const jlSimdFloat& x);
	static float32 Lerp(float32 a, float32 b, float32 t);
	static jlSimdFloat Lerp(const jlSimdFloat& a, const jlSimdFloat& b, const jlSimdFloat& t);
	static float32 SmoothStep(float32 a, float32 b, float32 t);
	static jlSimdFloat SmoothStep(const jlSimdFloat& a, const jlSimdFloat& b, const jlSimdFloat& t);
	static float32 SmootherStep(float32 a, float32 b, float32 t);
	static jlSimdFloat SmootherStep(const jlSimdFloat& a, const jlSimdFloat& b, const jlSimdFloat& t);

#if (JL_MATH_TRIG_TABLES)
private:
	static float32 *sinTable;
	static float32 *tanTable;
	static int32 trigTableSize;
	static float32 trigTableFactor;
#endif	
};

#include "math/jlMath.inl"

#if (JL_SIMD_ENABLED)
	#include "math/jlMathSSE.inl"
#else
	#include "math/jlMathFPU.inl"
#endif

#endif // JL_MATH_H
