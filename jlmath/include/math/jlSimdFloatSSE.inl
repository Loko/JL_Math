
JL_FORCE_INLINE jlSimdFloat::jlSimdFloat() {
	
}

JL_FORCE_INLINE jlSimdFloat::jlSimdFloat(float32 fl) {
	f = _mm_set1_ps(fl);
}

JL_FORCE_INLINE jlSimdFloat::jlSimdFloat(const quad128& qf) {
	f = qf;
}

JL_FORCE_INLINE jlSimdFloat::jlSimdFloat(const jlSimdFloat& sf) {
	f = sf.f;
}

JL_FORCE_INLINE jlSimdFloat& jlSimdFloat::operator =(const jlSimdFloat& sf) {
	f = sf.f;
	return *this;
}

JL_FORCE_INLINE jlSimdFloat::operator float32() const {
	return f.m128_f32[0];
}

JL_FORCE_INLINE float32 jlSimdFloat::getFloat() const {
	return f.m128_f32[0];
}

JL_FORCE_INLINE void jlSimdFloat::setFromFloat(float32 fl) {
	f = _mm_set1_ps(fl);
}

JL_FORCE_INLINE void jlSimdFloat::setZero() {
	f = _mm_setzero_ps();
}

JL_FORCE_INLINE void jlSimdFloat::setMin(const jlSimdFloat& a, const jlSimdFloat& b) {
	f = _mm_min_ps(a.f, b.f);
}

JL_FORCE_INLINE void jlSimdFloat::setMax(const jlSimdFloat& a, const jlSimdFloat& b) {
	f = _mm_max_ps(a.f, b.f);
}

JL_FORCE_INLINE jlSimdFloat jlSimdFloat::operator +(const jlSimdFloat& rhs) const {
	jlSimdFloat s;
	s.f = _mm_add_ps(f, rhs.f);
	return s;
}

JL_FORCE_INLINE jlSimdFloat jlSimdFloat::operator -(const jlSimdFloat& rhs) const {
	jlSimdFloat d;
	d.f = _mm_sub_ps(f, rhs.f);
	return d;
}

JL_FORCE_INLINE jlSimdFloat jlSimdFloat::operator *(const jlSimdFloat& rhs) const {
	jlSimdFloat p;
	p.f = _mm_mul_ps(f, rhs.f);
	return p;
}

JL_FORCE_INLINE jlSimdFloat jlSimdFloat::operator /(const jlSimdFloat& rhs) const {
	jlSimdFloat d;
	d.f = _mm_div_ps(f, rhs.f);
	return d;
}

JL_FORCE_INLINE jlSimdFloat jlSimdFloat::operator -() const {
	jlSimdFloat n;
	n.f = _mm_sub_ps(QUAD_ZERO, f);
	return n;
}

JL_FORCE_INLINE jlSimdFloat& jlSimdFloat::operator +=(const jlSimdFloat& rhs) {
	f = _mm_add_ps(f, rhs.f);
	return *this;
}

JL_FORCE_INLINE jlSimdFloat& jlSimdFloat::operator -=(const jlSimdFloat& rhs) {
	f = _mm_sub_ps(f, rhs.f);
	return *this;
}

JL_FORCE_INLINE jlSimdFloat& jlSimdFloat::operator *=(const jlSimdFloat& rhs) {
	f = _mm_mul_ps(f, rhs.f);
	return *this;
}

JL_FORCE_INLINE jlSimdFloat& jlSimdFloat::operator /=(const jlSimdFloat& rhs) {
	f = _mm_div_ps(f, rhs.f);
	return *this;
}

JL_FORCE_INLINE bool32 jlSimdFloat::operator <(const jlSimdFloat& rhs) const {
	return _mm_comilt_ss(f, rhs.f);
}

JL_FORCE_INLINE bool32 jlSimdFloat::operator >(const jlSimdFloat& rhs) const {
	return _mm_comigt_ss(f, rhs.f);
}

JL_FORCE_INLINE bool32 jlSimdFloat::operator ==(const jlSimdFloat& rhs) const {
	return _mm_comieq_ss(f, rhs.f);
}

JL_FORCE_INLINE bool32 jlSimdFloat::operator !=(const jlSimdFloat& rhs) const {
	return _mm_comineq_ss(f, rhs.f);
}

JL_FORCE_INLINE bool32 jlSimdFloat::operator <=(const jlSimdFloat& rhs) const {
	return _mm_comile_ss(f, rhs.f);
}

JL_FORCE_INLINE bool32 jlSimdFloat::operator >=(const jlSimdFloat& rhs) const {
	return _mm_comige_ss(f, rhs.f);
}

JL_FORCE_INLINE jlComp jlSimdFloat::compEqual(const jlSimdFloat& rhs) const {
	jlComp ce;
	ce.mask = _mm_cmpeq_ps(f, rhs.f);
	return ce;
}

JL_FORCE_INLINE jlComp jlSimdFloat::compNotEqual(const jlSimdFloat& rhs) const {
	jlComp cne;
	cne.mask = _mm_cmpneq_ps(f, rhs.f);
	return cne;
}

JL_FORCE_INLINE jlComp jlSimdFloat::compLess(const jlSimdFloat& rhs) const {
	jlComp cl;
	cl.mask = _mm_cmplt_ps(f, rhs.f);
	return cl;
}

JL_FORCE_INLINE jlComp jlSimdFloat::compGreater(const jlSimdFloat& rhs) const {
	jlComp cg;
	cg.mask = _mm_cmpgt_ps(f, rhs.f);
	return cg;
}

JL_FORCE_INLINE jlComp jlSimdFloat::compLessEqual(const jlSimdFloat& rhs) const {
	jlComp cle;
	cle.mask = _mm_cmple_ps(f, rhs.f);
	return cle;
}

JL_FORCE_INLINE jlComp jlSimdFloat::compGreaterEqual(const jlSimdFloat& rhs) const {
	jlComp cge;
	cge.mask = _mm_cmpge_ps(f, rhs.f);
	return cge;
}
