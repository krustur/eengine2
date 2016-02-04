#pragma once

#include "EMesh.h"
#include "ELog.h"
#include "ERenderer.h"

namespace EEngine
{
	class EMeshGenerator
	{
	public:
		EMeshGenerator(ERenderer &renderer);
		~EMeshGenerator();

		EMesh *GenerateMesh();

	private:
		void BuildGeometryBuffers(EMesh &mesh);
		void BuildFX(EMesh &mesh);
		//void BuildVertexLayout(EMesh &mesh);

		ELog _eLog;
		ERenderer &_renderer;
	};
}