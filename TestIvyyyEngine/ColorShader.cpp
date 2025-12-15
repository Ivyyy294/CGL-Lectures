#include "ColorShader.h"

ColorShader::ColorShader()
	: Shader(L"color.hlsl", L"color.ps")
{
}

bool ColorShader::InitializeShader(const D3DShaderRenderData& shaderData, ID3D10Blob* vertexShaderBuffer, ID3D10Blob* pixelShaderBuffer)
{
	HRESULT result;
	ID3D10Blob* errorMessage;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
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

	polygonLayout[1].SemanticName = "COLOR";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	// Get a count of the elements in the layout.
	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	// Create the vertex input layout.
	result = shaderData.m_device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(), &m_layout);
	
	if (FAILED(result))
	{
		return false;
	}

	result = CreateBuffer(shaderData.m_device, &m_matrixBuffer, sizeof(MatrixBufferType), NULL
		, D3D11_USAGE_DYNAMIC, D3D11_BIND_CONSTANT_BUFFER, D3D11_CPU_ACCESS_WRITE);
	
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

bool ColorShader::InitializeVertexBuffer(ID3D11Device* device, Mesh* mesh)
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

	for (int i = 0; i < vertexCount; ++i)
	{
		shaderData[i].position = XMFLOAT3 (vertices[i].x, vertices[i].y, vertices[i].z);
		shaderData[i].color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	}

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = shaderData;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	result = CreateBuffer(device, &m_vertexBuffer, sizeof(VertexType) * vertexCount, &vertexData
		, D3D11_USAGE_DEFAULT, D3D11_BIND_VERTEX_BUFFER, 0);

	//free shader data
	delete [] shaderData;

	if (FAILED(result))
	{
		return false;
	}



	return true;
}

unsigned int ColorShader::GetVertexBufferStride()
{
	return sizeof(VertexType);
}

bool ColorShader::SetShaderParameters (const D3DShaderRenderData& shaderData)
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

	return true;
}
