#include <Windows.h>
#include <Windowsx.h>
#include <sstream>
#include <cassert>
#include "EAppWindow.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

EAppWindow::EAppWindow(HINSTANCE hInstance, int nShowCmd) :
	_hInstance(hInstance),
	_nShowCmd(nShowCmd),
	_windowEventListener(nullptr)
{
}

EAppWindow::~EAppWindow()
{
}


bool EAppWindow::Init()
{
	WNDCLASS windowClass;

	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = StaticWndProc;
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
		this);

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

void EAppWindow::SetWindowEventListener(IEWindowEventListener *windowEventListener)
{
	_windowEventListener = windowEventListener;
}


LRESULT CALLBACK EAppWindow::StaticWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	EAppWindow * pParent;

	if (uMsg == WM_CREATE)
	{
		pParent = (EAppWindow*)((LPCREATESTRUCT)lParam)->lpCreateParams;
		SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG_PTR)pParent);
	}
	else
	{
		pParent = (EAppWindow*)GetWindowLongPtr(hWnd, GWL_USERDATA);
		if (!pParent) return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	//pParent->m_hWnd = hWnd;
	return pParent->WndProc(hWnd, uMsg, wParam, lParam);
}

LRESULT EAppWindow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	assert(_window == nullptr || hWnd == _window);

	switch (msg)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		case WM_MENUCHAR:
		{
			return MAKELRESULT(0, MNC_CLOSE);
		}
		case WM_GETMINMAXINFO:
		{
			((MINMAXINFO*)lParam)->ptMinTrackSize.x = 640;
			((MINMAXINFO*)lParam)->ptMinTrackSize.y = 480;
		}
		case WM_LBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_RBUTTONDOWN:
		{
			if (_windowEventListener != nullptr)
			{
				_windowEventListener->OnMouseDown(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				return 0;
			}
			break;
		}
		case WM_LBUTTONUP:
		case WM_MBUTTONUP:
		case WM_RBUTTONUP:
		{
			if (_windowEventListener != nullptr)
			{
				_windowEventListener->OnMouseUp(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				return 0;
			}
			break;
		}
		case WM_MOUSEMOVE:
		{
			if (_windowEventListener != nullptr)
			{
				_windowEventListener->OnMouseMove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				return 0;
			}
			break;			
		}
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void EAppWindow::BeginUpdate()
{
}

void EAppWindow::UpdateFramesPerSeconds(float framesPerSeconds)
{
	_framesPerSeconds = framesPerSeconds;
}

void EAppWindow::UpdateFrameTime(float frameTime)
{
	_frameTime = frameTime;
}

void EAppWindow::EndUpdate()
{
	std::wostringstream outs;
	outs.precision(6);
	outs << L"FPS: " << _framesPerSeconds << L"    " << L"Frame time: " << _frameTime << L" (ms)";
	SetWindowText(_window, outs.str().c_str());
}

