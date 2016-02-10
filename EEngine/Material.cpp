#include "Material.h"

namespace EEngine
{

	Material::Material(IShader* shader) : 
		_shader(shader)
	{
	}

	IShader *Material::GetShader()
	{
		return _shader;
	}
}