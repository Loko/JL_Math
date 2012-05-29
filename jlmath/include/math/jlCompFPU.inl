
JL_FORCE_INLINE jlComp::Mask jlComp::getMask() const {
	return static_cast<jlComp::Mask>(mask);
}

JL_FORCE_INLINE bool32 jlComp::anyIsSet() const {
	return mask;
}

JL_FORCE_INLINE bool32 jlComp::anyIsSet(jlComp::Mask m) const {
	return (mask & m);
}

JL_FORCE_INLINE bool32 jlComp::allAreSet() const {
	return (mask & jlComp::MASK_XYZW);
}

JL_FORCE_INLINE bool32 jlComp::allAreSet(jlComp::Mask m) const {
	return ((mask & m) == m);
}

JL_FORCE_INLINE void jlComp::setAnd(const jlComp& a, const jlComp& b) {
	mask = (a.mask & b.mask);
}

JL_FORCE_INLINE void jlComp::setOr(const jlComp& a, const jlComp& b) {
	mask = (a.mask | b.mask);
}

JL_FORCE_INLINE void jlComp::setXor(const jlComp& a, const jlComp& b) {
	mask = (a.mask ^ b.mask);
}

JL_FORCE_INLINE const jlCompMask& jlComp::getCompMask() const {
	return mask;
}

JL_FORCE_INLINE jlCompMask& jlComp::getCompMask() {
	return mask;
}

JL_FORCE_INLINE void jlComp::setCompMask(const jlCompMask& vm) {
	mask = vm;
}
