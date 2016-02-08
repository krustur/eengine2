#pragma once

#include "Mesh.h"
#include "Logger.h"
#include "Renderer.h"
#include "IGeometryGenerator.h"

namespace EEngine
{
	class MeshGenerator
	{
	public:
		MeshGenerator(Renderer &renderer);
		~MeshGenerator();

		Mesh *GenerateMesh(IGeometryGenerator &geometryGenerator);

	private:
		void BuildGeometryBuffers(IGeometryGenerator &geometryGenerator, Mesh &mesh);
		void BuildFX(Mesh &mesh);
		//void BuildVertexLayout(Mesh &mesh);

		Logger _logger;
		Renderer &_renderer;
	};
}