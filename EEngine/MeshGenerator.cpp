#include "MeshGenerator.h"

#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>

#include "Color.h"
#include "BoxGeometryGenerator.h"


namespace EEngine
{
	MeshGenerator::MeshGenerator(Renderer &renderer) :
		_logger(L"MeshRenderer"),
		_renderer(renderer)
	{		
	}

	MeshGenerator::~MeshGenerator()
	{
	}

	Mesh *MeshGenerator::GenerateMesh(IGeometryGenerator &geometryGenerator, Material *material)
	{
		Mesh *mesh = new Mesh(material);

		int geometryVerticeCount = geometryGenerator.GetVerticeCount();
		Vector3 *geometryVertices = geometryGenerator.GetVertices();

		int geometryIndicesCount = geometryGenerator.GetIndicesCount();
		unsigned int *geometryIndices = geometryGenerator.GetIndices();

		mesh->SetVertices(geometryVerticeCount, geometryVertices);
		mesh->SetIndexes(geometryIndicesCount, geometryIndices);

		return mesh;
	}
}