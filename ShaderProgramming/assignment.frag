#version 330 

in vec3 worldPos;
in vec3 normal;

out vec4 outColor;

//Unused
uniform sampler2D uTexture;

//light settings
const vec3 lightColor = vec3 (1.0f, 1.0f, 1.0f);
const vec3 lightDirection = normalize (vec3 (-0.5f, 1.0f, 1.5f));

//cam pos
const vec3 camPos = vec3 (0.0f, 10.0f, -10.0f);

//water settigns
const vec3 waterColor = vec3 (0.0f, 0.7f, 0.95f);
const vec3 waterSpecular = vec3 (0.95f, 1.0f, 1.0f);
const vec3 waterSpecular2 = vec3 (0.8f, 0.9f, 0.95f);
const float smootness = 0.3f;

vec3 Saturate (vec3 a)
{
	return clamp (a, vec3 (0.0f), vec3 (1.0f));
}

float DotClamped (vec3 a, vec3 b)
{
	return clamp (dot(a, b), 0.0f, 1.0f);
}

vec3 EnergyConservationBetweenDiffuseAndSpecular (vec3 albedo, vec3 specColor)
{
	float specularStrength = max(specColor.r, max(specColor.g, specColor.b));
	float oneMinusReflectivity = 1.0f - specularStrength;
	return albedo * (vec3(1.0f, 1.0f, 1.0f) - oneMinusReflectivity);
}

vec3 GetDiffuseColor()
{
	vec3 albedo = EnergyConservationBetweenDiffuseAndSpecular (waterColor, waterSpecular);
	vec3 diffuseLightIntesity = lightColor * DotClamped(lightDirection, normal);
	vec3 diffuseColor = Saturate (albedo * diffuseLightIntesity);
	return diffuseColor;
}

vec3 GetSpecularColor()
{
	vec3 viewDir = normalize (camPos - worldPos);
	vec3 halfVector = normalize(lightDirection + viewDir);
	vec3 specularLightIntesity1 = lightColor * pow(DotClamped(halfVector, normal), smootness * 1000.0f);
	vec3 specularLightIntesity2 = lightColor * pow(DotClamped(halfVector, normal), smootness * 200.0f);
	vec3 specular = Saturate (waterSpecular * specularLightIntesity1 + waterSpecular2 * specularLightIntesity2);
	return specular;
}

void main()
{
	//Diffuse
	vec3 diffuseColor = GetDiffuseColor();

	//Specular
	vec3 specular = GetSpecularColor();

	outColor = vec4 (Saturate(diffuseColor + specular), 1.0f);
}