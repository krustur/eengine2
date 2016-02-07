#pragma once

#include <DirectXMath.h>
#include "Renderer.h"
#include "Mesh.h"
#include "Logger.h"

namespace EEngine
{
	class MeshRenderer
	{
	public:
		MeshRenderer(Renderer &renderer);
		~MeshRenderer();

		void RenderMesh(Mesh *mesh, DirectX::XMMATRIX *worldViewProj);
	private:
		Renderer &_renderer;
		Logger _logger;
	};
};
