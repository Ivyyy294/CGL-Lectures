#include "TextureShaderClass.h"
#include <d3dcompiler.h>
#include <fstream>
#include "IvyyyTexture.h"

using namespace std;
using namespace Ivyyy;

TextureShaderClass::TextureShaderClass()
	: Shader(L"TextureVS.hlsl", L"TexturePS.hlsl")
{
}

void Ivyyy::TextureShaderClass::SetTexture(Texture::Ptr texture)
{
	m_srv = texture->GetTexture();
}

bool TextureShaderClass::InitializeShader(const D3DShaderRenderData& shaderData, ID3D10Blob* vertexShaderBuffer, ID3D10Blob* pixelShaderBuffer)
{
	HRESULT result;
	ID3D10Blob* errorMessage;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[3];
	unsigned int numElements;
	// Initialize the pointers this function will use to null.
	errorMessage = 0;

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
	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	// Create the vertex input layout.
	result = shaderData.m_device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(), &m_layout);
	if (FAILED(result))
	{
		return false;
	}

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	result = CreateBuffer (shaderData.m_device, &m_matrixBuffer, sizeof(MatrixBufferType), NULL
		, D3D11_USAGE_DYNAMIC, D3D11_BIND_CONSTANT_BUFFER, D3D11_CPU_ACCESS_WRITE);

	if (FAILED(result))
	{
		return false;
	}

	D3D11_SAMPLER_DESC samplerDesc;
	// Create a texture sampler state description.
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// Create the texture sampler state.
	result = shaderData.m_device->CreateSamplerState(&samplerDesc, &m_sampleState);
	if (FAILED(result))
	{
		return false;
	}

	// Setup the description of the light dynamic constant buffer that is in the pixel shader.
	// Note that ByteWidth always needs to be a multiple of 16 if using D3D11_BIND_CONSTANT_BUFFER or CreateBuffer will fail.
	result = CreateBuffer(shaderData.m_device, &m_lightBuffer, sizeof(LightBufferType), NULL
		, D3D11_USAGE_DYNAMIC, D3D11_BIND_CONSTANT_BUFFER, D3D11_CPU_ACCESS_WRITE);
	
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

bool TextureShaderClass::InitializeVertexBuffer(ID3D11Device* device, Mesh* mesh)
{
	VertexType* shaderData;
	D3D11_SUBRESOURCE_DATA vertexData;
	HRESULT result;

	const Vector3* vertices = mesh->GetVertices();
	int vertexCount = mesh->GetVertexCount();

	// Create the vertex array.
	shaderData = new VertexType[vertexCount];
	if (!shaderData)
	{
		return false;
	}

	const Vector2* uv = mesh->GetUV();
	const Vector3* normal = mesh->GetNormals();

	for (int i = 0; i < vertexCount; ++i)
	{
		shaderData[i].position = XMFLOAT3(vertices[i].x, vertices[i].y, vertices[i].z);
		shaderData[i].uv = XMFLOAT2 (uv[i].x, uv[i].y);
		shaderData[i].normal = XMFLOAT3 (normal[i].x, normal[i].y, normal[i].z);
	}

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = shaderData;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	result = CreateBuffer(device, &m_vertexBuffer, sizeof(VertexType) * vertexCount, &vertexData
		, D3D11_USAGE_DEFAULT, D3D11_BIND_VERTEX_BUFFER, 0);

	if (FAILED(result))
	{
		return false;
	}

	return true;
}

unsigned int TextureShaderClass::GetVertexBufferStride()
{
	return sizeof(VertexType);
}

bool TextureShaderClass::SetShaderParameters(const D3DShaderRenderData& shaderData)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;
	LightBufferType* dataPtr2;
	unsigned int bufferNumber;

	// Transpose the matrices to prepare them for the shader.
	XMMATRIX worldMatrix = XMMatrixTranspose(shaderData.m_worldMatrix);
	XMMATRIX viewMatrix = XMMatrixTranspose(shaderData.m_viewMatrix);
	XMMATRIX projectionMatrix = XMMatrixTranspose(shaderData.m_projectionMatrix);

	// Lock the constant buffer so it can be written to.
	result = shaderData.m_deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
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
	shaderData.m_deviceContext->Unmap(m_matrixBuffer, 0);

	// Set the position of the constant buffer in the vertex shader.
	bufferNumber = 0;

	// Finanly set the constant buffer in the vertex shader with the updated values.
	ID3D11Buffer* matrix = m_matrixBuffer;
	shaderData.m_deviceContext->VSSetConstantBuffers(bufferNumber, 1, &matrix);

	// Set shader texture resource in the pixel shader.
	shaderData.m_deviceContext->PSSetShaderResources(0, 1, &m_srv);

	// Set the sampler state in the pixel shader.
	shaderData.m_deviceContext->PSSetSamplers(0, 1, &m_sampleState);

	// Lock the light constant buffer so it can be written to.
	result = shaderData.m_deviceContext->Map(m_lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer.
	dataPtr2 = (LightBufferType*)mappedResource.pData;

	// Copy the lighting variables into the constant buffer.
	Color diffuseColor = shaderData.m_light->GetColor();
	Vector3 lightDirection = shaderData.m_light->GetDirection();

	dataPtr2->diffuseColor = XMFLOAT4 (diffuseColor.r, diffuseColor.g, diffuseColor.b, diffuseColor.a);
	dataPtr2->lightDirection = XMFLOAT3(lightDirection.x, lightDirection.y, lightDirection.z);
	dataPtr2->padding = 0.0f;

	// Unlock the constant buffer.
	shaderData.m_deviceContext->Unmap(m_lightBuffer, 0);

	// Set the position of the light constant buffer in the pixel shader.
	bufferNumber = 0;

	// Finally set the light constant buffer in the pixel shader with the updated values.
	shaderData.m_deviceContext->PSSetConstantBuffers(bufferNumber, 1, &m_lightBuffer);

	return true;
}

void Ivyyy::TextureShaderClass::ShutdownShader()
{
	Shader::ShutdownShader();

	// Release the sampler state.
	if (m_sampleState)
	{
		m_sampleState->Release();
		m_sampleState = 0;
	}

	// Release the light constant buffer.
	if (m_lightBuffer)
	{
		m_lightBuffer->Release();
		m_lightBuffer = 0;
	}
}
