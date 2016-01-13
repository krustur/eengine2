#pragma once
#include <windows.h>

class EApp
{
public:
	EApp(HINSTANCE hInstance, HWND windowHandle);
	virtual ~EApp();
	
	void Start();
	int Run();

private:
	HINSTANCE _hInstance;
	HWND _windowHandle;
};

