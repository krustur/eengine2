#include "Mesh.h"



namespace EEngine
{
	Mesh::Mesh() :
		_vertexBuffer(nullptr),
		_indexBuffer(nullptr),
		_inputLayout(nullptr),
		_effect(0),
		_effectTechnique(0),
		_effectWorldViewProj(0)
	{
	}

	Mesh::~Mesh()
	{
		if (_vertexBuffer)
		{
			_vertexBuffer->Release();
			_vertexBuffer = 0;
		}
		if (_indexBuffer)
		{
			_indexBuffer->Release();
			_indexBuffer = 0;
		}
		if (_effect)
		{
			_effect->Release();
			_effect = 0;
		}
		if (_inputLayout)
		{
			_inputLayout->Release();
			_inputLayout = 0;
		}
	}

	void Mesh::SetVertexBuffer(ID3D11Buffer* vertexBuffer)
	{
		_vertexBuffer = vertexBuffer;
	}

	void Mesh::SetIndexBuffer(ID3D11Buffer* indexBuffer)
	{
		_indexBuffer = indexBuffer;
	}

	void Mesh::SetInputLayout(ID3D11InputLayout* inputLayout)
	{
		_inputLayout = inputLayout;
	}

	void Mesh::SetEffect(ID3DX11Effect* effect)
	{
		_effect = effect;
	}

	void Mesh::SetEffectTechnique(ID3DX11EffectTechnique* effectTechnique)
	{
		_effectTechnique = effectTechnique;
	}

	void Mesh::SetEffectWorldViewProj(ID3DX11EffectMatrixVariable* effectWorldViewProj)
	{
		_effectWorldViewProj = effectWorldViewProj;
	}

	void Mesh::SetStride(int stride)
	{
		_stride = stride;
	}

	ID3D11Buffer * Mesh::GetVertexBuffer()
	{
		return _vertexBuffer;
	}

	ID3D11Buffer* Mesh::GetIndexBuffer()
	{
		return _indexBuffer;
	}

	ID3D11InputLayout* Mesh::GetInputLayout()
	{
		return _inputLayout;
	}

	ID3DX11Effect* Mesh::GetEffect()
	{
		return _effect;
	}

	ID3DX11EffectTechnique* Mesh::GetEffectTechnique()
	{
		return _effectTechnique;
	}

	ID3DX11EffectMatrixVariable* Mesh::GetEffectWorldViewProj()
	{
		return _effectWorldViewProj;
	}

	int Mesh::GetStride()
	{
		return _stride;
	}
}