#pragma once

#include <d3d11.h>
#include "inc/d3dx11effect.h"
#include "Material.h"
#include "Vector3.h"

namespace EEngine
{
	class Mesh
	{
	public:
		explicit Mesh(Material *material);
		~Mesh();

		void SetVertices(unsigned int verticeCount, Vector3 *vertices);
		void SetIndexes(unsigned int indexCount, unsigned int *indexes);

		ID3D11Buffer * GetVertexBuffer();
		ID3D11Buffer* GetIndexBuffer();

		Material* GetMaterial();

	private:
		ID3D11Buffer* _vertexBuffer;
		ID3D11Buffer* _indexBuffer;

		Material *_material;
	};
}
