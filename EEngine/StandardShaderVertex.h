#pragma once

#include <DirectXMath.h>
#include "Color.h"

namespace EEngine
{
	struct StandardShaderVertex
	{
		DirectX::XMFLOAT3 Pos;
		EEngine::Color Color; // TODO: Nah, not really
	};
}	