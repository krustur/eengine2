#pragma once

namespace EEngine
{
	struct Color
	{
		float _red;
		float _green;
		float _blue;
		float _alpha;

		explicit Color() {}
		
		explicit Color(float red, float green, float blue, float alpha) :
			_red(red),
			_green(green),
			_blue(blue),
			_alpha(alpha)
		{
		}
	};

	namespace Colors
	{
		extern const Color White;
		extern const Color Black;
		extern const Color Red;
		extern const Color Green;
		extern const Color Blue;
		extern const Color Yellow;
		extern const Color Cyan;
		extern const Color Magenta;
		extern const Color Silver;
		extern const Color LightSteelBlue;
	}
}