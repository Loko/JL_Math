/// @file jlQuaternion.h
/// @author Jeff Lansing

#ifndef JL_QUATERNION_H
#define JL_QUATERNION_H

#include "math/jlVector4.h"

/// A SIMD friendly quaternion
/// Internally wraps a vector4
class jlQuaternion {
public:
	JL_DECLARE_ALIGNED_ALLOC_OBJECT(16);

	jlQuaternion();
	jlQuaternion(const jlVector4& qvec);
	jlQuaternion(float32 x, float32 y, float32 z, float32 w);
	jlQuaternion(const jlQuaternion& cpy);
	jlQuaternion& operator =(const jlQuaternion& rhs);
	
	// accessors/setters
	float32& operator ()(int32 i);
	const float32& operator ()(int32 i) const;
	bool32 isOk() const;
	void store(float32 *ptr) const;
	void storeAligned(float32 *ptr) const;
	void load(const float32 *ptr);
	void loadAligned(const float32 *ptr);
	template <int32 i> jlSimdFloat getElem() const;
	template <int32 i> void setElem(const jlSimdFloat& s);
	void set(float32 x, float32 y, float32 z, float32 w);
	void set(const jlSimdFloat& x, const jlSimdFloat& y, const jlSimdFloat& z, const jlSimdFloat& w);
	void setAll(const jlSimdFloat& v);
	void setZero();
	void setAxisAngle(const jlVector4& axis, const jlSimdFloat &angle);
	void setIdentity();
	
	// set from euler
	// setRotationX
	// setRotationY
	// setRotationZ
	
	// operators
	jlQuaternion operator +(const jlQuaternion& rhs) const;
	jlQuaternion operator -(const jlQuaternion& rhs) const;
	jlQuaternion operator *(const jlQuaternion& rhs) const;
	jlVector4 operator *(const jlVector4& rhs) const;
	jlQuaternion operator *(const jlSimdFloat& s) const;
	jlQuaternion operator -() const;

	// arithmetic
	void setAdd(const jlQuaternion& a, const jlQuaternion& b);
	void setMul(const jlQuaternion& a, const jlQuaternion& b);
	void setMul(const jlQuaternion& q, const jlSimdFloat& s);
	void setSub(const jlQuaternion& a, const jlQuaternion& b);
	void setNegation(const jlQuaternion& q);
	void add(const jlQuaternion& rhs);
	void sub(const jlQuaternion& rhs);
	void negate();
	
	// dot/normalize/inverse
	jlSimdFloat dot(const jlQuaternion& q) const;
	void normalize();
	jlQuaternion inverse() const;
	jlQuaternion unitInverse() const;
	bool32 equals(const jlQuaternion& rhs) const;
	bool32 operator ==(const jlQuaternion& rhs) const;
	bool32 operator !=(const jlQuaternion& rhs) const;

	// internal data
	jlVector4 vec;

	static jlQuaternion Slerp(const jlQuaternion& q0, const jlQuaternion& q1, const jlSimdFloat& t);
	static jlQuaternion Nlerp(const jlQuaternion& q0, const jlQuaternion& q1, const jlSimdFloat& t);

	static const jlQuaternion ZERO;
	static const jlQuaternion IDENTITY;
};

#include "math/jlQuaternion.inl"

#endif // JL_QUATERNION_H
