
JL_FORCE_INLINE jlSimdFloat::jlSimdFloat() {
	
}

JL_FORCE_INLINE jlSimdFloat::jlSimdFloat(float32 fl) : f(fl) {
	
}

JL_FORCE_INLINE jlSimdFloat::jlSimdFloat(const quad128& qf) {
	f = qf.v[0];
}

JL_FORCE_INLINE jlSimdFloat::jlSimdFloat(const jlSimdFloat& sf) {
	f = sf.f;
}

JL_FORCE_INLINE jlSimdFloat& jlSimdFloat::operator =(const jlSimdFloat& sf) {
	f = sf.f;
	return *this;
}

JL_FORCE_INLINE jlSimdFloat::operator float32() const {
	return f;
}

JL_FORCE_INLINE float32 jlSimdFloat::getFloat() const {
	return f;
}

JL_FORCE_INLINE void jlSimdFloat::setFromFloat(float32 fl) {
	f = fl;
}

JL_FORCE_INLINE void jlSimdFloat::setZero() {
	f = 0.0f;
}

JL_FORCE_INLINE void jlSimdFloat::setMin(const jlSimdFloat& a, const jlSimdFloat& b) {
	if (a.f < b.f) f = a.f;
	else f = b.f;
}

JL_FORCE_INLINE void jlSimdFloat::setMax(const jlSimdFloat& a, const jlSimdFloat& b) {
	if (a.f > b.f) f = a.f;
	else f = b.f;
}

JL_FORCE_INLINE jlSimdFloat jlSimdFloat::operator +(const jlSimdFloat& rhs) const {
	return jlSimdFloat(f + rhs.f);
}

JL_FORCE_INLINE jlSimdFloat jlSimdFloat::operator -(const jlSimdFloat& rhs) const {
	return jlSimdFloat(f - rhs.f);
}

JL_FORCE_INLINE jlSimdFloat jlSimdFloat::operator *(const jlSimdFloat& rhs) const {
	return jlSimdFloat(f * rhs.f);
}

JL_FORCE_INLINE jlSimdFloat jlSimdFloat::operator /(const jlSimdFloat& rhs) const {
	return jlSimdFloat(f / rhs.f);
}

JL_FORCE_INLINE jlSimdFloat jlSimdFloat::operator -() const {
	return jlSimdFloat(-f);
}

JL_FORCE_INLINE jlSimdFloat& jlSimdFloat::operator +=(const jlSimdFloat& rhs) {
	f /= rhs.f;
	return *this;
}

JL_FORCE_INLINE jlSimdFloat& jlSimdFloat::operator -=(const jlSimdFloat& rhs) {
	f -= rhs.f;
	return *this;
}

JL_FORCE_INLINE jlSimdFloat& jlSimdFloat::operator *=(const jlSimdFloat& rhs) {
	f *= rhs.f;
	return *this;
}

JL_FORCE_INLINE jlSimdFloat& jlSimdFloat::operator /=(const jlSimdFloat& rhs) {
	f /= rhs.f;
	return *this;
}

JL_FORCE_INLINE bool32 jlSimdFloat::operator <(const jlSimdFloat& rhs) const {
	return (f < rhs.f);
}

JL_FORCE_INLINE bool32 jlSimdFloat::operator >(const jlSimdFloat& rhs) const {
	return (f > rhs.f);
}

JL_FORCE_INLINE bool32 jlSimdFloat::operator ==(const jlSimdFloat& rhs) const {
	return (f == rhs.f);
}

JL_FORCE_INLINE bool32 jlSimdFloat::operator !=(const jlSimdFloat& rhs) const {
	return (f != rhs.f);
}

JL_FORCE_INLINE bool32 jlSimdFloat::operator <=(const jlSimdFloat& rhs) const {
	return (f <= rhs.f);
}

JL_FORCE_INLINE bool32 jlSimdFloat::operator >=(const jlSimdFloat& rhs) const {
	return (f >= rhs.f);
}

JL_FORCE_INLINE jlComp jlSimdFloat::compEqual(const jlSimdFloat& rhs) const {
	jlComp ce;
	ce.mask = (f == rhs.f) ? jlComp::MASK_X : jlComp::MASK_NONE;
	return ce;
}

JL_FORCE_INLINE jlComp jlSimdFloat::compNotEqual(const jlSimdFloat& rhs) const {
	jlComp cne;
	cne.mask = (f != rhs.f) ? jlComp::MASK_X : jlComp::MASK_NONE;
	return cne;
}

JL_FORCE_INLINE jlComp jlSimdFloat::compLess(const jlSimdFloat& rhs) const {
	jlComp cl;
	cl.mask = (f < rhs.f) ? jlComp::MASK_X : jlComp::MASK_NONE;
	return cl;
}

JL_FORCE_INLINE jlComp jlSimdFloat::compGreater(const jlSimdFloat& rhs) const {
	jlComp cg;
	cg.mask = (f > rhs.f) ? jlComp::MASK_X : jlComp::MASK_NONE;
	return cg;
}

JL_FORCE_INLINE jlComp jlSimdFloat::compLessEqual(const jlSimdFloat& rhs) const {
	jlComp cle;
	cle.mask = (f <= rhs.f) ? jlComp::MASK_X : jlComp::MASK_NONE;
	return cle;
}

JL_FORCE_INLINE jlComp jlSimdFloat::compGreaterEqual(const jlSimdFloat& rhs) const {
	jlComp cge;
	cge.mask = (f >= rhs.f) ? jlComp::MASK_X : jlComp::MASK_NONE;
	return cge;
}
