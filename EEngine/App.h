#pragma once

#include <windows.h>
#include "Logger.h"
#include "Renderer.h"
#include "Timer.h"
#include "IEffect.h"
#include "IAppStatsListener.h"
#include "IWindowEventListener.h"

namespace EEngine
{
	class App : public IWindowEventListener
	{
	public:
		explicit App(HINSTANCE hInstance, HWND windowHandle);
		virtual ~App();

		void Init();
		int Run();

		Renderer *GetRenderer();

		void SetEffect(IEffect *effect);
		void SetAppStatsListener(IAppStatsListener *appStatsListener);

		virtual void OnActivate();
		virtual void OnDeactivate();
		virtual void OnMouseDown(WPARAM buttonState, int x, int y);
		virtual void OnMouseUp(WPARAM buttonState, int x, int y);
		virtual void OnMouseMove(WPARAM buttonState, int x, int y);
		virtual void OnResize(int width, int height);

	private:
		HINSTANCE _hInstance;
		HWND _windowHandle;

		Logger _logger;
		Renderer _renderer;
		Timer _timer;
		bool _paused;


		IEffect *_effect;
		IAppStatsListener *_appStatsListener;

		void UpdateStats();

	};
}
