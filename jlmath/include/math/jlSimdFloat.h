/// @file jlSimdFloat.h
/// @author Jeff Lansing

#ifndef JL_SIMD_FLOAT_H
#define JL_SIMD_FLOAT_H

#include "jlCore.h"
#include "math/jlComp.h"

/// A SIMD optimized type wrapper that is intended 
/// to be used like a floating point variable.  This helps 
/// avoid mixing FPU and SIMD math which cause pipeline 
/// stalls in performance critical code.  A wrapper is 
/// given in the absence of SIMD types, and should be used 
/// for portable benefits.
class jlSimdFloat {
public:
	jlSimdFloat();
	jlSimdFloat(float32 fl);
	jlSimdFloat(const quad128& qf);
	jlSimdFloat(const jlSimdFloat& sf);
	jlSimdFloat& operator =(const jlSimdFloat& sf);
	operator float32() const;
	float32 getFloat() const;
	void setFromFloat(float32 fl);
	
	// arithmetic ops
	jlSimdFloat operator +(const jlSimdFloat& rhs) const;
	jlSimdFloat operator -(const jlSimdFloat& rhs) const;
	jlSimdFloat operator *(const jlSimdFloat& rhs) const;
	jlSimdFloat operator /(const jlSimdFloat& rhs) const;
	jlSimdFloat operator -() const;
	jlSimdFloat& operator +=(const jlSimdFloat& rhs);
	jlSimdFloat& operator -=(const jlSimdFloat& rhs);
	jlSimdFloat& operator *=(const jlSimdFloat& rhs);
	jlSimdFloat& operator /=(const jlSimdFloat& rhs);
	
	// comparison ops
	bool32 operator <(const jlSimdFloat& rhs) const;
	bool32 operator >(const jlSimdFloat& rhs) const;
	bool32 operator ==(const jlSimdFloat& rhs) const;
	bool32 operator !=(const jlSimdFloat& rhs) const;
	bool32 operator <=(const jlSimdFloat& rhs) const;
	bool32 operator >=(const jlSimdFloat& rhs) const;
	jlComp compEqual(const jlSimdFloat& rhs) const;
	jlComp compNotEqual(const jlSimdFloat& rhs) const;
	jlComp compLess(const jlSimdFloat& rhs) const;
	jlComp compGreater(const jlSimdFloat& rhs) const;
	jlComp compLessEqual(const jlSimdFloat& rhs) const;
	jlComp compGreaterEqual(const jlSimdFloat& rhs) const;

	// misc
	void setZero();
	void setMin(const jlSimdFloat& a, const jlSimdFloat& b);
	void setMax(const jlSimdFloat& a, const jlSimdFloat& b);

	jlSimdInternalFloat f;
};

#if (JL_SIMD_ENABLED)
	#include "math/jlSimdFloatSSE.inl"
#else
	#include "math/jlSimdFloatFPU.inl"
#endif

#endif // JL_SIMD_FLOAT_H
