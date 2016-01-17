#include <windows.h>
#include "Eapp.h"
#include "EAppFactory.h"
#include "EAppWindowFactory.h"
#include <string>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmsLine, int nShowCmd)
{
	EAppWindowFactory windowFactory;
	auto &window = windowFactory.CreateAppWindow(hInstance, nShowCmd);
	window.Init();

	EAppFactory appFactory;
	auto &app = appFactory.CreateApp(hInstance, window.GetWindowHandle());

	window.Open();
	app.Init();
	auto runResult = app.Run();


	return runResult;
}

