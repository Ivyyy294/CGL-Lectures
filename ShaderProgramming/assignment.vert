#version 330 
#define M_PI 3.1415926535897932384626433832795

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inTexCoord;

out vec3 worldPos;
out vec3 normal;

uniform float uTime;
uniform mat4 uMVP;

const int waveCount = 14;

//wave definition
//Wave = vec4 (dir.x, dir.z, steepness, wavelength)
const vec4 waves[waveCount] = vec4[](
    vec4( 0.623f,  0.782f, 0.07f, 2.5f),
    vec4(-0.951f,  0.309f, 0.05f, 3.0f),
    vec4( 0.174f, -0.985f, 0.08f, 2.8f),
    vec4(-0.707f, -0.707f, 0.06f, 3.5f),
    vec4( 0.342f,  0.940f, 0.07f, 2.3f),
    vec4(-0.500f,  0.866f, 0.08f, 2.9f),
    vec4( 0.939f, -0.342f, 0.06f, 3.2f),

    // --- Medium waves ---
    vec4( 0.707f,  0.707f, 0.10f, 8.0f),
    vec4(-0.866f,  0.500f, 0.12f, 10.5f),
    vec4( 0.000f, -1.000f, 0.10f, 6.7f),
    vec4( 0.500f,  0.866f, 0.11f, 12.0f),

    // --- Large swells ---
    vec4( 0.984f,  0.173f, 0.08f, 60.0f),
    vec4( 0.996f,  0.087f, 0.07f, 80.0f),
    vec4( 0.939f,  0.342f, 0.07f, 45.0f)
);

//Wave = dir.x, dir.z, steepness, wavelength
vec3 GerstnerWave (vec4 wave, vec3 p, inout vec3 tangent, inout vec3 binormal)
{
	float steepness = wave.z;
	float waveLength = wave.w;

	float k = 2.0f * M_PI / waveLength;
	float c = sqrt(9.8 / k);
	vec2 d = normalize (wave.xy);
	vec2 posXZ = vec2 (p.x, p.z);
    float f = k * (dot (d, posXZ) + c * uTime);
	float a = steepness / k;

	vec3 offset;
	offset.x = d.x * (a * cos (f));
	offset.y = a * sin (f);
	offset.z = d.y * (a * cos(f));

	tangent += vec3(
				-d.x * d.x * (steepness * sin(f)),
				d.x * (steepness * cos(f)),
				-d.x * d.y * (steepness * sin(f))
			);
	binormal += vec3(
		-d.x * d.y * (steepness * sin(f)),
		d.y * (steepness * cos(f)),
		-d.y * d.y * (steepness * sin(f))
	);

	return offset;
}

void main()
{
	worldPos = inPosition;

	vec3 tangent = vec3(1.0f, 0.0f, 0.0f);
	vec3 binormal = vec3(0.0f, 0.0f, 1.0f);

	vec3 waveOffset = vec3(0.0f);
	
	for (int i = 0; i < waveCount; ++i)
		waveOffset += GerstnerWave (waves[i], inPosition, tangent, binormal);

	normal = normalize(cross(binormal, tangent));

	vec3 newPos = inPosition + waveOffset;
    gl_Position = uMVP * vec4 (newPos, 1.0f);
}
