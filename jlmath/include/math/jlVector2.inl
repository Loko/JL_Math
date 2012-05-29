JL_FORCE_INLINE jlVector2::jlVector2() : x(0.0f), y(0.0f) {
		
}

JL_FORCE_INLINE jlVector2::jlVector2(float32 fx, float32 fy) : x(fx), y(fy) {
		
}

JL_FORCE_INLINE jlVector2::jlVector2(const jlVector2& cpy) : x(cpy.x), y(cpy.y) {
	
}

JL_FORCE_INLINE jlVector2& jlVector2::operator =(const jlVector2& vec) {
	x = vec.x;
	y = vec.y;
	return *this;
}
	
JL_FORCE_INLINE bool jlVector2::isOk() const {
	return !jlMath::IsNaN(x) && !jlMath::IsNaN(y);
}

JL_FORCE_INLINE void jlVector2::store(float32 *ptr) const {
	*ptr = x;
	*(ptr + 1) = y;
}

JL_FORCE_INLINE void jlVector2::load(const float32 *ptr) {
	x = *ptr;
	y = *(ptr + 1);
}
	
JL_FORCE_INLINE const float32& jlVector2::operator()(int32 i) const {
	JL_ASSERT_MSG(i >= 0 && i < 2, "Index of %d is out of bounds of the jlVector2", i);
	return *(&x + i);
}

JL_FORCE_INLINE float32& jlVector2::operator()(int32 i) {
	JL_ASSERT_MSG(i >= 0 && i < 2, "Index of %d is out of bounds of the jlVector2", i);
	return *(&x + i);
}

JL_FORCE_INLINE void jlVector2::setZero() {
	x = 0.0f;
	y = 0.0f;
}

JL_FORCE_INLINE bool jlVector2::isZero() const {
	return (x == 0.0f && y == 0.0f);
}

JL_FORCE_INLINE bool jlVector2::isZero(float32 absTolerance) const {
	return jlMath::FloatEquals(x, 0.0f, absTolerance) && jlMath::FloatEquals(y, 0.0f, absTolerance);
}

JL_FORCE_INLINE void jlVector2::setAll(float32 v) {
	x = v;
	y = v;
}

JL_FORCE_INLINE void jlVector2::set(float32 fx, float32 fy) {
	x = fx;
	y = fy;
}

JL_FORCE_INLINE jlVector2 jlVector2::operator +(const jlVector2& rhs) const {
	return jlVector2(x + rhs.x, y + rhs.y);
}

JL_FORCE_INLINE jlVector2 jlVector2::operator -(const jlVector2 &rhs) const {
	return jlVector2(x - rhs.x, y - rhs.y);
}

JL_FORCE_INLINE jlVector2 jlVector2::operator *(float32 s) const {
	return jlVector2(x * s, y * s);
}

JL_FORCE_INLINE jlVector2 operator *(float32 s, const jlVector2& v) {
	return jlVector2(v.x * s, v.y * s);
}

JL_FORCE_INLINE jlVector2 jlVector2::operator *(const jlVector2& v) const {
	return jlVector2(x * v.x, y * v.y);
}

JL_FORCE_INLINE jlVector2 jlVector2::operator /(float32 d) const {
	return (d != 0.0f) ? jlVector2(x / d, y / d) : jlVector2(x, y);
}

JL_FORCE_INLINE jlVector2 jlVector2::operator /(const jlVector2& d) const {
	float32 rx = x, ry = y;
	if (d.x != 0.0f)
		rx /= d.x;
	if (d.y != 0.0f)
		ry /= d.y;
	return jlVector2(rx, ry);
}

JL_FORCE_INLINE jlVector2 jlVector2::operator -() const {
	return jlVector2(-x, -y);
}

JL_FORCE_INLINE jlVector2& jlVector2::operator +=(const jlVector2& rhs) {
	x += rhs.x;
	y += rhs.y;
	return *this;
}

JL_FORCE_INLINE jlVector2& jlVector2::operator -=(const jlVector2 &rhs) {
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

JL_FORCE_INLINE jlVector2& jlVector2::operator *=(float32 s) {
	x *= s;
	y *= s;
	return *this;
}

JL_FORCE_INLINE jlVector2& jlVector2::operator *=(const jlVector2& rhs) {
	x *= rhs.x;
	y *= rhs.y;
	return *this;
}

JL_FORCE_INLINE jlVector2& jlVector2::operator /=(float32 d) {
	JL_ASSERT(d != 0.0f);
	x /= d;
	y /= d;
	return *this;
}

JL_FORCE_INLINE jlVector2& jlVector2::operator /=(const jlVector2& d) {
	if (d.x != 0.0f)
		x /= d.x;
	if (d.y != 0.0f)
		y /= d.y;
	return *this;
}

JL_FORCE_INLINE void jlVector2::setAdd(const jlVector2& a, const jlVector2& b) {
	x = a.x + b.x;
	y = a.y + b.y;
}

JL_FORCE_INLINE void jlVector2::setSub(const jlVector2& a, const jlVector2& b) {
	x = a.x - b.x;
	y = a.y - b.y;
}

JL_FORCE_INLINE void jlVector2::setMul(const jlVector2& v, float32 s) {
	x = v.x * s;
	y = v.y * s;
}

JL_FORCE_INLINE void jlVector2::setMul(const jlVector2& a, const jlVector2& b) {
	x = a.x * b.x;
	y = a.y * b.y;
}

JL_FORCE_INLINE void jlVector2::setDiv(const jlVector2& v, float32 s) {
	if (s != 0.0f) {
		x = v.x / s;
		y = v.y / s;
	}
}

JL_FORCE_INLINE void jlVector2::setDiv(const jlVector2& v, const jlVector2& d) {
	if (d.x != 0.0f)
		x = v.x / d.x;
	if (d.y != 0.0f)
		y = v.y / d.y;
}

JL_FORCE_INLINE void jlVector2::setMin(const jlVector2& a, const jlVector2& b) {
	x = jlMath::Min(a.x, b.x);
	y = jlMath::Min(a.y, b.y);
}

JL_FORCE_INLINE void jlVector2::setMax(const jlVector2& a, const jlVector2& b) {
	x = jlMath::Max(a.x, b.x);
	y = jlMath::Max(a.y, b.y);
}

JL_FORCE_INLINE void jlVector2::add(const jlVector2& rhs) {
	x += rhs.x; 
	y += rhs.y;
}

JL_FORCE_INLINE void jlVector2::sub(const jlVector2& rhs) {
	x -= rhs.x;
	y -= rhs.y;
}

JL_FORCE_INLINE void jlVector2::mul(float32 s) {
	x *= s;
	y *= s;
}

JL_FORCE_INLINE void jlVector2::mul(const jlVector2& v) {
	x *= v.x;
	y *= v.y;
}
	
JL_FORCE_INLINE void jlVector2::div(const jlVector2& d) {
	if (d.x != 0.0f)
		x /= d.x;
	if (d.y != 0.0f)
		y /= d.y;
}

JL_FORCE_INLINE void jlVector2::div(float32 d) {
	if (d != 0.0f) {
		x /= d;
		y /= d;
	}
}

JL_FORCE_INLINE void jlVector2::negate() {
	x = -x;
	y = -y;
}

JL_FORCE_INLINE void jlVector2::setNegation(const jlVector2& v) {
	x = -v.x;
	y = -v.y;
}

JL_FORCE_INLINE float32 jlVector2::length() const {
	return jlMath::Sqrt(x*x + y*y);
}

JL_FORCE_INLINE float32 jlVector2::lengthSquared() const {
	return x*x + y*y;
}

JL_FORCE_INLINE float32 jlVector2::dot(const jlVector2& v) const {
	return x*v.x + y*v.y;
}

JL_FORCE_INLINE void jlVector2::normalize() {
	float32 lenSq = x*x + y*y;
	if (lenSq > FLOAT32_EPSILON) {
		float32 oneOverLen = 1.0f / jlMath::Sqrt(lenSq);
		x *= oneOverLen;
		y *= oneOverLen;
	}
}
	
JL_FORCE_INLINE float32 jlVector2::normalizeWithLength() {
	float32 lenSq = x*x + y*y;
	float32 len = lenSq;
	if (lenSq > FLOAT32_EPSILON) {
		len = jlMath::Sqrt(lenSq);
		float32 oneOverLen = 1.0f / len;
		x *= oneOverLen;
		y *= oneOverLen;
	}
	return len;
}

JL_FORCE_INLINE jlVector2 jlVector2::normalizedCopy() const {
	jlVector2 ncpy = jlVector2(x, y);
	float32 lenSq = x*x + y*y;
	if (lenSq > FLOAT32_EPSILON) {
		float32 oneOverLen = 1.0f / jlMath::Sqrt(lenSq);
		ncpy.x *= oneOverLen;
		ncpy.y *= oneOverLen;
	}
	return ncpy;
}

JL_FORCE_INLINE bool jlVector2::equals(const jlVector2& rhs) const {
	return (x == rhs.x && y == rhs.y);
}

JL_FORCE_INLINE bool jlVector2::equals(const jlVector2& rhs, float32 absTolerance) const {
	return jlMath::FloatEquals(x, rhs.x, absTolerance) && jlMath::FloatEquals(y, rhs.y, absTolerance);
}

JL_FORCE_INLINE bool jlVector2::operator ==(const jlVector2& rhs) const {
	return (x == rhs.x && y == rhs.y);
}

JL_FORCE_INLINE bool jlVector2::operator !=(const jlVector2& rhs) const {
	return (x != rhs.x || y != rhs.y);
}
	
/// @todo make dot and cross global?  may very well improve readability
JL_FORCE_INLINE float32 jlVector2::Dot(const jlVector2& u, const jlVector2& v) {
	return u.x*v.x + u.y*v.y; 
}

JL_FORCE_INLINE float32 jlVector2::Distance(const jlVector2& u, const jlVector2& v) {
	float32 dx = u.x - v.x;
	float32 dy = u.y - v.y;
	return jlMath::Sqrt(dx*dx + dy*dy);
}

JL_FORCE_INLINE float32 jlVector2::DistanceSquared(const jlVector2& u, const jlVector2& v) {
	float32 dx = u.x - v.x;
	float32 dy = u.y - v.y;
	return dx*dx + dy*dy;
}

JL_FORCE_INLINE float32 jlVector2::Cross(const jlVector2& a, const jlVector2& b) {
	return a.x * b.y - a.y * b.x;
}

JL_FORCE_INLINE jlVector2 jlVector2::Cross(const jlVector2& v, float32 s) {
	return jlVector2(-s * v.y, s * v.x);
}

JL_FORCE_INLINE jlVector2 jlVector2::Lerp(const jlVector2& a, const jlVector2& b, float32 t) {
	if (t <= 0.0f) {
		return a;
	} else if (t >= 1.0f) {
		return b;
	} else {
		jlVector2 r = jlVector2(b.x - a.x, b.y - a.y);
		r.mul(t);
		r.add(a);
		return r;
	}
}

JL_FORCE_INLINE jlVector2 jlVector2::SmoothStep(const jlVector2& a, const jlVector2& b, float32 t) {
	return jlVector2(jlMath::SmoothStep(a.x, b.x, t), jlMath::SmoothStep(a.y, b.y, t));
}

JL_FORCE_INLINE jlVector2 jlVector2::Reflect(const jlVector2& v, const jlVector2& n) {
	return jlVector2(v - (2.0f * v.dot(n) * n));
}

JL_FORCE_INLINE jlVector2 jlVector2::RightPerp(const jlVector2& v) {
	return jlVector2(v.y, -v.x);
}

JL_FORCE_INLINE jlVector2 jlVector2::LeftPerp(const jlVector2& v) {
	return jlVector2(-v.y, v.x);
}

JL_FORCE_INLINE bool jlVector2::Equals(const jlVector2& a, const jlVector2& b, float32 absTolerance) {
	return jlMath::FloatEquals(a.x, b.x, absTolerance) && jlMath::FloatEquals(a.y, b.y, absTolerance);
}
