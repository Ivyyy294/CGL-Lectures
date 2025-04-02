#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace Math {

// Calculates the 4x4 matrix for the given position and angle.
glm::mat4 ModelMatrix2D(const glm::vec2& position, float angle);

// Transforms the points of a polygon to world space.
std::vector<glm::vec2> TransformPolygon(const std::vector<glm::vec2>& points,
                                        const glm::vec2& position,
                                        float angle);

// Generates the points for a regular polygon in counter-clockwise order.
std::vector<glm::vec2> GenerateRegularPolygon(int pointCount, float radius = 1);

// Calculates the z component of the cross product (a.x, a.y, 0) x (b.x, b.y, 0).
float CrossProduct2D(const glm::vec2& a, const glm::vec2& b);

// Generates the points for a rectangle and transforms them to world space.
std::vector<glm::vec2> GetRectangleWorldPoints(const glm::vec2& position,
                                               float angle,
                                               const glm::vec2& halfExtends);

} // namespace Math