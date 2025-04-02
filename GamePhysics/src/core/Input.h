#pragma once

#include <glm/vec2.hpp>

namespace Input {

// Returns the mouse position in world coordinates.
glm::vec2 GetMousePos();
// Returns the mouse position in imgui window coordinates.
glm::vec2 GetMousePosInWindow();
// Returns true if the mouse button is currently pressed.
bool IsMouseDown(int mouseButton);
// Returns true if the mouse button was pressed this frame.
bool IsMouseClicked(int mouseButton);
// Returns true if the mouse button was released this frame.
bool IsMouseReleased(int mouseButton);

} // namespace Input