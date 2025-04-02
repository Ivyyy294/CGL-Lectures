cmake_minimum_required(VERSION 3.20)

set(NAME "GamePhysics")
project(${NAME})

set(CMAKE_CXX_STANDARD 11)

# Include all files inside the scenes folder in the build.
file(GLOB_RECURSE SCENE_SOURCES CONFIGURE_DEPENDS "src/scenes/**.cpp" "src/scenes/**.h")
file(GLOB_RECURSE OBJECTS_SOURCES  CONFIGURE_DEPENDS "src/objects/**.cpp" "src/scenes/**.h")
# Create a filter in Visual Studio for all files in the scenes folder.
source_group("scenes" FILES ${SCENE_SOURCES})
source_group("objects" FILES ${OBJECTS_SOURCES})

# All files to be build have to be added here.
add_executable(${NAME} src/main.cpp ${SCENE_SOURCES} ${OBJECTS_SOURCES})

target_include_directories(${NAME} PRIVATE src)

# Set as the initial startup project.
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${NAME})

# Enable folders in Visual Studio.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Copy assets to the build dir.
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(SDL_DLL_TARGET_DIR $<TARGET_FILE_DIR:${NAME}>)

# Include configuration for the core library.
add_subdirectory(src/core)

target_link_libraries(${NAME} core)