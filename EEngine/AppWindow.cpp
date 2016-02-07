#include "AppWindow.h"

#include <Windows.h>
#include <Windowsx.h>
#include <sstream>
#include <cassert>
#include <fstream>
#include <iostream>

namespace EEngine
{
	//LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	AppWindow::AppWindow(HINSTANCE hInstance, int nShowCmd) :
		_hInstance(hInstance),
		_nShowCmd(nShowCmd),
		_paused(false),
		_framesPerSeconds(0.0f),
		_frameTime(0.0f),
		_window(nullptr),
		_logger(L"AppWindow"),
		_windowWidth(0),
		_windowHeight(0),
		_sizeMoving(false),
		_minimized(false),
		_maximized(false)
	{
	}

	AppWindow::~AppWindow()
	{
	}


	bool AppWindow::Init()
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
		windowClass.lpszClassName = L"AppWindowClass";

		if (!RegisterClass(&windowClass))
		{
			MessageBox(0, L"RegisterClass failed", 0, 0);
			return false;
		}

		_window = CreateWindow(
			L"AppWindowClass",
			L"AppWindow",
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

	void AppWindow::Open()
	{
		ShowWindow(_window, _nShowCmd);
		UpdateWindow(_window);
	}

	const HWND &AppWindow::GetWindowHandle() const
	{
		return _window;
	}

	void AppWindow::SetWindowEventListener(IWindowEventListener *windowEventListener)
	{
		_windowEventListeners.push_back(windowEventListener);
	}


	LRESULT CALLBACK AppWindow::StaticWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		AppWindow * pParent;

		if (uMsg == WM_CREATE)
		{
			pParent = (AppWindow*)((LPCREATESTRUCT)lParam)->lpCreateParams;
			SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG_PTR)pParent);
		}
		else
		{
			pParent = (AppWindow*)GetWindowLongPtr(hWnd, GWL_USERDATA);
			if (!pParent) return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}

		//pParent->m_hWnd = hWnd;
		return pParent->WndProc(hWnd, uMsg, wParam, lParam);
	}

	LRESULT AppWindow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		assert(_window == nullptr || hWnd == _window);

		switch (msg)
		{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		case WM_ACTIVATE:
		{
			if (LOWORD(wParam) == WA_INACTIVE)
			{
				//_logger.LogLine(L"OnDeactivate");
				for (auto iterator = _windowEventListeners.begin(), end = _windowEventListeners.end(); iterator != end; ++iterator)
				{
					(*iterator)->OnDeactivate();
				}
			}
			else
			{
				//_logger.LogLine(L"OnActivate");
				for (auto iterator = _windowEventListeners.begin(), end = _windowEventListeners.end(); iterator != end; ++iterator)
				{
					(*iterator)->OnActivate();
				}
			}
			return 0;
		}
		case WM_SIZE:
		{
			_windowWidth = LOWORD(lParam);
			_windowHeight = HIWORD(lParam);

			if (wParam == SIZE_MINIMIZED)
			{
				//_logger.LogLine(L"OnMinimized");
				//_paused = true;
				_minimized = true;
				_maximized = false;
			}
			else if (wParam == SIZE_MAXIMIZED)
			{
				//_logger.LogLine(L"OnMaximized"); 
				//_paused = false;
				_minimized = false;
				_maximized = true;
				SendResizeEvent(_windowWidth, _windowHeight);
			}
			else if (wParam == SIZE_RESTORED)
			{
				if (_minimized)
				{
					//_logger.LogLine(L"OnRestored (from minimized)");
					//	_paused = false;
					_minimized = false;
					SendResizeEvent(_windowWidth, _windowHeight);
				}
				else if (_maximized)
				{
					//_logger.LogLine(L"OnRestored (from maximized)");
					//	_paused = false;
					_maximized = false;
					SendResizeEvent(_windowWidth, _windowHeight);
				}
				else if (_sizeMoving)
				{
				}
				else
				{
					//_logger.LogLine(L"OnRestored");
					SendResizeEvent(_windowWidth, _windowHeight);
				}
			}
			return 0;
		}
		case WM_ENTERSIZEMOVE:
		{
			//_logger.LogLine(L"OnEnterSizeMove");
			//_paused = true;
			_sizeMoving = true;
			return 0;
		}
		case WM_EXITSIZEMOVE:
		{
			//_logger.LogLine(L"OnExitSizeMove");
			//_paused = false;
			_sizeMoving = false;
			SendResizeEvent(_windowWidth, _windowHeight);
			return 0;
		}
		case WM_MENUCHAR:
		{
			return MAKELRESULT(0, MNC_CLOSE);
		}
		case WM_GETMINMAXINFO:
		{
			((MINMAXINFO*)lParam)->ptMinTrackSize.x = 640;
			((MINMAXINFO*)lParam)->ptMinTrackSize.y = 480;
			return 0;
		}
		case WM_LBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_RBUTTONDOWN:
		{
			SetCapture(_window);

			for (auto iterator = _windowEventListeners.begin(), end = _windowEventListeners.end(); iterator != end; ++iterator)
			{
				(*iterator)->OnMouseDown(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			}
			return 0;
		}
		case WM_LBUTTONUP:
		case WM_MBUTTONUP:
		case WM_RBUTTONUP:
		{
			for (auto iterator = _windowEventListeners.begin(), end = _windowEventListeners.end(); iterator != end; ++iterator)
			{
				(*iterator)->OnMouseUp(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			}

			ReleaseCapture();
			return 0;
		}
		case WM_MOUSEMOVE:
		{
			for (auto iterator = _windowEventListeners.begin(), end = _windowEventListeners.end(); iterator != end; ++iterator)
			{
				(*iterator)->OnMouseMove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			}
			return 0;
		}
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	void AppWindow::SendResizeEvent(int width, int height)
	{
		for (auto iterator = _windowEventListeners.begin(), end = _windowEventListeners.end(); iterator != end; ++iterator)
		{
			(*iterator)->OnResize(width, height);
		}
	}

	void AppWindow::BeginUpdate()
	{
	}

	void AppWindow::UpdatePausedState(bool paused)
	{
		_paused = paused;
	}

	void AppWindow::UpdateFramesPerSeconds(float framesPerSeconds)
	{
		_framesPerSeconds = framesPerSeconds;
	}

	void AppWindow::UpdateFrameTime(float frameTime)
	{
		_frameTime = frameTime;
	}

	void AppWindow::EndUpdate()
	{
		std::wostringstream outs;
		outs.precision(6);
		if (_paused)
		{
			outs << "[PAUSED] ";
		}
		outs << L"FPS: " << _framesPerSeconds << L"    " << L"Frame time: " << _frameTime << L" (ms)";
		SetWindowText(_window, outs.str().c_str());
	}
}