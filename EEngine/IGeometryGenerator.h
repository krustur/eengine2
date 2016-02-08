#pragma once

#include "Vector3.h"

namespace EEngine
{
	class IGeometryGenerator
	{
	public:
		IGeometryGenerator(){}
		virtual ~IGeometryGenerator() {}
		IGeometryGenerator(const IGeometryGenerator &other) = delete;
		IGeometryGenerator & operator= (const IGeometryGenerator & other) = delete;

		virtual unsigned int GetVerticeCount() = 0;
		virtual Vector3* GetVertices() = 0;
		virtual unsigned int GetIndicesCount() = 0;
		virtual unsigned int * GetIndices() = 0;
	};
}