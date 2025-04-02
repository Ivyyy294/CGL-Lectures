#pragma once

#include "core/Math.h"

namespace PhysicsUtils {

// Tests if two rectangles are colliding and returns the collision normal and
// intersection depth as well.
bool IsCollidingRectRect(const glm::vec2& rectAPosition,
                         float rectAAngle,
                         const glm::vec2& rectAHalfExtends,
                         const glm::vec2& rectBPosition,
                         float rectBAngle,
                         const glm::vec2& rectBHalfExtends,
                         glm::vec2& collisionNormal, // out
                         float& intersectionDepth    // out
);

// Tests if a circle and a rectangle are colliding and returns the collision
// normal and intersection depth as well.
bool IsCollidingCircleRect(const glm::vec2& circlePosition,
                           float circleRadius,
                           const glm::vec2& rectPosition,
                           float rectAngle,
                           const glm::vec2& rectHalfExtends,
                           glm::vec2& collisionNormal, // out
                           float& intersectionDepth    // out
);

// Tests if two polygons are colliding and returns the collision normal and
// intersection depth as well.
bool IsCollidingPolygonPolygon(const glm::vec2& polygonACenterOfMass,
                               const std::vector<glm::vec2>& polygonAPoints,
                               const glm::vec2& polygonBCenterOfMass,
                               const std::vector<glm::vec2>& polygonBPoints,
                               glm::vec2& collisionNormal, // out
                               float& intersectionDepth    // out
);

// Tests if a circle and a polygon are colliding and returns the collision
// normal and intersection depth as well.
bool IsCollidingCirclePolygon(const glm::vec2& circlePosition,
                              float circleRadius,
                              const glm::vec2& polygonCenterOfMass,
                              const std::vector<glm::vec2>& polygonPoints,
                              glm::vec2& collisionNormal, // out
                              float& intersectionDepth    // out
);

// Returns the moment of inertia for a circle.
float GetMomentOfInertiaCircle(float radius, float mass);
// Returns the moment of inertia for a rectangle.
float GetMomentOfInertiaRect(const glm::vec2& halfExtends, float mass);
// Returns the moment of inertia for a regular polygon.
float GetMomentOfInertiaRegularPolygon(int pointCount,
                                       float radius,
                                       float mass);

// Finds the contact points between two rectangles.
void FindContactPointsRectRect(const glm::vec2& rectAPosition,
                               float rectAAngle,
                               const glm::vec2& rectAHalfExtends,
                               const glm::vec2& rectBPosition,
                               float rectBAngle,
                               const glm::vec2& rectBHalfExtends,
                               glm::vec2& contactPoint1, // out
                               glm::vec2& contactPoint2, // out
                               int& contactPointCount    // out
);

// Finds the contact point between a circle and a rectangle.
glm::vec2 FindContactPointCircleRect(const glm::vec2& circlePosition,
                                     float circleRadius,
                                     const glm::vec2& rectPosition,
                                     float rectAngle,
                                     const glm::vec2& rectHalfExtends);

// Finds the contact points between two polygons.
void FindContactPointsPolygonPolygon(
    const std::vector<glm::vec2>& polygonAPoints,
    const std::vector<glm::vec2>& polygonBPoints,
    glm::vec2& contactPoint1, // out
    glm::vec2& contactPoint2, // out
    int& contactPointCount    // out
);

// Finds the contact point between a circle and a polygon.
glm::vec2 FindContactPointCirclePolygon(
    const glm::vec2& circlePosition,
    float circleRadius,
    const std::vector<glm::vec2>& polygonPoints);

} // namespace PhysicsUtils