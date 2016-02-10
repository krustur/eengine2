#pragma once

#include "IShader.h"

namespace EEngine
{
	class Material
	{
		public:
			explicit Material(IShader* shader);

			IShader *GetShader();

		private:
			IShader *_shader;
	};
}
