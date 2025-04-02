#include "PhysicsUtils.h"

#include <SDL_stdinc.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/epsilon.hpp>
#include <glm/gtx/norm.hpp>

bool PhysicsUtils::IsCollidingRectRect(const glm::vec2& rectAPosition,
                                       float rectAAngle,
                                       const glm::vec2& rectAHalfExtends,
                                       const glm::vec2& rectBPosition,
                                       float rectBAngle,
                                       const glm::vec2& rectBHalfExtends,
                                       glm::vec2& collisionNormal,
                                       float& intersectionDepth) {
    std::vector<glm::vec2> rectAPoints = Math::GetRectangleWorldPoints(
        rectAPosition, rectAAngle, rectAHalfExtends);
    std::vector<glm::vec2> rectBPoints = Math::GetRectangleWorldPoints(
        rectBPosition, rectBAngle, rectBHalfExtends);

    return IsCollidingPolygonPolygon(rectAPosition, rectAPoints, rectBPosition,
                                     rectBPoints, collisionNormal,
                                     intersectionDepth);
}

bool PhysicsUtils::IsCollidingCircleRect(const glm::vec2& circlePosition,
                                         float circleRadius,
                                         const glm::vec2& rectPosition,
                                         float rectAngle,
                                         const glm::vec2& rectHalfExtends,
                                         glm::vec2& collisionNormal,
                                         float& intersectionDepth) {
    std::vector<glm::vec2> rectPoints =
        Math::GetRectangleWorldPoints(rectPosition, rectAngle, rectHalfExtends);
    return IsCollidingCirclePolygon(circlePosition, circleRadius, rectPosition,
                                    rectPoints, collisionNormal,
                                    intersectionDepth);
}

// Finds minimum and maximum projected values for a polygon.
void ProjectPoints(const std::vector<glm::vec2>& polygonPoints,
                   glm::vec2 normal,
                   float& min,
                   float& max) {
    min = FLT_MAX;
    max = -FLT_MAX;
    for (int i = 0; i < polygonPoints.size(); i++) {
        float projected = glm::dot(polygonPoints[i], normal);
        if (projected < min) {
            min = projected;
        }
        if (projected > max) {
            max = projected;
        }
    }
}

bool PhysicsUtils::IsCollidingPolygonPolygon(
    const glm::vec2& polygonACenterOfMass,
    const std::vector<glm::vec2>& polygonAPoints,
    const glm::vec2& polygonBCenterOfMass,
    const std::vector<glm::vec2>& polygonBPoints,
    glm::vec2& collisionNormal,
    float& intersectionDepth) {
    float minA, maxA, minB, maxB;

    intersectionDepth = FLT_MAX;

    // Test the normals of polygon A.
    for (int i = 0; i < polygonAPoints.size(); i++) {
        glm::vec2 a = polygonAPoints[i];
        glm::vec2 b = polygonAPoints[(i + 1) % polygonAPoints.size()];

        glm::vec2 edge = b - a;
        glm::vec2 normal = glm::normalize(glm::vec2(edge.y, -edge.x));

        ProjectPoints(polygonAPoints, normal, minA, maxA);
        ProjectPoints(polygonBPoints, normal, minB, maxB);

        if (minA >= maxB || minB >= maxA) {
            // Separation found along this axis. The polygons do not intersect.
            return false;
        }

        // No separation. Need to find minimum depth.
        float depth = std::min(maxA - minB, maxB - minA);
        if (depth < intersectionDepth) {
            intersectionDepth = depth;
            collisionNormal = normal;
        }
    }

    // Test the normals of polygon B.
    for (int i = 0; i < polygonBPoints.size(); i++) {
        glm::vec2 a = polygonBPoints[i];
        glm::vec2 b = polygonBPoints[(i + 1) % polygonBPoints.size()];

        glm::vec2 edge = b - a;
        glm::vec2 normal = glm::normalize(glm::vec2(edge.y, -edge.x));

        ProjectPoints(polygonAPoints, normal, minA, maxA);
        ProjectPoints(polygonBPoints, normal, minB, maxB);

        if (minA >= maxB || minB >= maxA) {
            // Separation found along this axis. The polygons do not intersect.
            return false;
        }
        // No separation. Need to find minimum depth.
        float depth = std::min(maxA - minB, maxB - minA);
        if (depth < intersectionDepth) {
            intersectionDepth = depth;
            collisionNormal = normal;
        }
    }

    // Make sure the normal is pointing from the polygon A to polygon B.
    glm::vec2 dir = polygonBCenterOfMass - polygonACenterOfMass;

    if (glm::dot(dir, collisionNormal) < 0) {
        collisionNormal = -collisionNormal;
    }
    return true;
}

// Finds minimum and maximum projected values for a circle.
void ProjectCircle(const glm::vec2& circlePosition,
                   float circleRadius,
                   glm::vec2 normal,
                   float& min,
                   float& max) {
    glm::vec2 p1 = circlePosition + normal * circleRadius;
    glm::vec2 p2 = circlePosition - normal * circleRadius;
    min = glm::dot(p1, normal);
    max = glm::dot(p2, normal);

    if (min > max) {
        float tmp = max;
        max = min;
        min = tmp;
    }
}

glm::vec2 ClosestPointOnPolygon(const glm::vec2& position,
                                const std::vector<glm::vec2>& polygonPoints) {
    glm::vec2 result = glm::vec2(0);
    float minDistance = FLT_MAX;
    for (int i = 0; i < polygonPoints.size(); i++) {
        float distance = glm::length(polygonPoints[i] - position);
        if (distance < minDistance) {
            minDistance = distance;
            result = polygonPoints[i];
        }
    }
    return result;
}

bool PhysicsUtils::IsCollidingCirclePolygon(
    const glm::vec2& circlePosition,
    float circleRadius,
    const glm::vec2& polygonCenterOfMass,
    const std::vector<glm::vec2>& polygonPoints,
    glm::vec2& collisionNormal,
    float& intersectionDepth) {
    intersectionDepth = FLT_MAX;

    // Test the normals of the polygon.
    for (int i = 0; i < polygonPoints.size(); i++) {
        glm::vec2 a = polygonPoints[i];
        glm::vec2 b = polygonPoints[(i + 1) % polygonPoints.size()];

        glm::vec2 edge = b - a;
        glm::vec2 normal = glm::normalize(glm::vec2(edge.y, -edge.x));

        float minA, maxA, minB, maxB;

        ProjectCircle(circlePosition, circleRadius, normal, minA, maxA);
        ProjectPoints(polygonPoints, normal, minB, maxB);

        if (minA >= maxB || minB >= maxA) {
            return false;
        }
        // No separation. Need to find minimum depth.
        float depth = std::min(maxA - minB, maxB - minA);
        if (depth < intersectionDepth) {
            intersectionDepth = depth;
            collisionNormal = normal;
        }
    }

    // Test the circle normal.
    {
        glm::vec2 closestPoint =
            ClosestPointOnPolygon(circlePosition, polygonPoints);
        glm::vec2 normal = glm::normalize(closestPoint - circlePosition);
        float minA, maxA, minB, maxB;

        ProjectCircle(circlePosition, circleRadius, normal, minA, maxA);
        ProjectPoints(polygonPoints, normal, minB, maxB);

        if (minA >= maxB || minB >= maxA) {
            return false;
        }
        // No separation. Need to find minimum depth.
        float depth = std::min(maxA - minB, maxB - minA);
        if (depth < intersectionDepth) {
            intersectionDepth = depth;
            collisionNormal = normal;
        }
    }

    // Make sure the normal is pointing from the circle to the polygon.
    glm::vec2 dir = polygonCenterOfMass - circlePosition;
    if (glm::dot(dir, collisionNormal) < 0) {
        collisionNormal = -collisionNormal;
    }

    return true;
}

// https://en.wikipedia.org/wiki/List_of_moments_of_inertia
float PhysicsUtils::GetMomentOfInertiaCircle(float radius, float mass) {
    return 0.5f * mass * radius * radius;
}

float PhysicsUtils::GetMomentOfInertiaRect(const glm::vec2& halfExtends,
                                           float mass) {
    float w = halfExtends.x * 2;
    float h = halfExtends.y * 2;
    return 1.f / 12.f * mass * (w * w + h * h);
}

float PhysicsUtils::GetMomentOfInertiaRegularPolygon(int pointCount,
                                                     float radius,
                                                     float mass) {
    float sin = sinf(M_PI / pointCount);
    return 0.5f * mass * radius * radius * (1 - (2.f / 3.f * sin * sin));
}

void PhysicsUtils::FindContactPointsRectRect(const glm::vec2& rectAPosition,
                                             float rectAAngle,
                                             const glm::vec2& rectAHalfExtends,
                                             const glm::vec2& rectBPosition,
                                             float rectBAngle,
                                             const glm::vec2& rectBHalfExtends,
                                             glm::vec2& contactPoint1,
                                             glm::vec2& contactPoint2,
                                             int& contactPointCount) {
    std::vector<glm::vec2> rectAPoints = Math::GetRectangleWorldPoints(
        rectAPosition, rectAAngle, rectAHalfExtends);
    std::vector<glm::vec2> rectBPoints = Math::GetRectangleWorldPoints(
        rectBPosition, rectBAngle, rectBHalfExtends);
    FindContactPointsPolygonPolygon(rectAPoints, rectBPoints, contactPoint1,
                                    contactPoint2, contactPointCount);
}

glm::vec2 PhysicsUtils::FindContactPointCircleRect(
    const glm::vec2& circlePosition,
    float circleRadius,
    const glm::vec2& rectPosition,
    float rectAngle,
    const glm::vec2& rectHalfExtends) {
    std::vector<glm::vec2> rectPoints =
        Math::GetRectangleWorldPoints(rectPosition, rectAngle, rectHalfExtends);
    return FindContactPointCirclePolygon(circlePosition, circleRadius,
                                         rectPoints);
}

// p: point, a,b: ends of the line
void FindClosestPointOnLine(glm::vec2 p,
                            glm::vec2 a,
                            glm::vec2 b,
                            float& distanceSquared,
                            glm::vec2& contact) {
    glm::vec2 ab = b - a;
    glm::vec2 ap = p - a;
    float proj = glm::dot(ap, ab);
    float abLenSq = glm::length2(ab);
    float d = proj / abLenSq;
    if (d <= 0) {
        contact = a;
    } else if (d >= 1) {
        contact = b;
    } else {
        contact = a + ab * d;
    }
    distanceSquared = glm::length2(p - contact);
}

void PhysicsUtils::FindContactPointsPolygonPolygon(
    const std::vector<glm::vec2>& polygonAPoints,
    const std::vector<glm::vec2>& polygonBPoints,
    glm::vec2& contactPoint1,
    glm::vec2& contactPoint2,
    int& contactPointCount) {
    contactPoint1 = glm::vec2(0);
    contactPoint2 = glm::vec2(0);
    contactPointCount = 0;

    float minDistanceSq = FLT_MAX;

    float epsilon = 1e-6f;

    for (int i = 0; i < polygonAPoints.size(); i++) {
        glm::vec2 p = polygonAPoints[i];
        for (int j = 0; j < polygonBPoints.size(); j++) {
            glm::vec2 va = polygonBPoints[j];
            glm::vec2 vb = polygonBPoints[(j + 1) % polygonBPoints.size()];

            float distanceSq;
            glm::vec2 contact;
            FindClosestPointOnLine(p, va, vb, distanceSq, contact);

            if (glm::epsilonEqual(distanceSq, minDistanceSq, epsilon)) {
                // Two distances are the same -> we have two contact points

                if (!glm::all(
                        glm::epsilonEqual(contact, contactPoint1, epsilon))) {
                    // New unique contact point
                    contactPointCount = 2;
                    contactPoint2 = contact;
                } else {
                    // The same as the previous contact point
                }
            } else if (distanceSq < minDistanceSq) {
                // Absolute minimum distance -> there is only one contact point.
                minDistanceSq = distanceSq;
                contactPointCount = 1;
                contactPoint1 = contact;
            }
        }
    }

    for (int i = 0; i < polygonBPoints.size(); i++) {
        glm::vec2 p = polygonBPoints[i];
        for (int j = 0; j < polygonAPoints.size(); j++) {
            glm::vec2 va = polygonAPoints[j];
            glm::vec2 vb = polygonAPoints[(j + 1) % polygonAPoints.size()];

            float distanceSq;
            glm::vec2 contact;
            FindClosestPointOnLine(p, va, vb, distanceSq, contact);

            if (glm::epsilonEqual(distanceSq, minDistanceSq, epsilon)) {
                // Two distances are the same -> we have two contact points

                if (!glm::all(
                        glm::epsilonEqual(contact, contactPoint1, epsilon))) {
                    // New unique contact point
                    contactPointCount = 2;
                    contactPoint2 = contact;
                } else {
                    // The same as the previous contact point
                }
            } else if (distanceSq < minDistanceSq) {
                // Absolute minimum distance -> there is only one contact point.
                minDistanceSq = distanceSq;
                contactPointCount = 1;
                contactPoint1 = contact;
            }
        }
    }
}

glm::vec2 PhysicsUtils::FindContactPointCirclePolygon(
    const glm::vec2& circlePosition,
    float circleRadius,
    const std::vector<glm::vec2>& polygonPoints) {
    float minDistanceSq = FLT_MAX;
    glm::vec2 contactPoint = glm::vec2(0);

    for (int i = 0; i < polygonPoints.size(); i++) {
        glm::vec2 va = polygonPoints[i];
        glm::vec2 vb = polygonPoints[(i + 1) % polygonPoints.size()];

        float distanceSq;
        glm::vec2 contact;
        FindClosestPointOnLine(circlePosition, va, vb, distanceSq, contact);

        if (distanceSq < minDistanceSq) {
            minDistanceSq = distanceSq;
            contactPoint = contact;
        }
    }
    return contactPoint;
}
