#include "ShaderLecture.h"

// Store initial window data
ShaderLecture::ShaderLecture(int width, int height, const std::string& title)
    : mWidth(width)
    , mHeight(height)
    , mWindowTitle(title)
    , mWindow(nullptr)
    , mVAO(0)
    , mVBO(0)
{
}

bool ShaderLecture::Initialize(const std::string& vertexShaderToLoad, const std::string& fragmentShaderToLoad)
{
    // 1) Create a GLFW window
    if (!InitWindow())
    {
        return false;
    }

    // 2) Load OpenGL functions via GLEW
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Error: Failed to initialize GLEW!" << std::endl;
        return false;
    }

    // Set the render area
    glViewport(0, 0, mWidth, mHeight);

    // 3) Load the vertex/fragment shaders
    if (!mShader.Load(vertexShaderToLoad, fragmentShaderToLoad))
    {
        std::cerr << "Error: Failed to load/compile the shader!" << std::endl;
        return false;
    }

    // 4) Prepare the geometry (a simple 3D quad)
    InitQuad();
    return true;
}

void ShaderLecture::Run()
{
    // Enter the main loop
    RenderLoop();
}

ShaderLecture::~ShaderLecture()
{
    // Clean up on destruction
    CleanUp();
}

bool ShaderLecture::InitWindow()
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

void ShaderLecture::InitQuad()
{
    // 4 unique 3D vertices for a simple square (z = 0)
    float vertices[] = {
        // x,    y,    z
        -0.5f,  0.5f, 0.0f,  // top-left    (index 0)
         0.5f,  0.5f, 0.0f,  // top-right   (index 1)
         0.5f, -0.5f, 0.0f,  // bottom-right(index 2)
        -0.5f, -0.5f, 0.0f   // bottom-left (index 3)
    };

    float verticesFullscreen[] = {
        // x,    y,    z
        -1.0f,  1.0f, 0.0f,  // top-left    (index 0)
         1.0f,  1.0f, 0.0f,  // top-right   (index 1)
         1.0f, -1.0f, 0.0f,  // bottom-right(index 2)
        -1.0f, -1.0f, 0.0f   // bottom-left (index 3)
    };

    // 6 indices form 2 triangles: (0,1,2) and (2,3,0)
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    // Store how many indices we have
    mIndexCount = static_cast<GLuint>(sizeof(indices) / sizeof(indices[0]));

    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    // Create and fill the Vertex Buffer Object (VBO)
    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    
    if (!useFullWindowQuad)
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    else
        glBufferData(GL_ARRAY_BUFFER, sizeof(verticesFullscreen), verticesFullscreen, GL_STATIC_DRAW);

    // Create and fill the Element Buffer Object (EBO) for indices
    glGenBuffers(1, &mEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Tell OpenGL how to interpret the vertex data (3 floats = position)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        5 * sizeof(float),
        (void*)0
    );

	 // Tell OpenGL how to interpret the vertex data (3 floats = position)
	 glEnableVertexAttribArray(1);
	 glVertexAttribPointer(
		 1,
		 2,
		 GL_FLOAT,
		 GL_FALSE,
		 5 * sizeof(float),
		 (void*)(3 * sizeof (float))
	 );

    // Unbind the VAO. 
    glBindVertexArray(0);
}


void ShaderLecture::RenderLoop()
{
    // Keep drawing until the window closes
    while (!glfwWindowShouldClose(mWindow))
    {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Use our shader and draw the quad
        mShader.SetActive();
        glBindVertexArray(mVAO);
        // 6 indices total, of type GL_UNSIGNED_INT
        glDrawElements(GL_TRIANGLES, mIndexCount, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);

        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }
}

void ShaderLecture::CleanUp()
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
