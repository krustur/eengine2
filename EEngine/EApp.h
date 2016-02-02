#pragma once

#include <windows.h>
#include "ELog.h"
#include "ERenderer.h"
#include "ETimer.h"
#include "IEEffect.h"
#include "IEAppStatsListener.h"
#include "IEWindowEventListener.h"

namespace EEngine
{
	class EApp : public IEWindowEventListener
	{
	public:
		EApp(HINSTANCE hInstance, HWND windowHandle);
		virtual ~EApp();

		void Init();
		int Run();

		ERenderer *GetRenderer();

		void SetEffect(IEEffect *eEffect);
		void SetAppStatsListener(IEAppStatsListener *eAppStatsListener);

		virtual void OnActivate();
		virtual void OnDeactivate();
		virtual void OnMouseDown(WPARAM buttonState, int x, int y);
		virtual void OnMouseUp(WPARAM buttonState, int x, int y);
		virtual void OnMouseMove(WPARAM buttonState, int x, int y);
		virtual void OnResize(int width, int height);

	private:
		HINSTANCE _hInstance;
		HWND _windowHandle;

		ELog _eLog;
		ERenderer _eRenderer;
		ETimer _eTimer;
		bool _paused;


		IEEffect *_eEffect;
		IEAppStatsListener *_eAppStatsListener;

		void UpdateStats();

	};
}
