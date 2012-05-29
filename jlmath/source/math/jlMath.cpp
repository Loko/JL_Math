#include "math/jlMath.h"

const float32 jlMath::PI = jlMath::ATan(1.0f) * 4.0f;
const float32 jlMath::TWO_PI = PI * 2.0f;
const float32 jlMath::PI_OVER_TWO = PI * 0.5f;
const float32 jlMath::PI_OVER_FOUR = PI * 0.25f;
const float32 jlMath::ONE_OVER_PI = 1.0f / PI;
const float32 jlMath::ONE_OVER_TWO_PI = 1.0f / TWO_PI;
const float32 jlMath::DEG2RAD = PI / 180.0f;
const float32 jlMath::RAD2DEG = 180.0f / PI;
const float32 jlMath::LOG2 = log(2.0f);
const int32 jlMath::DEFAULT_TRIG_TABLE_SIZE = 4096;

#if JL_MATH_TRIG_TABLES
float32 * jlMath::sinTable = TBD_NULL;
float32 * jlMath::tanTable = TBD_NULL;
int32 jlMath::trigTableSize = 0;
float32 jlMath::trigTableFactor = 0.0f;
#endif

jlResult jlMath::SetupTrigTables(int32 tableSize) {
	#if JL_MATH_TRIG_TABLES
	TBD_ASSERT_MSG(tableSize > 0, "Can't have a negative trig table size!");
	trigTableSize = tableSize;
	if (tableSize) {
		trigTableFactor = tableSize / TWO_PI;
		sinTable = new float32[tableSize];
		tanTable = new float32[tableSize];

		float32 angle;
		int32 i;
		for (i = 0; i < tableSize; ++i) {
			angle = TWO_PI * i / tableSize;
			sinTable[i] = Sin(angle);
			tanTable[i] = Tan(angle);
		}
	}
	#else
	JL_UNREFERENCED(tableSize);
	#endif
	return JL_OK;
}

jlResult jlMath::UnloadTrigTables() {
	#if JL_MATH_TRIG_TABLES
	TBD_SAFE_DELETE_ARRAY(sinTable)
	TBD_SAFE_DELETE_ARRAY(tanTable)
	trigTableSize = 0;
	#endif
	return JL_OK;
}
