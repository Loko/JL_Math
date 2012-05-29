/// @file jlVector2.h
/// @authors Jeff Lansing

#ifndef JL_VECTOR2_H
#define JL_VECTOR2_H

#include "jlCore.h"
#include "math/jlMath.h"

/// A direction/point in 2D space
class jlVector2 {
public:
	jlVector2();
	jlVector2(float32 fx, float32 fy);
	jlVector2(const jlVector2& cpy);
	jlVector2& operator =(const jlVector2& vec);

	// accessors/setters
	const float32& operator()(int32 i) const;
	float32& operator()(int32 i);
	bool isOk() const;
	void store(float32 *ptr) const;
	void load(const float32 *ptr);
	void set(float32 fx, float32 fy);
	void setAll(float32 v);
	void setZero();
	bool isZero() const;
	bool isZero(float32 absTolerance) const;
	
	// operators
	jlVector2 operator +(const jlVector2& rhs) const;
	jlVector2 operator -(const jlVector2 &rhs) const;
	jlVector2 operator *(float32 s) const;
	jlVector2 operator *(const jlVector2& v) const;
	jlVector2 operator /(float32 d) const;
	jlVector2 operator /(const jlVector2& d) const;
	jlVector2 operator -() const;
	jlVector2& operator +=(const jlVector2& rhs);
	jlVector2& operator -=(const jlVector2 &rhs);
	jlVector2& operator *=(float32 s);
	jlVector2& operator *=(const jlVector2& rhs);
	jlVector2& operator /=(float32 d);
	jlVector2& operator /=(const jlVector2& d);

	// arithmetic/min/max
	void setAdd(const jlVector2& a, const jlVector2& b);
	void setSub(const jlVector2& a, const jlVector2& b);	
	void setMul(const jlVector2& v, float32 s);
	void setMul(const jlVector2& a, const jlVector2& b);
	void setDiv(const jlVector2& v, float32 s);
	void setDiv(const jlVector2& v, const jlVector2& d);
	void setMin(const jlVector2& a, const jlVector2& b);
	void setMax(const jlVector2& a, const jlVector2& b);
	void setNegation(const jlVector2& v);
	void add(const jlVector2& rhs);
	void sub(const jlVector2& rhs);
	void mul(float32 s);
	void mul(const jlVector2& scaleVector);
	void div(float32 d);
	void div(const jlVector2& d);
	void negate();

	// dot/cross/normalize
	float32 dot(const jlVector2& v) const;
	float32 length() const;
	float32 lengthSquared() const;
	void normalize();
	float32 normalizeWithLength();
	jlVector2 normalizedCopy() const;

	// comparisons
	bool equals(const jlVector2& v) const;
	bool equals(const jlVector2& v, float absTolerance) const;
	bool operator ==(const jlVector2& rhs) const;
	bool operator !=(const jlVector2& rhs) const;

	// internal data
	float32 x, y;

	static float32 Dot(const jlVector2& u, const jlVector2& v);
	static float32 Distance(const jlVector2& u, const jlVector2& v);
	static float32 DistanceSquared(const jlVector2& u, const jlVector2& v);
	static float32 Cross(const jlVector2& a, const jlVector2& b);
	static jlVector2 Cross(const jlVector2& v, float32 s);
	static jlVector2 Lerp(const jlVector2& a, const jlVector2& b, float32 t);
	static jlVector2 SmoothStep(const jlVector2& a, const jlVector2& b, float32 t);
	static jlVector2 Reflect(const jlVector2& v, const jlVector2& n);
	static jlVector2 RightPerp(const jlVector2& v);
	static jlVector2 LeftPerp(const jlVector2& v);
	static bool Equals(const jlVector2& a, const jlVector2& b, float32 absTolerance);
	
	// frequently used constants
	static const jlVector2 ZERO;
	static const jlVector2 UNIT_X;
	static const jlVector2 UNIT_Y;
	static const jlVector2 ONE;
	static const jlVector2 NEG_UNIT_X;
	static const jlVector2 NEG_UNIT_Y;
	static const jlVector2 NEG_ONE;
};

jlVector2 operator *(float32 s, const jlVector2& v);

#include "math/jlVector2.inl"

#endif // JL_VECTOR2_H
