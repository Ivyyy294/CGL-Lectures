// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

// Source: Madhav, Sanjay. 2018. Game Programming in C++: Creating 3D Games. Boston, MA, p. 142.


#pragma once

#include <iostream>
#include <GL/glew.h>


class Shader
{
public:
	Shader();
	~Shader();
	//Load the vertex/fragment shader with the given names
	bool Load(const std::string& vertName,
			  const std::string& fragName);
	void Unload();
	//Sets this as the active shader program
	void SetActive();

	GLuint GetUniformLocationByString(const std::string& uniformName);


private:
	//Tries to compile the specified shader
	bool CompileShader(const std::string& filename,
		GLenum shaderType, GLuint& outShader);
	//Tests whether shader compiled succesfully
	bool IsCompiled(GLuint shader);
	//Tests whether vertex/fragment program link
	bool IsValidProgram();

	//Store the shader object IDs
	GLuint mVertexShader;
	GLuint mFragShader;
	GLuint mShaderProgram;
};