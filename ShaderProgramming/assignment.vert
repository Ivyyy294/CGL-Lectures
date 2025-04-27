#version 330 
#define M_PI 3.1415926535897932384626433832795

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inTexCoord;

out vec2 vTexCoord;
out vec3 waveOffset;

uniform float uTime;
uniform mat4 uMVP;

//Wave = dir.x, dir.z, steepness, wavelength
vec3 GerstnerWave (vec4 wave, vec3 p)
{
	float steepness = wave.z;
	float waveLength = wave.w;
	vec2 direction = wave.xy;

	vec2 d = normalize (direction);
	vec2 posXZ = vec2 (p.x, p.z);
	float k = 2.0f * M_PI / waveLength; //Wave number
	float c = sqrt(9.8 / k);
    float f = k * (dot (d, posXZ) + c * uTime);
	float a = steepness / k;

	vec3 offset;
	offset.x += d.x * (a * cos (f));
	offset.y = a * sin (f);
	offset.z += d.y * (a * cos(f));

	return offset;
}

void main()
{
	//Shader parameter
	vec4 wave1 = vec4(1.0f, 0.0f, 0.4f, 30.0f);
	vec4 wave2 = vec4(-0.5f, 0.25f, 0.4f, 10.0f);
	vec4 wave3 = vec4(0.0f, 0.5f, 0.2f, 5.0f);

	waveOffset = GerstnerWave (wave1, inPosition);
	waveOffset += GerstnerWave (wave2, inPosition);
	waveOffset += GerstnerWave (wave3, inPosition);

	vec3 newPos = inPosition + waveOffset;
    gl_Position = uMVP * vec4 (newPos, 1.0f);
    vTexCoord = inTexCoord;
}
