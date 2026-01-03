struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 wPos : TEXCOORD1;
	float3 normal : NORMAL;
};

bool IsLine(float3 wPos, float3 normal, float spacing, float weight)
{
	float xVal = wPos.x % spacing;
	float yVal = wPos.y % spacing;
	float zVal = wPos.z % spacing;

	if (normal.x == 0.f && normal.z == 0.f)
	{
		if (abs(xVal) > weight && abs(zVal) > weight)
			return float4(0.f, 0.f, 0.f, 0.f);

		return float4(1.f, 1.f, 1.f, 1.f);
	}
	else if (normal.y == 0.f && normal.z == 0.f)
	{
		if (abs(yVal) > weight && abs(zVal) > weight)
			return float4(0.f, 0.f, 0.f, 0.f);

		return float4(1.f, 1.f, 1.f, 1.f);
	}
	else if (normal.x == 0.f && normal.y == 0.f)
	{
		if (abs(xVal) > weight && abs(yVal) > weight)
			return float4(0.f, 0.f, 0.f, 0.f);

		return float4(1.f, 1.f, 1.f, 1.f);
	}

	return float4(0.f, 0.f, 0.f, 0.f);
}

float4 main(PixelInputType input) : SV_TARGET
{
	float4 bgColor = float4 (0.f, 0.f, 0.f, 0.f);
	float4 lineColor = float4 (1.f, 1.f, 1.f, 1.f);

	float weight1 = 0.02f;
	float spacing1 = 1.f;

	float weight2 = 0.015f;
	float spacing2 = 0.5f;

	float weightBorder = 0.025f * 0.1f;

	if (input.tex.x > 1.f - weightBorder || input.tex.y > 1.f - weightBorder
	|| input.tex.x < weightBorder || input.tex.y < weightBorder)
		return lineColor;

	if (IsLine(input.wPos, input.normal, spacing1, weight1))
		return lineColor * 0.8f;

	if (IsLine(input.wPos, input.normal, spacing2, weight1))
		return lineColor * 0.25f;

	return bgColor;
}