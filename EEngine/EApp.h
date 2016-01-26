#pragma once

#include <windows.h>
#include "ELog.h"
#include "ERenderer.h"
#include "ETimer.h"
#include "IEEffect.h"
#include "IEAppStatsListener.h"

class EApp
{
public:
	EApp(HINSTANCE hInstance, HWND windowHandle);
	virtual ~EApp();
	
	void Init();
	int Run();

	ELog *GetLog();
	ERenderer *GetRenderer();

	void SetEffect(IEEffect *eEffect);
	void SetAppStatsListener(IEAppStatsListener *eAppStatsListener);

private:
	HINSTANCE _hInstance;
	HWND _windowHandle;

	ELog *_eLog;
	ERenderer *_eRenderer;
	ETimer *_eTimer;

	IEEffect *_eEffect;
	IEAppStatsListener *_eAppStatsListener;

	void UpdateStats();

};

