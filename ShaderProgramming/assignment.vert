#version 330 

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inTexCoord;

out vec2 vTexCoord;

uniform float uTime;
uniform mat4 uMVP;

void main()
{
    float offset = uTime;
    gl_Position = uMVP * vec4(inPosition.x, inPosition.y, inPosition.z, 1.0);   
    vTexCoord = inTexCoord;
}
