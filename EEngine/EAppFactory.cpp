#include "EAppFactory.h"
#include "EApp.h"

namespace EEngine
{
	EApp & EAppFactory::CreateApp(HINSTANCE instance, HWND windowHandle)
	{
		return _raiiFactory.Create(new EApp(instance, windowHandle));
	}
}