#include <iostream>
#include "math/jlVector2.h"
#include "math/jlVector4.h"
#include "math/jlMatrix4.h"
#include "math/jlQuaternion.h"
#include "util/jlRandom.h"

/* BEGIN DEBUG PRINT FUNCTIONS */
void printFloat(float f) { std::cout << "{" << f << "}" << std::endl; }
void printInt(int i) { std::cout << "{" << i << "}" << std::endl; }
void printSimdFloat(const jlSimdFloat& sf) { std::cout << "{" << sf.getFloat() << "}" << std::endl; }
void printVector2(const jlVector2& v) { std::cout << "{" << v.x << ", " << v.y << "}" << std::endl; }
void printVector4(const jlVector4& v) { std::cout << "{" << v(0) << ", " << v(1) << ", " << v(2) << ", " << v(3) << "}" << std::endl; }
void printQuaternion(const jlQuaternion& q) { std::cout << "{" << q(0) << ", " << q(1) << ", " << q(2) << ", " << q(3) << "}" << std::endl; }
void printMatrix4(const jlMatrix4& m) {
	for (int r = 0; r < 4; ++r) {
		std::cout << "\t";
		for (int c = 0; c < 4; ++c) {
			std::cout << " " << m(r, c) << ", ";
		}
		std::cout << std::endl;
	}
}
/* END DEBUG PRINT FUNCTIONS */

/* BEGIN EXPRESSION PRINT MACROS */
#define PRINT_OP(EXPR, PRINT_FUNC) \
	std::cout << #EXPR << " = "; \
	PRINT_FUNC(EXPR)

#define PRINT_VEC4_OP(EXPR) PRINT_OP(EXPR, printVector4)
#define PRINT_VEC4_OP2(VAR2PRINT, EXPR) \
	std::cout << #EXPR << " = "; \
	(EXPR);						\
	printVector4(VAR2PRINT)

#define PRINT_SIMDFLOAT_OP(EXPR) PRINT_OP(EXPR, printSimdFloat)
#define PRINT_SIMDFLOAT_OP2(VAR2PRINT, EXPR) \
	std::cout << #EXPR << " = "; \
	(EXPR);						\
	printSimdFloat(VAR2PRINT)

#define PRINT_VEC2_OP(EXPR) PRINT_OP(EXPR, printVector2)
#define PRINT_VEC2_OP2(VAR2PRINT, EXPR) \
	std::cout << #EXPR << " = "; \
	(EXPR);						\
	printVector2(VAR2PRINT)

#define PRINT_FLOAT_OP(EXPR) PRINT_OP(EXPR, printFloat)
#define PRINT_FLOAT_OP2(VAR2PRINT, EXPR) \
	std::cout << #EXPR << " = "; \
	(EXPR);						\
	printVector2(VAR2PRINT)

#define PRINT_INT_OP(EXPR) PRINT_OP(EXPR, printInt)
#define PRINT_MATRIX4_OP(EXPR) PRINT_OP(EXPR, printMatrix4)
#define PRINT_QUATERNION_OP(EXPR) PRINT_OP(EXPR, printQuaternion)
/* END EXPRESSION PRINT MACROS */

/* BEGIN RANDOM GENERATION FUNCTIONS */
jlVector4 * generateRandomVectors(int32 numVectors, float32 scalarMin, float32 scalarMax) {
	JL_ASSERT(numVectors > 0);
	jlVector4 *vectors = new jlVector4[numVectors];
	if (vectors) {
		jlRandom random;
		random.init(numVectors);
		random.seed(jlRandom::DEFAULT_SEED);
		for (int32 i = 0; i < numVectors; i++) {
			float32 x = random.randFloat32(scalarMin, scalarMax);
			float32 y = random.randFloat32(scalarMin, scalarMax);
			float32 z = random.randFloat32(scalarMin, scalarMax);
			//float32 w = random.randFloat32(scalarMin, scalarMax);
			vectors[i].set(x, y, z, 0.0f);
		}
	}
	return vectors;
}

jlMatrix4 * generateRandomMatrices(int32 numMatrices, float32 scalarMin, float32 scalarMax) {
	JL_ASSERT(numMatrices > 0);
	jlMatrix4 *matrices = new jlMatrix4[numMatrices];
	if (matrices) {
		jlRandom random;
		random.init(numMatrices);
		random.seed(jlRandom::DEFAULT_SEED);
		for (int32 i = 0; i < numMatrices; ++i) {
			float32 m00, m01, m02, m03;
			float32 m10, m11, m12, m13;
			float32 m20, m21, m22, m23;
			float32 m30, m31, m32, m33;
			m00 = random.randFloat32(scalarMin, scalarMax);
			m01 = random.randFloat32(scalarMin, scalarMax);
			m02 = random.randFloat32(scalarMin, scalarMax);
			m03 = random.randFloat32(scalarMin, scalarMax);
			m10 = random.randFloat32(scalarMin, scalarMax);
			m11 = random.randFloat32(scalarMin, scalarMax);
			m12 = random.randFloat32(scalarMin, scalarMax);
			m13 = random.randFloat32(scalarMin, scalarMax);
			m20 = random.randFloat32(scalarMin, scalarMax);
			m21 = random.randFloat32(scalarMin, scalarMax);
			m22 = random.randFloat32(scalarMin, scalarMax);
			m23 = random.randFloat32(scalarMin, scalarMax);
			m30 = random.randFloat32(scalarMin, scalarMax);
			m31 = random.randFloat32(scalarMin, scalarMax);
			m32 = random.randFloat32(scalarMin, scalarMax);
			m33 = random.randFloat32(scalarMin, scalarMax);
			matrices[i] = jlMatrix4(m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33);
		}
	}
	return matrices;
}
/* END RANDOM GENERATION FUNCTIONS */

/* NORMALIZATION/MATRIX MULTIPLY TEST */
void normalizeVectors(jlVector4 *ptr, int32 n) {
	JL_ASSERT(ptr != NULL && n > 0);
	for (int i = 0; i < n; i++) {
		ptr[i].normalize3();
	}
}

int32 runMatrixVectorTest(int32 numVectorsAndMatrices) {
	jlVector4 *vecArr = generateRandomVectors(numVectorsAndMatrices, -200.0f, 200.0f);
	jlMatrix4 *matArr = generateRandomMatrices(numVectorsAndMatrices, -2.0f, 2.0f);
	if (!vecArr || !matArr) return 0;
	for (int32 m = 0; m < numVectorsAndMatrices; ++m) {
		vecArr[m] = matArr[m] * vecArr[m];
	}
	return 1;
}

bool32 runNormalizationTest(int32 numVectors, float32 scalarMin, float32 scalarMax) {
	JL_ASSERT(numVectors > 0); JL_ASSERT(scalarMin <= scalarMax);
	jlVector4 *arr = generateRandomVectors(numVectors, scalarMin, scalarMax);
	if (!arr) return 0;
	normalizeVectors(arr, numVectors);
	delete [] arr;
	return 1;
}
/* END NORMALIZATION TEST */

/* AABB TEST */
struct jlAABB {
	jlVector4 min;
	jlVector4 max;
};

bool32 testAABB(const jlAABB& a, const jlAABB& b) {
	jlComp comp;
	jlComp aMinCompBMax = a.min.compLess(b.max);
	jlComp bMinCompAMax = b.min.compLess(a.max);
	comp.setAnd(aMinCompBMax, bMinCompAMax);
	return comp.allAreSet(jlComp::MASK_XYZ);
}

bool32 testAABBSlow(const jlAABB& a, const jlAABB& b) {
	if (a.max(0) < b.min(0) || a.min(0) > b.max(0)) return 0;
	if (a.max(1) < b.min(1) || a.min(1) > b.max(1)) return 0;
	if (a.max(2) < b.min(2) || a.min(2) > b.max(2)) return 0;
	return 1;
}
/* END AABB TEST */

void runSinTest() {
	for (int32 angle = -180; angle < 180; angle++) {
		float32 fangle = jlMath::DEG2RAD * angle;
		float32 fsin = jlMath::Sin(fangle);
		float32 fcos = jlMath::Cos(fangle);
		jlSimdFloat simAngle = jlSimdFloat(fangle);
		jlSimdFloat simSin = jlMath::FastSin(simAngle);
		jlSimdFloat simCos = jlMath::FastCos(simAngle);
		std::cout << "Float Ang: " << fangle << " Simd Ang: " << simAngle.getFloat() << " FSin: " << fsin << " SimdSin: " << simSin.getFloat() << std::endl;
		std::cout << "Float Ang: " << fangle << " Simd Ang: " << simAngle.getFloat() << " FCos: " << fcos << " SimdCos: " << simCos.getFloat() << std::endl;
	}
}

/* BEGIN BARYCENTRIC/RAY TEST */
void barycentric(const jlVector4& a, const jlVector4& b, const jlVector4& c, const jlVector4& pt, jlSimdFloat* JL_RESTRICT u, jlSimdFloat* JL_RESTRICT v, jlSimdFloat* JL_RESTRICT w) {
	jlVector4 ab = b - a, ac = c - a, ap = pt - a;
	jlSimdFloat one = jlSimdFloat(1.0f);
	jlSimdFloat d00 = ab.lengthSquared3();
	jlSimdFloat d01 = ab.dot3(ac);
	jlSimdFloat d11 = ac.lengthSquared3();
	jlSimdFloat d20 = ap.dot3(ab);
	jlSimdFloat d21 = ap.dot3(ac);
	jlSimdFloat denom = d00 * d11 - d01 * d01;
	*v = (d11 * d20 - d01 * d21) / denom;
	*w = (d00 * d21 - d01 * d20) / denom;
	*u = one - *v - *w;
}

jlSimdFloat testBarycentric(const jlVector4& a, const jlVector4& b, const jlVector4& c, const jlVector4& pt, int32 iterations) {
	jlSimdFloat u, v, w;
	jlSimdFloat accum = jlSimdFloat(0.0f);
	for (int32 iter = 0; iter < iterations; ++iter) {
		barycentric(a, b, c, pt, &u, &v, &w);
		accum += (u + v + w);
	}
	return accum;
}

void testBarycentric() {
	std::cout << "-- Performing Barycentric Test --" << std::endl;
	// a known counterclockwise triangle
	jlVector4 a = jlVector4(0.0f, 0.0f, 0.0f, 1.0f);
	jlVector4 b = jlVector4(10.0f, 0.0, 0.0f, 1.0f);
	jlVector4 c = jlVector4(5.0f, 5.0f, 0.0f, 1.0f);
	
	jlRandom rand;
	rand.init(32);
	rand.seed(jlRandom::DEFAULT_SEED);
	float32 rx = rand.randFloat32();
	float32 ry = rand.randFloat32();
	float32 rz = rand.randFloat32();
	jlVector4 randPt = jlVector4(rx, ry, rz, 1.0f);
	jlSimdFloat u, v, w;
	barycentric(a, b, c, randPt, &u, &v, &w);
	PRINT_SIMDFLOAT_OP(u);
	PRINT_SIMDFLOAT_OP(v);
	PRINT_SIMDFLOAT_OP(w);
	std::cout << "-- Done Barycentric Test --" << std::endl;
}

bool32 testRayTriangle(const jlVector4& origin, const jlVector4& dir, const jlVector4& a, const jlVector4& b, const jlVector4& c) {
	jlVector4 pn = jlVector4::Cross(b - a, c - a);
	pn.normalize3();
	jlSimdFloat zero = jlSimdFloat(0.0f);
	jlSimdFloat one = jlSimdFloat(1.0f);
	jlSimdFloat pd = jlVector4::Dot3(pn, a);
	jlSimdFloat t = (pd - jlVector4::Dot3(origin, pn)) / jlVector4::Dot3(dir, pn);
	if (t <= zero) return 0;
	jlVector4 pt = origin + dir * t;
	jlSimdFloat u, v, w;
	barycentric(a, b, c, pt, &u, &v, &w);
	return (v >= zero && w >= zero && (v + w) <= one);
}

bool32 testRay(const jlVector4& JL_RESTRICT a, const jlVector4& JL_RESTRICT b, const jlVector4& JL_RESTRICT c,						// ccw triangle
	const jlVector4& JL_RESTRICT origin, const jlVector4& JL_RESTRICT dir, jlSimdFloat& JL_RESTRICT t, jlVector4& JL_RESTRICT n,	// ray origin, direction, distance, normal
	jlVector4& JL_RESTRICT pt, jlSimdFloat& JL_RESTRICT u, jlSimdFloat& JL_RESTRICT v, jlSimdFloat& JL_RESTRICT w,					// pt of intersection, and its barycentric coords
	const jlSimdFloat& JL_RESTRICT maxT = jlSimdFloat(FLOAT32_MAX))																	// max T value for the ray cast
{
	n = jlVector4::Cross(b - a, c - a);
	n.normalize3();
	jlSimdFloat zero = jlSimdFloat(0.0f);
	jlSimdFloat pd;
	pd = -n.dot3(a);
	t = (-pd + origin.dot3(n)) / n.dot3(dir);
	jlSimdFloat one = jlSimdFloat(1.0f);
	if (t < zero || t > maxT) return 0;
	pt = origin + dir * t;
	barycentric(a, b, c, pt, &u, &v, &w);
	return (v >= zero && w >= zero && (v + w) <= one);
}

int32 runRayTriangleTest(const jlVector4& a, const jlVector4& b, const jlVector4& c, int32 numRays) {
	// treat the vectors in groups of 2
	// first is the ray origin
	// second is the ray direction
	int32 numVectors = numRays * 2;
	int32 i;
	int32 numIntersections = 0;
	jlVector4 *arr = generateRandomVectors(numVectors, -200.0f, 200.0f);
	for (i = 1; i < numVectors; i += 2) {
		arr[i].normalize3();
	}
	for (i = 0; i < numVectors; i += 2) {
		if (testRayTriangle(arr[i], arr[i + 1], a, b, c)) numIntersections++;
	}
	return numIntersections;
}

int32 runRayTriangleStressTest(const jlVector4& a, const jlVector4& b, const jlVector4& c, int32 numRays) {
	// treat the vectors in groups of 2
	// first is the ray origin
	// second is the ray direction
	int32 numVectors = numRays * 2;
	int32 i;
	int32 numIntersections = 0;
	jlVector4 *arr = generateRandomVectors(numVectors, -200.0f, 200.0f);
	for (i = 1; i < numVectors; i += 2) {
		arr[i].normalize3();
	}
	jlVector4 pt, normal;
	jlSimdFloat t, u, v, w;
	const jlSimdFloat MAX_T = jlSimdFloat(500.0f);
	for (i = 0; i < numVectors; i += 2) {
		if (testRay(a, b, c, arr[i], arr[i + 1], t, normal, pt, u, v, w, MAX_T)) numIntersections++;
	}
	return numIntersections;
}
/* END BARYCENTRIC/RAY TEST */

/* BEGIN SoA/AoS TESTS */
/// Array of Structs Particle
struct jlParticle {
	static const jlVector4 DEFAULT_SIZE;
	static const jlSimdFloat DEFAULT_ENERGY;

	jlVector4 position;
	jlVector4 acceleration;
	jlVector4 velocity;
	jlVector4 color;
	jlVector4 size;
	jlSimdFloat energy;

	jlParticle() : position(jlVector4::ZERO_PT), acceleration(jlVector4::ZERO), velocity(jlVector4::ZERO), 
		color(1.0f, 1.0f, 1.0f, 1.0f), size(DEFAULT_SIZE), energy(DEFAULT_ENERGY)  { }

	void update(const jlSimdFloat& dt) {
		jlVector4 dv = acceleration * dt;
		energy -= dt;
		jlVector4 vel = velocity + dv * dt;
		position += vel;
		velocity = vel;
	}
};

const jlVector4 jlParticle::DEFAULT_SIZE = jlVector4(5.0f, 5.0f, 5.0f);
const jlSimdFloat jlParticle::DEFAULT_ENERGY = jlSimdFloat(5.0f);
const int32 MAX_NUM_PARTICLES = 1024;

static jlParticle PARTICLE_LIST[MAX_NUM_PARTICLES];

void updateAOSParticles(int32 iterations) {
	jlSimdFloat timeSlice = jlSimdFloat(1.0f / 60.0f);
	for (int32 iter = 0; iter < iterations; ++iter) {
		for (int32 p = 0; p < MAX_NUM_PARTICLES; p += 4) {
			PARTICLE_LIST[p].update(timeSlice);
			PARTICLE_LIST[p + 1].update(timeSlice);
			PARTICLE_LIST[p + 2].update(timeSlice);
			PARTICLE_LIST[p + 3].update(timeSlice);
		}
	}
}

/// Struct of Arrays Particles
struct jlParticles {
	jlVector4 accelerations[MAX_NUM_PARTICLES];
	jlVector4 velocities[MAX_NUM_PARTICLES];
	jlVector4 positions[MAX_NUM_PARTICLES];
	jlVector4 colors[MAX_NUM_PARTICLES];
	jlVector4 sizes[MAX_NUM_PARTICLES];
	jlSimdFloat energies[MAX_NUM_PARTICLES];
};

jlParticles ALL_PARTICLES;

void initSOAParticles() {
	for (int32 i = 0; i < MAX_NUM_PARTICLES; ++i) {
		ALL_PARTICLES.accelerations[i].setZero4();
		ALL_PARTICLES.velocities[i].setZero4();
		ALL_PARTICLES.positions[i].set(0.0f, 0.0f, 0.0f, 1.0f);
		ALL_PARTICLES.colors[i].setAll(1.0f);
		ALL_PARTICLES.sizes[i].setAll(1.0f);
		ALL_PARTICLES.energies[i] = jlSimdFloat(1.0f);
	}
}

void updateSOAParticles(int32 iterations) {
	jlSimdFloat dt = jlSimdFloat(1.0f / 60.0f);
	for (int32 iter = 0; iter < iterations; iter++) {
		for (int32 ap = 0; ap < MAX_NUM_PARTICLES; ap += 4) {
			// update accelerations
			jlVector4 a0 = ALL_PARTICLES.accelerations[ap];
			jlVector4 a1 = ALL_PARTICLES.accelerations[ap + 1];
			jlVector4 a2 = ALL_PARTICLES.accelerations[ap + 2];
			jlVector4 a3 = ALL_PARTICLES.accelerations[ap + 3];

			a0 *= dt;
			a1 *= dt;
			a2 *= dt;
			a3 *= dt;

			ALL_PARTICLES.accelerations[ap] = a0;
			ALL_PARTICLES.accelerations[ap + 1] = a1;
			ALL_PARTICLES.accelerations[ap + 2] = a2;
			ALL_PARTICLES.accelerations[ap + 3] = a3;
		}
		for (int32 vp = 0; vp < MAX_NUM_PARTICLES; vp += 4) {
			// update velocities/positions
			jlVector4 dv0 = ALL_PARTICLES.velocities[vp] + ALL_PARTICLES.accelerations[vp] * dt;
			jlVector4 dv1 = ALL_PARTICLES.velocities[vp + 1] + ALL_PARTICLES.accelerations[vp + 1] * dt;
			jlVector4 dv2 = ALL_PARTICLES.velocities[vp + 2] + ALL_PARTICLES.accelerations[vp + 2] * dt;
			jlVector4 dv3 = ALL_PARTICLES.velocities[vp + 3] + ALL_PARTICLES.accelerations[vp + 3] * dt;
			
			dv0 *= dt;
			dv1 *= dt;
			dv2 *= dt;
			dv3 *= dt;

			jlVector4 p0 = ALL_PARTICLES.positions[vp];
			jlVector4 p1 = ALL_PARTICLES.positions[vp + 1];
			jlVector4 p2 = ALL_PARTICLES.positions[vp + 2];
			jlVector4 p3 = ALL_PARTICLES.positions[vp + 3];

			ALL_PARTICLES.velocities[vp] = dv0;
			ALL_PARTICLES.velocities[vp + 1] = dv1;
			ALL_PARTICLES.velocities[vp + 2] = dv2;
			ALL_PARTICLES.velocities[vp + 3] = dv3;

			p0 += dv0;
			p1 += dv1;
			p2 += dv2;
			p3 += dv3;
			
			ALL_PARTICLES.positions[vp] = p0;
			ALL_PARTICLES.positions[vp + 1] = p1;
			ALL_PARTICLES.positions[vp + 2] = p2;
			ALL_PARTICLES.positions[vp + 3] = p3;
		}
		for (int32 ep = 0; ep < MAX_NUM_PARTICLES; ep += 4) {
			// update energies
			ALL_PARTICLES.energies[ep] -= dt;
			ALL_PARTICLES.energies[ep + 1] -= dt;
			ALL_PARTICLES.energies[ep + 2] -= dt;
			ALL_PARTICLES.energies[ep + 3] -= dt;
		}
	}
}

// http://stackoverflow.com/questions/794632/programmatically-get-the-cache-line-size
#include <stdlib.h>
#include <windows.h>
size_t cacheLineSize() {
    size_t line_size = 0;
    DWORD buffer_size = 0;
    DWORD i = 0;
    SYSTEM_LOGICAL_PROCESSOR_INFORMATION * buffer = 0;

    GetLogicalProcessorInformation(0, &buffer_size);
    buffer = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION *)malloc(buffer_size);
    GetLogicalProcessorInformation(&buffer[0], &buffer_size);

    for (i = 0; i != buffer_size / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION); ++i) {
        if (buffer[i].Relationship == RelationCache && buffer[i].Cache.Level == 1) {
            line_size = buffer[i].Cache.LineSize;
            break;
        }
    }

    free(buffer);
    return line_size;
}
/* END SoA/AoS TESTS */

/* BEGIN UNIT TESTS */
void testVector4() {
	std::cout << "-- Begin Testing jlVector4 --" << std::endl;
	jlVector4 a = jlVector4(1.0f, 2.0f, 3.0f);
	jlVector4 b = jlVector4(3.0f, 4.0f, 5.0f);
	jlSimdFloat s = jlSimdFloat(3.0f);
	PRINT_VEC4_OP(a);
	PRINT_VEC4_OP(b);
	PRINT_SIMDFLOAT_OP(s);
	// basic arithmetic ops
	PRINT_VEC4_OP(a + b);
	PRINT_VEC4_OP(a - b);
	PRINT_VEC4_OP(a * s);
	PRINT_VEC4_OP(a / s);
	PRINT_VEC4_OP(a += b); a.set(1.0f, 2.0f, 3.0f);
	PRINT_VEC4_OP(a -= b); a.set(1.0f, 2.0f, 3.0f);
	PRINT_VEC4_OP(a *= s); a.set(1.0f, 2.0f, 3.0f);
	PRINT_VEC4_OP(a /= s); a.set(1.0f, 2.0f, 3.0f);
	PRINT_VEC4_OP(-a);
	// length/dot
	PRINT_VEC4_OP(a);
	PRINT_VEC4_OP(b);
	PRINT_SIMDFLOAT_OP(a.lengthSquared3());
	PRINT_SIMDFLOAT_OP(a.length3());
	PRINT_SIMDFLOAT_OP(a.dot3(b));
	// normalize
	a.set(1.0f, 1.0f, 1.0f, 0.0f);
	PRINT_VEC4_OP(a);
	PRINT_VEC4_OP2(a, a.normalize3());
	a.set(5.0f, 5.0f, 5.0f, 5.0f);
	PRINT_VEC4_OP2(a, a.normalize4());
	a.set(5.0f, 5.0f, 5.0f);
	jlSimdFloat len = a.normalize3WithLength();
	PRINT_VEC4_OP2(a, a.normalize3());
	PRINT_SIMDFLOAT_OP(len);
	// cross
	jlVector4 uy = jlVector4(0, 1, 0);
	jlVector4 uz = jlVector4(0, 0, 1);
	PRINT_VEC4_OP(uy);
	PRINT_VEC4_OP(uz);
	PRINT_VEC4_OP(uy.cross(uz)); // right hand rule 1, 0, 0
	// set/get
	jlSimdFloat sv = jlSimdFloat(2.0f);
	a.setAll(sv);
	PRINT_VEC4_OP(a);
	PRINT_SIMDFLOAT_OP(a.getElem<0>());
	a.set(2.0f, 3.0f, 4.0f);
	for (int idx = 0; idx < 4; idx++) {
		PRINT_SIMDFLOAT_OP(a.getElem(idx));
	}
	// min/max
	PRINT_VEC4_OP(a);
	PRINT_VEC4_OP(b);
	jlVector4 min, max;
	PRINT_VEC4_OP2(min, min.setMin(a, b));
	PRINT_VEC4_OP2(max, max.setMax(a, b));
	jlComp abcomp = a.compEqual(b);
	PRINT_INT_OP(abcomp.allAreSet(jlComp::MASK_XYZ)); // checks for xyz equality
	jlComp bacomp = a.compNotEqual(b);
	PRINT_INT_OP(bacomp.anyIsSet(jlComp::MASK_XYZ)); // checks for xyz equality
	std::cout << "-- End jlVector4 Testing --" << std::endl;
}

void testVector2() {
	std::cout << "-- Begin Testing jlVector2 --" << std::endl;
	jlVector2 a = jlVector2(2.0f, 5.0f);
	jlVector2 b = jlVector2(4.0f, -1.0f);
	float s = 2.0f;
	PRINT_VEC2_OP(a);
	PRINT_VEC2_OP(b);
	PRINT_FLOAT_OP(s);
	// arithmetic ops
	PRINT_VEC2_OP(a + b);
	PRINT_VEC2_OP(a - b);
	PRINT_VEC2_OP(a * s);
	PRINT_VEC2_OP(a / s);
	PRINT_VEC2_OP(a += b);
	PRINT_VEC2_OP(a -= b);
	PRINT_VEC2_OP(a *= s);
	PRINT_VEC2_OP(a /= s);
	PRINT_VEC2_OP(-a);
	// length/dot
	a.set(1.0f, 0.0f);
	b.set(0.0f, 1.0f);
	PRINT_VEC2_OP(a);
	PRINT_VEC2_OP(b);
	PRINT_FLOAT_OP(a.dot(b));
	a.set(4.0f, 2.5f);
	b.set(3.0f, 6.0f);
	PRINT_VEC2_OP(a);
	PRINT_VEC2_OP(b);
	PRINT_FLOAT_OP(a.dot(b));
	PRINT_FLOAT_OP(a.length());
	PRINT_FLOAT_OP(a.lengthSquared());
	PRINT_VEC2_OP2(a, a.normalize());
	PRINT_VEC2_OP2(b, b.normalize());
	std::cout << "-- Begin jlVector2 Testing --" << std::endl;
}

void testSimdFloat() {
	std::cout << "-- Begin Testing jlSimdFloat --" << std::endl;
	jlSimdFloat zero = jlSimdFloat(0.0f);

	// get/set
	jlSimdFloat a = jlSimdFloat(2.0f);
	jlSimdFloat b = jlSimdFloat(4.0f);
	PRINT_SIMDFLOAT_OP(a);
	PRINT_SIMDFLOAT_OP(b);
	a.setZero();
	PRINT_SIMDFLOAT_OP(a);
	a.setFromFloat(6.0f);
	PRINT_SIMDFLOAT_OP(a);
	// arithmetic
	PRINT_SIMDFLOAT_OP(a + b);
	PRINT_SIMDFLOAT_OP(a - b);
	PRINT_SIMDFLOAT_OP(a * b);
	PRINT_SIMDFLOAT_OP(a / b);
	PRINT_SIMDFLOAT_OP(-a);
	PRINT_SIMDFLOAT_OP(a += b);
	PRINT_SIMDFLOAT_OP(a -= b);
	PRINT_SIMDFLOAT_OP(a *= b);
	PRINT_SIMDFLOAT_OP(a /= b);
	// comparisons
	a = 3.0f;
	b = 3.0f;
	PRINT_SIMDFLOAT_OP(a);
	PRINT_SIMDFLOAT_OP(b);
	PRINT_INT_OP(a == b);
	PRINT_INT_OP(a != b);
	PRINT_INT_OP(a < b);
	PRINT_INT_OP(a > b);
	PRINT_INT_OP(a <= b);
	PRINT_INT_OP(a >= b);
	a = 6.0f;
	PRINT_SIMDFLOAT_OP(a);
	PRINT_SIMDFLOAT_OP(b);
	PRINT_INT_OP(a == b);
	PRINT_INT_OP(a != b);
	PRINT_INT_OP(a < b);
	PRINT_INT_OP(a > b);
	PRINT_INT_OP(a <= b);
	PRINT_INT_OP(a >= b);
	std::cout << "-- End jlSimdFloat Testing --" << std::endl;
}

void testMatrix4() {
	std::cout << "-- Begin Testing jlMatrix4 --" << std::endl;
	jlMatrix4 a;
	jlSimdFloat s = jlSimdFloat(5.0f);
	a.setIdentity();
	jlMatrix4 b;
	jlVector4 t = jlVector4(10.0f, 0.0f, 0.0f, 1.0f);
	b.makeTranslation(t);
	PRINT_MATRIX4_OP(a);
	PRINT_MATRIX4_OP(b);
	PRINT_MATRIX4_OP(a * b);
	b.setZero();
	PRINT_MATRIX4_OP(b);
	PRINT_MATRIX4_OP(a);
	a.setAll(3.0f);
	b.setAll(2.0f);
	PRINT_MATRIX4_OP(a + b);
	PRINT_MATRIX4_OP(a - b);
	PRINT_MATRIX4_OP(a * b);
	PRINT_MATRIX4_OP(-a);
	PRINT_MATRIX4_OP(a * s);
	jlVector4 vv = jlVector4(0.0f, 0.0f, 1.0f, 0.0f);
	a.makeTranslation(t);
	jlVector4 pt = jlVector4(20.0f, 5.0f, 0.0f, 1.0f);
	PRINT_VEC4_OP(a * pt); // should translate the point 10, 0, 0
	PRINT_MATRIX4_OP(a);
	PRINT_MATRIX4_OP(a * a.inverse()); // should be identity
	std::cout << "-- End Testing jlMatrix4 --" << std::endl;
}

void testQuaternion() {
	std::cout << "-- Begin Testing jlQuaternion --" << std::endl;
	jlQuaternion a, b;
	a.setAxisAngle(jlVector4::ZERO, jlSimdFloat(0.0f));
	b.setAxisAngle(jlVector4::ZERO, jlSimdFloat(jlMath::PI_OVER_TWO));
	PRINT_QUATERNION_OP(a);
	PRINT_QUATERNION_OP(b);
	jlMatrix4 qm; qm.makeRotationZ(0.0f);
	jlQuaternion fm = qm.toQuaternion();
	PRINT_QUATERNION_OP(fm);
	
	// when we rotate 1, 0, 0, 0 by a 90 degree y axis rotation, we should get 0, 0, -1
	jlSimdFloat theta90 = jlSimdFloat(jlMath::PI_OVER_TWO);
	jlQuaternion qy90; qy90.setAxisAngle(jlVector4::UNIT_Y, theta90);
	jlVector4 vr = jlVector4::UNIT_X;
	jlVector4 vrRotated = qy90 * vr;
	PRINT_VEC4_OP(vrRotated);
	
	int32 iterations = 10;
	jlQuaternion q0; 
	q0.setAxisAngle(jlVector4::UNIT_Z, jlSimdFloat(0.0f));
	jlQuaternion q1; 
	q1.setAxisAngle(jlVector4::UNIT_Z, jlSimdFloat(jlMath::PI));
	PRINT_QUATERNION_OP(q0);
	PRINT_QUATERNION_OP(q1);
	jlSimdFloat modifier = jlSimdFloat(1.0f / iterations);
	for (int32 i = 0; i <= iterations; ++i) {
		jlSimdFloat t = modifier * jlSimdFloat(static_cast<float32>(i));
		t.setMin(t, jlSimdFloat(1.0f));
		PRINT_QUATERNION_OP(jlQuaternion::Slerp(q0, q1, t));
	}
	std::cout << "-- End Testing jlQuaternion --" << std::endl;
}
/* END UNIT TESTS */

int main(int argc, char *argv[]) {
	JL_UNREFERENCED(argc); JL_UNREFERENCED(argv);
	testVector4(); // interchange with your own tests here
	std::cout << "Done With All Tests!" << std::endl;
	return 0;
}
