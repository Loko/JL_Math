JL_FORCE_INLINE float32 jlMath::Cos(float32 x) {
	return cos(x);
}

JL_FORCE_INLINE float32 jlMath::Sin(float32 x) {
	return sin(x);
}

JL_FORCE_INLINE float32 jlMath::Cos(float32 x, bool8 useTable) {
	#if JL_MATH_TRIG_TABLES
	if (useTable) {
		TBD_SLOW_ASSERT_MSG(trigTableSize > 0, "Haven't set the trig tables to a valid size!");
		x += PI_OVER_TWO;
		if (x >= 0.0f) {
			return sinTable[((int32)(x * trigTableFactor)) % trigTableSize];
		} else {
			return sinTable[(((int32)(-x * trigTableFactor)) % trigTableSize) - 1];
		}
	}
	#else
	JL_UNREFERENCED(useTable);
	#endif
	return Cos(x);
}

JL_FORCE_INLINE float32 jlMath::Sin(float32 x, bool8 useTable) {
	#if JL_MATH_TRIG_TABLES
	if (useTable) {
		TBD_SLOW_ASSERT_MSG(trigTableSize > 0, "Haven't set the trig tables to a valid size!");
		if (x >= 0.0f) {
			return sinTable[((int32)(x * trigTableFactor)) % trigTableSize];
		} else {
			return sinTable[(((int32)(-x * trigTableFactor)) % trigTableSize) - 1];
		}
	}
	#else
	JL_UNREFERENCED(useTable);
	#endif
	return Sin(x);
}

JL_FORCE_INLINE float32 jlMath::Tan(float32 x, bool8 useTable) {
	#if JL_MATH_TRIG_TABLES
	if (useTable) {
		TBD_SLOW_ASSERT_MSG(trigTableSize > 0, "Haven't set the trig tables to a valid size!");
		return tanTable[((int32)(x * trigTableFactor)) % trigTableSize];
	}
	#else
	JL_UNREFERENCED(useTable);
	#endif
	return Tan(x);
}

JL_FORCE_INLINE float32 jlMath::Tan(float32 x) {
	return tan(x);
}

JL_FORCE_INLINE float32 jlMath::ASin(float32 x) {
	if (-1.0f < x) {
		if (x < 1.0f) {
			return asin(x);
		} else {
			return PI_OVER_TWO;
		}
	} else {
		return -PI_OVER_TWO;
	}
}

JL_FORCE_INLINE float32 jlMath::ACos(float32 x) {
	if (-1.0f < x) {
		if (x < 1.0f) {
			return acos(x);
		} else {
			return 0.0f;
		}
	} else {
		return PI;
	}
}

JL_FORCE_INLINE float32 jlMath::ATan(float32 x) {
	return atan(x);
}

JL_FORCE_INLINE float32 jlMath::ATan2(float32 y, float32 x) {
	return atan2(y, x);
}

JL_FORCE_INLINE float32 jlMath::Sqrt(float32 x) {
	return sqrt(x);
}

JL_FORCE_INLINE float32 jlMath::InvSqrt(float32 x) {
	return 1.0f / sqrt(x);
}
	
JL_FORCE_INLINE float32 jlMath::FastInvSqrt(float32 x) {
	float32 xhalf = 0.5f * x;
	int32 i = *(int32 *) &x;
	i = 0x5f3759df - (i >> 1);
	x = *(float32 *) &i;
	x = x*(1.5f - xhalf * x * x);
	return x;
}

JL_FORCE_INLINE float32 jlMath::Abs(float32 x) {
	// could be done with bitshifting
	return (x < 0) ? -x : x;
}

JL_FORCE_INLINE int32 jlMath::IAbs(int32 x) {
	// could be done with bitshifting
	return (x < 0) ? -x : x;
}

JL_FORCE_INLINE float32 jlMath::Floor(float32 x) {
	return floor(x);
}

JL_FORCE_INLINE float32 jlMath::Ceil(float32 x) {
	return ceil(x);
}

JL_FORCE_INLINE float32 jlMath::Sign(float32 x) {
	// this is doable without branches, but not as portable
	// http://www.musicdsp.org/showone.php?id=249
	return static_cast<float32>(x > 0) - static_cast<float32>(x < 0);
}

JL_FORCE_INLINE int32 jlMath::ISign(int32 x) {
	// this is doable without branches, but not as portable
	// http://www.musicdsp.org/showone.php?id=249
	return (x > 0) - (x < 0);
}

JL_FORCE_INLINE float32 jlMath::IsPositive(float32 x) {
	return (x > 0.0f) ? 1.0f : 0.0f; 
}

JL_FORCE_INLINE float32 jlMath::IsNegative(float32 x) {
	return (x < 0.0f) ? 1.0f : 0.0f; 
}

JL_FORCE_INLINE bool32 jlMath::IsNaN(float32 x) {
	if (x != x)
		return true;
	return x == FLOAT32_INFINITY || x == FLOAT32_NEG_INFINITY;
}

JL_FORCE_INLINE float32 jlMath::Pow(float32 x, float32 power) {
	return pow(x, power);
}

JL_FORCE_INLINE float32 jlMath::Pow(float32 x, int32 power) {
	return pow(x, power);
}

JL_FORCE_INLINE bool32 jlMath::IsPowerOf2(int32 x) {
	return (x & (x - 1)) == 0;
}

JL_FORCE_INLINE int32 jlMath::NearestPowerOf2(int32 x) {
	--x;
    x |= x >> 16;
    x |= x >> 8;
    x |= x >> 4;
    x |= x >> 2;
    x |= x >> 1;
    ++x;
    return x;
}

JL_FORCE_INLINE float32 jlMath::Saturate(float32 x) {
	if (x < 0.0f) return 0.0f;
	if (x > 1.0f) return 1.0f;
	return x;
}

JL_FORCE_INLINE float32 jlMath::Clamp(float32 x, float32 min, float32 max) {
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

JL_FORCE_INLINE int32 jlMath::IClamp(int32 x, int32 min, int32 max) {
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

template<typename T>
JL_FORCE_INLINE T jlMath::Clamp(T x, T min, T max) {
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

JL_FORCE_INLINE float32 jlMath::Lerp(float32 a, float32 b, float32 t) {
	return a + (b - a) * t;
}

JL_FORCE_INLINE float32 jlMath::SmoothStep(float32 a, float32 b, float32 t) {
	float32 x = t * t * (3.0f - 2.0f * t);
	return a + ((b - a) * x);
}

JL_FORCE_INLINE float32 jlMath::SmootherStep(float32 a, float32 b, float32 t) {
	float32 x = t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f);
    return a + ((b - a) * x);
}

JL_FORCE_INLINE float32 jlMath::DegreesToRadians(float32 deg) {
	return deg * DEG2RAD;
}

JL_FORCE_INLINE float32 jlMath::Min(float32 x, float32 y) {
	return (x < y) ? x : y;
}

JL_FORCE_INLINE int32 jlMath::IMin(int32 x, int32 y) {
	return (x < y) ? x : y;
}

template<typename T>
JL_FORCE_INLINE T jlMath::Min(T x, T y) {
	return (x < y) ? x : y;
}

JL_FORCE_INLINE float32 jlMath::Max(float32 x, float32 y) {
	return (x < y) ? y : x;
}

JL_FORCE_INLINE int32 jlMath::IMax(int32 x, int32 y) {
	return (x < y) ? y : x;
}

template<typename T>
JL_FORCE_INLINE T jlMath::Max(T x, T y) {
	return (x < y) ? y : x;
}

JL_FORCE_INLINE bool32 jlMath::FloatEquals(float32 x, float32 y, float32 absTolerance) {
	return Abs(y - x) <= absTolerance;
}

JL_FORCE_INLINE bool32 jlMath::FloatEquals(float32 x, float32 y, float32 absTolerance, float32 relTolerance) {
	return Abs(y - x) <= Max(absTolerance, relTolerance * Max(Abs(x), Abs(y)));
}

JL_FORCE_INLINE float32 jlMath::RadiansToDegrees(float32 rad) {
	return rad * RAD2DEG;
}

JL_FORCE_INLINE float32 jlMath::Log(float32 x) {
	return log(x);
}

JL_FORCE_INLINE float32 jlMath::Log2(float32 x) {
	return log(x) / LOG2;
}

JL_FORCE_INLINE float32 jlMath::LogN(float32 x, float32 n) {
	return log(x) / log(n);
}

JL_FORCE_INLINE float32 jlMath::WrapAngle(float32 x) {
	x += PI;
	x -= Floor(x * ONE_OVER_PI) * TWO_PI;
	x -= PI;
	return x;
}