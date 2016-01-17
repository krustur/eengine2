#pragma once

#include <Windows.h>
#include "EAppWindow.h"
#include "ERaiiFactory.h"

class EAppWindowFactory final
{
public:
	EAppWindow &CreateAppWindow(HINSTANCE hInstance, int nShowCmd);
private:
	ERaiiFactory<EAppWindow> _raiiFactory;
};

