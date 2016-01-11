#include <windows.h>
#include "Eapp.h"
#include "EAppFactory.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmsLine, int nShowCmd)
{
	EApp *app = EAppFactory::CreateApp();
}