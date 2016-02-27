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
		explicit MeshGenerator(Renderer &renderer);
		~MeshGenerator();
		Mesh* GenerateMesh(IGeometryGenerator& geometryGenerator, Material* material);

	private:
		Logger _logger;
		Renderer &_renderer;
	};
}