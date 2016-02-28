#include "StandardShader.h"

#include <d3dcompiler.h>

#include "StandardShaderVertex.h"

namespace EEngine
{
	StandardShader::StandardShader(Renderer &renderer) :
		_logger(L"StandardShader"),
		_renderer(renderer),
		_inputLayout(nullptr),
		_effect(nullptr),
		_effectTechnique(nullptr),
		_effectWorldViewProj(nullptr)		
	{

	}

	ID3D11Buffer*  StandardShader::AllocateVertexBuffer(unsigned int verticeCount, Vector3 *vertices)
	{
		StandardShaderVertex *shaderVertices = new StandardShaderVertex[verticeCount];
		for (unsigned int i = 0; i < verticeCount; i++)
		{
			shaderVertices[i].Pos.x = vertices[i].x;
			shaderVertices[i].Pos.y = vertices[i].y; 
			shaderVertices[i].Pos.z = vertices[i].z;
			shaderVertices[i].Color = Color(
				static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
				static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
				static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
				1.f);
		}

		D3D11_BUFFER_DESC vertexBufferDescription;
		vertexBufferDescription.Usage = D3D11_USAGE_IMMUTABLE;
		vertexBufferDescription.ByteWidth = sizeof(StandardShaderVertex) * verticeCount;
		vertexBufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDescription.CPUAccessFlags = 0;
		vertexBufferDescription.MiscFlags = 0;
		vertexBufferDescription.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA vertexInitialData;
		vertexInitialData.pSysMem = shaderVertices;

		ID3D11Buffer *vertexBuffer;
		HRESULT hresult = (_renderer.GetD3dDevice()->CreateBuffer(&vertexBufferDescription, &vertexInitialData, &vertexBuffer));
		if (FAILED(hresult))
		{
			_logger.LogHResult(hresult);
		}
		return vertexBuffer;
	}

	ID3D11Buffer* StandardShader::AllocateIndexBuffer(unsigned int indexCount, unsigned int *indexes)
	{
		int geometryIndicesCount = indexCount;
		unsigned int *geometryIndices = indexes;

		D3D11_BUFFER_DESC indicesBufferDescription;
		indicesBufferDescription.Usage = D3D11_USAGE_IMMUTABLE;
		indicesBufferDescription.ByteWidth = sizeof(UINT) * geometryIndicesCount;
		indicesBufferDescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indicesBufferDescription.CPUAccessFlags = 0;
		indicesBufferDescription.MiscFlags = 0;
		indicesBufferDescription.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA indicesInitializationData;
		indicesInitializationData.pSysMem = geometryIndices;

		ID3D11Buffer* indexBuffer;
		HRESULT hresult = (_renderer.GetD3dDevice()->CreateBuffer(&indicesBufferDescription, &indicesInitializationData, &indexBuffer));
		if (FAILED(hresult))
		{
			_logger.LogHResult(hresult);
		}

		return indexBuffer;
	}

	void StandardShader::BuildFX()
	{
		DWORD shaderFlags = 0;
#if defined( DEBUG ) || defined( _DEBUG )
		shaderFlags |= D3D10_SHADER_DEBUG;
		shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif

		ID3D10Blob* compiledShader = 0;
		ID3D10Blob* compilationMessages = 0;
		HRESULT hresult = D3DCompileFromFile(L"../EEngine/HLSL/StandardShader.fx", 0, 0, 0, "fx_5_0", shaderFlags, 0, &compiledShader, &compilationMessages);

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

		ID3DX11EffectTechnique* effectTechnique = effect->GetTechniqueByName("StandardShaderTechnique");
		ID3DX11EffectMatrixVariable* effectWorldViewProj = effect->GetVariableByName("g_WorldViewProj")->AsMatrix();

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

		_effect = effect;
		_effectTechnique = effectTechnique;
		_effectWorldViewProj = effectWorldViewProj;
		_inputLayout = inputLayout;
	}

	ID3D11InputLayout* StandardShader::GetInputLayout()
	{
		return _inputLayout;
	}

	ID3DX11Effect* StandardShader::GetEffect()
	{
		return _effect;
	}

	ID3DX11EffectTechnique* StandardShader::GetEffectTechnique()
	{
		return _effectTechnique;
	}

	ID3DX11EffectMatrixVariable* StandardShader::GetEffectWorldViewProj()
	{
		return _effectWorldViewProj;
	}

	int  StandardShader::GetStride()
	{
		return sizeof(StandardShaderVertex);
	}

}