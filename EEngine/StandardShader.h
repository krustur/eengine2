#pragma once

#include "IShader.h"
#include "Logger.h"
#include "Vector3.h"
#include "Renderer.h"
#include "inc/d3dx11effect.h"

namespace EEngine
{
	class StandardShader : public IShader
	{
		public:
			explicit StandardShader(Renderer &renderer);

			virtual void BuildFX() override;

			virtual ID3D11Buffer*  AllocateVertexBuffer(unsigned int verticeCount, Vector3 *vertices) override;
			virtual ID3D11Buffer*  AllocateIndexBuffer(unsigned int indexCount, unsigned int *indexes) override;

			virtual ID3D11InputLayout* GetInputLayout() override;
			virtual ID3DX11Effect* GetEffect() override;
			virtual ID3DX11EffectTechnique* GetEffectTechnique() override;
			virtual ID3DX11EffectMatrixVariable* GetEffectWorldViewProj() override;
			virtual int GetStride() override;

		private:
			Renderer &_renderer;
			Logger _logger;

			ID3D11InputLayout* _inputLayout;

			ID3DX11Effect* _effect;
			ID3DX11EffectTechnique* _effectTechnique;
			ID3DX11EffectMatrixVariable* _effectWorldViewProj;
	};
}