
//Request GLSL 3.3
#version 330

in vec3 vTexCoord;
out vec4 outColor;

void main()
{
	outColor = vec4 (vTexCoord, 1.0f);
}

