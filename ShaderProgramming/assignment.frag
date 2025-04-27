#version 330 

in vec2 vTexCoord;
in vec3 worldPos;;
in vec3 normal;
in float waveHeight;

out vec4 outColor; 

uniform sampler2D uTexture;

float DotClamped (vec3 a, vec3 b)
{
	return clamp (dot(a, b), 0.0f, 1.0f);
}

void main()
{
	vec3 camPos = vec3 (0.0f, 10.0f, -10.0f);
	vec3 sunDirection = normalize (vec3 (0.5f, 1.0f, 0.5f));
	vec3 sunColor = vec3 (1.0f, 1.0f, 0.95f);
	vec3 waterColor = vec3 (0.0f, 0.4f, 0.7f);
	float smootness = 0.4f;

	vec3 diffuseColor = waterColor * sunColor * DotClamped(sunDirection, normal);

	vec3 viewDir = normalize (camPos - worldPos);
	vec3 halfVector = normalize(sunDirection + viewDir);
	vec3 specular = sunColor * pow(DotClamped(halfVector, normal), smootness * 100.0f);

	outColor = clamp(vec4(diffuseColor + specular, 1.0f), vec4(0.0f), vec4(1.0f));
}