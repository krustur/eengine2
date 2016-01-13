#include <Windows.h>
#include "EAppWindow.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

EAppWindow::EAppWindow(HINSTANCE hInstance, int nShowCmd) :
	_hInstance(hInstance),
	_nShowCmd(nShowCmd)
{
}

EAppWindow::~EAppWindow()
{
}


bool EAppWindow::Init()
{
	WNDCLASS windowClass;

	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WndProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = _hInstance;
	windowClass.hIcon = LoadIcon(0, IDI_APPLICATION); //TODO: Use LoadImage instead https://msdn.microsoft.com/en-us/library/windows/desktop/ms648045(v=vs.85).aspx
	windowClass.hCursor = LoadCursor(0, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	windowClass.lpszMenuName = 0;
	windowClass.lpszClassName = L"EAppWindowClass";

	if (!RegisterClass(&windowClass))
	{
		MessageBox(0, L"RegisterClass failed", 0, 0);
		return false;
	}

	_window = CreateWindow(
		L"EAppWindowClass",
		L"EAppWindow",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		0,
		0,
		_hInstance,
		0);

	if (_window == 0)
	{
		MessageBox(0, L"CreateWindow failed", 0, 0);
		return false;
	}

	return true;
}

void EAppWindow::Open()
{	
	ShowWindow(_window, _nShowCmd);
	UpdateWindow(_window);
}

const HWND &EAppWindow::GetWindowHandle() const
{
	return _window;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		case WM_LBUTTONDOWN:
		{
			MessageBox(0, L"You clicked it!", L"Hello", MB_OK);
			return 0;
		} 
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
