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

vec3 GetSpecularColor(vec3 specularColor, float smoothness)
{
	vec3 viewDir = normalize (camPos - worldPos);
	vec3 halfVector = normalize(lightDirection + viewDir);
	vec3 specularLightIntesity = lightColor * pow(DotClamped(halfVector, normal), smoothness);
	vec3 specular = specularColor * specularLightIntesity;
	return specular;
}

void main()
{
	//Diffuse
	vec3 diffuseColor = GetDiffuseColor();

	//Specular white
	vec3 specular1 = GetSpecularColor(waterSpecular,  smootness * 1000.0f);

	//Specular turquoise 
	vec3 specular2 = GetSpecularColor(waterSpecular2,  smootness * 200.0f);

	outColor = vec4 (Saturate(diffuseColor + specular1 + specular2), 1.0f);
}