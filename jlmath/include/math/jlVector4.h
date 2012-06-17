/// @file jlVector4.h
/// @author Jeff Lansing

#ifndef JL_VECTOR4_H
#define JL_VECTOR4_H

#include "jlCore.h"
#include "math/jlMath.h"
#include "math/jlSimdFloat.h"
#include "math/jlComp.h"

/// A SIMD friendly interface for manipulating vectors
/// Platform differences are resolved at this level, which 
/// make this same interface usable for quaternions and matrices
class jlVector4 {
public:
	JL_DECLARE_ALIGNED_ALLOC_OBJECT(16);

	jlVector4();
	jlVector4(float32 x, float32 y, float32 z, float32 w = 0.0f);
	explicit jlVector4(const quad128& q);
	jlVector4(const jlVector4& vec);
	jlVector4& operator =(const jlVector4& rhs);
	
	// accessors/setters
	float32& operator()(int32 i);
	const float32& operator()(int32 i) const;
	bool32 isOk() const;
	void store(float32 *ptr) const;
	void storeAligned(float32 *ptr) const;
	void load(const float32 *ptr);
	void loadAligned(const float32 *ptr);
	quad128& getQuad();
	const quad128& getQuad() const;
	template <int32 i> jlSimdFloat getElem() const;
	jlSimdFloat getElem(int32 i) const;
	template <int32 i> void setElem(const jlSimdFloat& s);
	void set(const jlSimdFloat& x, const jlSimdFloat& y, const jlSimdFloat& z, const jlSimdFloat& w = jlSimdFloat(0.0f));
	void set(float32 x, float32 y, float32 z, float32 w = 0.0f);
	void setAll(const jlSimdFloat& v);
	void setZero3();
	void setZero4();
	void splice(const jlCompMask& mask);

	// operators
	jlVector4 operator +(const jlVector4& rhs) const;
	jlVector4 operator -(const jlVector4& rhs) const;
	jlVector4 operator *(const jlSimdFloat& s) const;
	friend jlVector4 operator *(const jlSimdFloat& s, const jlVector4& v);
	jlVector4 operator *(const jlVector4& rhs) const;
	jlVector4 operator /(const jlSimdFloat& s) const;
	jlVector4 operator /(const jlVector4& rhs) const;
	jlVector4 operator -() const;
	jlVector4& operator +=(const jlVector4& rhs);
	jlVector4& operator -=(const jlVector4 &rhs);
	jlVector4& operator *=(const jlSimdFloat& s);
	jlVector4& operator /=(const jlSimdFloat& d);
	jlVector4& operator /=(const jlVector4& rhs);

	// arithmetic/min/max
	void setAdd(const jlVector4& a, const jlVector4& b);
	void setSub(const jlVector4& a, const jlVector4& b);
	void setMul(const jlVector4& a, const jlVector4& b);
	void setMul(const jlVector4& v, const jlSimdFloat& s);
	void setDiv(const jlVector4& v, const jlSimdFloat& s);
	void setDiv(const jlVector4& v, const jlVector4& d);
	void setCross(const jlVector4& lhs, const jlVector4& rhs);
	void setMin(const jlVector4& lhs, const jlVector4& rhs);
	void setMax(const jlVector4& lhs, const jlVector4& rhs);
	void setNegation(const jlVector4& vec);
	template <int32 i> void setReplication(const jlVector4& vec);
	void add(const jlVector4& rhs);
	void sub(const jlVector4& rhs);
	void mul(const jlVector4& rhs);
	void mul(const jlSimdFloat& s);
	void div(const jlSimdFloat& s);
	void div(const jlVector4& d);
	void negate();

	// dot/cross/normalize
	jlSimdFloat dot3(const jlVector4& rhs) const;
	jlSimdFloat dot4(const jlVector4& rhs) const;
	jlSimdFloat length3() const;
	jlSimdFloat lengthSquared3() const;
	jlSimdFloat length4() const;
	jlSimdFloat lengthSquared4() const;
	jlVector4 cross(const jlVector4& rhs) const;
	void normalize3();
	void normalize4();
	jlSimdFloat normalize3WithLength();

	// comparison operations
	jlComp compEqual(const jlVector4& vec) const;
	jlComp compNotEqual(const jlVector4& vec) const;
	jlComp compLess(const jlVector4& vec) const;
	jlComp compGreater(const jlVector4& vec) const;
	jlComp compLessEqual(const jlVector4& vec) const;
	jlComp compGreaterEqual(const jlVector4& vec) const;
	bool32 isZero3() const;
	bool32 isZero4() const;
	bool32 equals3(const jlVector4& vec) const;
	bool32 equals4(const jlVector4& vec) const;
	bool32 operator ==(const jlVector4& rhs) const;
	bool32 operator !=(const jlVector4& rhs) const;

	// internal data type
	JL_ALIGN_16 quad128 quad;

	static jlSimdFloat Dot3(const jlVector4& lhs, const jlVector4& rhs);
	static jlSimdFloat Dot4(const jlVector4& lhs, const jlVector4& rhs);
	static jlSimdFloat Distance(const jlVector4& lhs, const jlVector4& rhs);
	static jlSimdFloat DistanceSquared(const jlVector4& lhs, const jlVector4& rhs);
	static jlVector4 Cross(const jlVector4& lhs, const jlVector4& rhs);
	static jlVector4 Lerp(const jlVector4& a, const jlVector4& b, const jlSimdFloat& t);
	static jlVector4 Slerp(const jlVector4& a, const jlVector4& b, const jlSimdFloat& t);
	static jlVector4 SmoothStep(const jlVector4& a, const jlVector4& b, const jlSimdFloat& t);
	static jlVector4 Reflect(const jlVector4& v, const jlVector4& n);

	static const jlVector4 ZERO;
	static const jlVector4 UNIT_X;
	static const jlVector4 UNIT_Y;
	static const jlVector4 UNIT_W;
	static const jlVector4 NEG_UNIT_X;
	static const jlVector4 NEG_UNIT_Y;
	static const jlVector4 NEG_UNIT_Z;
	static const jlVector4 ZERO_PT;
	static const jlVector4 ONE;
	static const jlVector4 UNIT_Z;
};

#if (JL_SIMD_ENABLED)
	#include "math/jlVector4SSE.inl"
#else
	#include "math/jlVector4FPU.inl"
#endif

#endif // JL_VECTOR4_H
