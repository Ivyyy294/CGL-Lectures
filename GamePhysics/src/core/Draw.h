#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

struct ImColor;

namespace Draw {

// Draws a line from the start to the end point.
void Line(const glm::vec2& start, const glm::vec2& end);
// Draws an arrow from the start to the end point.
void Arrow(const glm::vec2& start,
           const glm::vec2& end,
           float headThickness = 0.02f);
// Draws a circle.
void Circle(const glm::vec2& center, float radius, bool filled = false);
// Draws an axis aligned rectangle.
void AABB(const glm::vec2& min, const glm::vec2& max, bool filled = false);
// Draws a polygon.
void Polygon(const glm::vec2 position,
             const glm::vec2* points,
             int pointCount,
             bool filled = false);
void Polygon(const glm::mat4& modelMatrix,
             const glm::vec2* points,
             int pointCount,
             bool filled = false);
// Draws a polyline.
void Polyline(const glm::vec2 position,
              const glm::vec2* points,
              int pointCount);
void Polyline(const glm::mat4& modelMatrix,
              const glm::vec2* points,
              int pointCount);
// Draws a rectangle.
void Rect(const glm::vec2& position,
          float angle,
          const glm::vec2& halfExtends,
          bool filled = false);
void Rect(const glm::mat4& modelMatrix,
          const glm::vec2& halfExtends,
          bool filled = false);
// Draws a grid.
void Grid(const glm::vec2& min,
          const glm::vec2& max,
          const glm::vec2& lineDistance);
// Draws some text.
void Text(const glm::vec2& position, const char* text);

// Sets the color to draw with.
void SetColor(ImColor color);
// Sets the thickness to draw with.
void SetThickness(float thickness);
// Resets color and thickness.
void Reset();

// Draws a handle that the user can use to modify the position.
// Only supports one handle to be drawn at the same time, see https://github.com/CedricGuillemet/ImGuizmo/issues/16.
bool PositionHandle(glm::vec2& position);
bool PositionHandle(glm::mat4& modelMatrix);
// Draws a handle that the user can use to modify the rotation.
// Only supports one handle to be drawn at the same time, see https://github.com/CedricGuillemet/ImGuizmo/issues/16.
bool RotationHandle(const glm::vec2& position, float& angle);
bool RotationHandle(glm::mat4& modelMatrix);

// Returns true if the point is inside the visible rect of the viewport.
bool IsPointVisible(const glm::vec2& point);

// Begins drawing a frame. Called from Simple2DScene.
void Begin();
// Finishs drawing a frame. Called from Simple2DScene.
void End();
// Sets the camera matrix. Called from Simple2DScene.
void SetCamera(const glm::mat4& vpMatrix);
// Sets the viewport up in the current ImGui window. Called from Simple2DScene.
void SetupImGuiViewport();
// Sets the viewport. Called from Simple2DScene.
void SetViewport(float x, float y, float width, float height);
// Converts vector from screen space to world space.
glm::vec2 VectorScreenToGame(glm::vec2 vector);

} // namespace Draw