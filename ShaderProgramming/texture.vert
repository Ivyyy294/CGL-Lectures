
//Request GLSL 3.3
#version 330

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inTexCoord;

uniform float uTime;

uniform struct FlagParameter
{
	float width;
	float length;
} mFlagParameter;

uniform struct WindParameter
{
	float speed;
	float strength;
} mWindParameter;

//Input attribute
out vec3 outPosition;
out vec2 vTexCoord;

vec2 CalculateNormPos ()
{
	vec2 normPos;
	float xOffset = mFlagParameter.length * 0.5f;
	float yOffset = mFlagParameter.width * 0.5f;

	normPos.x = (inPosition.x + xOffset) / (xOffset * 2.0f);
	normPos.y = (inPosition.y + yOffset) / mFlagParameter.width;
	return normPos;
}

vec2 GetWindOffset ()
{
	vec2 normPos = CalculateNormPos();

	float amplitude = mWindParameter.strength * 0.5f;
	float speed = mWindParameter.speed;
	float frequency = speed * 2f;
	float incline = speed * 0.1f;

	vec2 offset;
	offset.x = 0.0f;

	//Y axis
	float frequencyY = normPos.x * frequency + uTime * speed;
	float amplitudeY = 0.1f * amplitude * normPos.x;
	offset.y = sin (frequencyY) * amplitudeY;
	
	//X axis
	float frequencyX = normPos.y * frequency + uTime * speed;
	float amplitudeX = 0.05f * amplitude * normPos.x;
	offset.x = cos (frequencyX) * amplitudeX;

	//Incline
	offset.x += incline * cos (inPosition.y) - incline + (incline * -0.1f * normPos.y);

	return offset;
}

void main()
{
	CalculateNormPos();

	vec2 windOffset = GetWindOffset();

	gl_Position = vec4 (inPosition, 1.0);
	gl_Position.x += windOffset.x;
	gl_Position.y += windOffset.y;

	outPosition = inPosition;
	vTexCoord = inTexCoord;
}