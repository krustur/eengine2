#include "EAppWindowFactory.h"

EAppWindow & EAppWindowFactory::CreateAppWindow(HINSTANCE hInstance, int nShowCmd)
{
	return _raiiFactory.Create(new EAppWindow(hInstance, nShowCmd)); 
}