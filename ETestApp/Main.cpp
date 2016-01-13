#include <windows.h>
#include "Eapp.h"
#include "EAppFactory.h"
#include "EAppWindowFactory.h"
#include <string>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmsLine, int nShowCmd)
{
	EAppWindow &window = EAppWindowFactory::CreateAppWindow(hInstance, nShowCmd);
	window.Init();

	EApp &app = EAppFactory::CreateApp(hInstance, window.GetWindowHandle());

	window.Open();
	app.Start();
	auto runResult = app.Run();

	return runResult;
}

