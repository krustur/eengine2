#pragma once
#include <windows.h>

class EApp
{
public:
	EApp(HINSTANCE hInstance);
	virtual ~EApp();
	
	void Start();
	int Run();

private:
	HINSTANCE _hInstance;
};

