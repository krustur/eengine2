#pragma once

#include <Windows.h>
#include "EApp.h"
#include "ERaiiFactory.h"

namespace EEngine
{
	class EAppFactory
	{
	public:
		EApp & CreateApp(HINSTANCE instance, HWND windowHandle);

	private:
		ERaiiFactory<EApp> _raiiFactory;
	};
}