#pragma once

#include "IvyyyColor.h"
#include "IvyyyMeshMaterial.h"

using namespace Ivyyy;

class ColorMaterial : public MeshMaterial
{
//Defines
	struct LightBufferType
	{
		XMFLOAT4 albedo;
		XMFLOAT4 diffuseColor;
		XMFLOAT3 lightDirection;
		float padding;  // Added extra padding so structure is a multiple of 16 for CreateBuffer function requirements.
	};

	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 uv;
		XMFLOAT3 normal;
	};
//Variables
private:
	ID3D11Buffer* m_lightBuffer{ 0 };
	bool m_init = false;
	Color m_color = Color::White;

//Methods
public:
	ColorMaterial();
	bool CopyShaderParameters(ID3D11DeviceContext* deviceContext, const GlobalRenderData& globalRenderData, const MeshRenderData& meshRenderData) const override;
	bool InitShaderRessources(ID3D11Device* device) override;

	void SetColor (Color color) {m_color = color;}
	Color GetColor() const {return m_color;}
protected:
	void ShutdownShaderRessources() override;
};

