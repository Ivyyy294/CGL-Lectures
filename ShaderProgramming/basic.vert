
//Request GLSL 3.3
#version 330



//Input attribute
in vec3 inPosition;
out vec3 outPosition;

void main()
{
	gl_Position = vec4 (inPosition, 1.0);
	outPosition = inPosition;
}