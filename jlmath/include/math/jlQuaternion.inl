
JL_FORCE_INLINE jlQuaternion::jlQuaternion() {
		
}

JL_FORCE_INLINE jlQuaternion::jlQuaternion(const jlVector4& qvec) {
	vec = qvec;
}

JL_FORCE_INLINE jlQuaternion::jlQuaternion(float32 x, float32 y, float32 z, float32 w) {
	vec.set(x, y, z, w);
}

JL_FORCE_INLINE jlQuaternion::jlQuaternion(const jlQuaternion& cpy) {
	vec = cpy.vec;
}

JL_FORCE_INLINE jlQuaternion& jlQuaternion::operator=(const jlQuaternion& rhs) {
	vec = rhs.vec;
	return *this;
}
	
JL_FORCE_INLINE float32& jlQuaternion::operator()(int32 i) {
	return vec(i);
}

JL_FORCE_INLINE const float32& jlQuaternion::operator()(int32 i) const {
	return vec(i);
}

JL_FORCE_INLINE bool32 jlQuaternion::isOk() const {
	return vec.isOk();
}

JL_FORCE_INLINE void jlQuaternion::store(float32 *ptr) const {
	vec.store(ptr);
}

JL_FORCE_INLINE void jlQuaternion::storeAligned(float32 *ptr) const {
	vec.storeAligned(ptr);
}

JL_FORCE_INLINE void jlQuaternion::load(const float32 *ptr) {
	vec.load(ptr);
}

JL_FORCE_INLINE void jlQuaternion::loadAligned(const float32 *ptr) {
	vec.loadAligned(ptr);
}

template <int32 i> 
JL_FORCE_INLINE jlSimdFloat jlQuaternion::getElem() const {
	return vec.getElem<i>();	
}

template <int32 i> 
JL_FORCE_INLINE void jlQuaternion::setElem(const jlSimdFloat& s) {
	vec.setElem(s);
}

JL_FORCE_INLINE void jlQuaternion::setIdentity() {
	vec.set(0.0f, 0.0f, 0.0f, 1.0f);
}

JL_FORCE_INLINE void jlQuaternion::set(float32 x, float32 y, float32 z, float32 w) {
	vec.set(x, y, z, w);
}

JL_FORCE_INLINE void jlQuaternion::setAll(const jlSimdFloat& sv) {
	vec.setAll(sv);
}

JL_FORCE_INLINE void jlQuaternion::setZero() {
	vec.setZero4();
}

JL_FORCE_INLINE void jlQuaternion::setAxisAngle(const jlVector4& axis, const jlSimdFloat& theta) {
	jlSimdFloat half = jlSimdFloat(0.5f);
	jlSimdFloat halfTheta = theta * half;
	jlSimdFloat halfSinTheta = jlMath::Sin(halfTheta);
	jlSimdFloat halfCosTheta = jlMath::Cos(halfTheta);
	vec.setMul(axis, halfSinTheta);
	vec.setElem<3>(halfCosTheta);
}

JL_FORCE_INLINE jlQuaternion jlQuaternion::operator +(const jlQuaternion& rhs) const {
	jlQuaternion sum;
	sum.vec.setAdd(vec, rhs.vec);
	return sum;
}

JL_FORCE_INLINE jlQuaternion jlQuaternion::operator -(const jlQuaternion& rhs) const {
	jlQuaternion diff;
	diff.vec.setSub(vec, rhs.vec);
	return diff;
}

JL_FORCE_INLINE jlQuaternion jlQuaternion::operator *(const jlQuaternion& rhs) const {
	jlQuaternion q;
	q.setMul(*this, rhs);
	return q;
}

JL_FORCE_INLINE jlVector4 jlQuaternion::operator *(const jlVector4& rhs) const {
	jlVector4 v = jlVector4(rhs(0), rhs(1), rhs(2), 0.0f);
	jlVector4 uv, uuv;
	jlVector4 quatvec = jlVector4(vec(0), vec(1), vec(2), 0.0f);
	jlSimdFloat two = jlSimdFloat(2.0f);
	uv = quatvec.cross(v);
	uuv = quatvec.cross(uv);
	jlSimdFloat twoW = two * vec.getElem<3>();
	uv.mul(twoW);
	uuv.mul(two);
	jlVector4 result;
	result.setAdd(v, uv);
	result.setAdd(result, uuv);
	return result;
}

JL_FORCE_INLINE jlQuaternion jlQuaternion::operator *(const jlSimdFloat& s) const {
	return jlQuaternion(vec * s);
}

JL_FORCE_INLINE jlQuaternion jlQuaternion::operator -() const {
	return jlQuaternion(-vec);
}

JL_FORCE_INLINE void jlQuaternion::setAdd(const jlQuaternion& a, const jlQuaternion& b) {
	vec.setAdd(a.vec, b.vec);
}

JL_FORCE_INLINE void jlQuaternion::setMul(const jlQuaternion& q0, const jlQuaternion& q1) {
	jlSimdFloat q0w = q0.getElem<3>();
	jlSimdFloat q1w = q0.getElem<3>();
	jlVector4 cross, tmp;
	cross.setCross(q0.vec, q1.vec);
	tmp.setMul(q1.vec, q0w);
	cross.add(tmp);
	tmp.setMul(q0.vec, q1w);
	cross.add(tmp);
	jlSimdFloat w = (q0w * q1w) - q0.vec.dot3(q1.vec);
	vec = cross;
	vec.setElem<3>(w);
}

JL_FORCE_INLINE void jlQuaternion::setMul(const jlQuaternion& q, const jlSimdFloat& s) {
	vec.setMul(q.vec, s);
}

JL_FORCE_INLINE void jlQuaternion::setSub(const jlQuaternion& a, const jlQuaternion& b) {
	vec.setSub(a.vec, b.vec);
}

JL_FORCE_INLINE void jlQuaternion::setNegation(const jlQuaternion& q) {
	vec.setNegation(q.vec);
}

JL_FORCE_INLINE void jlQuaternion::add(const jlQuaternion& q) {
	vec.add(q.vec);
}

JL_FORCE_INLINE void jlQuaternion::sub(const jlQuaternion& q) {
	vec.sub(q.vec);
}

JL_FORCE_INLINE void jlQuaternion::negate() {
	vec.negate();
}

JL_FORCE_INLINE jlSimdFloat jlQuaternion::dot(const jlQuaternion& q) const {
	return vec.dot4(q.vec);
}

JL_FORCE_INLINE void jlQuaternion::normalize() {
	vec.normalize4();
}

JL_FORCE_INLINE jlQuaternion jlQuaternion::inverse() const {
	jlQuaternion inv = jlQuaternion::ZERO;
	jlSimdFloat lenSq = vec.dot4(vec);
	jlSimdFloat zero = jlSimdFloat(0.0f);
	jlSimdFloat one = jlSimdFloat(1.0f);
	if (lenSq > zero) {
		jlSimdFloat invLenSq = one / lenSq;
		inv.vec = -vec * invLenSq;
		inv.vec.setElem<3>(-inv.vec.getElem<3>());
	}
	return inv;
}

JL_FORCE_INLINE jlQuaternion jlQuaternion::unitInverse() const {
	jlQuaternion ui;
	ui.vec.setNegation(vec);
	return ui;
}

JL_FORCE_INLINE bool32 jlQuaternion::equals(const jlQuaternion& rhs) const {
	return vec.equals4(rhs.vec);
}

JL_FORCE_INLINE bool32 jlQuaternion::operator ==(const jlQuaternion& rhs) const {
	return vec.equals4(rhs.vec);
}

JL_FORCE_INLINE bool32 jlQuaternion::operator !=(const jlQuaternion& rhs) const {
	return !vec.equals4(rhs.vec);
}

JL_FORCE_INLINE jlQuaternion jlQuaternion::Slerp(const jlQuaternion& q0, const jlQuaternion& q1, const jlSimdFloat& t) {
	jlSimdFloat cos = q0.dot(q1);
	jlSimdFloat zero = jlSimdFloat(0.0f);
	jlSimdFloat one = jlSimdFloat(1.0f);
	jlSimdFloat clampedT; clampedT.setMin(t, one); clampedT.setMax(clampedT, zero);
	jlQuaternion r = q1;
	if (cos < zero) {
		cos = -cos;
		r = -q1;
	}
	jlSimdFloat absCos = jlSimdFloat(jlMath::Abs(cos));
	jlSimdFloat eps = jlSimdFloat(FLOAT32_EPSILON);
	if (absCos < one - eps) {
		jlSimdFloat sin = jlMath::Sqrt(one - cos * cos);
		jlSimdFloat ang = jlMath::ATan2(sin, cos);
		jlSimdFloat invSin = one / sin;
		jlSimdFloat k0 = jlMath::Sin((one - clampedT) * ang) * invSin;
		jlSimdFloat k1 = jlMath::Sin(clampedT * ang) * invSin;
		return q0 * k1 + r * k1;
	} else {
		jlQuaternion lrp = q0 * (one - clampedT) + r * clampedT;
		lrp.normalize();
		return lrp;
	}
}

JL_FORCE_INLINE jlQuaternion jlQuaternion::Nlerp(const jlQuaternion& q0, const jlQuaternion& q1, const jlSimdFloat& t) {
	jlSimdFloat one = jlSimdFloat(1.0f);
	jlSimdFloat w = one - t;
	jlQuaternion interp = q0 * w + q1 * t;
	return interp;
}
