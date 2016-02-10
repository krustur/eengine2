#include "Mesh.h"



namespace EEngine
{
	Mesh::Mesh(Material *material) :
		_vertexBuffer(nullptr),
		_indexBuffer(nullptr),
		_material(material)
	{
	}

	Mesh::~Mesh()
	{
		if (_vertexBuffer)
		{
			_vertexBuffer->Release();
			_vertexBuffer = nullptr;
		}
		if (_indexBuffer)
		{
			_indexBuffer->Release();
			_indexBuffer = nullptr;
		}
	}

	void Mesh::SetVertices(unsigned int verticeCount, Vector3 *vertices)
	{
		_vertexBuffer = _material->GetShader()->AllocateVertexBuffer(verticeCount, vertices);
	}

	void Mesh::SetIndexes(unsigned int indexCount, unsigned int *indexes)
	{
		_indexBuffer = _material->GetShader()->AllocateIndexBuffer(indexCount, indexes);

	}

	ID3D11Buffer * Mesh::GetVertexBuffer()
	{
		return _vertexBuffer;
	}

	ID3D11Buffer* Mesh::GetIndexBuffer()
	{
		return _indexBuffer;
	}

	Material *Mesh::GetMaterial()
	{
		return _material;
	}
}