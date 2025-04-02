#include "Random.h"

void Random::Seed(unsigned int seed) {
    srand(seed);
}

int Random::RandomInt(int minInclusive, int maxExclusive) {
    return rand() % (maxExclusive - minInclusive) + minInclusive;
}

float Random::RandomFloat01() {
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

float Random::RandomFloat(float minInclusive, float maxExclusive) {
    return minInclusive +
           static_cast<float>(rand()) /
               static_cast<float>(RAND_MAX / (maxExclusive - minInclusive));
}

bool Random::RandomBool() {
    return rand() % 2;
}

Color Random::RandomColor() {
    return ImColor(RandomFloat01(), RandomFloat01(), RandomFloat01());
}

Color Random::RandomColorHSV(float hMin,
                             float hMax,
                             float sMin,
                             float sMax,
                             float vMin,
                             float vMax) {
    return ImColor::HSV(RandomFloat(hMin, hMax), RandomFloat(sMin, sMax),
                        RandomFloat(vMin, vMax));
}
