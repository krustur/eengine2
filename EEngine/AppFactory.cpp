#include "AppFactory.h"

#include "App.h"

namespace EEngine
{
	App & AppFactory::CreateApp(HINSTANCE instance, HWND windowHandle)
	{
		return _raiiFactory.Create(new App(instance, windowHandle));
	}
}