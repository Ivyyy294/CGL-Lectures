#include "Simple2DScene.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <time.h>

#include "core/Random.h"
#include "imgui.h"

Simple2DScene::Simple2DScene()
    : projection(glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f)),
      view(glm::mat4(1.0f)),
      matrix(glm::mat4(1.0f)),
      identity(glm::mat4(1.0f)),
      cameraCenter(0, 0),
      orthographicSize(10),
      isCameraWindowVisible(true),
      isMovingCamera(false) {
    Random::Seed(time(nullptr));
}

Simple2DScene::~Simple2DScene() {}

void Simple2DScene::Render() {
    if (isCameraWindowVisible) {
        ImGui::Begin("Camera");
        ImGui::DragFloat2("Center", &cameraCenter[0], 0.1f);
        ImGui::DragFloat("Orthographic Size", &orthographicSize, 0.1f, 0.1f,
                         1000, "%.1f", ImGuiSliderFlags_AlwaysClamp);
        ImGui::End();
    }

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 1));
    ImGui::Begin("Viewport");

    // Only if the window is hovered, control the camera with the mouse.
    if (ImGui::IsWindowHovered()) {
        const auto& io = ImGui::GetIO();
        if (io.MouseWheel != 0) {
            orthographicSize *= io.MouseWheel < 0 ? 1.1f : 0.9f;
        }

        if (ImGui::IsMouseDown(ImGuiMouseButton_Right) ||
            ImGui::IsMouseDown(ImGuiMouseButton_Middle)) {
            if (!isMovingCamera) {
                isMovingCamera = true;
                lastMousePos = Input::GetMousePosInWindow();
            } else {
                glm::vec2 currentMousePos = Input::GetMousePosInWindow();
                glm::vec2 diff = currentMousePos - lastMousePos;
                cameraCenter -= Draw::VectorScreenToGame(diff);
                lastMousePos = currentMousePos;
            }
        } else {
            if (isMovingCamera) {
                isMovingCamera = false;
            }
        }
    }

    auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
    auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();

    auto viewportWidth = viewportMaxRegion.x - viewportMinRegion.x;
    auto viewportHeight = viewportMaxRegion.y - viewportMinRegion.y;

    float aspect = viewportWidth / viewportHeight;
    float h = orthographicSize / 2;
    float w = aspect * h;
    projection = glm::ortho(cameraCenter.x - w, cameraCenter.x + w,
                            cameraCenter.y - h, cameraCenter.y + h);

    Draw::Begin();
    Draw::SetupImGuiViewport();
    Draw::SetCamera(projection);
    Draw();
    Draw::End();
    ImGui::End();
    ImGui::PopStyleColor();

    DrawGUI();
}