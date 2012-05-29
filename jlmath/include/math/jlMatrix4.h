/// @file jlMatrix4.h
/// @author Jeff Lansing

#ifndef JL_MATRIX4_H
#define JL_MATRIX4_H

#include "math/jlMath.h"
#include "math/jlVector2.h"
#include "math/jlVector4.h"
#include "math/jlQuaternion.h"

/// Column major SIMD friendly interface for matrices
/// Used primarily for linear transformations of vectors
/// If the last w component of an jlVector4 is 1 it will 
/// be transformed like a pt, if 0 it will be transformed 
/// like a vector.  Use transformPosition/transformDirection 
/// to force a desired behavior if necessary.
class jlMatrix4 {
public:
	jlMatrix4();
	jlMatrix4(const jlVector4& c0, const jlVector4& c1, const jlVector4& c2, const jlVector4& c3);
	jlMatrix4(float32 m11, float32 m12, float32 m13, float32 m14, float32 m21, float32 m22, float32 m23, float32 m24, 
		float32 m31, float32 m32, float32 m33, float32 m34, float32 m41, float32 m42, float32 m43, float32 m44);
	jlMatrix4& operator =(const jlMatrix4& m);

	// accessors/setters
	float32& operator ()(int32 row, int32 col);
	const float32& operator ()(int32 row, int32 col) const;
	bool32 isOk() const;
	void storeColMajor(float32 *cm) const;
	void storeColMajorAligned(float32 *cm) const;
	void storeRowMajor(float32 *rm) const;
	void storeRowMajorAligned(float32 *rm) const;
	void loadColMajor(const float32 *cm);
	void loadColMajorAligned(const float32 *cm);
	void loadRowMajor(const float32 *rm);
	void loadRowMajorAligned(const float32 *rm);
	template <int32 row, int32 col> jlSimdFloat getElem() const;
	template <int32 row, int32 col> void setElem(const jlSimdFloat& s);
	const jlVector4& getColumn(int32 c) const;
	jlVector4& getColumn(int32 c);
	jlVector4 getRow(int32 i) const;
	void setColumn(const jlVector4& c, int32 i);
	void setRow(const jlVector4& r, int32 i);
	void setZero();
	void setIdentity();
	void setAll(const jlSimdFloat& sf);
	void setDiagonal(const jlVector4& diag);
	
	// operators
	jlMatrix4 operator +(jlMatrix4& rhs) const;
	jlMatrix4 operator -(jlMatrix4& rhs) const;
	jlMatrix4 operator *(const jlMatrix4& rhs) const;
	jlVector4 operator *(const jlVector4& rhs) const;
	jlMatrix4 operator *(const jlSimdFloat& s) const;
	jlMatrix4 operator -() const;
	jlMatrix4& operator +=(jlMatrix4& rhs);
	jlMatrix4& operator -=(jlMatrix4& rhs);
	jlMatrix4& operator *=(const jlMatrix4& rhs);
	jlMatrix4& operator *=(const jlSimdFloat& s);

	// arithmetic ops
	void setAdd(const jlMatrix4& m0, const jlMatrix4& m1);
	void setSub(const jlMatrix4& m0, const jlMatrix4& m1);
	void setMul(const jlMatrix4& m, const jlSimdFloat& s);
	void setMul(const jlMatrix4& m0, const jlMatrix4& m1);
	void setNegation(const jlMatrix4& m);
	void add(const jlMatrix4& m);
	void sub(const jlMatrix4& m);
	void mul(const jlSimdFloat& s);
	void mul(const jlMatrix4& m);
	jlVector4 mul(const jlVector4& v) const; // alias of transform
	void negate();
	jlVector4 transform(const jlVector4& vec) const;
	jlVector2 transform(const jlVector2& vec) const;
	jlVector4 transformPosition(const jlVector4& vec) const;
	jlVector2 transformPosition(const jlVector2& vec) const;
	jlVector4 transformDirection(const jlVector4& vec) const;
	jlVector2 transformDirection(const jlVector2& vec) const;

	// misc
	jlMatrix4 getTranspose() const;
	void transpose();
	jlMatrix4 inverse() const;
	void invert();
	bool32 equals(const jlMatrix4& m) const;
	bool32 operator ==(const jlMatrix4& m) const;
	bool32 operator !=(const jlMatrix4& m) const;
	bool32 isZero() const;
	bool32 isIdentity() const;
	bool32 isAffine() const;

	// internal data
	jlVector4 col0;
	jlVector4 col1;
	jlVector4 col2;
	jlVector4 col3;

	// conversion/creation
	void makeTranslation(const jlSimdFloat& tx, const jlSimdFloat& ty, const jlSimdFloat& tz);
	void makeTranslation(const jlVector4& t);
	void makeScale(const jlSimdFloat& sx, const jlSimdFloat& sy, const jlSimdFloat& sz);
	void makeScale(const jlVector4& sv);
	void makeRotationZ(const jlSimdFloat& rad);
	void makeRotationY(const jlSimdFloat& rad);
	void makeRotationX(const jlSimdFloat& rad);
	void fromQuaternion(const jlQuaternion& q);
	jlQuaternion toQuaternion() const;

	static const jlMatrix4 ZERO;
	static const jlMatrix4 IDENTITY;
	static const jlMatrix4 NEG_IDENTITY;
};

jlMatrix4 operator *(const jlSimdFloat& s, const jlMatrix4& m);

#include "math/jlMatrix4.inl"

#endif // JL_MATRIX4_H
