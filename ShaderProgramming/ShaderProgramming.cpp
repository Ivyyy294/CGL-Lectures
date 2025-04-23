// ShaderProgramming.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "glm.hpp"
#include "ShaderLecture3.h"
//#include "ShaderLecture2.h"

int main()
{
    ShaderLecture3 lectureApp (800, 800, "Shader Programming Session 3");

	 if (!lectureApp.Initialize ("matrix.vert", "matrix.frag", 20, 20, "PrideTexture.jpg"))
		return 1;

	lectureApp.InitializeScene (glm::vec3(0.0f, 5.0f, 4.0f), glm::vec3 (0.0f, 0.0f, -2.0f));

	lectureApp.Run();

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
