
//Request GLSL 3.3
#version 330

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inTexCoord;

uniform float uTime;

uniform struct FlagParameter
{
	float m_width;
	float m_length;
} mFlagParameter;

uniform struct WindParameter
{
	float m_speed;
	float m_strength;
	int m_windSimLayer;
} mWindParameter;

//Input attribute
out vec2 displacement;
out vec3 outPosition;
out vec2 vTexCoord;

vec2 CalculateNormPos ()
{
	vec2 normPos;
	float xOffset = mFlagParameter.m_length * 0.5f;
	float yOffset = mFlagParameter.m_width * 0.5f;

	normPos.x = (inPosition.x + xOffset) / (xOffset * 2.0f);
	normPos.y = (inPosition.y + yOffset) / mFlagParameter.m_width;
	return normPos;
}

vec2 GetWindOffset ()
{
	vec2 normPos = CalculateNormPos();

	float amplitude = mWindParameter.m_strength * 0.5f;
	float speed = mWindParameter.m_speed;
	float frequency = speed * 2.0f;
	float incline = speed * 0.05f;

	vec2 offset;
	offset.x = 0.0f;
	offset.y = 0.0f;

	float frequencyY = normPos.x * frequency + uTime * speed;
	float amplitudeY = 0.1f * amplitude * normPos.x;

	float frequencyX = normPos.y * frequency + uTime * speed;
	float amplitudeX = 0.05f * amplitude * normPos.x;

	float offsetFrequency = 1.0f + (1.0f / speed);

	for (int i = 0; i < mWindParameter.m_windSimLayer; ++i)
	{
		//Y axis
		offset.y += sin (frequencyY) * amplitudeY;
		frequencyY *= offsetFrequency;
		amplitudeY *= 0.5f;
		
		//X axis
		offset.x += cos (frequencyX) * amplitudeX;
		frequencyX *= offsetFrequency;
		amplitudeX *= 0.5f;
	}
	
	//Incline
	offset.x += incline * sin (1.0f - normPos.y);

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