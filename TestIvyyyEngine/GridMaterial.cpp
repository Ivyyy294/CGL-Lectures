#include "GridMaterial.h"

struct MatrixBufferType
{
	XMMATRIX world;
	XMMATRIX view;
	XMMATRIX projection;
	XMFLOAT3 scale;
};

GridMaterial::GridMaterial()
	: MeshMaterial (L"GridVS.hlsl", L"GridPS.hlsl")
{
}

bool GridMaterial::InitShaderRessources(ID3D11Device* device)
{
	if (m_initDone)
		return true;

	HRESULT result = CreateInputLayout(device);

	if (FAILED(result))
		return false;

	result = CreateMatrixBuffer (device);

	if (FAILED(result))
		return false;

	m_initDone = true;
	return true;
}

bool GridMaterial::CopyShaderParameters(ID3D11DeviceContext* deviceContext, const GlobalRenderData& globalRenderData, const MeshRenderData& meshRenderData) const
{
	HRESULT result = CopyMatrixBuffer (deviceContext, globalRenderData, meshRenderData);

	if (FAILED(result))
		return false;

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	deviceContext->IASetInputLayout(m_layout);

	return true;
}

void GridMaterial::ShutdownShaderRessources()
{
	MeshMaterial::ShutdownShaderRessources();

	// Release the matrix constant buffer.
	if (m_sampleState)
	{
		m_sampleState->Release();
		m_sampleState = 0;
	}
}

HRESULT GridMaterial::CreateInputLayout(ID3D11Device* device)
{
	D3D11_INPUT_ELEMENT_DESC polygonLayout[3];

	// Create the vertex input layout description.
	// This setup needs to match the VertexType stucture in the ModelClass and in the shader.
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "TEXCOORD";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	polygonLayout[2].SemanticName = "NORMAL";
	polygonLayout[2].SemanticIndex = 0;
	polygonLayout[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[2].InputSlot = 0;
	polygonLayout[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[2].InstanceDataStepRate = 0;

	// Get a count of the elements in the layout.
	int numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	// Create the vertex input layout.
	return device->CreateInputLayout(polygonLayout, numElements, m_shader->VSBuffer()->GetBufferPointer(),
		m_shader->VSBuffer()->GetBufferSize(), &m_layout);
}

HRESULT GridMaterial::CreateMatrixBuffer(ID3D11Device* device)
{
	D3D11_BUFFER_DESC bufferDesc = {};

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.ByteWidth = sizeof(MatrixBufferType);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	return device->CreateBuffer(&bufferDesc, NULL, &m_matrixBuffer);
}

HRESULT GridMaterial::CopyMatrixBuffer(ID3D11DeviceContext* deviceContext, const GlobalRenderData& globalRenderData, const MeshRenderData& meshRenderData) const
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;

	// Transpose the matrices to prepare them for the shader.
	XMMATRIX worldMatrix = XMMatrixTranspose(meshRenderData.worldMatrix);
	XMMATRIX viewMatrix = XMMatrixTranspose(globalRenderData.viewMatrix);
	XMMATRIX projectionMatrix = XMMatrixTranspose(globalRenderData.projectionMatrix);

	// Lock the constant buffer so it can be written to.
	HRESULT result = deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	if (SUCCEEDED(result))
	{
		// Get a pointer to the data in the constant buffer.
		MatrixBufferType* dataPtr = (MatrixBufferType*)mappedResource.pData;

		// Copy the matrices into the constant buffer.
		dataPtr->world = worldMatrix;
		dataPtr->view = viewMatrix;
		dataPtr->projection = projectionMatrix;

		XMVECTOR scale, trans, rot;
		XMMatrixDecompose (&scale, &rot, &trans, worldMatrix);
		dataPtr->scale = {XMVectorGetX(scale), XMVectorGetY(scale) , XMVectorGetZ(scale) };

		// Unlock the constant buffer.
		deviceContext->Unmap(m_matrixBuffer, 0);

		deviceContext->VSSetConstantBuffers(0, 1, &m_matrixBuffer);
	}

	return result;
}
