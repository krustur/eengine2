#include "EAppWindowFactory.h"



EAppWindowFactory::EAppWindowFactory()
{
}


EAppWindowFactory::~EAppWindowFactory()
{
}

EAppWindow & EAppWindowFactory::CreateAppWindow(HINSTANCE hInstance, int nShowCmd)
{
	auto window = new EAppWindow(hInstance, nShowCmd);
	return *window;
}
