#include "math/jlMatrix4.h"

const jlMatrix4 jlMatrix4::ZERO(jlVector4::ZERO, jlVector4::ZERO, jlVector4::ZERO, jlVector4::ZERO);
const jlMatrix4 jlMatrix4::IDENTITY(jlVector4::UNIT_X, jlVector4::UNIT_Y, jlVector4::UNIT_Y, jlVector4::ZERO_PT);
const jlMatrix4 jlMatrix4::NEG_IDENTITY(jlVector4::NEG_UNIT_X, jlVector4::NEG_UNIT_Y, jlVector4::NEG_UNIT_Z, -jlVector4::ZERO_PT);
