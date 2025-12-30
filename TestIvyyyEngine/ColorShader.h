#pragma once

#include "IvyyyMeshMaterial.h"

using namespace Ivyyy;

class ColorShader : public MeshMaterial
{
public:
	ColorShader();
	bool CopyShaderParameters(ID3D11DeviceContext* deviceContext, const MeshMaterial::GlobalShaderParameters& shaderData) const override;
	bool InitShaderRessources(ID3D11Device* device) override;

protected:
	void ShutdownShaderRessources() override;

private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};

	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};
};

