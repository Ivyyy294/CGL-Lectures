
//Request GLSL 3.3
#version 330

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inTexCoord;

//Input attribute
out vec3 outPosition;
out vec2 vTexCoord;

uniform float uTime;

void main()
{
	float norm = (inPosition.x + 0.6) / 1.2f;
	float offset = sin(uTime * 1.5f + inPosition.x * 5.0f) * 0.2f;

	gl_Position = vec4 (inPosition, 1.0);
	gl_Position.y += offset * norm;
	outPosition = inPosition;
	vTexCoord = inTexCoord;
}