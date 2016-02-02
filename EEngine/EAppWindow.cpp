#include "EAppWindow.h"

#include <Windows.h>
#include <Windowsx.h>
#include <sstream>
#include <cassert>
#include <fstream>
#include <iostream>

namespace EEngine
{
	//LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	EAppWindow::EAppWindow(HINSTANCE hInstance, int nShowCmd) :
		_hInstance(hInstance),
		_nShowCmd(nShowCmd),
		_paused(false),
		_framesPerSeconds(0.0f),
		_frameTime(0.0f),
		_window(nullptr),
		_eLog(L"EAppWindow"),
		_windowWidth(0),
		_windowHeight(0),
		_sizeMoving(false),
		_minimized(false),
		_maximized(false)
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
		_windowEventListeners.push_back(windowEventListener);
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
		}
		case WM_ACTIVATE:
		{
			if (LOWORD(wParam) == WA_INACTIVE)
			{
				//_eLog.LogLine(L"OnDeactivate");
				for (auto iterator = _windowEventListeners.begin(), end = _windowEventListeners.end(); iterator != end; ++iterator)
				{
					(*iterator)->OnDeactivate();
				}
			}
			else
			{
				//_eLog.LogLine(L"OnActivate");
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
				//_eLog.LogLine(L"OnMinimized");
				//_paused = true;
				_minimized = true;
				_maximized = false;
			}
			else if (wParam == SIZE_MAXIMIZED)
			{
				//_eLog.LogLine(L"OnMaximized"); 
				//_paused = false;
				_minimized = false;
				_maximized = true;
				SendResizeEvent(_windowWidth, _windowHeight);
			}
			else if (wParam == SIZE_RESTORED)
			{
				if (_minimized)
				{
					//_eLog.LogLine(L"OnRestored (from minimized)");
					//	_paused = false;
					_minimized = false;
					SendResizeEvent(_windowWidth, _windowHeight);
				}
				else if (_maximized)
				{
					//_eLog.LogLine(L"OnRestored (from maximized)");
					//	_paused = false;
					_maximized = false;
					SendResizeEvent(_windowWidth, _windowHeight);
				}
				else if (_sizeMoving)
				{
				}
				else
				{
					//_eLog.LogLine(L"OnRestored");
					SendResizeEvent(_windowWidth, _windowHeight);
				}
			}
			return 0;
		}
		case WM_ENTERSIZEMOVE:
		{
			//_eLog.LogLine(L"OnEnterSizeMove");
			//_paused = true;
			_sizeMoving = true;
			return 0;
		}
		case WM_EXITSIZEMOVE:
		{
			//_eLog.LogLine(L"OnExitSizeMove");
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

	void EAppWindow::SendResizeEvent(int width, int height)
	{
		for (auto iterator = _windowEventListeners.begin(), end = _windowEventListeners.end(); iterator != end; ++iterator)
		{
			(*iterator)->OnResize(width, height);
		}
	}

	void EAppWindow::BeginUpdate()
	{
	}

	void EAppWindow::UpdatePausedState(bool paused)
	{
		_paused = paused;
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
		if (_paused)
		{
			outs << "[PAUSED] ";
		}
		outs << L"FPS: " << _framesPerSeconds << L"    " << L"Frame time: " << _frameTime << L" (ms)";
		SetWindowText(_window, outs.str().c_str());
	}
}