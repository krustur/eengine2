#pragma once

#include <windows.h>
#include <list>
#include "IEAppStatsListener.h"
#include "IEWindowEventListener.h"

class EAppWindow : public IEAppStatsListener
{
public:
	EAppWindow(HINSTANCE hInstance, int nShowCmd);
	virtual ~EAppWindow();
	
	bool Init();
	void Open();
	const HWND &GetWindowHandle() const;

	void SetWindowEventListener(IEWindowEventListener *windowEventListener);

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

	HWND _window = 0;

	std::list<IEWindowEventListener *> _windowEventListeners;	

	bool _paused;
	float _framesPerSeconds;
	float _frameTime;	
};

