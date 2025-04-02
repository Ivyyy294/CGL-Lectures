# Core library
    file(GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS "**.cpp")
    file(GLOB_RECURSE CORE_HEADERS CONFIGURE_DEPENDS "**.h")

add_library(core STATIC ${CORE_SOURCES} ${CORE_HEADERS})
target_include_directories(core PUBLIC ..)

# Dependencies
include(FetchContent)

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(core ${OPENGL_gl_LIBRARY})

# glm
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0af55ccecd98d4e5a8d1fad7de25ba429d60e863
)
FetchContent_GetProperties(glm)
FetchContent_MakeAvailable(glm)
target_include_directories(core PUBLIC ${glm_SOURCE_DIR})
set_target_properties(glm PROPERTIES FOLDER "Dependencies")

# SDL2
find_package(SDL2 REQUIRED)
target_link_libraries(core SDL2::SDL2 SDL2::SDL2main)

if (WIN32)
  # Copy DLL files on Windows to the target App build folder.
  add_custom_command(TARGET core POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:SDL2::SDL2>
    ${SDL_DLL_TARGET_DIR}/SDL2.dll)
endif ()

# Dear ImGui
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG 790f2b9a7aa2a23a2fb47ed8f48293f27c3ac658 # latest commit on docking branch
)
FetchContent_MakeAvailable(imgui)
set(IMGUI_INCLUDE_DIR ${imgui_SOURCE_DIR}/)
file(GLOB IMGUI_SOURCES ${imgui_SOURCE_DIR}/*.cpp)
file(GLOB IMGUI_HEADERS ${imgui_SOURCE_DIR}/*.h)
add_library(imgui STATIC
    ${IMGUI_SOURCES}
    ${IMGUI_HEADERS}
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.h ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.h ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC ${IMGUI_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})
target_link_libraries(imgui ${OPENGL_LIBRARIES} SDL2::SDL2)
set_target_properties(imgui PROPERTIES FOLDER "Dependencies")

target_link_libraries(core imgui)

# ImGuizmo
FetchContent_Declare(
    imguizmo
    GIT_REPOSITORY https://github.com/CedricGuillemet/ImGuizmo.git
    GIT_TAG b10e91756d32395f5c1fefd417899b657ed7cb88
)
FetchContent_MakeAvailable(imguizmo)
set(imguizmo_INCLUDE_DIR ${imguizmo_SOURCE_DIR}/)
file(GLOB imguizmo_SOURCES ${imguizmo_SOURCE_DIR}/*.cpp)
file(GLOB imguizmo_HEADERS ${imguizmo_SOURCE_DIR}/*.h)
add_library(imguizmo STATIC
    ${imguizmo_SOURCES}
    ${imguizmo_HEADERS}
)

target_include_directories(imguizmo PUBLIC ${imguizmo_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})
target_link_libraries(imguizmo imgui)
set_target_properties(imguizmo PROPERTIES FOLDER "Dependencies")

target_link_libraries(core imguizmo)
