#pragma once          // Ensures this header is only included once
#define GLEW_STATIC   // Link against the static version of GLEW

#include <GL/glew.h>   // Loads modern OpenGL functions
#include <GLFW/glfw3.h>// For creating a window and handling input
#include <stb_image.h>
#include "Shader.h"    // Manages compiling and using GLSL shaders
#include <glm/glm.hpp>

class PracticalAssignment
{
public:
    // Stores window dimensions and title
    PracticalAssignment(int width, int height, const std::string& title);

    // Sets up the window, OpenGL, and loads the shader
    bool Initialize(const std::string& vertexShaderToLoad, const std::string& fragmentShaderToLoad, int meshWidth, int meshHeight, const std::string& textureToLoad);
    void InitializeScene(const glm::vec3& objectPosition, const glm::vec3& cameraPosition);

    // Renders repeatedly until the window is closed
    void Run();

    // Cleans up on destruction
    ~PracticalAssignment();

private:
    // Creates the GLFW window and context
    bool InitWindow();

    // Creates a simple 3D quad in a vertex buffer
    void InitQuad(int meshWidth, int meshHeight);

    // Main loop for drawing and polling events
    void RenderLoop();

    // Frees resources and destroys the window
    void CleanUp();

    void ObjectPositionUpdated();


    int mWidth;
    int mHeight;
    std::string mWindowTitle;
    GLFWwindow* mWindow;

    Shader mShader;   // Our custom Shader

    GLuint mIndexCount;
    GLuint mVAO;
    GLuint mVBO;
    GLuint mEBO;

    bool useFullWindowQuad = false;

    GLint mTimeUniformLoc;
    GLint mTextureLoc;

    glm::vec3 mObjectPosition;
    glm::vec3 mCameraPosition;
    glm::mat4 mModel;
    glm::mat4 mView;
    glm::mat4 mProjection;

    GLint mMvpLoc;

    unsigned int texture;
};
