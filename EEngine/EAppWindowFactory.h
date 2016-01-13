#pragma once

#include <Windows.h>
#include "EAppWindow.h"

class EAppWindowFactory final
{
public:
	EAppWindowFactory();
	~EAppWindowFactory();

	static EAppWindow &CreateAppWindow(HINSTANCE hInstance, int nShowCmd);
};

