
//Request GLSL 3.3
#version 330

//Input attribute
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inTexCoord;
out vec3 vTexCoord;

uniform float uTime;
uniform mat4 uMVP;

void main()
{
	float offset = sin (uTime);
	gl_Position = uMVP * vec4 (inPosition.x, inPosition.y + offset, inPosition.z, 1.0);
	vTexCoord = inTexCoord;
}