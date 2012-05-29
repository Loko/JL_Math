#ifndef JL_RANDOM_H
#define JL_RANDOM_H

#include "jlCore.h"

/// A SIMD optimized random number generator
/// Adapted from SFMT: http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/SFMT/
class jlRandom {
public:
	jlRandom();
	~jlRandom();

	// check/allocate/use existing space for the random number generator
	bool32 isInit() const;
	void init(int32 size);
	// will use an existing buffer, which must be deleted elsewhere
	void init(quadint128 *inplaceBuffer, int32 size);
	
	// set the desired seed for the rng
	void seed(uint32 seed = jlRandom::DEFAULT_SEED);

	// get a random uint/int/float
	uint32 randUint32();
	uint32 randUint32(uint32 max);
	uint32 randUint32(uint32 min, uint32 max);
	int32 randInt32();
	int32 randInt32(int32 max);
	int32 randInt32(int32 min, int32 max);
	float32 randFloat32();
	float32 randFloat32(float32 max);
	float32 randFloat32(float32 min, float32 max);

	int32 getSize() const; // size of the internal buffer
	int32 getSize32() const; // size if regarded as 32 bit ints
	const quadint128 * getBuffer() const;
	const uint32 * getBuffer32() const;
	bool32 getOwnsBuffer() const;
	void setOwnsBuffer(bool32 ownsBuffer);

	static float32 ToFloat32(uint32 rnum);
	static void GenerateRandomValues(quadint128 *buffer, int32 size);
	//static void UpdateCertification

	static const uint32 DEFAULT_SEED = 1234;
private:
	void updateCertification(uint32 *ubufferPtr);
	JL_DISALLOW_COPY_AND_ASSIGN(jlRandom);

	JL_ALIGN_16 quadint128 *buffer;
	int32 size;
	int32 idx;
	uint8 flags;
};

#endif // JL_RANDOM_H
