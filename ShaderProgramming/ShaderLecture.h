#pragma once          // Ensures this header is only included once
#define GLEW_STATIC   // Link against the static version of GLEW

#include <GL/glew.h>   // Loads modern OpenGL functions
#include <GLFW/glfw3.h>// For creating a window and handling input
#include "Shader.h"    // Manages compiling and using GLSL shaders

class ShaderLecture
{
public:
    // Stores window dimensions and title
    ShaderLecture(int width, int height, const std::string& title);

    // Sets up the window, OpenGL, and loads the shader
    bool Initialize(const std::string& vertexShaderToLoad, const std::string& fragmentShaderToLoad);

    // Renders repeatedly until the window is closed
    void Run();

    // Cleans up on destruction
    ~ShaderLecture();

private:
    // Creates the GLFW window and context
    bool InitWindow();

    // Creates a simple 3D quad in a vertex buffer
    void InitQuad();

    // Main loop for drawing and polling events
    void RenderLoop();

    // Frees resources and destroys the window
    void CleanUp();

    int mWidth;
    int mHeight;
    std::string mWindowTitle;
    GLFWwindow* mWindow;

    Shader mShader;   // Our custom Shader

    GLuint mIndexCount;
    GLuint mVAO;
    GLuint mVBO;
    GLuint mEBO;

    bool useFullWindowQuad = true;
};
