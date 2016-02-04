#include "EMesh.h"



namespace EEngine
{
	EMesh::EMesh() :
		_vertexBuffer(nullptr),
		_indexBuffer(nullptr),
		_inputLayout(nullptr),
		_effect(0),
		_effectTechnique(0),
		_effectWorldViewProj(0)
	{
	}

	EMesh::~EMesh()
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

	void EMesh::SetVertexBuffer(ID3D11Buffer* vertexBuffer)
	{
		_vertexBuffer = vertexBuffer;
	}

	void EMesh::SetIndexBuffer(ID3D11Buffer* indexBuffer)
	{
		_indexBuffer = indexBuffer;
	}

	void EMesh::SetInputLayout(ID3D11InputLayout* inputLayout)
	{
		_inputLayout = inputLayout;
	}

	void EMesh::SetEffect(ID3DX11Effect* effect)
	{
		_effect = effect;
	}

	void EMesh::SetEffectTechnique(ID3DX11EffectTechnique* effectTechnique)
	{
		_effectTechnique = effectTechnique;
	}

	void EMesh::SetEffectWorldViewProj(ID3DX11EffectMatrixVariable* effectWorldViewProj)
	{
		_effectWorldViewProj = effectWorldViewProj;
	}

	void EMesh::SetStride(int stride)
	{
		_stride = stride;
	}

	ID3D11Buffer * EMesh::GetVertexBuffer()
	{
		return _vertexBuffer;
	}

	ID3D11Buffer* EMesh::GetIndexBuffer()
	{
		return _indexBuffer;
	}

	ID3D11InputLayout* EMesh::GetInputLayout()
	{
		return _inputLayout;
	}

	ID3DX11Effect* EMesh::GetEffect()
	{
		return _effect;
	}

	ID3DX11EffectTechnique* EMesh::GetEffectTechnique()
	{
		return _effectTechnique;
	}

	ID3DX11EffectMatrixVariable* EMesh::GetEffectWorldViewProj()
	{
		return _effectWorldViewProj;
	}

	int EMesh::GetStride()
	{
		return _stride;
	}
}