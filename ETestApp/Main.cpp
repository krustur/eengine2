#include <windows.h>
#include "AppFactory.h"
#include "AppWindowFactory.h"
#include "Logger.h"
#include "BoxTest.h"

using namespace EEngine;

void TestCode()
{
	auto log = ELog(L"knut");
	log.Log("Log (char*)");
	log.LogLine("LogLine (char*)");
	log.Log(L"Log (LPTSTR)");
	log.LogLine(L"LogLing (LPTSTR)");
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmsLine, int nShowCmd)
{
	AppWindowFactory windowFactory;
	auto &window = windowFactory.CreateAppWindow(hInstance, nShowCmd);
	window.Init();

	AppFactory appFactory;
	auto &app = appFactory.CreateApp(hInstance, window.GetWindowHandle());
	app.SetAppStatsListener(&window);

	window.Open();

	TestCode();
	
	app.Init();

	BoxTest boxTest(&app);
	boxTest.Init();

	app.SetEffect(&boxTest);
	window.SetWindowEventListener(&boxTest);
	window.SetWindowEventListener(&app);
	window.SetWindowEventListener(app.GetRenderer());

	auto runResult = app.Run();

	return runResult;
}

