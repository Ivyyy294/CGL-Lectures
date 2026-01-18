#pragma once

#include "IvyyyMeshMaterial.h"

using namespace Ivyyy;

class GridMaterial : public MeshMaterial
{
//Variables
private:
	bool m_initDone = false;
	ID3D11SamplerState* m_sampleState{ 0 };
//Methods
public:
	GridMaterial();
	bool InitShaderRessources(ID3D11Device* device) override;
	bool CopyShaderParameters(ID3D11DeviceContext* deviceContext, const GlobalRenderData& globalRenderData, const MeshRenderData& meshRenderData) const override;

protected:
	void ShutdownShaderRessources() override;

private:
	HRESULT CreateInputLayout (ID3D11Device* device);
	HRESULT CreateMatrixBuffer (ID3D11Device* device);
	HRESULT CopyMatrixBuffer (ID3D11DeviceContext* deviceContext, const GlobalRenderData& globalRenderData, const MeshRenderData& meshRenderData) const;
};

