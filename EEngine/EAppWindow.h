#pragma once
#include <windows.h>

class EAppWindow
{
public:
	EAppWindow(HINSTANCE hInstance, int nShowCmd);
	virtual ~EAppWindow();
	
	bool Open();
	const HWND &GetWindowHandle() const;

private:
	HINSTANCE _hInstance;
	int _nShowCmd;

	HWND _window = 0;
	/*LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);*/
};

