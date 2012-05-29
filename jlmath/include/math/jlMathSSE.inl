
// http://www.unknowncheats.me/forum/c-and-c/57668-fast-sine-and-cosine-simd.html
JL_FORCE_INLINE jlSimdFloat jlMath::FastCos(const jlSimdFloat& x) {
	jlSimdFloat halfPi = jlSimdFloat(jlMath::PI_OVER_TWO);
	jlSimdFloat fourPi = jlSimdFloat(jlMath::TWO_PI * 2.0f);
	jlSimdFloat v = x + halfPi;
	quad128 x4 = _mm_sub_ps( v.f, _mm_and_ps( _mm_cmpgt_ps( v.f, fourPi.f ), _mm_mul_ps( _mm_set_ps1( 2.0f ), fourPi.f ) ) );
	return jlMath::FastSin(x4);
}

JL_FORCE_INLINE jlSimdFloat jlMath::FastSin(const jlSimdFloat& x) {
	jlSimdFloat s;
	quad128 anded = _mm_and_ps(x.f, *(quad128 *)&_mm_set1_epi32(0x7FFFFFFF));
	quad128 mulAnded = _mm_mul_ps(x.f, anded);
	quad128 min4 = _mm_set_ps(-4.0f / (jlMath::PI * jlMath::PI), -4.0f / (jlMath::PI * jlMath::PI), -4.0f / (jlMath::PI * jlMath::PI), -4.0f / (jlMath::PI * jlMath::PI));
	quad128 mulMinAnded = _mm_mul_ps(min4, mulAnded);
	quad128 fourOverPi = _mm_set_ps(4.0f / jlMath::PI, 4.0f / jlMath::PI, 4.0f / jlMath::PI, 4.0f / jlMath::PI);
	quad128 xFourPi = _mm_mul_ps(fourOverPi, x.f);
	quad128 impreciseSin = _mm_add_ps(xFourPi, mulMinAnded);
	// additional precision
	quad128 precVal = _mm_set_ps(0.225f, 0.225f, 0.225f, 0.225f);
	quad128 absImpreciseSin = _mm_and_ps(impreciseSin, *(quad128 *)&_mm_set1_epi32(0x7FFFFFFF));
	quad128 impreciseSinMulAbsImpreciseSin = _mm_mul_ps(impreciseSin, absImpreciseSin);
	quad128 mulImpreciseSinMinusImpreciseSin = _mm_sub_ps(impreciseSinMulAbsImpreciseSin, impreciseSin);
	quad128 modifiedSinMulPrec = _mm_mul_ps(precVal, mulImpreciseSinMinusImpreciseSin);
	quad128 finalSinSum = _mm_add_ps(modifiedSinMulPrec, impreciseSin);
	s.f = finalSinSum;
	return s;
}

JL_FORCE_INLINE jlSimdFloat jlMath::Abs(const jlSimdFloat& x) {
	const quad128 absMask = _mm_set1_ps(-1.0f);
	return jlSimdFloat(_mm_andnot_ps(x.f, absMask));
}

JL_FORCE_INLINE jlSimdFloat jlMath::Clamp(const jlSimdFloat& x, const jlSimdFloat& min, const jlSimdFloat& max) {
	JL_SLOW_ASSERT(min <= max);
	quad128 lowerBound = _mm_max_ps(x.f, min.f);
	return jlSimdFloat(_mm_min_ps(lowerBound, max.f));
}

JL_FORCE_INLINE jlSimdFloat jlMath::Min(const jlSimdFloat& x, const jlSimdFloat& y) {
	return jlSimdFloat(_mm_min_ps(x.f, y.f));
}

JL_FORCE_INLINE jlSimdFloat jlMath::Max(const jlSimdFloat& x, const jlSimdFloat& y) {
	return jlSimdFloat(_mm_max_ps(x.f, y.f));
}

JL_FORCE_INLINE jlSimdFloat jlMath::Sqrt(const jlSimdFloat& x) {
	return jlSimdFloat(_mm_sqrt_ps(x.f));
}

JL_FORCE_INLINE jlSimdFloat jlMath::InvSqrt(const jlSimdFloat& x) {
	return jlSimdFloat(_mm_rsqrt_ps(x.f));
}

JL_FORCE_INLINE jlSimdFloat jlMath::Saturate(const jlSimdFloat& x) {
	const quad128 zero = _mm_set1_ps(0.0f);
	quad128 lowerBound = _mm_max_ps(x.f, zero);
	const quad128 one = _mm_set1_ps(1.0f);
	return jlSimdFloat(_mm_min_ps(lowerBound, one));
}

JL_FORCE_INLINE jlSimdFloat jlMath::Lerp(const jlSimdFloat& a, const jlSimdFloat& b, const jlSimdFloat& t) {
	const quad128 zero = _mm_set1_ps(0.0f);
	quad128 minT = _mm_max_ps(t.f, zero);
	const quad128 one = _mm_set1_ps(1.0f);
	quad128 sub = _mm_sub_ps(b.f, a.f);
	quad128 clampedT = _mm_min_ps(minT, one);
	return jlSimdFloat(_mm_add_ps(a.f, _mm_mul_ps(sub, clampedT)));
}

JL_FORCE_INLINE jlSimdFloat jlMath::SmoothStep(const jlSimdFloat& a, const jlSimdFloat& b, const jlSimdFloat& t) {
	const quad128 two = _mm_set1_ps(2.0f);
	const quad128 three = _mm_set1_ps(3.0f);
	quad128 twoT = _mm_mul_ps(two, t.f);
	quad128 tt = _mm_mul_ps(t.f, t.f);
	quad128 threeSubTwoT = _mm_sub_ps(three, twoT);
	quad128 ab = _mm_sub_ps(b.f, a.f);
	quad128 x = _mm_mul_ps(tt, threeSubTwoT);
	quad128 disp = _mm_mul_ps(ab, x);
	return jlSimdFloat(_mm_add_ps(a.f, disp));
}

JL_FORCE_INLINE jlSimdFloat jlMath::SmootherStep(const jlSimdFloat& a, const jlSimdFloat& b, const jlSimdFloat& t) {
	const quad128 ten = _mm_set1_ps(10.0f);
	const quad128 fifteen = _mm_set1_ps(15.0f);
	const quad128 six = _mm_set1_ps(6.0f);
	quad128 tt = _mm_mul_ps(t.f, t.f);
	quad128 sixT = _mm_mul_ps(six, t.f);
	quad128 ttt = _mm_mul_ps(tt, t.f);
	quad128 sixTMinusFifteen = _mm_sub_ps(sixT, fifteen);
	quad128 ab = _mm_sub_ps(b.f, a.f);
	quad128 sixTMinusFifteenXT = _mm_mul_ps(sixTMinusFifteen, t.f);
	quad128 mulTen = _mm_add_ps(sixTMinusFifteenXT, ten);
	quad128 mulTTT = _mm_mul_ps(ttt, mulTen);
	quad128 disp = _mm_mul_ps(ab, mulTTT);
	return jlSimdFloat(_mm_add_ps(a.f, disp));
}
