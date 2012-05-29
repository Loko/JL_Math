/// @file jlVector4SSE.h
/// @author Jeff Lansing

#ifndef JL_SIMD_ENABLED
#error "Cannot include SSE2 vector4 with this configuration!"
#endif

/// SIMD enabled 4 float container, enables very fast parrallel ops
/// be careful to ensure JL_ALIGN_16 is used for loadAligned and storeAligned
/// Reference: http://msdn.microsoft.com/en-us/library/x5c07e2a%28v=vs.80%29.aspx
/// Other: // http://www.cs.uaf.edu/2006/fall/cs301/lecture/11_17_sse.html
JL_FORCE_INLINE jlVector4::jlVector4() { }

JL_FORCE_INLINE jlVector4::jlVector4(const quad128& q) : quad(q) {  }

JL_FORCE_INLINE jlVector4::jlVector4(float32 x, float32 y, float32 z, float32 w) : quad(_mm_setr_ps(x, y, z, w)) { }

JL_FORCE_INLINE jlVector4::jlVector4(const jlVector4& vec) : quad(vec.quad) { }

JL_FORCE_INLINE jlVector4& jlVector4::operator =(const jlVector4& vec) {
	quad = vec.quad;
	return *this;
}

JL_FORCE_INLINE const float32& jlVector4::operator()(int32 i) const {
	JL_ASSERT_MSG(i >= 0 && i < 4, "Index of %d is out of bounds of the jlVector4", i);
	return quad.m128_f32[i];
}

JL_FORCE_INLINE float32& jlVector4::operator()(int32 i) {
	JL_ASSERT_MSG(i >= 0 && i < 4, "Index of %d is out of bounds of the jlVector4", i);
	return quad.m128_f32[i];
}

JL_FORCE_INLINE bool32 jlVector4::isOk() const {
	// todo check out cmpord
	return (!jlMath::IsNaN(quad.m128_f32[0]) && !jlMath::IsNaN(quad.m128_f32[1]) &&
		!jlMath::IsNaN(quad.m128_f32[2]) && !jlMath::IsNaN(quad.m128_f32[3]));
}

JL_FORCE_INLINE void jlVector4::store(float32 *vec) const {
	_mm_storeu_ps(vec, quad);
}

JL_FORCE_INLINE void jlVector4::storeAligned(float32 *vec) const {
	_mm_store_ps(vec, quad);
}

JL_FORCE_INLINE void jlVector4::load(const float32 *vec) {
	quad = _mm_loadu_ps(vec);
}

JL_FORCE_INLINE void jlVector4::loadAligned(const float32 *vec) {
	quad = _mm_load_ps(vec);
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
	return jlSimdFloat(_mm_shuffle_ps(quad, quad, _MM_SHUFFLE(0, 0, 0, 0)));
}

template <>
JL_FORCE_INLINE jlSimdFloat jlVector4::getElem<1>() const {
	return jlSimdFloat(_mm_shuffle_ps(quad, quad, _MM_SHUFFLE(1, 1, 1, 1)));
}

template <>
JL_FORCE_INLINE jlSimdFloat jlVector4::getElem<2>() const {
	return jlSimdFloat(_mm_shuffle_ps(quad, quad, _MM_SHUFFLE(2, 2, 2, 2)));
}

template <>
JL_FORCE_INLINE jlSimdFloat jlVector4::getElem<3>() const {
	return jlSimdFloat(_mm_shuffle_ps(quad, quad, _MM_SHUFFLE(3, 3, 3, 3)));
}

JL_FORCE_INLINE jlSimdFloat jlVector4::getElem(int32 i) const {
	JL_ASSERT_MSG(i >= 0 && i <= 3, "Invalid index for jlVector4");
	switch (i) {
		case 0:
			return jlSimdFloat(quad);
		case 1:
			return jlSimdFloat(_mm_shuffle_ps(quad, quad, _MM_SHUFFLE(1, 1, 1, 1)));
		case 2:
			return jlSimdFloat(_mm_shuffle_ps(quad, quad, _MM_SHUFFLE(2, 2, 2, 2)));
		default: // 3
			return jlSimdFloat(_mm_shuffle_ps(quad, quad, _MM_SHUFFLE(3, 3, 3, 3)));
	}
}

template <int32 i> 
JL_FORCE_INLINE void jlVector4::setElem(const jlSimdFloat& s) {
	JL_STATIC_ASSERT_FAIL();
}

template <>
JL_FORCE_INLINE void jlVector4::setElem<0>(const jlSimdFloat& s) {
	quad = _mm_shuffle_ps(_mm_unpacklo_ps(quad, s.f), quad, _MM_SHUFFLE(3,2,1,0));	
}

template <>
JL_FORCE_INLINE void jlVector4::setElem<1>(const jlSimdFloat& s) {
	quad = _mm_shuffle_ps( _mm_unpacklo_ps(quad, s.f), quad, _MM_SHUFFLE(3,2,1,0));
}

template <>
JL_FORCE_INLINE void jlVector4::setElem<2>(const jlSimdFloat& s) {
	quad = _mm_shuffle_ps(quad, _mm_unpackhi_ps(quad, s.f), _MM_SHUFFLE(2,3,1,0));
}

template <>
JL_FORCE_INLINE void jlVector4::setElem<3>(const jlSimdFloat& s) {
	quad = _mm_shuffle_ps(quad, _mm_unpackhi_ps(quad, s.f), _MM_SHUFFLE(3,0,1,0));
}

JL_FORCE_INLINE void jlVector4::set(const jlSimdFloat& x, const jlSimdFloat& y, const jlSimdFloat& z, const jlSimdFloat& w) {
	quad128 xy = _mm_unpacklo_ps(x.f, y.f);
	quad128 zw = _mm_unpacklo_ps(z.f, w.f);
	quad = _mm_movelh_ps(xy, zw);
}

JL_FORCE_INLINE void jlVector4::set(float32 x, float32 y, float32 z, float32 w) {
	quad = _mm_setr_ps(x, y, z, w);
}

JL_FORCE_INLINE void jlVector4::setAll(const jlSimdFloat& v) {
	quad = v.f;
}

JL_FORCE_INLINE void jlVector4::setZero3() {
	float32 w = quad.m128_f32[3];
	quad = _mm_setr_ps(0.0f, 0.0f, 0.0f, w);
}

JL_FORCE_INLINE void jlVector4::setZero4() {
	quad = _mm_setzero_ps();	
}

JL_FORCE_INLINE bool32 jlVector4::isZero3() const {
	int32 maskXYZ = 7;
	return _mm_movemask_ps(_mm_cmpeq_ps(quad, QUAD_ZERO)) & maskXYZ; 
}

JL_FORCE_INLINE bool32 jlVector4::isZero4() const {
	return _mm_movemask_ps(_mm_cmpeq_ps(quad, QUAD_ZERO)); 
}

JL_FORCE_INLINE jlVector4 jlVector4::operator+(const jlVector4& rhs) const {
	jlVector4 s;
	s.quad = _mm_add_ps(quad, rhs.quad);
	return s;
}

JL_FORCE_INLINE jlVector4 jlVector4::operator-(const jlVector4& rhs) const {
	jlVector4 d;
	d.quad = _mm_sub_ps(quad, rhs.quad);
	return d;
}

JL_FORCE_INLINE jlVector4 jlVector4::operator*(const jlSimdFloat& s) const {
	jlVector4 p;
	p.quad = _mm_mul_ps(quad, s.f);
	return p;
}

JL_FORCE_INLINE jlVector4 operator*(const jlSimdFloat& s, const jlVector4& v) {
	jlVector4 p = jlVector4(v.quad);
	p.mul(s);
	return p;
}

JL_FORCE_INLINE jlVector4 jlVector4::operator/(const jlSimdFloat& s) const {
	jlVector4 d;
	d.quad = _mm_div_ps(quad, s.f);
	return d;
}

JL_FORCE_INLINE jlVector4 jlVector4::operator/(const jlVector4& rhs) const {
	jlVector4 div;
	div.quad = _mm_div_ps(quad, rhs.quad);
	return div;
}

// negate methods could probably be faster using an abs mask
JL_FORCE_INLINE jlVector4 jlVector4::operator -() const {
	jlVector4 n;
	n.quad = _mm_sub_ps(QUAD_ZERO, quad);
	return n;
}

JL_FORCE_INLINE jlVector4& jlVector4::operator +=(const jlVector4& rhs) {
	quad = _mm_add_ps(quad, rhs.quad);
	return *this;
}

JL_FORCE_INLINE jlVector4& jlVector4::operator -=(const jlVector4 &rhs) {
	quad = _mm_sub_ps(quad, rhs.quad);
	return *this;
}

JL_FORCE_INLINE jlVector4& jlVector4::operator *=(const jlSimdFloat& s) {
  quad = _mm_mul_ps(quad, s.f);
	return *this;
}

JL_FORCE_INLINE jlVector4& jlVector4::operator /=(const jlSimdFloat& s) {
	quad = _mm_div_ps(quad, s.f);
	return *this;
}

JL_FORCE_INLINE jlVector4& jlVector4::operator /=(const jlVector4& rhs) {
	quad = _mm_div_ps(quad, rhs.quad);
	return *this;
}

JL_FORCE_INLINE void jlVector4::setAdd(const jlVector4& a, const jlVector4& b) {
	quad = _mm_add_ps(a.quad, b.quad);
}

JL_FORCE_INLINE void jlVector4::setSub(const jlVector4& a, const jlVector4& b) {
	quad = _mm_sub_ps(a.quad, b.quad);
}

JL_FORCE_INLINE void jlVector4::setMul(const jlVector4& v, const jlSimdFloat& s) {
	//quad128 sv = _mm_set1_ps(s);
	quad = _mm_mul_ps(v.quad, s.f);
}

JL_FORCE_INLINE void jlVector4::setMul(const jlVector4& a, const jlVector4& b) {
	quad = _mm_mul_ps(a.quad, b.quad);
}

JL_FORCE_INLINE void jlVector4::setDiv(const jlVector4& v, const jlSimdFloat& s) {
	quad = _mm_div_ps(v.quad, s.f);
}

JL_FORCE_INLINE void jlVector4::setDiv(const jlVector4& v, const jlVector4& d) {
	quad = _mm_div_ps(v.quad, d.quad);
}

JL_FORCE_INLINE void jlVector4::setCross(const jlVector4& lhs, const jlVector4& rhs) {
	quad128 cross0;
	quad128 cross1;
	cross0 = _mm_mul_ps(
		_mm_shuffle_ps(lhs.quad, lhs.quad, _MM_SHUFFLE(3,0,2,1)),
		_mm_shuffle_ps(rhs.quad, rhs.quad, _MM_SHUFFLE(3,1,0,2))
	);
	cross1 = _mm_mul_ps(
		_mm_shuffle_ps(lhs.quad, lhs.quad, _MM_SHUFFLE(3,1,0,2)),
		_mm_shuffle_ps(rhs.quad, rhs.quad, _MM_SHUFFLE(3,0,2,1))
	);
	quad = _mm_sub_ps(cross0, cross1);
}

JL_FORCE_INLINE	void jlVector4::setMin(const jlVector4& lhs, const jlVector4& rhs) {
	quad = _mm_min_ps(lhs.quad, rhs.quad);
}

JL_FORCE_INLINE	void jlVector4::setMax(const jlVector4& lhs, const jlVector4& rhs) {
	quad = _mm_max_ps(lhs.quad, rhs.quad);
}

JL_FORCE_INLINE void jlVector4::setNegation(const jlVector4& vec) {
	quad = _mm_sub_ps(QUAD_ZERO, vec.quad);
}

template <int32 i>
JL_FORCE_INLINE void jlVector4::setReplication(const jlVector4& vec) {
	quad = _mm_shuffle_ps(vec.quad, vec.quad, _MM_SHUFFLE(i, i, i, i));
}

JL_FORCE_INLINE void jlVector4::add(const jlVector4& rhs) {
	quad = _mm_add_ps(quad, rhs.quad);
}

JL_FORCE_INLINE void jlVector4::sub(const jlVector4& rhs) {
	quad = _mm_sub_ps(quad, rhs.quad);
}

JL_FORCE_INLINE void jlVector4::mul(const jlSimdFloat& s) {
  quad = _mm_mul_ps(quad, s.f);
}

JL_FORCE_INLINE void jlVector4::mul(const jlVector4& a) {
	quad = _mm_mul_ps(quad, a.quad);
}

JL_FORCE_INLINE void jlVector4::div(const jlSimdFloat& s) {
	quad = _mm_div_ps(quad, s.f);
}

JL_FORCE_INLINE	void jlVector4::div(const jlVector4& d) {
	quad = _mm_div_ps(quad, d.quad);
}

JL_FORCE_INLINE void jlVector4::negate() {
	quad = _mm_sub_ps(QUAD_ZERO, quad);
}

JL_FORCE_INLINE jlSimdFloat jlVector4::length3() const {
	quad128 p = _mm_mul_ps(quad, quad);
	quad128 xySum = _mm_add_ss(_mm_shuffle_ps(p, p, _MM_SHUFFLE(1,1,1,1)), p);
	quad128 dot = _mm_add_ss(_mm_shuffle_ps(p, p, _MM_SHUFFLE(2,2,2,2)), xySum);
	return jlSimdFloat(_mm_sqrt_ss(dot));
}

JL_FORCE_INLINE jlSimdFloat jlVector4::lengthSquared3() const {
	quad128 p = _mm_mul_ps(quad, quad);
	quad128 xySum = _mm_add_ss( _mm_shuffle_ps(p, p, _MM_SHUFFLE(1,1,1,1)), p);
	quad128 dot = _mm_add_ss( _mm_shuffle_ps(p, p, _MM_SHUFFLE(2,2,2,2)), xySum);
	return jlSimdFloat(dot);
}

JL_FORCE_INLINE jlSimdFloat jlVector4::length4() const {
	quad128 p = _mm_mul_ps(quad, quad);
	quad128 sum0 = _mm_add_ps(_mm_shuffle_ps(p, p, _MM_SHUFFLE(1,0,3,2)), p);
	quad128 sum1 = _mm_shuffle_ps(sum0, sum0, _MM_SHUFFLE(2,3,0,1));
	quad128 dot = _mm_add_ps(sum0, sum1);
	return jlSimdFloat(_mm_sqrt_ss(dot));
}

JL_FORCE_INLINE jlSimdFloat jlVector4::lengthSquared4() const {
	jlSimdFloat lenSq4;
	quad128 p = _mm_mul_ps(quad, quad);
	quad128 sum0 = _mm_add_ps(_mm_shuffle_ps(p, p, _MM_SHUFFLE(1,0,3,2)), p);
	quad128 sum1 = _mm_shuffle_ps(sum0, sum0, _MM_SHUFFLE(2,3,0,1));
	lenSq4.f =  _mm_add_ps(sum0, sum1);
	return lenSq4;
}

JL_FORCE_INLINE jlSimdFloat jlVector4::dot3(const jlVector4& rhs) const {
	jlSimdFloat d3;
	quad128 x2 = _mm_mul_ps(quad, rhs.quad);
	quad128 xySum = _mm_add_ss(_mm_shuffle_ps(x2, x2, _MM_SHUFFLE(1,1,1,1)), x2);
	d3.f = _mm_add_ss(_mm_shuffle_ps(x2, x2, _MM_SHUFFLE(2,2,2,2)), xySum);
	return d3;
}

JL_FORCE_INLINE jlSimdFloat jlVector4::dot4(const jlVector4& rhs) const {
	jlSimdFloat sr;
	quad128 x2 = _mm_mul_ps(quad, rhs.quad);
	quad128 sum0 = _mm_add_ps(_mm_shuffle_ps(x2, x2, _MM_SHUFFLE(1,0,3,2)), x2);
	quad128 sum1 = _mm_shuffle_ps(sum0, sum0, _MM_SHUFFLE(2,3,0,1));
	sr.f = _mm_add_ps(sum0, sum1);
	return sr;
}

JL_FORCE_INLINE jlVector4 jlVector4::cross(const jlVector4& rhs) const {
	quad128 cross0;
	quad128 cross1;
	cross0 = _mm_mul_ps(
		_mm_shuffle_ps(quad, quad, _MM_SHUFFLE(3,0,2,1)),
		_mm_shuffle_ps(rhs.quad, rhs.quad, _MM_SHUFFLE(3,1,0,2))
	);
	cross1 = _mm_mul_ps(
		_mm_shuffle_ps(quad, quad, _MM_SHUFFLE(3,1,0,2)),
		_mm_shuffle_ps(rhs.quad, rhs.quad, _MM_SHUFFLE(3,0,2,1))
	);
	return jlVector4(_mm_sub_ps(cross0, cross1));
}

JL_FORCE_INLINE void jlVector4::normalize3() {
	// find the lenSq first
	quad128 mult = _mm_mul_ps(quad, quad);
	quad128 xySum = _mm_add_ss(_mm_shuffle_ps(mult, mult, _MM_SHUFFLE(1,1,1,1)), mult);
	quad128 lenSq = _mm_add_ss(_mm_shuffle_ps(mult, mult, _MM_SHUFFLE(2,2,2,2)), xySum);
	// if it is zero, the actual scalar adjustment is different
	quad128 lenSqCmpZero = _mm_cmpeq_ss(lenSq, QUAD_SINGLE_ZERO);
	quad128 invMag = _mm_rsqrt_ss(lenSq);
	quad128 refined = _mm_mul_ss(
		_mm_mul_ss(QUAD_SINGLE_INV_TWO, invMag),
		_mm_sub_ss(QUAD_SINGLE_THREE, _mm_mul_ss( _mm_mul_ss(lenSq, invMag), invMag))
	);
	// multiplier is 0 if the lenSq is zero
	quad128 multiplier = _mm_andnot_ps(lenSqCmpZero, refined);
	quad128 replicatedMultiplier = _mm_shuffle_ps(multiplier, multiplier, _MM_SHUFFLE(0, 0, 0, 0));
	quad = _mm_mul_ps(quad, replicatedMultiplier);
}

JL_FORCE_INLINE void jlVector4::normalize4() {
	// same as above, but for all four components
	quad128 mult = _mm_mul_ps(quad, quad);
	quad128 sum0 = _mm_add_ps(_mm_shuffle_ps(mult, mult, _MM_SHUFFLE(1,0,3,2)), mult);
	quad128 sum1 = _mm_shuffle_ps(sum0, sum0, _MM_SHUFFLE(2,3,0,1));
	quad128 lenSq = _mm_add_ps(sum0, sum1);
	quad128 lenSqCmpZero = _mm_cmpeq_ss(lenSq, QUAD_SINGLE_ZERO);
	quad128 invMag = _mm_rsqrt_ss(lenSq);
	const quad128 refined = _mm_mul_ss(
		_mm_mul_ss(QUAD_INV_TWO, invMag),
		_mm_sub_ss(QUAD_THREE, _mm_mul_ss(_mm_mul_ss(lenSq, invMag), invMag))
	);
	// Ensures that we return 0 if the length is 0
	quad128 multiplier = _mm_andnot_ps(lenSqCmpZero, refined);
	quad128 replicatedMultiplier = _mm_shuffle_ps(multiplier, multiplier, _MM_SHUFFLE(0, 0, 0, 0));
	quad = _mm_mul_ps(quad, replicatedMultiplier);
}

JL_FORCE_INLINE jlSimdFloat jlVector4::normalize3WithLength() {
	// find the lenSq first
	jlSimdFloat lensf;
	quad128 mult = _mm_mul_ps(quad, quad);
	quad128 xySum = _mm_add_ss(_mm_shuffle_ps(mult, mult, _MM_SHUFFLE(1,1,1,1)), mult);
	quad128 lenSq = _mm_add_ss(_mm_shuffle_ps(mult, mult, _MM_SHUFFLE(2,2,2,2)), xySum);
	// if it is zero, the actual scalar adjustment is different
	quad128 len = _mm_sqrt_ss(lenSq);
	lensf.f = len;
	quad128 lenSqCmpZero = _mm_cmpeq_ss(lenSq, QUAD_SINGLE_ZERO);
	quad128 invMag = _mm_div_ss(QUAD_SINGLE_ZERO, len);//_mm_rsqrt_ss(lenSq);
	quad128 refined = _mm_mul_ss(
		_mm_mul_ss(QUAD_SINGLE_INV_TWO, invMag),
		_mm_sub_ss(QUAD_SINGLE_THREE, _mm_mul_ss( _mm_mul_ss(lenSq, invMag), invMag))
	);
	// multiplier is 0 if the lenSq is zero
	quad128 multiplier = _mm_andnot_ps(lenSqCmpZero, refined);
	quad128 replicatedMultiplier = _mm_shuffle_ps(multiplier, multiplier, _MM_SHUFFLE(0, 0, 0, 0));
	quad = _mm_mul_ps(quad, replicatedMultiplier);
	return lensf;
}

JL_FORCE_INLINE bool32 jlVector4::equals3(const jlVector4& vec) const {
	const int quadMaskXYZ = 7;
	return _mm_movemask_ps(_mm_cmpeq_ps(quad, vec.quad)) == quadMaskXYZ;
}

JL_FORCE_INLINE bool32 jlVector4::equals4(const jlVector4& vec) const {
	const int quadMaskXYZW = 15;
	return _mm_movemask_ps(_mm_cmpeq_ps(quad, vec.quad)) == quadMaskXYZW;
}

JL_FORCE_INLINE bool32 jlVector4::operator ==(const jlVector4& rhs) const {
	return this->equals4(rhs);
}

JL_FORCE_INLINE bool32 jlVector4::operator !=(const jlVector4& rhs) const {
	return !(this->equals4(rhs));
}

JL_FORCE_INLINE jlComp jlVector4::compEqual(const jlVector4& vec) const {
	jlComp ce;
	ce.mask = _mm_cmpeq_ps(quad, vec.quad);
	return ce;
}

JL_FORCE_INLINE jlComp jlVector4::compNotEqual(const jlVector4& vec) const {
	jlComp ce;
	ce.mask = _mm_cmpneq_ps(quad, vec.quad);
	return ce;
}

JL_FORCE_INLINE jlComp jlVector4::compLess(const jlVector4& vec) const {
	jlComp ce;
	ce.mask = _mm_cmplt_ps(quad, vec.quad);
	return ce;
}

JL_FORCE_INLINE jlComp jlVector4::compGreater(const jlVector4& vec) const {
	jlComp ce;
	ce.mask = _mm_cmpgt_ps(quad, vec.quad);
	return ce;
}

JL_FORCE_INLINE jlComp jlVector4::compLessEqual(const jlVector4& vec) const {
	jlComp ce;
	ce.mask = _mm_cmple_ps(quad, vec.quad);
	return ce;
}

JL_FORCE_INLINE jlComp jlVector4::compGreaterEqual(const jlVector4& vec) const {
	jlComp ce;
	ce.mask = _mm_cmpge_ps(quad, vec.quad);
	return ce;
}

JL_FORCE_INLINE jlSimdFloat jlVector4::Dot3(const jlVector4& lhs, const jlVector4& rhs) {
	quad128 p = _mm_mul_ps(lhs.quad, rhs.quad);
	quad128 xySum = _mm_add_ss(_mm_shuffle_ps(p, p, _MM_SHUFFLE(1,1,1,1)), p);
	return jlSimdFloat(_mm_add_ss(_mm_shuffle_ps(p, p, _MM_SHUFFLE(2,2,2,2)), xySum));
}

JL_FORCE_INLINE jlSimdFloat jlVector4::Dot4(const jlVector4& lhs, const jlVector4& rhs) {
	jlSimdFloat d4;
	quad128 x2 = _mm_mul_ps(lhs.quad, rhs.quad);
	quad128 sum0 = _mm_add_ps(_mm_shuffle_ps(x2, x2, _MM_SHUFFLE(1,0,3,2)), x2);
	quad128 sum1 = _mm_shuffle_ps(sum0,sum0, _MM_SHUFFLE(2,3,0,1));
	d4.f = _mm_add_ps(sum0, sum1);
	return d4;
}

JL_FORCE_INLINE jlSimdFloat jlVector4::Distance(const jlVector4& lhs, const jlVector4& rhs) {
	jlVector4 d(_mm_sub_ps(lhs.quad, rhs.quad));
	return d.length3();
}

JL_FORCE_INLINE jlSimdFloat jlVector4::DistanceSquared(const jlVector4& lhs, const jlVector4& rhs) {
	jlVector4 d;
	d.setSub(lhs, rhs);
	return d.lengthSquared3();
}

JL_FORCE_INLINE jlVector4 jlVector4::Cross(const jlVector4& lhs, const jlVector4& rhs) {
	jlVector4 cross;
	quad128 cross0, cross1;
	cross0 = _mm_mul_ps(
		_mm_shuffle_ps(lhs.quad, lhs.quad, _MM_SHUFFLE(3,0,2,1)),
		_mm_shuffle_ps(rhs.quad, rhs.quad, _MM_SHUFFLE(3,1,0,2)));
	cross1 = _mm_mul_ps(
		_mm_shuffle_ps(lhs.quad, lhs.quad, _MM_SHUFFLE(3,1,0,2)),
		_mm_shuffle_ps(rhs.quad, rhs.quad, _MM_SHUFFLE(3,0,2,1)));
	cross.quad = _mm_sub_ps(cross0, cross1);
	return cross;
}

JL_FORCE_INLINE jlVector4 jlVector4::Lerp(const jlVector4& lhs, const jlVector4& rhs, const jlSimdFloat& t) {
	quad128 qt = _mm_max_ps(t.f, QUAD_ZERO);
	qt = _mm_min_ps(qt, QUAD_ONE);
	quad128 lrp = _mm_add_ps(lhs.quad, _mm_mul_ps(_mm_sub_ps(rhs.quad, lhs.quad), qt));
	return jlVector4(lrp);
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
	jlSimdFloat zero = jlSimdFloat(0.0f);
	jlSimdFloat one = jlSimdFloat(1.0f);
	jlSimdFloat two = jlSimdFloat(2.0f);
	jlSimdFloat three = jlSimdFloat(3.0f);
	jlSimdFloat ct; ct.setMax(t, zero); ct.setMin(ct, one);
	jlVector4 interp = jlVector4(a);
	jlVector4 ab; ab.setSub(b, a);
	jlSimdFloat tt = ct * ct;
	jlSimdFloat t2 = two * ct;
	jlSimdFloat x = tt * (three - two * ct);
	ab.mul(x);
	interp.add(ab);
	return interp;
}

JL_FORCE_INLINE jlVector4 jlVector4::Reflect(const jlVector4& v, const jlVector4& n) {
	jlSimdFloat s = jlSimdFloat(2.0f);
	return v - (s * v.dot3(n) * n);
}
