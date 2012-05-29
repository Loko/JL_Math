
JL_FORCE_INLINE jlSimdFloat jlMath::FastCos(const jlSimdFloat& x) {
	return jlSimdFloat(0.0f);
}

JL_FORCE_INLINE jlSimdFloat jlMath::FastSin(const jlSimdFloat& x) {
	return jlSimdFloat(0.0f);
}

JL_FORCE_INLINE jlSimdFloat jlMath::Abs(const jlSimdFloat& x) {
	float32 absolute = jlMath::Abs(x.f);
	return jlSimdFloat(absolute);
}

JL_FORCE_INLINE jlSimdFloat jlMath::Clamp(const jlSimdFloat& x, const jlSimdFloat& min, const jlSimdFloat& max) {
	float32 lowerBound = jlMath::Max(x.f, 0.0f);
	float32 clamped = jlMath::Min(lowerBound, 1.0f);
	return jlSimdFloat(clamped);
}

JL_FORCE_INLINE jlSimdFloat jlMath::Min(const jlSimdFloat& x, const jlSimdFloat& y) {
	float32 fmin = jlMath::Min(x.f, y.f);
	return jlSimdFloat(fmin);
}

JL_FORCE_INLINE jlSimdFloat jlMath::Max(const jlSimdFloat& x, const jlSimdFloat& y) {
	float32 fmax = jlMath::Max(x.f, y.f);
	return jlSimdFloat(fmax);
}

JL_FORCE_INLINE jlSimdFloat jlMath::Sqrt(const jlSimdFloat& x) {
	float32 fsqrt = jlMath::Sqrt(x.f);
	return jlSimdFloat(fsqrt);
}

JL_FORCE_INLINE jlSimdFloat jlMath::InvSqrt(const jlSimdFloat& x) {
	float32 invSqrt = 1.0f / sqrt(x.f);
	return jlSimdFloat(invSqrt);
}

JL_FORCE_INLINE jlSimdFloat jlMath::Saturate(const jlSimdFloat& x) {
	float32 fmin = jlMath::Max(x.f, 0.0f);
	float32 fclamped = jlMath::Min(fmin, 1.0f);
	return jlSimdFloat(fclamped);
}

JL_FORCE_INLINE jlSimdFloat jlMath::Lerp(const jlSimdFloat& a, const jlSimdFloat& b, const jlSimdFloat& t) {
	float32 tmin = jlMath::Max(t.f, 0.0f);
	float32 tclamped = jlMath::Min(tmin, 1.0f);
	float32 ab = b - a;
	return jlSimdFloat(a.f + ab * tclamped);
}

JL_FORCE_INLINE jlSimdFloat jlMath::SmoothStep(const jlSimdFloat& a, const jlSimdFloat& b, const jlSimdFloat& t) {
	float32 fsmoothstep = jlMath::SmoothStep(a.f, b.f, t.f);
	return jlSimdFloat(fsmoothstep);
}

JL_FORCE_INLINE jlSimdFloat jlMath::SmootherStep(const jlSimdFloat& a, const jlSimdFloat& b, const jlSimdFloat& t) {
	float32 fsmootherstep = jlMath::SmoothStep(a.f, b.f, t.f);
	return jlSimdFloat(fsmootherstep);
}
