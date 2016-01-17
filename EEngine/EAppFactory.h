#pragma once

#include <Windows.h>
#include "EApp.h"
#include "ERaiiFactory.h"

class EAppFactory 
{
public:
	//EAppFactory(){}	

	EApp & CreateApp(HINSTANCE instance, HWND windowHandle);

private:
	ERaiiFactory<EApp> _raiiFactory;
};

