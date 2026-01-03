/////////////
// GLOBALS //
/////////////
cbuffer MatrixBuffer
{
	 matrix worldMatrix;
	 matrix viewMatrix;
	 matrix projectionMatrix;
	 float3 scale;
};

//////////////
// TYPEDEFS //
//////////////
struct VertexInputType
{
	float4 position : POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 wPos : TEXCOORD1;
	float3 normal : NORMAL;
};

PixelInputType main(VertexInputType input)
{
	PixelInputType output;

	// Change the position vector to be 4 units for proper matrix calculations.
	input.position.w = 1.0f;
	output.wPos = input.position.xyz * scale;

	// Calculate the position of the vertex against the world, view, and projection matrices.
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	// Store the color the pixel shader.
	output.tex = input.tex;


	// Calculate the normal vector against the world matrix only.
	//mul(input.normal, (float3x3)worldMatrix);
	output.normal = input.normal;

	// Normalize the normal vector.
	output.normal = normalize(output.normal);

	return output;
}