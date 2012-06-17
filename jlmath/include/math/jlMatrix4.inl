

JL_FORCE_INLINE jlMatrix4::jlMatrix4() { }

JL_FORCE_INLINE jlMatrix4::jlMatrix4(const jlVector4& c0, const jlVector4& c1, const jlVector4& c2, 
	const jlVector4& c3) : col0(c0), col1(c1), col2(c2), col3(c3) {

}

JL_FORCE_INLINE jlMatrix4::jlMatrix4(float m11, float32 m12, float32 m13, float32 m14, float32 m21, float32 m22, float32 m23, float32 m24, 
									 float32 m31, float32 m32, float32 m33, float32 m34, float32 m41, float32 m42, float32 m43, float32 m44) 
{
	col0.set(m11, m21, m31, m41);
	col1.set(m12, m22, m32, m42);
	col2.set(m13, m23, m33, m43);
	col3.set(m14, m24, m34, m44);
}

JL_FORCE_INLINE jlMatrix4& jlMatrix4::operator =(const jlMatrix4& m) {
	col0 = m.col0;
	col1 = m.col1;
	col2 = m.col2;
	col3 = m.col3;
	return *this;
}

JL_FORCE_INLINE float32& jlMatrix4::operator()(int32 row, int32 col) {
	JL_ASSERT_MSG(row >= 0 && row < 4, "Index of %d is out of bounds of the jlMatrix4 Row/Col", row);
	JL_ASSERT_MSG(col >= 0 && col < 4, "Index of %d is out of bounds of the jlMatrix4 Row/Col", col);
	return getColumn(col)(row);
}

JL_FORCE_INLINE const float32& jlMatrix4::operator()(int32 row, int32 col) const {
	JL_ASSERT_MSG(row >= 0 && row < 4, "Index of %d is out of bounds of the jlMatrix4 Row/Col", row);
	JL_ASSERT_MSG(col >= 0 && col < 4, "Index of %d is out of bounds of the jlMatrix4 Row/Col", col);
	return getColumn(col)(row);
}

JL_FORCE_INLINE bool32 jlMatrix4::isOk() const {
	return col0.isOk() && col1.isOk() && col2.isOk() && col3.isOk();
}

JL_FORCE_INLINE void jlMatrix4::storeColMajor(float32 *cm) const {
	col0.store(cm);
	col1.store(cm + 4);
	col2.store(cm + 8);
	col3.store(cm + 12);
}

JL_FORCE_INLINE void jlMatrix4::storeColMajorAligned(float32 *cm) const {
	col0.storeAligned(cm);
	col1.storeAligned(cm + 4);
	col2.storeAligned(cm + 8);
	col3.storeAligned(cm + 12);
}

JL_FORCE_INLINE void jlMatrix4::storeRowMajor(float32 *rm) const {
	jlVector4 cur = getRow(0);
	cur.store(rm);
	cur = getRow(1);
	cur.store(rm + 4);
	cur = getRow(2);
	cur.store(rm + 8);
	cur = getRow(3);
	cur.store(rm + 12);
}

JL_FORCE_INLINE void jlMatrix4::storeRowMajorAligned(float32 *rm) const {
	jlVector4 cur = getRow(0);
	cur.storeAligned(rm);
	cur = getRow(1);
	cur.storeAligned(rm + 4);
	cur = getRow(2);
	cur.storeAligned(rm + 8);
	cur = getRow(3);
	cur.storeAligned(rm + 12);
}

JL_FORCE_INLINE void jlMatrix4::loadColMajor(const float32 *cm) {
	col0.load(cm);
	col1.load(cm + 4);
	col2.load(cm + 8);
	col3.load(cm + 12);
}

JL_FORCE_INLINE void jlMatrix4::loadColMajorAligned(const float32 *cm) {
	col0.loadAligned(cm);
	col1.loadAligned(cm + 4);
	col2.loadAligned(cm + 8);
	col3.loadAligned(cm + 12);
}

JL_FORCE_INLINE void jlMatrix4::loadRowMajor(const float32 *rm) {
	jlVector4 cur = getRow(0);
	cur.load(rm);
	cur = getRow(1);
	cur.load(rm + 4);
	cur = getRow(2);
	cur.load(rm + 8);
	cur = getRow(3);
	cur.load(rm + 12);
}

JL_FORCE_INLINE void jlMatrix4::loadRowMajorAligned(const float32 *rm) {
	jlVector4 cur = getRow(0);
	cur.loadAligned(rm);
	cur = getRow(1);
	cur.loadAligned(rm + 4);
	cur = getRow(2);
	cur.loadAligned(rm + 8);
	cur = getRow(3);
	cur.loadAligned(rm + 12);
}

JL_FORCE_INLINE jlVector4& jlMatrix4::getColumn(int32 i) {
	JL_ASSERT_MSG(i >= 0 && i < 4, "Index of %d is out of bounds of the jlMatrix4 Column", i);
	return (&col0)[i];
}

JL_FORCE_INLINE const jlVector4& jlMatrix4::getColumn(int32 i) const {
	JL_ASSERT_MSG(i >= 0 && i < 4, "Index of %d is out of bounds of the jlMatrix4 Column", i);
	return (&col0)[i];
}

JL_FORCE_INLINE jlVector4 jlMatrix4::getRow(int32 i) const {
	JL_ASSERT_MSG(i >= 0 && i < 4, "Index of %d is out of bounds of the jlMatrix4 Row", i);
	jlVector4 r = jlVector4(col0(i), col1(i), col2(i), col3(i));
	return r;
}

JL_FORCE_INLINE void jlMatrix4::setColumn(const jlVector4& c, int32 i) {
	JL_ASSERT_MSG(i >= 0 && i < 4, "Index of %d is out of bounds of the jlMatrix4 Column", i);
	jlVector4 *cptr = (&col0 + i);
	*cptr = c;
}

JL_FORCE_INLINE void jlMatrix4::setRow(const jlVector4& r, int32 i) {
	col0(i) = r(0);
	col1(i) = r(1);
	col2(i) = r(2);
	col3(i) = r(3);
}

template <int32 row, int32 col> 
JL_FORCE_INLINE jlSimdFloat jlMatrix4::getElem() const {
	JL_STATIC_ASSERT((row >= 0 && row <= 3 && col >= 0 && col <= 3));
	return (&col0)[col].getElem<row>();
}

template <int32 row, int32 col>
JL_FORCE_INLINE void jlMatrix4::setElem(const jlSimdFloat& s) {
	(&col0)[col].setElem<row>(s);
}

JL_FORCE_INLINE void jlMatrix4::setZero() {
	col0.setZero4();
	col1.setZero4();
	col2.setZero4();
	col3.setZero4();
}

JL_FORCE_INLINE void jlMatrix4::setIdentity() {
	col0.set(1.0f, 0.0f, 0.0f, 0.0f);
	col1.set(0.0f, 1.0f, 0.0f, 0.0f);
	col2.set(0.0f, 0.0f, 1.0f, 0.0f);
	col3.set(0.0f, 0.0f, 0.0f, 1.0f);
}

JL_FORCE_INLINE void jlMatrix4::setAll(const jlSimdFloat& sf) {
	col0.setAll(sf);
	col1.setAll(sf);
	col2.setAll(sf);
	col3.setAll(sf);
}

JL_FORCE_INLINE void jlMatrix4::setDiagonal(const jlVector4& diag) {
	setZero();
	(*this)(0, 0) = diag(0);
	(*this)(1, 1) = diag(1);
	(*this)(2, 2) = diag(2);
	(*this)(3, 3) = diag(3);
}

// isZero, tolerance is completely temporary
JL_FORCE_INLINE bool32 jlMatrix4::isZero() const {
	return col0.isZero4() && col1.isZero4() && col2.isZero4() && col3.isZero4();
}
	
JL_FORCE_INLINE bool32 jlMatrix4::isIdentity() const {
	return col0.equals4(jlVector4::UNIT_X) && col1.equals4(jlVector4::UNIT_Y) && 
		col2.equals4(jlVector4::UNIT_Z) && col3.equals4(jlVector4::UNIT_W);
}

JL_FORCE_INLINE bool32 jlMatrix4::isAffine() const {
	jlVector4 lastRow = jlVector4(col0(3), col1(3), col2(3), col3(3));
	return lastRow == jlVector4::ZERO_PT;
}

JL_FORCE_INLINE bool32 jlMatrix4::equals(const jlMatrix4& m) const {
	return col0.equals4(m.col0) && col1.equals4(m.col1) && 
		col2.equals4(m.col2) && col3.equals4(m.col3);
}

JL_FORCE_INLINE bool32 jlMatrix4::operator ==(const jlMatrix4& m) const {
	return this->equals(m);
}

JL_FORCE_INLINE bool32 jlMatrix4::operator !=(const jlMatrix4& m) const {
	return !(this->equals(m));
}

JL_FORCE_INLINE jlMatrix4 jlMatrix4::operator +(jlMatrix4& rhs) const {
	jlMatrix4 sum;
	sum.col0.setAdd(col0, rhs.col0);
	sum.col1.setAdd(col1, rhs.col1);
	sum.col2.setAdd(col2, rhs.col2);
	sum.col3.setAdd(col3, rhs.col3);
	return sum;
}

JL_FORCE_INLINE jlMatrix4 jlMatrix4::operator -(jlMatrix4& rhs) const {
	jlMatrix4 diff;
	diff.col0.setSub(col0, rhs.col0);
	diff.col1.setSub(col1, rhs.col1);
	diff.col2.setSub(col2, rhs.col2);
	diff.col3.setSub(col3, rhs.col3);
	return diff;
}

JL_FORCE_INLINE jlMatrix4 jlMatrix4::operator *(const jlMatrix4& rhs) const {
	jlMatrix4 product;
	product.col0 = transform(rhs.col0);
	product.col1 = transform(rhs.col1);
	product.col2 = transform(rhs.col2);
	product.col3 = transform(rhs.col3);
	return product;
}

JL_FORCE_INLINE jlMatrix4 jlMatrix4::operator *(const jlSimdFloat& s) const {
	return jlMatrix4(col0 * s, col1 * s, col2 * s, col3 * s);
}

JL_FORCE_INLINE jlMatrix4 operator *(const jlSimdFloat& s, const jlMatrix4& m) {
	return m * s;
}

JL_FORCE_INLINE jlVector4 jlMatrix4::operator *(const jlVector4& rhs) const {
	return transform(rhs);
}

JL_FORCE_INLINE jlMatrix4 jlMatrix4::operator -() const {
	jlMatrix4 n = jlMatrix4(col0, col1, col2, col3);
	n.col0.negate();
	n.col1.negate();
	n.col2.negate();
	n.col3.negate();
	return n;
}

JL_FORCE_INLINE jlMatrix4& jlMatrix4::operator +=(jlMatrix4& rhs) {
	col0.add(rhs.col0);
	col1.add(rhs.col1);
	col2.add(rhs.col2);
	col3.add(rhs.col3);
	return *this;
}

JL_FORCE_INLINE jlMatrix4& jlMatrix4::operator -=(jlMatrix4& rhs) {
	col0.sub(rhs.col0);
	col1.sub(rhs.col1);
	col2.sub(rhs.col2);
	col3.sub(rhs.col3);
	return *this;
}

JL_FORCE_INLINE jlMatrix4& jlMatrix4::operator *=(const jlMatrix4& rhs) {
	mul(rhs);
	return *this;
}

JL_FORCE_INLINE jlMatrix4& jlMatrix4::operator *=(const jlSimdFloat& s) {
	mul(s);
	return *this;
}

JL_FORCE_INLINE void jlMatrix4::setAdd(const jlMatrix4& m0, const jlMatrix4& m1) {
	col0.setAdd(m0.col0, m1.col0);
	col1.setAdd(m0.col1, m1.col1);
	col2.setAdd(m0.col2, m1.col2);
	col3.setAdd(m0.col3, m1.col3);
}

JL_FORCE_INLINE void jlMatrix4::setSub(const jlMatrix4& m0, const jlMatrix4& m1) {
	col0.setSub(m0.col0, m1.col0);
	col1.setSub(m0.col1, m1.col1);
	col2.setSub(m0.col2, m1.col2);
	col3.setSub(m0.col3, m1.col3);
}

JL_FORCE_INLINE void jlMatrix4::setMul(const jlMatrix4& m, const jlSimdFloat& s) {
	col0.setMul(m.col0, s);
	col1.setMul(m.col1, s);
	col2.setMul(m.col2, s);
	col3.setMul(m.col3, s);
}

JL_FORCE_INLINE void jlMatrix4::setMul(const jlMatrix4& m0, const jlMatrix4& m1) {
	col0 = m0.transform(m1.col0);
	col1 = m0.transform(m1.col1);
	col2 = m0.transform(m1.col2);
	col3 = m0.transform(m1.col3);
}

JL_FORCE_INLINE void jlMatrix4::setNegation(const jlMatrix4& m) {
	col0.setNegation(m.col0);
	col1.setNegation(m.col1);
	col2.setNegation(m.col2);
	col3.setNegation(m.col3);
}

JL_FORCE_INLINE void jlMatrix4::add(const jlMatrix4& m) {
	col0.add(m.col0);
	col1.add(m.col1);
	col2.add(m.col2);
	col3.add(m.col3);
}

JL_FORCE_INLINE void jlMatrix4::sub(const jlMatrix4& m) {
	col0.sub(m.col0);
	col1.sub(m.col1);
	col2.sub(m.col2);
	col3.sub(m.col3);
}

JL_FORCE_INLINE void jlMatrix4::mul(const jlSimdFloat& s) {
	col0.mul(s);
	col1.mul(s);
	col2.mul(s);
	col3.mul(s);
}

JL_FORCE_INLINE void jlMatrix4::mul(const jlMatrix4& m) {
	jlMatrix4 tmp;
	tmp.setMul(*this, m);
	*this = tmp;
}

JL_FORCE_INLINE jlVector4 jlMatrix4::mul(const jlVector4& v) const {
	return transform(v);
}

JL_FORCE_INLINE jlVector4 jlMatrix4::transform(const jlVector4& vec) const {
	jlVector4 xform;
	jlVector4 tmp;
	// dot rows by the columns
	jlVector4 r0, r1, r2, r3;
	r0.setReplication<0>(vec);
	r1.setReplication<1>(vec);
	r2.setReplication<2>(vec);
	r3.setReplication<3>(vec);
	// perform the additions and multiplies for each
	xform.setMul(r0, col0);
	tmp.setMul(r1, col1);
	xform.add(tmp);
	tmp.setMul(r2, col2);
	xform.add(tmp);
	tmp.setMul(r3, col3);
	xform.add(tmp);
	return xform;
}

// same as above, expect the translation is omitted
JL_FORCE_INLINE jlVector4 jlMatrix4::transformPosition(const jlVector4& vec) const {
	jlVector4 xform;
	jlVector4 tmp;
	jlVector4 r0, r1, r2, r3;
	r0.setReplication<0>(vec);
	r1.setReplication<1>(vec);
	r2.setReplication<2>(vec);
	xform.setMul(r0, col0);
	xform.add(col3);
	tmp.setMul(r1, col1);
	xform.add(tmp);
	tmp.setMul(r2, col2);
	xform.add(tmp);
	return xform;
}

JL_FORCE_INLINE jlVector2 jlMatrix4::transformPosition(const jlVector2& vec) const {
	return jlVector2(vec.x * (*this)(0, 0) + vec.y * (*this)(1, 0) + (*this)(0, 3), 
					vec.x * (*this)(0, 1) + vec.y * (*this)(1, 1) + (*this)(1, 3));
}

JL_FORCE_INLINE jlVector4 jlMatrix4::transformDirection(const jlVector4& vec) const {
	jlMatrix4 inv = inverse();
	jlMatrix4 invTranspose = inv.getTranspose();
	return invTranspose.transform(vec);
}

JL_FORCE_INLINE jlVector2 jlMatrix4::transformDirection(const jlVector2& vec) const {
	return jlVector2(vec.x * (*this)(0, 0) + vec.y * (*this)(1, 0), 
				vec.x * (*this)(0, 1) + vec.y * (*this)(1, 1));
}

JL_FORCE_INLINE jlMatrix4 jlMatrix4::getTranspose() const {
	return jlMatrix4(getRow(0), getRow(1), getRow(2), getRow(3));
}

JL_FORCE_INLINE void jlMatrix4::transpose() {
	jlVector4 oldRow0 = getRow(0), oldRow1 = getRow(1), oldRow2 = getRow(2), oldRow3 = getRow(3);
	col0 = oldRow0; col1 = oldRow1; col2 = oldRow2; col3 = oldRow3;
}

// using OGRE 3D's method of inverting matrices
JL_FORCE_INLINE jlMatrix4 jlMatrix4::inverse() const {
	jlSimdFloat m00 = getElem<0, 0>(); jlSimdFloat m01 = getElem<0, 1>(); jlSimdFloat m02 = getElem<0, 2>(); jlSimdFloat m03 = getElem<0, 3>();
	jlSimdFloat m10 = getElem<1, 0>(); jlSimdFloat m11 = getElem<1, 1>(); jlSimdFloat m12 = getElem<1, 2>(); jlSimdFloat m13 = getElem<1, 3>();
	jlSimdFloat m20 = getElem<2, 0>(); jlSimdFloat m21 = getElem<2, 1>(); jlSimdFloat m22 = getElem<2, 2>(); jlSimdFloat m23 = getElem<2, 3>();
	jlSimdFloat m30 = getElem<3, 0>(); jlSimdFloat m31 = getElem<3, 1>(); jlSimdFloat m32 = getElem<3, 2>(); jlSimdFloat m33 = getElem<3, 3>();

	jlMatrix4 im = jlMatrix4(col0, col1, col2, col3);

	jlSimdFloat v0 = m20 * m31 - m21 * m30;
    jlSimdFloat v1 = m20 * m32 - m22 * m30;
    jlSimdFloat v2 = m20 * m33 - m23 * m30;
    jlSimdFloat v3 = m21 * m32 - m22 * m31;
    jlSimdFloat v4 = m21 * m33 - m23 * m31;
    jlSimdFloat v5 = m22 * m33 - m23 * m32;
	
	jlSimdFloat t00 = + (v5 * m11 - v4 * m12 + v3 * m13);
	jlSimdFloat t10 = - (v5 * m10 - v2 * m12 + v1 * m13);
	jlSimdFloat t20 = + (v4 * m10 - v2 * m11 + v0 * m13);
	jlSimdFloat t30 = - (v3 * m10 - v1 * m11 + v0 * m12);

	jlSimdFloat invDet = 1 / (t00 * m00 + t10 * m01 + t20 * m02 + t30 * m03);

    jlSimdFloat d00 = t00 * invDet;
    jlSimdFloat d10 = t10 * invDet;
    jlSimdFloat d20 = t20 * invDet;
    jlSimdFloat d30 = t30 * invDet;

    jlSimdFloat d01 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
    jlSimdFloat d11 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
    jlSimdFloat d21 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
    jlSimdFloat d31 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

    v0 = m10 * m31 - m11 * m30;
    v1 = m10 * m32 - m12 * m30;
    v2 = m10 * m33 - m13 * m30;
    v3 = m11 * m32 - m12 * m31;
    v4 = m11 * m33 - m13 * m31;
    v5 = m12 * m33 - m13 * m32;

    jlSimdFloat d02 = + (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
    jlSimdFloat d12 = - (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
    jlSimdFloat d22 = + (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
    jlSimdFloat d32 = - (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

    v0 = m21 * m10 - m20 * m11;
    v1 = m22 * m10 - m20 * m12;
    v2 = m23 * m10 - m20 * m13;
    v3 = m22 * m11 - m21 * m12;
    v4 = m23 * m11 - m21 * m13;
    v5 = m23 * m12 - m22 * m13;

    jlSimdFloat d03 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
    jlSimdFloat d13 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
    jlSimdFloat d23 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
    jlSimdFloat d33 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

	return jlMatrix4(d00, d01, d02, d03, d10, d11, d12, d13, d20, d21, d22, d23, d30, d31, d32, d33);
}

JL_FORCE_INLINE void jlMatrix4::invert() {
	*this = this->inverse();
}

JL_FORCE_INLINE void jlMatrix4::makeTranslation(const jlSimdFloat& tx, const jlSimdFloat& ty, const jlSimdFloat& tz) {
	col0 = jlVector4::UNIT_X;
	col1 = jlVector4:: UNIT_Y;
	col2 = jlVector4::UNIT_Z;
	col3 = jlVector4(tx.getFloat(), ty.getFloat(), tz.getFloat(), 1.0f);
}

JL_FORCE_INLINE void jlMatrix4::makeTranslation(const jlVector4& t) {
	col0 = jlVector4::UNIT_X;
	col1 = jlVector4::UNIT_Y;
	col2 = jlVector4::UNIT_Z;
	col3 = t;
}

JL_FORCE_INLINE void jlMatrix4::makeScale(const jlSimdFloat& sx, const jlSimdFloat& sy, const jlSimdFloat& sz) {
	col0.setMul(jlVector4::UNIT_X, sx);
	col1.setMul(jlVector4::UNIT_Y, sy);
	col2.setMul(jlVector4::UNIT_Z, sz);
	col3 = jlVector4::UNIT_W;
}

JL_FORCE_INLINE void jlMatrix4::makeScale(const jlVector4& sv) {
	setZero();
	(*this)(0, 0) = sv(0);
	(*this)(1, 1) = sv(1);
	(*this)(2, 2) = sv(2);
	(*this)(3, 3) = 1.0f;
}

JL_FORCE_INLINE void jlMatrix4::makeRotationX(const jlSimdFloat& rad) {
	setZero();
	float32 cos = jlMath::Cos(rad);
	float32 sin = jlMath::Sin(rad);
	(*this)(0, 0) = 1.0f; 
	(*this)(1, 1) = cos;
	(*this)(2, 1) = sin; 
	(*this)(1, 2) = -sin;
	(*this)(2, 2) = cos;
	(*this)(3, 3) = 1.0f;
}

JL_FORCE_INLINE void jlMatrix4::makeRotationY(const jlSimdFloat& rad) {
	setZero();
	float32 cos = jlMath::Cos(rad);
	float32 sin = jlMath::Sin(rad);
	(*this)(0, 0) = cos; 
	(*this)(0, 2) = sin;
	(*this)(2, 0) = -sin; 
	(*this)(2, 2) = cos;
	(*this)(2, 2) = 1.0f;
	(*this)(3, 3) = 1.0f;
}

JL_FORCE_INLINE void jlMatrix4::makeRotationZ(const jlSimdFloat& rad) {
	setZero();
	float32 cos = jlMath::Cos(rad);
	float32 sin = jlMath::Sin(rad);
	(*this)(0, 0) = cos; (*this)(0, 1) = -sin;
	(*this)(1, 0) = sin; (*this)(1, 1) = cos;
	(*this)(2, 2) = 1.0f;
	(*this)(3, 3) = 1.0f;
}

JL_FORCE_INLINE void jlMatrix4::fromQuaternion(const jlQuaternion& q) {
	jlSimdFloat x = q(0);
	jlSimdFloat y = q(1);
	jlSimdFloat z = q(2);
		
	jlQuaternion tmpSum = q + q;
	jlSimdFloat tx = tmpSum(0);
	jlSimdFloat ty = tmpSum(1);
	jlSimdFloat tz = tmpSum(2);
	jlSimdFloat tw = q(3);
	jlSimdFloat twx = tx * tw;
    jlSimdFloat twy = ty * tw;
    jlSimdFloat twz = tz * tw;
    jlSimdFloat txx = tx * x;
    jlSimdFloat txy = ty * x;
    jlSimdFloat txz = tz * x;
    jlSimdFloat tyy = ty * y;
    jlSimdFloat tyz = tz * y;
    jlSimdFloat tzz = tz * z;

	(*this)(0, 0) = 1.0f - (tyy + tzz);
	(*this)(0, 1) = txy - twz;
	(*this)(0, 2) = txz + twy;
	(*this)(0, 3) = 0.0f;
	(*this)(1, 0) = txy + twz;
	(*this)(1, 1) = 1.0f - (txx + tzz);
	(*this)(1, 2) = tyz - twx;
	(*this)(1, 3) = 0.0f;
	(*this)(2, 0) = txz - twy;
	(*this)(2, 1) = tyz + twx;
	(*this)(2, 2) = 1.0f - (txx + tyy);
	(*this)(2, 3) = 0.0f;
	col3 = jlVector4::ZERO_PT;
}

JL_FORCE_INLINE jlQuaternion jlMatrix4::toQuaternion() const {
	jlSimdFloat zero = jlSimdFloat(0.0f);
	jlSimdFloat half = jlSimdFloat(0.5f);
	jlSimdFloat one = jlSimdFloat(1.0f);
	jlSimdFloat trace = col0(0) + col1(1) + col2(2);
	jlSimdFloat root;
	jlVector4 qvec;
	if (trace > zero) {
		root = jlMath::Sqrt(trace + one);
		qvec(3) = (root * half);
		root = half / root;
		qvec(0) = (((*this)(2, 1) - (*this)(1, 2)) * root);
		qvec(1) = (((*this)(0, 2) - (*this)(2, 0)) * root);
		qvec(2) = (((*this)(1, 0) - (*this)(0, 1)) * root);
	} else {
		int32 j, k;
		int32 i = 0;
		int32 QNEXT_LUT[3] = {1, 2, 0};
		if ((*this)(1, 1) > (*this)(0, 0)) {
			i = 1;
		}
		if ((*this)(2, 2) > (*this)(i, i)) {
			i = 2;
		}
		j = QNEXT_LUT[i];
		k = QNEXT_LUT[j];
		root = jlMath::Sqrt((*this)(i, i) - (*this)(j, j) - (*this)(k, k) + 1.0f);
		qvec(i) = root * half;
		root = half / root;
		qvec(3) = ((*this)(k, j) - (*this)(j, k)) * root;
		qvec(j) = ((*this)(j, i) + (*this)(i, j)) * root;
		qvec(k) = ((*this)(k, i) + (*this)(i, k)) * root;
	}
	return jlQuaternion(qvec);
}
