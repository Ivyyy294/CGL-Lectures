#pragma once

#include "Circle.h"
#include "Wall.h"

class Physics {
public:
    static void Run(GameObject::Vec& vec);
    static void ResolveCollision(GameObject* obj1, GameObject* obj2);
    static void ResolveCollision(Circle* circle, Wall* wall);
    static void ResolveCollision(Circle* circle1, Circle* circle2);
    static void ResolveCollision(Wall* wall1, Wall* wall2){};
};
