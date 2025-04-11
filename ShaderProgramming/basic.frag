
//Request GLSL 3.3
#version 330

in vec3 outPosition;
out vec4 outColor;

vec4 Pattern1 (vec3 pos)
{
	if (pos.x < 0.0)
		return vec4 (pos.x * - 1.0, 0.0, 0.0, 1.0);
	else
		return vec4 (0.0, pos.x, 0.0, 1.0);
}

vec4 Pattern2 (vec3 pos)
{
	float c = (sin (pos.x * 20) + 1 ) * 0.5;

	return vec4 (c, c, 0.0, 1.0);
}

vec4 Pattern3 (vec3 pos)
{
	float distance = length(pos);

	return vec4 (1 - distance, 0.0, 0.0, 1.0);
}

vec4 Pattern4 (vec3 pos)
{
	float distance = length(pos);
	float r = distance * (sin (pos.x * 20) + 1 ) * 0.5;
	float g = distance * (sin (pos.y * 20) + 1 ) * 0.5;

	return vec4 (r, g, 0.0, 1.0);
}

void main()
{
//-1 + 1
int patternAnzX = 3;
int patternAnzY = 2;
float patternFractionX = 1.0 / patternAnzX;
float patternFractionY = 1.0 / patternAnzY;

vec3 virtualPos = outPosition;

float normalizedPosX = (outPosition.x + 1) * 0.5;
float normalizedPosY = (outPosition.y + 1) * 0.5;

float pattern = normalizedPosX / patternFractionX;// + ((1 - normalizedPosY) / patternFractionY) * patternAnzX;

//Normalize to virtual rect
normalizedPosX = mod (normalizedPosX, patternFractionX) / patternFractionX;
normalizedPosY = mod (normalizedPosY, patternFractionY) / patternFractionY;

virtualPos.x = (normalizedPosX * 2.0) -1.0;
virtualPos.y = (normalizedPosY * 2.0) -1.0;

if (pattern <= 1.0)
	outColor = Pattern1(virtualPos);
else if (pattern <= 2.0)
	outColor = Pattern2(virtualPos);
else if (pattern <= 3.0)
	outColor = Pattern3(virtualPos);
else if (pattern <= 4.0)
	outColor = Pattern4(virtualPos);
}

