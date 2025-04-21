#pragma once          // Ensures this header is only included once
#define GLEW_STATIC   // Link against the static version of GLEW

#include <GL/glew.h>   // Loads modern OpenGL functions
#include <GLFW/glfw3.h>// For creating a window and handling input
#include <stb_image.h>
#include "Shader.h"    // Manages compiling and using GLSL shaders

class ShaderLecture2
{
public:
    // Stores window dimensions and title
    ShaderLecture2(int width, int height, const std::string& title);

    // Sets up the window, OpenGL, and loads the shader
    bool Initialize(const std::string& vertexShaderToLoad, const std::string& fragmentShaderToLoad, int meshWidth, int meshHeight, const std::string& textureToLoad);

    // Renders repeatedly until the window is closed
    void Run();

    // Cleans up on destruction
    ~ShaderLecture2();

private:
    // Creates the GLFW window and context
    bool InitWindow();

    // Creates a simple 3D quad in a vertex buffer
    void InitQuad(int meshWidth, int meshHeight);

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

    bool useFullWindowQuad = false;

    GLint mTimeUniformLoc;
    GLint mTextureLoc;

	 GLint mFlagParameterWidthLoc;
	 GLint mFlagParameterLengthLoc;

	 GLint mWindParameterSpeedLoc;
	 GLint mWindParameterStrengthLoc;

    unsigned int texture;

	 struct FlagParameter
	 {
		float m_width = 0.0f;
		float m_length = 0.0f;
	 } mFlagParameter;

	 struct WindParameter
	 {
		 float m_speed = 6.0f;
		 float m_strength = 1.0f;
	 } mWindParameter;
};
