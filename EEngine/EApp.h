#pragma once

#include <windows.h>
#include "ERenderer.h"

class EApp
{
public:
	EApp(HINSTANCE hInstance, HWND windowHandle);
	virtual ~EApp();
	
	void Init();
	int Run();

private:
	HINSTANCE _hInstance;
	HWND _windowHandle;

	ERenderer *_eRenderer;
};

