#include "EAppFactory.h"
#include "EApp.h"

EApp & EAppFactory::CreateApp(HINSTANCE instance, HWND windowHandle)
{
	return _raiiFactory.Create(new EApp(instance, windowHandle));
}


