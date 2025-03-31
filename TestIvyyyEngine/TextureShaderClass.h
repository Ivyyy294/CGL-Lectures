#pragma once

#include "IvyyyShader.h"
#include "IvyyyTexture.h"

namespace Ivyyy
{
	class TextureShaderClass : public Shader
	{
	public:
		TextureShaderClass ();

		void SetTexture(Texture::Ptr texture);

	protected:
		bool InitializeShader(const D3DShaderRenderData& shaderData, ID3D10Blob* vertexShaderBuffer, ID3D10Blob* pixelShaderBuffer) override;
		bool InitializeVertexBuffer(ID3D11Device* device, Mesh* mesh) override;
		unsigned int GetVertexBufferStride() override;
		bool SetShaderParameters(const D3DShaderRenderData& shaderData) override;
		void ShutdownShader() override;

	private:
		ID3D11ShaderResourceView* m_srv { 0 };
		ID3D11SamplerState* m_sampleState { 0 };
		ID3D11Buffer* m_lightBuffer { 0 };

		struct VertexType
		{
			XMFLOAT3 position;
			XMFLOAT2 uv;
			XMFLOAT3 normal;
		};

		struct MatrixBufferType
		{
			XMMATRIX world;
			XMMATRIX view;
			XMMATRIX projection;
		};

		struct LightBufferType
		{
			XMFLOAT4 diffuseColor;
			XMFLOAT3 lightDirection;
			float padding;  // Added extra padding so structure is a multiple of 16 for CreateBuffer function requirements.
		};
	};

	//class TextureShaderClass : public Shader
	//{
	//	//variables
	//private:
	//	struct MatrixBufferType
	//	{
	//		XMMATRIX world;
	//		XMMATRIX view;
	//		XMMATRIX projection;
	//	};

	//	struct VertexType
	//	{
	//		XMFLOAT3 position;
	//		XMFLOAT2 texture;
	//	};

	//	ID3D11SamplerState* m_sampleState;
	//	Texture* m_texture;

	//	//Methods
	//public:
	//	TextureShaderClass ();
	//	TextureShaderClass(const TextureShaderClass&);
	//	~TextureShaderClass();

	//	bool Initialize (const D3DShaderRenderData& shaderData) override;
	//	bool Render (const D3DShaderRenderData& shaderData) override;

	//private:
	//	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	//	void ShutdownShader();
	//	bool SetShaderParameters(const D3DShaderRenderData& shaderData) override;
	//	void RenderShader(ID3D11DeviceContext*, int);

	//	bool LoadTexture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* filename);
	//	void ReleaseTexture();

	//	// Inherited via Shader
	//	bool InitializeVertexBuffer(ID3D11Device* device, Mesh* mesh) override;
	//	bool InitializeShader(ID3D11Device* device, HWND hwnd, ID3D10Blob* vertexShaderBuffer, ID3D10Blob* pixelShaderBuffer) override;
	//	unsigned int GetVertexBufferStride() override;
	//};

}

