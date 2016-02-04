#pragma once

#include <d3d11.h>
#include "inc/d3dx11effect.h"

namespace EEngine
{
	class EMesh
	{
	public:
		EMesh();
		~EMesh();

		void SetVertexBuffer(ID3D11Buffer* vertexBuffer);		
		void SetIndexBuffer(ID3D11Buffer* indexBuffer);
		void SetInputLayout(ID3D11InputLayout* inputLayout);
		void SetEffect(ID3DX11Effect* effect);
		void SetEffectTechnique(ID3DX11EffectTechnique* effectTechnique);
		void SetEffectWorldViewProj(ID3DX11EffectMatrixVariable* effectWorldViewProj);
		void SetStride(int stride);

		ID3D11Buffer * GetVertexBuffer();
		ID3D11Buffer* GetIndexBuffer();
		ID3D11InputLayout* GetInputLayout();
		ID3DX11Effect* GetEffect();
		ID3DX11EffectTechnique* GetEffectTechnique();
		ID3DX11EffectMatrixVariable* GetEffectWorldViewProj();
		int GetStride();

	private:
		ID3D11Buffer* _vertexBuffer;
		ID3D11Buffer* _indexBuffer;
		ID3D11InputLayout* _inputLayout;

		ID3DX11Effect* _effect;
		ID3DX11EffectTechnique* _effectTechnique;
		ID3DX11EffectMatrixVariable* _effectWorldViewProj;

		int _stride;
	};
}