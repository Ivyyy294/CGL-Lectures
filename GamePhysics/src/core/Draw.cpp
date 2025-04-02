#include "Draw.h"

// Directly convert from imgui vectors to glm vectors.
#define IM_VEC2_CLASS_EXTRA                            \
    constexpr ImVec2(glm::vec2& f) : x(f.x), y(f.y) {} \
    operator glm::vec2() const { return glm::vec2(x, y); }
#define IM_VEC4_CLASS_EXTRA                                                  \
    constexpr ImVec4(const glm::vec4& f) : x(f.x), y(f.y), z(f.z), w(f.w) {} \
    operator glm::vec4() const { return glm::vec4(x, y, z, w); }

#include <SDL_stdinc.h>
#include <iostream>
#include <vector>

#include "imgui.h"
#include "ImGuizmo.h"
#include "Math.h"

namespace Draw {

ImDrawList* drawList;
glm::mat4 camMatrix;
glm::mat4 camMatrixInv;

struct Context {
    float x = 0;
    float y = 0;
    float width = 0;
    float height = 0;
    ImColor color = ImColor(255, 255, 255, 255);
    float thickness = 1.0f;
};

Context gContext;

void Begin() {
    drawList = ImGui::GetWindowDrawList();
}

void End() {
    Reset();
}

void SetViewport(float x, float y, float width, float height) {
    gContext.x = x;
    gContext.y = y;
    gContext.width = width;
    gContext.height = height;
}

void SetCamera(const glm::mat4& vpMatrix) {
    camMatrix = vpMatrix;
    camMatrixInv = glm::inverse(vpMatrix);
}

ImVec2 transformPoint(const glm::mat4& mat, const glm::vec2& p) {
    glm::vec4 trans(p, 0, 1);
    trans = mat * trans;
    trans *= 0.5f / trans.w;
    trans += glm::vec4(0.5f, 0.5f, 0, 0);
    trans.y = 1.f - trans.y;
    trans.x *= gContext.width;
    trans.y *= gContext.height;
    trans.x += gContext.x;
    trans.y += gContext.y;
    return ImVec2(trans.x, trans.y);
}

float transformLength(const glm::mat4& mat, float l) {
    return mat[0][0] * 0.5f * l * gContext.width;
}

void Line(const glm::vec2& start, const glm::vec2& end) {
    ImVec2 startl = transformPoint(camMatrix, start);
    ImVec2 endl = transformPoint(camMatrix, end);
    drawList->AddLine(startl, endl, gContext.color, gContext.thickness);
}

void Arrow(const glm::vec2& start, const glm::vec2& end, float headThickness) {
    glm::vec2 dir = end - start;
    float headLength = gContext.thickness / camMatrix[0][0] * headThickness;
    Line(start, start + dir - 0.8f * headLength * glm::normalize(dir));
    float headAngle = M_PI / 6;
    float angle = glm::atan(dir.y, dir.x);
    glm::vec2 points[3];
    points[0] = end;
    points[1] = glm::vec2(end.x - headLength * cosf(angle - headAngle),
                          end.y - headLength * sinf(angle - headAngle));
    points[2] = glm::vec2(end.x - headLength * cosf(angle + headAngle),
                          end.y - headLength * sinf(angle + headAngle));
    Polygon(glm::mat4(1), points, 3, true);
}

void SetupImGuiViewport() {
    auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
    auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
    auto viewportOffset = ImGui::GetWindowPos();
    auto viewportX = viewportMinRegion.x + viewportOffset.x;
    auto viewportY = viewportMinRegion.y + viewportOffset.y;
    auto viewportWidth = viewportMaxRegion.x - viewportMinRegion.x;
    auto viewportHeight = viewportMaxRegion.y - viewportMinRegion.y;
    Draw::SetViewport(viewportX, viewportY, viewportWidth, viewportHeight);
}

void Circle(const glm::vec2& center, float radius, bool filled) {
    ImVec2 centerl = transformPoint(camMatrix, center);
    float radiusl = transformLength(camMatrix, radius);

    if (radiusl > 1e10 || radiusl < 0) {
        return;
    }
    if (filled) {
        drawList->AddCircleFilled(centerl, radiusl, gContext.color, 0);
    } else {
        drawList->AddCircle(centerl, radiusl, gContext.color, 0,
                            gContext.thickness);
    }
}

void AABB(const glm::vec2& min, const glm::vec2& max, bool filled) {
    ImVec2 minl = transformPoint(camMatrix, min);
    ImVec2 maxl = transformPoint(camMatrix, max);

    if (filled) {
        drawList->AddRectFilled(minl, maxl, gContext.color, 0, 0);
    } else {
        drawList->AddRect(minl, maxl, gContext.color, 0, ImDrawFlags_None,
                          gContext.thickness);
    }
}

void Polygon(const glm::vec2 position,
             const glm::vec2* points,
             const int pointCount,
             bool filled) {
    std::vector<ImVec2> pointsl(pointCount);

    for (int i = 0; i < pointCount; i++) {
        pointsl[i] = transformPoint(camMatrix, points[i] + position);
    }

    if (filled) {
        drawList->AddConvexPolyFilled(pointsl.data(), pointCount,
                                      gContext.color);
    } else {
        drawList->AddPolyline(pointsl.data(), pointCount, gContext.color,
                              ImDrawFlags_Closed, gContext.thickness);
    }
}

void Polygon(const glm::mat4& modelMatrix,
             const glm::vec2* points,
             int pointCount,
             bool filled) {
    glm::mat4 mvpMatrix = camMatrix * modelMatrix;
    std::vector<ImVec2> pointsl(pointCount);

    for (int i = 0; i < pointCount; i++) {
        pointsl[i] = transformPoint(mvpMatrix, points[i]);
    }

    if (filled) {
        drawList->AddConvexPolyFilled(pointsl.data(), pointCount,
                                      gContext.color);
    } else {
        drawList->AddPolyline(pointsl.data(), pointCount, gContext.color,
                              ImDrawFlags_Closed, gContext.thickness);
    }
}

void Polyline(const glm::vec2 position,
              const glm::vec2* points,
              int pointCount) {
    std::vector<ImVec2> pointsl(pointCount);

    for (int i = 0; i < pointCount; i++) {
        pointsl[i] = transformPoint(camMatrix, points[i] + position);
    }
    drawList->AddPolyline(pointsl.data(), pointCount, gContext.color,
                          ImDrawFlags_None, gContext.thickness);
}

void Polyline(const glm::mat4& modelMatrix,
              const glm::vec2* points,
              int pointCount) {
    glm::mat4 mvpMatrix = camMatrix * modelMatrix;
    std::vector<ImVec2> pointsl(pointCount);

    for (int i = 0; i < pointCount; i++) {
        pointsl[i] = transformPoint(mvpMatrix, points[i]);
    }
    drawList->AddPolyline(pointsl.data(), pointCount, gContext.color,
                          ImDrawFlags_None, gContext.thickness);
}

void Rect(const glm::vec2& position,
          float angle,
          const glm::vec2& halfExtends,
          bool filled) {
    glm::mat4 modelMatrix = Math::ModelMatrix2D(position, angle);
    Rect(modelMatrix, halfExtends, filled);
}

void Rect(const glm::mat4& modelMatrix,
          const glm::vec2& halfExtends,
          bool filled) {
    glm::mat4 mvpMatrix = camMatrix * modelMatrix;
    ImVec2 pointsl[4];
    pointsl[0] =
        transformPoint(mvpMatrix, glm::vec2(-halfExtends.x, -halfExtends.y));
    pointsl[1] =
        transformPoint(mvpMatrix, glm::vec2(+halfExtends.x, -halfExtends.y));
    pointsl[2] =
        transformPoint(mvpMatrix, glm::vec2(+halfExtends.x, +halfExtends.y));
    pointsl[3] =
        transformPoint(mvpMatrix, glm::vec2(-halfExtends.x, +halfExtends.y));
    if (filled) {
        drawList->AddConvexPolyFilled(pointsl, 4, gContext.color);
    } else {
        drawList->AddPolyline(pointsl, 4, gContext.color, ImDrawFlags_Closed,
                              gContext.thickness);
    }
}

void Grid(const glm::vec2& min,
          const glm::vec2& max,
          const glm::vec2& lineDistance) {
    // Horizontal lines
    for (int y = min.y; y <= max.y; y += lineDistance.y) {
        Line(glm::vec2(min.x, y), glm::vec2(max.x, y));
    }
    // Vertical lines
    for (int x = min.x; x <= max.x; x += lineDistance.x) {
        Line(glm::vec2(x, min.y), glm::vec2(x, max.y));
    }
}

void Text(const glm::vec2& position, const char* text) {
    ImVec2 positionl = transformPoint(camMatrix, position);
    drawList->AddText(positionl, gContext.color, text);
}

void SetColor(ImColor color) {
    gContext.color = color;
}

void SetThickness(float thickness) {
    gContext.thickness = thickness;
}

void Reset() {
    gContext.color = 0xffffffff;
    gContext.thickness = 1;
}

bool PositionHandle(glm::vec2& position) {
    glm::mat4 modelMatrix = Math::ModelMatrix2D(position, 0);
    bool manipulated = PositionHandle(modelMatrix);
    position.x = modelMatrix[3][0];
    position.y = modelMatrix[3][1];
    return manipulated;
}

bool PositionHandle(glm::mat4& modelMatrix) {
    glm::mat4 identity = glm::mat4(1);
    ImGuizmo::SetDrawlist(drawList);
    ImGuizmo::SetOrthographic(true);
    ImGuizmo::SetRect(gContext.x, gContext.y, gContext.width, gContext.height);
    return ImGuizmo::Manipulate(&identity[0][0], &camMatrix[0][0],
                                ImGuizmo::TRANSLATE, ImGuizmo::WORLD,
                                &modelMatrix[0][0]);
}

bool RotationHandle(const glm::vec2& position, float& angle) {
    glm::mat4 modelMatrix = Math::ModelMatrix2D(position, angle);
    bool manipulated = RotationHandle(modelMatrix);
    angle = atan2f(modelMatrix[0][1], modelMatrix[0][0]);
    return manipulated;
}

bool RotationHandle(glm::mat4& modelMatrix) {
    glm::mat4 identity = glm::mat4(1);
    ImGuizmo::SetDrawlist(drawList);
    ImGuizmo::SetOrthographic(true);
    ImGuizmo::SetRect(gContext.x, gContext.y, gContext.width, gContext.height);
    return ImGuizmo::Manipulate(&identity[0][0], &camMatrix[0][0],
                                ImGuizmo::ROTATE_Z, ImGuizmo::WORLD,
                                &modelMatrix[0][0]);
}

bool IsPointVisible(const glm::vec2& point) {
    auto screen = transformPoint(camMatrix, point);
    return screen.x >= gContext.x && screen.x <= gContext.x + gContext.width &&
           screen.y >= gContext.y && screen.y <= gContext.y + gContext.height;
}

glm::vec2 VectorScreenToGame(glm::vec2 vector) {
    return vector / glm::vec2(camMatrix[0][0], camMatrix[1][1]);
}

} // namespace Draw

namespace Input {

glm::vec2 GetMousePos() {
    glm::vec2 mouse = ImGui::GetMousePos();

    mouse.x -= Draw::gContext.x;
    mouse.y -= Draw::gContext.y;
    mouse.x /= Draw::gContext.width;
    mouse.y /= Draw::gContext.height;
    mouse.y = 1.f - mouse.y;
    mouse.x -= 0.5f;
    mouse.y -= 0.5f;
    mouse /= 0.5f;
    glm::vec4 position = glm::vec4(mouse, 0, 1);
    position = Draw::camMatrixInv * position;

    return position;
}

glm::vec2 GetMousePosInWindow() {
    glm::vec2 mouse = ImGui::GetMousePos();

    mouse.x -= Draw::gContext.x;
    mouse.y -= Draw::gContext.y;
    mouse.x /= Draw::gContext.width;
    mouse.y /= Draw::gContext.height;
    mouse.y = 1.f - mouse.y;
    mouse.x -= 0.5f;
    mouse.y -= 0.5f;
    mouse /= 0.5f;
    return mouse;
}
bool IsMouseDown(int mouseButton) {
    return ImGui::IsMouseDown(mouseButton);
}
bool IsMouseClicked(int mouseButton) {
    return ImGui::IsMouseClicked(mouseButton);
}
bool IsMouseReleased(int mouseButton) {
    return ImGui::IsMouseReleased(mouseButton);
}
} // namespace Input