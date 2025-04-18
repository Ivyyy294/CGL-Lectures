#define STB_IMAGE_IMPLEMENTATION


#include "ShaderLecture2.h"
#include <vector>
#include <glm/glm.hpp>

// Store initial window data
ShaderLecture2::ShaderLecture2(int width, int height, const std::string& title)
    : mWidth(width)
    , mHeight(height)
    , mWindowTitle(title)
    , mWindow(nullptr)
    , mVAO(0)
    , mVBO(0)
    , mEBO(0)
    , mIndexCount(0)
    , texture(0)
    , mTimeUniformLoc(-1)
    , mTextureLoc(-1)
{
}

bool ShaderLecture2::Initialize(const std::string& vertexShaderToLoad, const std::string& fragmentShaderToLoad, int meshWidth, int meshHeight, const std::string& textureToLoad)
{
    // 1) Create a GLFW window
    if (!InitWindow())
    {
        return false;
    }

    std::cout << "Initialized GLFW Window." << std::endl;

    // 2) Load OpenGL functions via GLEW
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Error: Failed to initialize GLEW!" << std::endl;
        return false;
    }

    std::cout << "Initialized GLEW." << std::endl;

    // Set the render area
    glViewport(0, 0, mWidth, mHeight);

    // 3) Load the vertex/fragment shaders
    if (!mShader.Load(vertexShaderToLoad, fragmentShaderToLoad))
    {
        std::cerr << "Error: Failed to load/compile the shader!" << std::endl;
        return false;
    }

    std::cout << "Loaded Shaders." << std::endl;

    // 4) Get the reference to the uTime uniform in the shader
    mShader.SetActive();
    mTimeUniformLoc = mShader.GetUniformLocationByString("uTime");
    mTextureLoc = mShader.GetUniformLocationByString("uTexture");
	 mAnchorXPosLoc = mShader.GetUniformLocationByString("uAnchorXPos");
	 mFlagWidthLoc = mShader.GetUniformLocationByString("mFlagWidth");

    std::cout << "Identified Uniforms." << std::endl;

    // 5) Load and create a texture
     // load and create a texture 
    // -------------------------
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    
    unsigned char* data = stbi_load(textureToLoad.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    std::cout << "Loaded Texture." << std::endl;

    // 6) Prepare the geometry (a simple 3D quad)
    InitQuad(meshWidth, meshHeight);

    std::cout << "Initialized Mesh." << std::endl;

    return true;
}

void ShaderLecture2::Run()
{
    // Enter the main loop
    RenderLoop();
}

ShaderLecture2::~ShaderLecture2()
{
    // Clean up on destruction
    CleanUp();
}

bool ShaderLecture2::InitWindow()
{
    if (!glfwInit())
    {
        std::cerr << "Error: GLFW initialization failed!" << std::endl;
        return false;
    }

    // Specify OpenGL 3.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window
    mWindow = glfwCreateWindow(mWidth, mHeight, mWindowTitle.c_str(), nullptr, nullptr);
    if (!mWindow)
    {
        std::cerr << "Error: Failed to create window!" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(mWindow);
    return true;
}

void ShaderLecture2::InitQuad(int meshWidth, int meshHeight)
{
    std::vector<float> vertices;
    vertices.reserve(meshWidth * meshHeight * 5);

	 mAnchorXPos = 0.6f;
	 mFlagWidth = 0.8f;
    glm::vec3 upperLeft(-mAnchorXPos, mFlagWidth * 0.5f, 0.0f);
    glm::vec3 lowerRight(mAnchorXPos, -mFlagWidth * 0.5f, 0.0f);

    for (int row = 0; row < meshHeight; ++row)
    {
        // 'v' in [0..1], increasing top->bottom
        float v = static_cast<float>(row) / static_cast<float>(meshHeight - 1);

        for (int col = 0; col < meshWidth; ++col)
        {
            // 'u' in [0..1], increasing left->right
            float u = static_cast<float>(col) / static_cast<float>(meshWidth - 1);

            // Interpolate in x, y, z
            // (1 - u,v) * upperLeft + (u,v) * lowerRight
            float x = upperLeft.x + u * (lowerRight.x - upperLeft.x);
            float y = upperLeft.y + v * (lowerRight.y - upperLeft.y);
            float z = upperLeft.z + u * (lowerRight.z - upperLeft.z);
            // ^ If you want the plane to tilt in Z as well.
            //   If you want a strictly flat plane at upperLeft.z, use that instead:
            // float z = upperLeft.z;

            // Push back the data
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
            vertices.push_back(u);
            vertices.push_back(v);
        }
    }

    // 2) Generate the indices
    // We'll create two triangles per cell in the grid.
    std::vector<unsigned int> indices;
    indices.reserve((meshWidth - 1) * (meshHeight - 1) * 6);

    for (int row = 0; row < meshHeight - 1; ++row)
    {
        for (int col = 0; col < meshWidth - 1; ++col)
        {
            // Current vertex index
            int current = row * meshWidth + col;
            int right = row * meshWidth + (col + 1);
            int below = (row + 1) * meshWidth + col;
            int belowRight = (row + 1) * meshWidth + (col + 1);

            // Triangle 1: (current, right, belowRight)
            indices.push_back(current);
            indices.push_back(right);
            indices.push_back(belowRight);

            // Triangle 2: (current, belowRight, below)
            indices.push_back(current);
            indices.push_back(belowRight);
            indices.push_back(below);
        }
    }

    // Store how many indices we have
    mIndexCount = static_cast<GLuint>(indices.size());

    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    // Create and fill the Vertex Buffer Object (VBO)
    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Create and fill the Element Buffer Object (EBO) for indices
    glGenBuffers(1, &mEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // We have (x, y, z, u, v) => total of 5 floats
    GLsizei stride = 5 * sizeof(float);

    // Position (location = 0) uses the first 3 floats
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        stride,
        (void*)0
    );

    // UV (location = 1) uses the last 2 floats
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1,
        2,
        GL_FLOAT,
        GL_FALSE,
        stride,
        (void*)(3 * sizeof(float))
    );

    // Unbind the VAO. 
    glBindVertexArray(0);
}


void ShaderLecture2::RenderLoop()
{
    // Keep drawing until the window closes
    while (!glfwWindowShouldClose(mWindow))
    {
        glClearColor(0.095f, 0.095f, 0.095f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Use our shader and draw the quad
        mShader.SetActive();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(mTextureLoc, 0);

        glUniform1f(mTimeUniformLoc, static_cast<float>(glfwGetTime()));
        glUniform1f(mAnchorXPosLoc, mAnchorXPos);
        glUniform1f(mFlagWidthLoc, mFlagWidth);

        glBindVertexArray(mVAO);
        // 6 indices total, of type GL_UNSIGNED_INT
        glDrawElements(GL_TRIANGLES, mIndexCount, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);

        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }
}

void ShaderLecture2::CleanUp()
{
    // Free GPU buffers
    if (mVAO)
    {
        glDeleteVertexArrays(1, &mVAO);
        mVAO = 0;
    }
    if (mVBO)
    {
        glDeleteBuffers(1, &mVBO);
        mVBO = 0;
    }
    if (mEBO)
    {
        glDeleteBuffers(1, &mEBO);
        mEBO = 0;
    }

    // Unload shaders
    mShader.Unload();

    // Destroy the window
    if (mWindow)
    {
        glfwDestroyWindow(mWindow);
        mWindow = nullptr;
    }
    glfwTerminate();
}
