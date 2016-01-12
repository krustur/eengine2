#include "EAppFactory.h"

#include "EApp.h"

EAppFactory::EAppFactory()
{
}


EAppFactory::~EAppFactory()
{
}

EApp & EAppFactory::CreateApp(HINSTANCE instance)
{
	auto app = new EApp(instance);
	return *app;
}
