#pragma once

#include <DirectXMath.h>
#include "ERenderer.h"
#include "EMesh.h"

namespace EEngine
{
	class EMeshRenderer
	{
	public:
		EMeshRenderer(ERenderer &renderer);
		~EMeshRenderer();

		void RenderMesh(EMesh *mesh, DirectX::XMMATRIX *worldViewProj);
	private:
		ERenderer &_renderer;
		ELog _logger;
	};
};
