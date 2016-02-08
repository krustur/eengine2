#include "BoxGeometryGenerator.h"

namespace EEngine
{
	BoxGeometryGenerator::BoxGeometryGenerator(float size) :
		_vertices(new Vector3[8]),
		_indices(new unsigned int[36]),
		_size(size)
	{
		_vertices[0] = { -_size, -_size, -_size };
		_vertices[1] = { -_size, +_size, -_size };
		_vertices[2] = { +_size, +_size, -_size };
		_vertices[3] = { +_size, -_size, -_size };
		_vertices[4] = { -_size, -_size, +_size };
		_vertices[5] = { -_size, +_size, +_size };
		_vertices[6] = { +_size, +_size, +_size };
		_vertices[7] = { +_size, -_size, +_size };

		_indices[0] = 0;
		_indices[1] = 1;
		_indices[2] = 2;
		_indices[3] = 0;
		_indices[4] = 2;
		_indices[5] = 3;
		_indices[6] = 4;
		_indices[7] = 6;
		_indices[8] = 5;
		_indices[9] = 4;
		_indices[10] = 7;
		_indices[11] = 6;
		_indices[12] = 4;
		_indices[13] = 5;
		_indices[14] = 1;
		_indices[15] = 4;
		_indices[16] = 1;
		_indices[17] = 0;
		_indices[18] = 3;
		_indices[19] = 2;
		_indices[20] = 6;
		_indices[21] = 3;
		_indices[22] = 6;
		_indices[23] = 7;
		_indices[24] = 1;
		_indices[25] = 5;
		_indices[26] = 6;
		_indices[27] = 1;
		_indices[28] = 6;
		_indices[29] = 2;
		_indices[30] = 4;
		_indices[31] = 0;
		_indices[32] = 3;
		_indices[33] = 4;
		_indices[34] = 3;
		_indices[35] = 7;
	}


	BoxGeometryGenerator::~BoxGeometryGenerator()
	{
		delete[] _vertices;
		delete[] _indices;
	}
	
	unsigned int BoxGeometryGenerator::GetVerticeCount()
	{
		return 8;
	}

	Vector3* BoxGeometryGenerator::GetVertices()
	{
		return _vertices;
	}

	unsigned int BoxGeometryGenerator::GetIndicesCount()
	{
		return 36;
	}

	unsigned int* BoxGeometryGenerator::GetIndices()
	{
		return _indices;
	}
}