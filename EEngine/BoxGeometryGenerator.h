#pragma once

#include "IGeometryGenerator.h"

namespace EEngine
{
	class BoxGeometryGenerator : public IGeometryGenerator
	{
	public:
		explicit BoxGeometryGenerator(float size);
		virtual ~BoxGeometryGenerator();
		BoxGeometryGenerator(const BoxGeometryGenerator &other) = delete;
		BoxGeometryGenerator & operator= (const BoxGeometryGenerator & other) = delete;

		virtual unsigned int GetVerticeCount();
		virtual Vector3* GetVertices();
		virtual unsigned int GetIndicesCount();
		virtual unsigned int * GetIndices();

	private:
		Vector3 *_vertices;
		unsigned int *_indices;
		float _size;
	};
}