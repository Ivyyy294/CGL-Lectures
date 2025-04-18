
//Request GLSL 3.3
#version 330

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inTexCoord;

//Input attribute
out vec3 outPosition;
out vec2 vTexCoord;
out vec2 windOffset;

uniform float uTime;
uniform float uAnchorXPos;
uniform float mFlagWidth;

float normPosX;
float normPosY;

void CalculateNormPos()
{
	normPosX = (inPosition.x + uAnchorXPos) / (uAnchorXPos * 2.0f);
	normPosY = (inPosition.y + mFlagWidth * 0.5f) / mFlagWidth;
}

vec2 GetWindOffset ()
{
	float amplitude = 0.5f;
	float speed = 5f;
	float frequency = speed * 2f;
	float incline = speed * 0.1f;

	vec2 offset;
	offset.x = 0.0f;

	//Y axis
	float frequencyY = normPosX * frequency + uTime * speed;
	float amplitudeY = 0.1f * amplitude * normPosX;
	offset.y = sin (frequencyY) * amplitudeY;
	
	//X axis
	float frequencyX = normPosY * frequency + uTime * speed;
	float amplitudeX = 0.05f * amplitude * normPosX;
	offset.x = cos (frequencyX) * amplitudeX;

	//Incline
	offset.x += incline * cos (inPosition.y) - incline + (incline * -0.1f * normPosY);

	return offset;
}

void main()
{
	CalculateNormPos();

	windOffset = GetWindOffset();

	gl_Position = vec4 (inPosition, 1.0);
	gl_Position.x += windOffset.x;
	gl_Position.y += windOffset.y;

	outPosition = inPosition;
	vTexCoord = inTexCoord;
}