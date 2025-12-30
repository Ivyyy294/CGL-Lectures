#include "ColorShader.h"

ColorShader::ColorShader()
	: MeshMaterial(L"color.hlsl", L"color.ps")
{
}

bool ColorShader::InitShaderRessources(ID3D11Device* device)
{
	//HRESULT result;
	//ID3D10Blob* errorMessage;
	//D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	//unsigned int numElements;

	//// Initialize the pointers this function will use to null.
	//errorMessage = 0;

	//// Create the vertex input layout description.
	//// This setup needs to match the VertexType stucture in the ModelClass and in the shader.
	//polygonLayout[0].SemanticName = "POSITION";
	//polygonLayout[0].SemanticIndex = 0;
	//polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	//polygonLayout[0].InputSlot = 0;
	//polygonLayout[0].AlignedByteOffset = 0;
	//polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	//polygonLayout[0].InstanceDataStepRate = 0;

	//polygonLayout[1].SemanticName = "COLOR";
	//polygonLayout[1].SemanticIndex = 0;
	//polygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	//polygonLayout[1].InputSlot = 0;
	//polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	//polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	//polygonLayout[1].InstanceDataStepRate = 0;

	//// Get a count of the elements in the layout.
	//numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	//// Create the vertex input layout.
	//result = device->CreateInputLayout(polygonLayout, numElements, m_shader->VSBuffer(),
	//	m_shader->VSSize(), &m_layout);
	//
	//if (FAILED(result))
	//	return false;

	//result = CreateBuffer(device, &m_matrixBuffer, sizeof(MatrixBufferType), NULL
	//	, D3D11_USAGE_DYNAMIC, D3D11_BIND_CONSTANT_BUFFER, D3D11_CPU_ACCESS_WRITE);
	//
	//if (FAILED(result))
	//{
	//	return false;
	//}

	return true;
}

void ColorShader::ShutdownShaderRessources()
{
	MeshMaterial::ShutdownShaderRessources();
}

bool ColorShader::CopyShaderParameters(ID3D11DeviceContext* deviceContext, const MeshMaterial::GlobalShaderParameters& shaderData) const
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;
	unsigned int bufferNumber;

	// Transpose the matrices to prepare them for the shader.
	XMMATRIX worldMatrix = XMMatrixTranspose(shaderData.m_worldMatrix);
	XMMATRIX viewMatrix = XMMatrixTranspose(shaderData.m_viewMatrix);
	XMMATRIX projectionMatrix = XMMatrixTranspose(shaderData.m_projectionMatrix);

	// Lock the constant buffer so it can be written to.
	result = deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer.
	dataPtr = (MatrixBufferType*)mappedResource.pData;

	// Copy the matrices into the constant buffer.
	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;

	// Unlock the constant buffer.
	deviceContext->Unmap(m_matrixBuffer, 0);

	// Set the position of the constant buffer in the vertex shader.
	bufferNumber = 0;

	// Finanly set the constant buffer in the vertex shader with the updated values.
	ID3D11Buffer* matrix = m_matrixBuffer;
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &matrix);

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	deviceContext->IASetInputLayout(m_layout);

	return true;
}
