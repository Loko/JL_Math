/// @file jlComp.h
/// @author Jeff Lansing

#ifndef JL_COMP_H
#define JL_COMP_H

#include "jlCore.h"

// Specialized type representing a comparison on two 
// jlVector4s/jlSimdFloats.  Verify if any/all are 
// set given a mask after a comparison to derive 
// useful information.  Use a different mask or perform 
// and/or/xor ops to avoid running the comparisons again.
class jlComp {
public:
	// Masks representing component(s) of an jlVector4/jlSimdFloat
	enum Mask {
		MASK_NONE = 0,
		MASK_SIMD_FLOAT = 1,
		MASK_X = 1,
		MASK_Y = 2,
		MASK_XY = 3,
		MASK_Z = 4,
		MASK_XYZ = 7,
		MASK_W = 8,
		MASK_XYZW = 15
	};
	
	jlComp::Mask getMask() const;
	bool32 anyIsSet() const;
	bool32 anyIsSet(jlComp::Mask m) const;
	bool32 allAreSet() const;
	bool32 allAreSet(jlComp::Mask m) const;
	void setAnd(const jlComp& a, const jlComp& b);
	void setOr(const jlComp& a, const jlComp& b);
	void setXor(const jlComp& a, const jlComp& b);
	const jlCompMask& getCompMask() const;
	jlCompMask& getCompMask();
	void setCompMask(const jlCompMask& vm);

	jlCompMask mask;
};

#if (JL_SIMD_ENABLED && JL_PLATFORM == JL_PLATFORM_WINDOWS)
	#include "math/jlCompSSE.inl"
#else
	#include "math/jlCompFPU.inl"
#endif

#endif // JL_COMP_H
