#pragma once

#include <d3d11.h>
#include "inc/d3dx11effect.h"

#include "Vector3.h"

namespace EEngine
{

	class IShader
	{
	public:
		IShader() {};
		virtual ~IShader() {};

		virtual void BuildFX() = 0;

		virtual ID3D11Buffer*  AllocateVertexBuffer(unsigned int verticeCount, Vector3 *vertices) = 0;
		virtual ID3D11Buffer*  AllocateIndexBuffer(unsigned int indexCount, unsigned int *indexes) = 0;

		virtual ID3D11InputLayout* GetInputLayout() = 0;
		virtual ID3DX11Effect* GetEffect() = 0;
		virtual ID3DX11EffectTechnique* GetEffectTechnique() = 0;
		virtual ID3DX11EffectMatrixVariable* GetEffectWorldViewProj() = 0;
		virtual int GetStride() = 0;
	};
	
}
