#include "AppWindowFactory.h"

namespace EEngine
{
	AppWindow & AppWindowFactory::CreateAppWindow(HINSTANCE hInstance, int nShowCmd)
	{
		return _raiiFactory.Create(new AppWindow(hInstance, nShowCmd));
	}
}