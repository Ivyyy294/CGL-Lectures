//Practical Assignment for Shader Lecture
//Your name and matricle number here

#include <iostream>
#include "PracticalAssignment.h"

int main()
{
    PracticalAssignment assignment(800, 800, "Shader Programming - Assignment - Lara Gülpen");

    if (!assignment.Initialize("assignment.vert", "assignment.frag", 200, 200, "grid.jpg"))
    {
        return 1; // Initialization failed
    }

    assignment.InitializeScene(
        glm::vec3(0.0f, 0.0f, 0.0f),   
        glm::vec3(0.0f, 10.0f, -20.0f)   
    );

    assignment.Run();

    return 0;
}
