#pragma once

#include <windows.h>
#include <list>
#include "IAppStatsListener.h"
#include "IWindowEventListener.h"
#include "Logger.h"

namespace EEngine
{
	class AppWindow : public IAppStatsListener
	{
	public:
		explicit AppWindow(HINSTANCE hInstance, int nShowCmd);
		virtual ~AppWindow();

		bool Init();
		void Open();
		const HWND &GetWindowHandle() const;

		void SetWindowEventListener(IWindowEventListener *windowEventListener);

		void BeginUpdate();
		void UpdatePausedState(bool paused);
		void UpdateFramesPerSeconds(float framesPerSeconds);
		void UpdateFrameTime(float frameTime);
		void EndUpdate();

		static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:
		HINSTANCE _hInstance;
		int _nShowCmd;

		HWND _window;

		Logger _logger;

		std::list<IWindowEventListener *> _windowEventListeners;

		bool _paused;
		float _framesPerSeconds;
		float _frameTime;

		int _windowWidth;
		int _windowHeight;
		bool _sizeMoving;
		bool _maximized;
		bool _minimized;

		void SendResizeEvent(int width, int height);
	};
}