#pragma once
#include <Windows.h>
#include "EApp.h"

class EAppFactory final
{
public:
	EAppFactory();
	 ~EAppFactory();

	static EApp &CreateApp(HINSTANCE instance, HWND windowHandle);
};

