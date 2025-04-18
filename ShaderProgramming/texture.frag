
//Request GLSL 3.3
#version 330

in vec2 windOffset;
in vec2 vTexCoord;
out vec4 outColor;

uniform sampler2D uTexture;

void main()
{
	outColor = texture(uTexture, vTexCoord);

	//if (windOffset.y < 0.0f)
	//{
	//	float factor = sin(-windOffset.y * 5.0f);
	//	outColor.r -= outColor.r * factor;
	//	outColor.g -= outColor.g * factor;
	//	outColor.b -= outColor.b * factor;
	//}
}

