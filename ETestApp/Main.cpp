#include <windows.h>
#include "Eapp.h"
#include "EAppFactory.h"
#include "EAppWindowFactory.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmsLine, int nShowCmd)
{
	EApp *app = EAppFactory::CreateApp();
	EApp &app = EAppFactory::CreateApp(hInstance);
	EAppWindow &window = EAppWindowFactory::CreateAppWindow(hInstance, nShowCmd);
	window.Open();
	app.Start();
	auto runResult = app.Run();

	return runResult;
}