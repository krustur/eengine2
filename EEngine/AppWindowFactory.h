#pragma once

#include <Windows.h>
#include "AppWindow.h"
#include "RaiiFactory.h"

namespace EEngine
{
	class AppWindowFactory final
	{
	public:
		AppWindow &CreateAppWindow(HINSTANCE hInstance, int nShowCmd);
	private:
		RaiiFactory<AppWindow> _raiiFactory;
	};
}