#pragma once

#include "Mesh.h"
#include "Logger.h"
#include "Renderer.h"

namespace EEngine
{
	class MeshGenerator
	{
	public:
		MeshGenerator(Renderer &renderer);
		~MeshGenerator();

		Mesh *GenerateMesh();

	private:
		void BuildGeometryBuffers(Mesh &mesh);
		void BuildFX(Mesh &mesh);
		//void BuildVertexLayout(Mesh &mesh);

		Logger _logger;
		Renderer &_renderer;
	};
}