#pragma once

#include <stdlib.h>
#include "core/Colors.h"

namespace Random {

void Seed(unsigned int seed);
int RandomInt(int minInclusive, int maxExclusive);
float RandomFloat01();
float RandomFloat(float minInclusive, float maxExclusive);
bool RandomBool();
Color RandomColor();
Color RandomColorHSV(float hMin = 0.0f,
                     float hMax = 1.0f,
                     float sMin = 0.0f,
                     float sMax = 1.0f,
                     float vMin = 0.0f,
                     float vMax = 1.0f);

} // namespace Random