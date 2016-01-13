#include "EApp.h"

EApp::EApp(HINSTANCE hInstance, HWND windowHandle)	:
	_hInstance(hInstance),
	_windowHandle(windowHandle)
{
}


EApp::~EApp()
{
}

void EApp::Start()
{
}

int EApp::Run()
{
	MSG message = { 0 };

	BOOL getMessageResult = 1;
	while ((getMessageResult = GetMessage(&message, 0, 0, 0)) != 0)
	{
		if (getMessageResult == -1)
		{
			MessageBox(0, L"GetMessage failed", L"Error", MB_OK);
			break;
		}
		else
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}

	return static_cast<int>(message.wParam);
}