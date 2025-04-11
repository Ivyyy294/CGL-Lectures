#pragma once

#include "BouncingBall.h"
#include "Wall.h"

class Physics {
public:
    static void Run();
    static void ResolveCollision(PhysicObject* obj1, PhysicObject* obj2);
};
