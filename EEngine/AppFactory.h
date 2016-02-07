#pragma once

#include <Windows.h>
#include "App.h"
#include "RaiiFactory.h"

namespace EEngine
{
	class AppFactory
	{
	public:
		App & CreateApp(HINSTANCE instance, HWND windowHandle);

	private:
		RaiiFactory<App> _raiiFactory;
	};
}