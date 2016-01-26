#pragma once

#include <windows.h>
#include "IEAppStatsListener.h"

class EAppWindow : public IEAppStatsListener
{
public:
	EAppWindow(HINSTANCE hInstance, int nShowCmd);
	virtual ~EAppWindow();
	
	bool Init();
	void Open();
	const HWND &GetWindowHandle() const;

	void BeginUpdate();
	void UpdateFramesPerSeconds(float framesPerSeconds);
	void UpdateFrameTime(float frameTime);
	void EndUpdate();

private:
	HINSTANCE _hInstance;
	int _nShowCmd;

	HWND _window = 0;

	float _framesPerSeconds;
	float _frameTime;	
};

