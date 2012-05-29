#include "util/jlRandom.h"

namespace {
	const uint8 JL_RANDOM_FLAGS_NONE = 0;
	const uint8 JL_RANDOM_FLAGS_OWNS_BUFFER = 1;

	const uint32 MSK1 = 0xdfffffefU;
	const uint32 MSK2 = 0xddfecb7fU;
	const uint32 MSK3 = 0xbffaffffU;
	const uint32 MSK4 = 0xbffffff6U;
	const uint32 POS1 = 122U;
	const uint32 SR1 = 11;
	const uint32 SR2 = 1;
	const uint32 SL2 = 1;
	const uint32 SL1 = 18;
	const uint32 PARITY1 = 0x00000001U;
	const uint32 PARITY2 = 0x00000000U;
	const uint32 PARITY3 = 0x00000000U;
	const uint32 PARITY4 = 0xc98e126aU;
}

#if (JL_SIMD_ENABLED)
	#define JL_RANDOM_UINT32_PTR(BUFFER) (&(BUFFER[0].m128i_u32[0]))
#else
	#define JL_RANDOM_UINT32_PTR(BUFFER) (&(BUFFER[0].v[0]))
#endif

#define JL_RANDOM_SIZE_AS_UINT32(SIZE) SIZE * 4


jlRandom::jlRandom() : buffer(JL_NULL), size(0), idx(0), flags(JL_RANDOM_FLAGS_NONE) { }

jlRandom::~jlRandom() {
	if (getOwnsBuffer()) jlFreeAligned(buffer);
}

bool32 jlRandom::isInit() const {
	return (buffer != JL_NULL);
}

void jlRandom::init(int32 sz) {
	JL_ASSERT(!isInit());
	JL_ASSERT(sz > 0);
	buffer = static_cast<quadint128 *>(jlAllocAligned(sz * sizeof(quadint128), 16));
	size = sz;
	flags = JL_RANDOM_FLAGS_OWNS_BUFFER;
}

void jlRandom::init(quadint128 *allocatedBuffer, int32 sz) {
	JL_ASSERT(!isInit());
	JL_ASSERT(sz > 0 && allocatedBuffer != JL_NULL);
	buffer = allocatedBuffer;
	size = sz;
	flags = JL_RANDOM_FLAGS_NONE;
}

void jlRandom::seed(uint32 s) {
	uint32 *rptr = JL_RANDOM_UINT32_PTR(buffer);
	rptr[0] = s;
	int32 N32 = JL_RANDOM_SIZE_AS_UINT32(size);
	for (int32 i = 1; i < N32; i++) {
		rptr[i] = 1812433253UL * (rptr[i - 1] ^ rptr[i - 1] >> 30) + i;
	}
	idx = N32;
	updateCertification(rptr);
}

void jlRandom::updateCertification(uint32 *ubufferPtr) {
	int32 inner = 0;
	int32 i, j;
	uint32 work;
	static const uint32 PARITY_LUT[] = {PARITY1, PARITY2, PARITY3, PARITY4};
	for (i = 0; i < 4; i++) {
		inner ^= ubufferPtr[i] & PARITY_LUT[i];
	}
	for (i = 16; i > 0; i >>= 1)
	inner ^= inner >> i;
	inner &= 1;
	/* check OK */
	if (inner == 1) {
		return;
	}
	for (i = 0; i < 4; i++) {
		work = 1;
		for (j = 0; j < 32; j++) {
			if ((work & PARITY_LUT[i]) != 0) {
				ubufferPtr[i] ^= work;
				return;
			}
			work = work << 1;
		}
    }
}

uint32 jlRandom::randUint32() {
	uint32 rnum;
	if (idx > JL_RANDOM_SIZE_AS_UINT32(size)) {
		GenerateRandomValues(buffer, size);
		idx = 0;
	}
	uint32 *rptr = JL_RANDOM_UINT32_PTR(buffer);
	rnum = rptr[idx++];
	return rnum;
}

uint32 jlRandom::randUint32(uint32 max) {
	float32 t = randFloat32();
	return static_cast<uint32>(max * t);
}

uint32 jlRandom::randUint32(uint32 min, uint32 max) {
	JL_ASSERT(min <= max);
	float32 t = randFloat32();
	return min + static_cast<uint32>((max - min) * t);
}

int32 jlRandom::randInt32() {
	return static_cast<int32>(randUint32());
}

int32 jlRandom::randInt32(int32 max) {
	return static_cast<int32>(randUint32(max));
}

int32 jlRandom::randInt32(int32 min, int32 max) {
	JL_ASSERT(min <= max);
	return static_cast<int32>(randUint32(min, max));
}

float32 jlRandom::randFloat32() {
	return jlRandom::ToFloat32(randUint32());
}

float32 jlRandom::randFloat32(float32 max) {
	return randFloat32() * max;
}

float32 jlRandom::randFloat32(float32 min, float32 max) {
	JL_ASSERT(min <= max);
	float32 t = randFloat32();
	return min + (max - min) * t;
}

int32 jlRandom::getSize() const {
	return size;
}

int32 jlRandom::getSize32() const {
	return JL_RANDOM_SIZE_AS_UINT32(size);
}

const quadint128 * jlRandom::getBuffer() const {
	return buffer;
}

const uint32 * jlRandom::getBuffer32() const {
	return JL_RANDOM_UINT32_PTR(buffer);
}

bool32 jlRandom::getOwnsBuffer() const {
	return flags & JL_RANDOM_FLAGS_OWNS_BUFFER;
}

void jlRandom::setOwnsBuffer(bool32 ownsBuffer) {
	if (ownsBuffer) {
		flags |= JL_RANDOM_FLAGS_OWNS_BUFFER;
	} else {
		flags &= ~JL_RANDOM_FLAGS_OWNS_BUFFER;
	}
}

float32 jlRandom::ToFloat32(uint32 rnum) {
	return rnum * (1.0f / 4294967296.0f);
}

#if (JL_SIMD_ENABLED) // SIMD version of GenerateRandomValues
namespace {
	quadint128 sseRecursion(quadint128 *a, quadint128 *b, quadint128 c, quadint128 d, quadint128 mask) {
		quadint128 v, x, y, z;
		x = _mm_load_si128(a);
		y = _mm_srli_epi32(*b, SR1);
		z = _mm_srli_si128(c, SR2);
		v = _mm_slli_epi32(d, SL1);
		z = _mm_xor_si128(z, x);
		z = _mm_xor_si128(z, v);
		x = _mm_slli_si128(x, SL2);
		y = _mm_and_si128(y, mask);
		z = _mm_xor_si128(z, x);
		z = _mm_xor_si128(z, y);
		return z;
	}
}

void jlRandom::GenerateRandomValues(quadint128 *buffer, int32 size) {
	int32 i;
	quadint128 r, r1, r2, mask;
	mask = _mm_set_epi32(MSK4, MSK3, MSK2, MSK1);
	r1 = _mm_load_si128(&buffer[size - 2]);
    r2 = _mm_load_si128(&buffer[size - 1]);
    for (i = 0; i < size - POS1; i++) {
		r = sseRecursion(&buffer[i], &buffer[i + POS1], r1, r2, mask);
		_mm_store_si128(&buffer[i], r);
		r1 = r2;
		r2 = r;
    }
    for (; i < size; i++) {
		r = sseRecursion(&buffer[i], &buffer[i + POS1 - size], r1, r2, mask);
		_mm_store_si128(&buffer[i], r);
		r1 = r2;
		r2 = r;
    }
}

#else // FPU version of GenerateRandomValues
namespace {
	void lshift128(quadint128 *out, quadint128 const *in, int shift) {
		uint64 th, tl, oh, ol;

		th = ((uint64)in->v[3] << 32) | ((uint64)in->v[2]);
		tl = ((uint64)in->v[1] << 32) | ((uint64)in->v[0]);

		oh = th << (shift * 8);
		ol = tl << (shift * 8);
		oh |= tl >> (64 - shift * 8);
		out->v[1] = (uint32)(ol >> 32);
		out->v[0] = (uint32)ol;
		out->v[3] = (uint32)(oh >> 32);
		out->v[2] = (uint32)oh;
	}
	
	void rshift128(quadint128 *out, quadint128 const *in, int shift) {
		uint64 th, tl, oh, ol;

		th = ((uint64)in->v[3] << 32) | ((uint64)in->v[2]);
		tl = ((uint64)in->v[1] << 32) | ((uint64)in->v[0]);

		oh = th >> (shift * 8);
		ol = tl >> (shift * 8);
		ol |= th << (64 - shift * 8);
		out->v[1] = (uint32)(ol >> 32);
		out->v[0] = (uint32)ol;
		out->v[3] = (uint32)(oh >> 32);
		out->v[2] = (uint32)oh;
	}

	void fpuRecursion(quadint128 *r, quadint128 *a, quadint128 *b, quadint128 *c, quadint128 *d) {
		quadint128 x;
		quadint128 y;
		lshift128(&x, a, SL2);
		rshift128(&y, c, SR2);
		r->v[0] = a->v[0] ^ x.v[0] ^ ((b->v[0] >> SR1) & MSK1) ^ y.v[0] ^ (d->v[0] << SL1);
		r->v[1] = a->v[1] ^ x.v[1] ^ ((b->v[1] >> SR1) & MSK2) ^ y.v[1] ^ (d->v[1] << SL1);
		r->v[2] = a->v[2] ^ x.v[2] ^ ((b->v[2] >> SR1) & MSK3) ^ y.v[2] ^ (d->v[2] << SL1);
		r->v[3] = a->v[3] ^ x.v[3] ^ ((b->v[3] >> SR1) & MSK4) ^ y.v[3] ^ (d->v[3] << SL1);
	}
}

void jlRandom::GenerateRandomValues(quadint128 *buffer, int32 size) {
	int32 i;
	quadint128 *r1, *r2;

	r1 = &buffer[size - 2];
	r2 = &buffer[size - 1];
	for (i = 0; i < size - POS1; i++) {
		fpuRecursion(&buffer[i], &buffer[i], &buffer[i + POS1], r1, r2);
		r1 = r2;
		r2 = &buffer[i];
	}
	for (; i < size; i++) {
		fpuRecursion(&buffer[i], &buffer[i], &buffer[i + POS1 - size], r1, r2);
		r1 = r2;
		r2 = &buffer[i];
	}
}

#endif 
