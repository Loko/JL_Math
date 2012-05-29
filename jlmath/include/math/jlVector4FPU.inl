/// @file jlVector4FPU.h
/// @author Jeff Lansing

#if JL_SIMD_ENABLED
#error "Cannot include jlVector4FPU.inl with this configuration"
#endif

/// Wrapped that adheres to the jlVector4 interface using a simple array of floats
JL_FORCE_INLINE jlVector4::jlVector4() { }

JL_FORCE_INLINE jlVector4::jlVector4(const quad128& q) {
	quad.v[0] = q.v[0];
	quad.v[1] = q.v[1];
	quad.v[2] = q.v[2];
	quad.v[3] = q.v[3];
}

JL_FORCE_INLINE jlVector4::jlVector4(float32 x, float32 y, float32 z, float32 w) {
	quad.v[0] = x;
	quad.v[1] = y;
	quad.v[2] = z;
	quad.v[3] = w;
}

JL_FORCE_INLINE jlVector4::jlVector4(const jlVector4& vec) {
	quad.v[0] = vec.quad.v[0];
	quad.v[1] = vec.quad.v[1];
	quad.v[2] = vec.quad.v[2];
	quad.v[3] = vec.quad.v[3];
}

JL_FORCE_INLINE jlVector4& jlVector4::operator =(const jlVector4& vec) {
	quad.v[0] = vec.quad.v[0];
	quad.v[1] = vec.quad.v[1];
	quad.v[2] = vec.quad.v[2];
	quad.v[3] = vec.quad.v[3];
	return *this;
}

JL_FORCE_INLINE const float32& jlVector4::operator()(int32 i) const {
	JL_ASSERT_MSG(i >= 0 && i < 4, "Index of %d is out of bounds of the vector4", i);
	return quad.v[i];
}

JL_FORCE_INLINE float32& jlVector4::operator()(int32 i) {
	JL_ASSERT_MSG(i >= 0 && i < 4, "Index of %d is out of bounds of the vector4", i);
	return quad.v[i];
}

JL_FORCE_INLINE bool32 jlVector4::isOk() const {
	return (!jlMath::IsNaN(quad.v[0]) && !jlMath::IsNaN(quad.v[1]) &&
		!jlMath::IsNaN(quad.v[2]) && !jlMath::IsNaN(quad.v[3]));
}

JL_FORCE_INLINE void jlVector4::store(float32 *ptr) const {
	ptr[0] = quad.v[0];
	ptr[1] = quad.v[1];
	ptr[2] = quad.v[2];
	ptr[3] = quad.v[3];
}

JL_FORCE_INLINE void jlVector4::storeAligned(float32 *ptr) const {
	ptr[0] = quad.v[0];
	ptr[1] = quad.v[1];
	ptr[2] = quad.v[2];
	ptr[3] = quad.v[3];
}

JL_FORCE_INLINE void jlVector4::load(const float32 *ptr) {
	quad.v[0] = ptr[0];
	quad.v[1] = ptr[1];
	quad.v[2] = ptr[2];
	quad.v[3] = ptr[3];
}

JL_FORCE_INLINE void jlVector4::loadAligned(const float32 *ptr) {
	quad.v[0] = ptr[0];
	quad.v[1] = ptr[1];
	quad.v[2] = ptr[2];
	quad.v[3] = ptr[3];
}

JL_FORCE_INLINE quad128& jlVector4::getQuad() {
	return quad;
}

JL_FORCE_INLINE const quad128& jlVector4::getQuad() const {
	return quad;
}

template <int32 i>
JL_FORCE_INLINE jlSimdFloat jlVector4::getElem() const {
	JL_STATIC_ASSERT_FAIL();
}

template <>
JL_FORCE_INLINE jlSimdFloat jlVector4::getElem<0>() const {
	return jlSimdFloat(quad.v[0]);
}

template <>
JL_FORCE_INLINE jlSimdFloat jlVector4::getElem<1>() const {
	return jlSimdFloat(quad.v[1]);
}

template <>
JL_FORCE_INLINE jlSimdFloat jlVector4::getElem<2>() const {
	return jlSimdFloat(quad.v[2]);
}

template <>
JL_FORCE_INLINE jlSimdFloat jlVector4::getElem<3>() const {
	return jlSimdFloat(quad.v[3]);
}

JL_FORCE_INLINE jlSimdFloat jlVector4::getElem(int32 i) const {
	JL_ASSERT_MSG(i >= 0 && i <= 3, "Invalid index for jlVector4");
	return jlSimdFloat(quad.v[i]);
}

template <int32 i> 
JL_FORCE_INLINE void jlVector4::setElem(const jlSimdFloat& s) {
	JL_STATIC_ASSERT_FAIL();
}

template <>
JL_FORCE_INLINE void jlVector4::setElem<0>(const jlSimdFloat& s) {
	quad.v[0] = s.f;
}

template <>
JL_FORCE_INLINE void jlVector4::setElem<1>(const jlSimdFloat& s) {
	quad.v[1] = s.f;
}

template <>
JL_FORCE_INLINE void jlVector4::setElem<2>(const jlSimdFloat& s) {
	quad.v[2] = s.f;
}

template <>
JL_FORCE_INLINE void jlVector4::setElem<3>(const jlSimdFloat& s) {
	quad.v[3] = s.f;
}

JL_FORCE_INLINE void jlVector4::set(const jlSimdFloat& x, const jlSimdFloat& y, const jlSimdFloat& z, const jlSimdFloat& w) {
	quad.v[0] = x.f;
	quad.v[1] = y.f;
	quad.v[2] = z.f;
	quad.v[3] = w.f;
}

JL_FORCE_INLINE void jlVector4::set(float32 x, float32 y, float32 z, float32 w) {
	quad.v[0] = x;
	quad.v[1] = y;
	quad.v[2] = z;
	quad.v[3] = w;
}

JL_FORCE_INLINE void jlVector4::setAll(const jlSimdFloat& v) {
	float32 val = v.f;
	quad.v[0] = val;
	quad.v[1] = val;
	quad.v[2] = val;
	quad.v[3] = val;
}

JL_FORCE_INLINE void jlVector4::setZero3() {
	quad.v[0] = 0.0f;
	quad.v[1] = 0.0f;
	quad.v[2] = 0.0f;
}

JL_FORCE_INLINE void jlVector4::setZero4() {
	quad.v[0] = 0.0f;
	quad.v[1] = 0.0f;
	quad.v[2] = 0.0f;
	quad.v[3] = 0.0f;
}

JL_FORCE_INLINE jlVector4 jlVector4::operator +(const jlVector4& rhs) const {
	jlVector4 sum;
	sum.quad.v[0] = quad.v[0] + rhs.quad.v[0];
	sum.quad.v[1] = quad.v[1] + rhs.quad.v[1];
	sum.quad.v[2] = quad.v[2] + rhs.quad.v[2];
	sum.quad.v[3] = quad.v[3] + rhs.quad.v[3];
	return sum;
}

JL_FORCE_INLINE jlVector4 jlVector4::operator-(const jlVector4& rhs) const {
	jlVector4 diff;
	diff.quad.v[0] = quad.v[0] - rhs.quad.v[0];
	diff.quad.v[1] = quad.v[1] - rhs.quad.v[1];
	diff.quad.v[2] = quad.v[2] - rhs.quad.v[2];
	diff.quad.v[3] = quad.v[3] - rhs.quad.v[3];
	return diff;
}

JL_FORCE_INLINE jlVector4 jlVector4::operator*(const jlSimdFloat& s) const {
	float32 val = s.f;
	jlVector4 sv;
	sv.quad.v[0] = quad.v[0] * val;
	sv.quad.v[1] = quad.v[1] * val;
	sv.quad.v[2] = quad.v[2] * val;
	sv.quad.v[3] = quad.v[3] * val;
	return sv;
}

JL_FORCE_INLINE jlVector4 operator*(const jlSimdFloat& s, const jlVector4& vec) {
	float32 val = s.f;
	jlVector4 sv;
	sv.quad.v[0] = vec.quad.v[0] * val;
	sv.quad.v[1] = vec.quad.v[1] * val;
	sv.quad.v[2] = vec.quad.v[2] * val;
	sv.quad.v[3] = vec.quad.v[3] * val;
	return sv;
}

JL_FORCE_INLINE jlVector4 jlVector4::operator /(const jlSimdFloat& d) const {
	float32 val = d.f;
	jlVector4 div;
	div.quad.v[0] = quad.v[0] / val;
	div.quad.v[1] = quad.v[1] / val;
	div.quad.v[2] = quad.v[2] / val;
	div.quad.v[3] = quad.v[3] / val;
	return div;
}

JL_FORCE_INLINE jlVector4 jlVector4::operator /(const jlVector4& rhs) const {
	jlVector4 div;
	div.quad.v[0] = quad.v[0] / rhs.quad.v[0];
	div.quad.v[1] = quad.v[1] / rhs.quad.v[1];
	div.quad.v[2] = quad.v[2] / rhs.quad.v[2];
	div.quad.v[3] = quad.v[3] / rhs.quad.v[3];
	return div;
}

JL_FORCE_INLINE jlVector4 jlVector4::operator -() const {
	jlVector4 neg;
	neg.quad.v[0] = -quad.v[0];
	neg.quad.v[1] = -quad.v[1];
	neg.quad.v[2] = -quad.v[2];
	neg.quad.v[3] = -quad.v[3];
	return neg;
}

JL_FORCE_INLINE jlVector4& jlVector4::operator +=(const jlVector4& rhs) {
	quad.v[0] += rhs.quad.v[0];
	quad.v[1] += rhs.quad.v[1];
	quad.v[2] += rhs.quad.v[2];
	quad.v[3] += rhs.quad.v[3];
	return *this;
}

JL_FORCE_INLINE jlVector4& jlVector4::operator -=(const jlVector4& rhs) {
	quad.v[0] -= rhs.quad.v[0];
	quad.v[1] -= rhs.quad.v[1];
	quad.v[2] -= rhs.quad.v[2];
	quad.v[3] -= rhs.quad.v[3];
	return *this;
}

JL_FORCE_INLINE jlVector4& jlVector4::operator *=(const jlSimdFloat& s) {
	float32 val = s.f;
	quad.v[0] *= val;
	quad.v[1] *= val;
	quad.v[2] *= val;
	quad.v[3] *= val;
	return *this;
}

JL_FORCE_INLINE jlVector4& jlVector4::operator /=(const jlSimdFloat& d) {
	float32 val = d.f;
	quad.v[0] /= val;
	quad.v[1] /= val;
	quad.v[2] /= val;
	quad.v[3] /= val;
	return *this;
}

JL_FORCE_INLINE jlVector4& jlVector4::operator /=(const jlVector4& d) {
	quad.v[0] /= d.quad.v[0];
	quad.v[1] /= d.quad.v[1];
	quad.v[2] /= d.quad.v[2];
	quad.v[3] /= d.quad.v[3];
	return *this;
}

JL_FORCE_INLINE void jlVector4::setAdd(const jlVector4& a, const jlVector4& b) {
	quad.v[0] = a.quad.v[0] + b.quad.v[0];
	quad.v[1] = a.quad.v[1] + b.quad.v[1];
	quad.v[2] = a.quad.v[2] + b.quad.v[2];
	quad.v[3] = a.quad.v[3] + b.quad.v[3];
}

JL_FORCE_INLINE void jlVector4::setSub(const jlVector4& a, const jlVector4& b) {
	quad.v[0] = a.quad.v[0] - b.quad.v[0];
	quad.v[1] = a.quad.v[1] - b.quad.v[1];
	quad.v[2] = a.quad.v[2] - b.quad.v[2];
	quad.v[3] = a.quad.v[3] - b.quad.v[3];
}

JL_FORCE_INLINE void jlVector4::setMul(const jlVector4& a, const jlVector4& b) {
	quad.v[0] = a.quad.v[0] * b.quad.v[0];
	quad.v[1] = a.quad.v[1] * b.quad.v[1];
	quad.v[2] = a.quad.v[2] * b.quad.v[2];
	quad.v[3] = a.quad.v[3] * b.quad.v[3];
}

JL_FORCE_INLINE void jlVector4::setMul(const jlVector4& a, const jlSimdFloat& s) {
	quad.v[0] = a.quad.v[0] * s.f;
	quad.v[1] = a.quad.v[1] * s.f;
	quad.v[2] = a.quad.v[2] * s.f;
	quad.v[3] = a.quad.v[3] * s.f;
}

JL_FORCE_INLINE void jlVector4::setDiv(const jlVector4& a, const jlVector4& b) {
	quad.v[0] = a.quad.v[0] / b.quad.v[0];
	quad.v[1] = a.quad.v[1] / b.quad.v[1];
	quad.v[2] = a.quad.v[2] / b.quad.v[2];
	quad.v[3] = a.quad.v[3] / b.quad.v[3];
}

JL_FORCE_INLINE void jlVector4::setDiv(const jlVector4& a, const jlSimdFloat& s) {
	quad.v[0] = a.quad.v[0] / s.f;
	quad.v[1] = a.quad.v[1] / s.f;
	quad.v[2] = a.quad.v[2] / s.f;
	quad.v[3] = a.quad.v[3] / s.f;
}

JL_FORCE_INLINE void jlVector4::setCross(const jlVector4& lhs, const jlVector4& rhs) {
	// IMPLEMENT ME!
}

JL_FORCE_INLINE void jlVector4::setMin(const jlVector4& lhs, const jlVector4& rhs) {
	quad.v[0] = jlMath::Min(lhs.quad.v[0], rhs.quad.v[0]);
	quad.v[1] = jlMath::Min(lhs.quad.v[1], rhs.quad.v[1]);
	quad.v[2] = jlMath::Min(lhs.quad.v[2], rhs.quad.v[2]);
	quad.v[3] = jlMath::Min(lhs.quad.v[3], rhs.quad.v[3]);
}

JL_FORCE_INLINE void jlVector4::setMax(const jlVector4& lhs, const jlVector4& rhs) {
	quad.v[0] = jlMath::Max(lhs.quad.v[0], rhs.quad.v[0]);
	quad.v[1] = jlMath::Max(lhs.quad.v[1], rhs.quad.v[1]);
	quad.v[2] = jlMath::Max(lhs.quad.v[2], rhs.quad.v[2]);
	quad.v[3] = jlMath::Max(lhs.quad.v[3], rhs.quad.v[3]);
}

JL_FORCE_INLINE void jlVector4::setNegation(const jlVector4& vec) {
	quad.v[0] = -vec.quad.v[0];
	quad.v[1] = -vec.quad.v[1];
	quad.v[2] = -vec.quad.v[2];
	quad.v[3] = -vec.quad.v[3];
}

template <int32 i>
JL_FORCE_INLINE void jlVector4::setReplication(const jlVector4& vec) {
	float elem = vec(i);
	quad.v[0] = elem;
	quad.v[1] = elem;
	quad.v[2] = elem;
	quad.v[3] = elem;
}

JL_FORCE_INLINE void jlVector4::add(const jlVector4& rhs) {
	quad.v[0] += rhs.quad.v[0];
	quad.v[1] += rhs.quad.v[1];
	quad.v[2] += rhs.quad.v[2];
	quad.v[3] += rhs.quad.v[3];
}

JL_FORCE_INLINE void jlVector4::sub(const jlVector4& rhs) {
	quad.v[0] -= rhs.quad.v[0];
	quad.v[1] -= rhs.quad.v[1];
	quad.v[2] -= rhs.quad.v[2];
	quad.v[3] -= rhs.quad.v[3];
}

JL_FORCE_INLINE void jlVector4::mul(const jlVector4& rhs) {
	quad.v[0] *= rhs.quad.v[0];
	quad.v[1] *= rhs.quad.v[1];
	quad.v[2] *= rhs.quad.v[2];
	quad.v[3] *= rhs.quad.v[3];
}

JL_FORCE_INLINE void jlVector4::mul(const jlSimdFloat& s) {
	quad.v[0] *= s.f;
	quad.v[1] *= s.f;
	quad.v[2] *= s.f;
	quad.v[3] *= s.f;
}

JL_FORCE_INLINE void jlVector4::div(const jlVector4& div) {
	quad.v[0] /= div.quad.v[0];
	quad.v[1] /= div.quad.v[1];
	quad.v[2] /= div.quad.v[2];
	quad.v[3] /= div.quad.v[3];
}

JL_FORCE_INLINE void jlVector4::div(const jlSimdFloat& s) {
	quad.v[0] /= s.f;
	quad.v[1] /= s.f;
	quad.v[2] /= s.f;
	quad.v[3] /= s.f;
}

JL_FORCE_INLINE void jlVector4::negate() {
	quad.v[0] = -quad.v[0];
	quad.v[1] = -quad.v[1];
	quad.v[2] = -quad.v[2];
	quad.v[3] = -quad.v[3];
}

JL_FORCE_INLINE jlSimdFloat jlVector4::dot3(const jlVector4& rhs) const {
	return jlSimdFloat(quad.v[0] * rhs.quad.v[0] + quad.v[1] * rhs.quad.v[1] + quad.v[2] * rhs.quad.v[2]);
}

JL_FORCE_INLINE jlSimdFloat jlVector4::dot4(const jlVector4& rhs) const {
	return jlSimdFloat(quad.v[0] * rhs.quad.v[0] + quad.v[1] * rhs.quad.v[1] + quad.v[2] * rhs.quad.v[2] + quad.v[3] * rhs.quad.v[3]);
}

JL_FORCE_INLINE jlSimdFloat jlVector4::length3() const {
	return jlSimdFloat(jlMath::Sqrt(quad.v[0] * quad.v[0] + quad.v[1] * quad.v[1] + quad.v[2] * quad.v[2]));
}

JL_FORCE_INLINE jlSimdFloat jlVector4::lengthSquared3() const {
	return jlSimdFloat(quad.v[0] * quad.v[0] + quad.v[1] * quad.v[1] + quad.v[2] * quad.v[2]);
}

JL_FORCE_INLINE jlSimdFloat jlVector4::length4() const {
	return jlSimdFloat(jlMath::Sqrt(quad.v[0] * quad.v[0] + quad.v[1] * quad.v[1] + quad.v[2] * quad.v[2] + quad.v[3] * quad.v[3]));
}

JL_FORCE_INLINE jlSimdFloat jlVector4::lengthSquared4() const {
	return jlSimdFloat(quad.v[0] * quad.v[0] + quad.v[1] * quad.v[1] + quad.v[2] * quad.v[2] + quad.v[3] * quad.v[3]);
}

JL_FORCE_INLINE jlVector4 jlVector4::cross(const jlVector4& rhs) const {
	float32 cx = quad.v[1] * rhs.quad.v[2] - rhs.quad.v[1] * quad.v[2];
	float32 cy = quad.v[2] * rhs.quad.v[0] - rhs.quad.v[2] * quad.v[0];
	float32 cz = quad.v[0] * rhs.quad.v[1] - rhs.quad.v[0] * quad.v[1];
	return jlVector4(cx, cy, cz, 0.0f);
}

JL_FORCE_INLINE void jlVector4::normalize3() {
	float32 lenSq3 = quad.v[0]*quad.v[0] + quad.v[1]*quad.v[1] + quad.v[2]*quad.v[2];
	if (lenSq3 > FLOAT32_EPSILON) {
		float32 invLen3 = 1.0f / jlMath::Sqrt(lenSq3);
		quad.v[0] *= invLen3;
		quad.v[1] *= invLen3;
		quad.v[2] *= invLen3;
	}
}

JL_FORCE_INLINE void jlVector4::normalize4() {
	float32 lenSq4 = quad.v[0]*quad.v[0] + quad.v[1]*quad.v[1] + quad.v[2]*quad.v[2] + quad.v[3]*quad.v[3];
	if (lenSq4 > FLOAT32_EPSILON) {
		float32 invLen4 = 1.0f / jlMath::Sqrt(lenSq4);
		quad.v[0] *= invLen4;
		quad.v[1] *= invLen4;
		quad.v[2] *= invLen4;
		quad.v[3] *= invLen4;
	}
}

JL_FORCE_INLINE jlSimdFloat jlVector4::normalize3WithLength() {
	float32 lenSq3 = quad.v[0]*quad.v[0] + quad.v[1]*quad.v[1] + quad.v[2]*quad.v[2];
	float32 len3 = lenSq3;
	if (lenSq3 > FLOAT32_EPSILON) {
		len3 = jlMath::Sqrt(lenSq3);
		float32 invLen3 = 1.0f / len3;
		quad.v[0] *= invLen3;
		quad.v[1] *= invLen3;
		quad.v[2] *= invLen3;
	}
	return len3;
}


JL_FORCE_INLINE jlComp jlVector4::compEqual(const jlVector4& vec) const {
	jlComp ce;
	ce.mask = ((quad.v[0] == vec.quad.v[0]) ? jlComp::MASK_X : jlComp::MASK_NONE) |
			  ((quad.v[1] == vec.quad.v[1]) ? jlComp::MASK_Y : jlComp::MASK_NONE) |
			  ((quad.v[2] == vec.quad.v[2]) ? jlComp::MASK_Z : jlComp::MASK_NONE) |
			  ((quad.v[3] == vec.quad.v[3]) ? jlComp::MASK_W : jlComp::MASK_NONE);
	return ce;
}

JL_FORCE_INLINE jlComp jlVector4::compNotEqual(const jlVector4& vec) const {
	jlComp cne;
	cne.mask = ((quad.v[0] != vec.quad.v[0]) ? jlComp::MASK_X : jlComp::MASK_NONE) |
			   ((quad.v[1] != vec.quad.v[1]) ? jlComp::MASK_Y : jlComp::MASK_NONE) |
			   ((quad.v[2] != vec.quad.v[2]) ? jlComp::MASK_Z : jlComp::MASK_NONE) |
			   ((quad.v[3] != vec.quad.v[3]) ? jlComp::MASK_W : jlComp::MASK_NONE);
	return cne;
}

JL_FORCE_INLINE jlComp jlVector4::compLess(const jlVector4& vec) const {
	jlComp clt;
	clt.mask = ((quad.v[0] < vec.quad.v[0]) ? jlComp::MASK_X : jlComp::MASK_NONE) |
			   ((quad.v[1] < vec.quad.v[1]) ? jlComp::MASK_Y : jlComp::MASK_NONE) |
			   ((quad.v[2] < vec.quad.v[2]) ? jlComp::MASK_Z : jlComp::MASK_NONE) |
			   ((quad.v[3] < vec.quad.v[3]) ? jlComp::MASK_W : jlComp::MASK_NONE);
	return clt;
}

JL_FORCE_INLINE jlComp jlVector4::compGreater(const jlVector4& vec) const {
	jlComp cgt;
	cgt.mask = ((quad.v[0] > vec.quad.v[0]) ? jlComp::MASK_X : jlComp::MASK_NONE) |
			   ((quad.v[1] > vec.quad.v[1]) ? jlComp::MASK_Y : jlComp::MASK_NONE) |
			   ((quad.v[2] > vec.quad.v[2]) ? jlComp::MASK_Z : jlComp::MASK_NONE) |
			   ((quad.v[3] > vec.quad.v[3]) ? jlComp::MASK_W : jlComp::MASK_NONE);
	return cgt;
}

JL_FORCE_INLINE jlComp jlVector4::compLessEqual(const jlVector4& vec) const {
	jlComp cle;
	cle.mask = ((quad.v[0] <= vec.quad.v[0]) ? jlComp::MASK_X : jlComp::MASK_NONE) |
			   ((quad.v[1] <= vec.quad.v[1]) ? jlComp::MASK_Y : jlComp::MASK_NONE) |
			   ((quad.v[2] <= vec.quad.v[2]) ? jlComp::MASK_Z : jlComp::MASK_NONE) |
			   ((quad.v[3] <= vec.quad.v[3]) ? jlComp::MASK_W : jlComp::MASK_NONE);
	return cle;
}

JL_FORCE_INLINE jlComp jlVector4::compGreaterEqual(const jlVector4& vec) const {
	jlComp cge;
	cge.mask = ((quad.v[0] >= vec.quad.v[0]) ? jlComp::MASK_X : jlComp::MASK_NONE) |
			   ((quad.v[1] >= vec.quad.v[1]) ? jlComp::MASK_Y : jlComp::MASK_NONE) |
			   ((quad.v[2] >= vec.quad.v[2]) ? jlComp::MASK_Z : jlComp::MASK_NONE) |
			   ((quad.v[3] >= vec.quad.v[3]) ? jlComp::MASK_W : jlComp::MASK_NONE);
	return cge;
}

JL_FORCE_INLINE bool32 jlVector4::isZero3() const {
	return (quad.v[0] == 0.0f && quad.v[1] == 0.0f && quad.v[2] == 0.0f);
}

JL_FORCE_INLINE bool32 jlVector4::isZero4() const {
	return (quad.v[0] == 0.0f && quad.v[1] == 0.0f && quad.v[2] == 0.0f && quad.v[3] == 0.0f);
}

JL_FORCE_INLINE bool32 jlVector4::equals3(const jlVector4& vec) const {
	return (quad.v[0] == vec.quad.v[0] && quad.v[1] == vec.quad.v[1] && quad.v[2] == vec.quad.v[2]);
}

JL_FORCE_INLINE bool32 jlVector4::equals4(const jlVector4& vec) const {
	return (quad.v[0] == vec.quad.v[0] && quad.v[1] == vec.quad.v[1] && quad.v[2] == vec.quad.v[2] && quad.v[3] == vec.quad.v[3]);
}

JL_FORCE_INLINE bool32 jlVector4::operator ==(const jlVector4& rhs) const {
	return equals4(rhs);	
}

JL_FORCE_INLINE bool32 jlVector4::operator !=(const jlVector4& rhs) const {
	return !equals4(rhs);
}

JL_FORCE_INLINE jlSimdFloat jlVector4::Dot3(const jlVector4& lhs, const jlVector4& rhs) {
	return lhs.dot3(rhs);	
}

JL_FORCE_INLINE jlSimdFloat jlVector4::Dot4(const jlVector4& lhs, const jlVector4& rhs) {
	return lhs.dot3(rhs);
}

JL_FORCE_INLINE jlSimdFloat jlVector4::Distance(const jlVector4& lhs, const jlVector4& rhs) {
	jlVector4 diff;
	diff.setSub(lhs, rhs);
	return diff.length3();
}

JL_FORCE_INLINE jlSimdFloat jlVector4::DistanceSquared(const jlVector4& lhs, const jlVector4& rhs) {
	jlVector4 diff;
	diff.setSub(lhs, rhs);
	return diff.lengthSquared3();
}

JL_FORCE_INLINE jlVector4 jlVector4::Cross(const jlVector4& lhs, const jlVector4& rhs) {
	return lhs.cross(rhs);
}

JL_FORCE_INLINE jlVector4 jlVector4::Lerp(const jlVector4& a, const jlVector4& b, const jlSimdFloat& t) {
	jlVector4 ab;
	ab.setSub(b, a);
	jlVector4 interp = jlVector4(a);
	ab.mul(t);
	interp.add(ab);
	return interp;
}

JL_FORCE_INLINE jlVector4 jlVector4::Slerp(const jlVector4& a, const jlVector4& b, const jlSimdFloat& t) {
	jlSimdFloat dot = a.dot3(b);
	jlSimdFloat theta = jlMath::ACos(dot) * t; // clamps to -1 to 1 in ACos for you
	jlVector4 relativeVec = b - a * dot;
	jlSimdFloat cos = jlMath::Cos(theta);
	jlSimdFloat sin = jlMath::Sin(theta);
	relativeVec.normalize3();
	return a * cos + relativeVec * sin;
}

JL_FORCE_INLINE jlVector4 jlVector4::SmoothStep(const jlVector4& a, const jlVector4& b, const jlSimdFloat& t) {
	jlSimdFloat two = jlSimdFloat(2.0f);
	jlSimdFloat three = jlSimdFloat(3.0f);
	jlSimdFloat tt = t * t;
	jlSimdFloat t2 = two * t;
	jlVector4 ab;
	ab.setSub(b, a);
	jlVector4 interp = jlVector4(a);
	jlSimdFloat x = tt * (three - two * t);
	ab.mul(x);
	interp.add(ab);
	return interp;
}

JL_FORCE_INLINE jlVector4 jlVector4::Reflect(const jlVector4& v, const jlVector4& n) {
	jlSimdFloat two = jlSimdFloat(2.0f);
	return v - two * (v.dot3(n) * n);
}
