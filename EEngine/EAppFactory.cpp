#include "EAppFactory.h"
#include "EApp.h"

EAppFactory::EAppFactory()
{
}


EAppFactory::~EAppFactory()
{
}

EApp & EAppFactory::CreateApp(HINSTANCE instance, HWND windowHandle)
{
	auto app = new EApp(instance, windowHandle);
	return *app;
}
