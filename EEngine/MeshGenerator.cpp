#include "MeshGenerator.h"

#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>

#include "Color.h"


namespace EEngine
{
	struct Vertex
	{
		DirectX::XMFLOAT3 Pos;
		EEngine::Color Color;
	};

	MeshGenerator::MeshGenerator(Renderer &renderer) :
		_logger(L"MeshRenderer"),
		_renderer(renderer)
	{
	}


	MeshGenerator::~MeshGenerator()
	{
	}

	Mesh *MeshGenerator::GenerateMesh()
	{
		auto mesh = new Mesh();

		BuildGeometryBuffers(*mesh);
		BuildFX(*mesh);

		return mesh;
	}

	void MeshGenerator::BuildGeometryBuffers(Mesh &mesh)
	{
		float size = 0.5f;
		Vertex vertices[] =
		{
			{ DirectX::XMFLOAT3(-size, -size, -size), EEngine::Colors::White },
			{ DirectX::XMFLOAT3(-size, +size, -size), EEngine::Colors::Black },
			{ DirectX::XMFLOAT3(+size, +size, -size), EEngine::Colors::Red },
			{ DirectX::XMFLOAT3(+size, -size, -size), EEngine::Colors::Green },
			{ DirectX::XMFLOAT3(-size, -size, +size), EEngine::Colors::Blue },
			{ DirectX::XMFLOAT3(-size, +size, +size), EEngine::Colors::Yellow },
			{ DirectX::XMFLOAT3(+size, +size, +size), EEngine::Colors::Cyan },
			{ DirectX::XMFLOAT3(+size, -size, +size), EEngine::Colors::Magenta }
		};

		D3D11_BUFFER_DESC vertexBufferDescription;
		vertexBufferDescription.Usage = D3D11_USAGE_IMMUTABLE;
		vertexBufferDescription.ByteWidth = sizeof(Vertex) * 8;
		vertexBufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDescription.CPUAccessFlags = 0;
		vertexBufferDescription.MiscFlags = 0;
		vertexBufferDescription.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA vertexInitialData;
		vertexInitialData.pSysMem = vertices;

		ID3D11Buffer *vertexBuffer;
		HRESULT hresult = (_renderer.GetD3dDevice()->CreateBuffer(&vertexBufferDescription, &vertexInitialData, &vertexBuffer));
		if (FAILED(hresult))
		{
			_logger.LogHResult(hresult);
		}

		UINT indices[] = {

			0, 1, 2,	// front
			0, 2, 3,
			4, 6, 5,	// back
			4, 7, 6,
			4, 5, 1,	// left
			4, 1, 0,
			3, 2, 6,	// right
			3, 6, 7,
			1, 5, 6,	// top
			1, 6, 2,
			4, 0, 3,	// bottom
			4, 3, 7
		};

		D3D11_BUFFER_DESC indicesBufferDescription;
		indicesBufferDescription.Usage = D3D11_USAGE_IMMUTABLE;
		indicesBufferDescription.ByteWidth = sizeof(UINT) * 36;
		indicesBufferDescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indicesBufferDescription.CPUAccessFlags = 0;
		indicesBufferDescription.MiscFlags = 0;
		indicesBufferDescription.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA indicesInitializationData;
		indicesInitializationData.pSysMem = indices;

		ID3D11Buffer* indexBuffer;
		hresult = (_renderer.GetD3dDevice()->CreateBuffer(&indicesBufferDescription, &indicesInitializationData, &indexBuffer));
		if (FAILED(hresult))
		{
			_logger.LogHResult(hresult);
		}
		mesh.SetVertexBuffer(vertexBuffer);
		mesh.SetIndexBuffer(indexBuffer);
		mesh.SetStride(sizeof(Vertex));
	}

	void MeshGenerator::BuildFX(Mesh &mesh)
	{
		DWORD shaderFlags = 0;
#if defined( DEBUG ) || defined( _DEBUG )
		shaderFlags |= D3D10_SHADER_DEBUG;
		shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif

		ID3D10Blob* compiledShader = 0;
		ID3D10Blob* compilationMessages = 0;
		HRESULT hresult = D3DCompileFromFile(L"../EEngine/HLSL/color.fx", 0, 0, 0, "fx_5_0", shaderFlags, 0, &compiledShader, &compilationMessages);

		if (compilationMessages != 0)
		{
			_logger.LogLine((char *)compilationMessages->GetBufferPointer());

			compilationMessages->Release();
			compilationMessages = 0;
		}

		if (FAILED(hresult))
		{
			_logger.LogHResult(hresult);
		}

		ID3DX11Effect* effect;
		hresult = (D3DX11CreateEffectFromMemory(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), 0, _renderer.GetD3dDevice(), &effect));
		if (FAILED(hresult))
		{
			_logger.LogHResult(hresult);
		}

		if (compiledShader)
		{
			compiledShader->Release();
			compiledShader = 0;
		}

		ID3DX11EffectTechnique* effectTechnique = effect->GetTechniqueByName("ColorTech");
		ID3DX11EffectMatrixVariable* effectWorldViewProj = effect->GetVariableByName("gWorldViewProj")->AsMatrix();

		D3D11_INPUT_ELEMENT_DESC inputElementDescriptions[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		D3DX11_PASS_DESC effectPassDescription;
		effectTechnique->GetPassByIndex(0)->GetDesc(&effectPassDescription);

		ID3D11InputLayout* inputLayout;

		hresult = (_renderer.GetD3dDevice()->CreateInputLayout(inputElementDescriptions, 2, effectPassDescription.pIAInputSignature, effectPassDescription.IAInputSignatureSize, &inputLayout));
		if (FAILED(hresult))
		{
			_logger.LogHResult(hresult);
		}

		mesh.SetEffect(effect);
		mesh.SetEffectTechnique(effectTechnique);
		mesh.SetEffectWorldViewProj(effectWorldViewProj);
		mesh.SetInputLayout(inputLayout);
	}

}