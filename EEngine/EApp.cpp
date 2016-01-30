#include <sstream>
#include "EApp.h"
#include "ELog.h"

EApp::EApp(HINSTANCE hInstance, HWND windowHandle)	:
	_hInstance(hInstance),
	_windowHandle(windowHandle),
	_eLog(ELog(L"EApp")),
	_eRenderer(ERenderer(windowHandle)),
	_eTimer(ETimer()),
	_paused(false),
	_eEffect(nullptr),
	_eAppStatsListener(nullptr)
{	
}

EApp::~EApp()
{
}

void EApp::Init()
{
	_eRenderer.Init();
}

int EApp::Run()
{
	MSG message = { 0 };

	_eTimer.Init();

	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			_eTimer.Tick();

			UpdateStats();

			if (!_paused)
			{
				if (_eEffect != nullptr)
				{
					_eEffect->UpdateScene(_eTimer.GetDeltaTime());
					_eEffect->DrawScene();
				}
			}
			else
			{
				Sleep(100);
			}
		}
	}	

	return static_cast<int>(message.wParam);
}

ERenderer * EApp::GetRenderer()
{
	return &_eRenderer;
}

void EApp::SetEffect(IEEffect *eEffect)
{
	_eEffect = eEffect;
}

void EApp::SetAppStatsListener(IEAppStatsListener *eAppStatsListener)
{
	_eAppStatsListener = eAppStatsListener;
}

void EApp::UpdateStats()
{
	if (_eAppStatsListener != nullptr)
	{
		_eAppStatsListener->BeginUpdate();
		_eAppStatsListener->UpdatePausedState(_paused);
	}

	static int frameCount = 0;
	static float timeElapsed = 0.0f;

	frameCount++;

	if ((_eTimer.GetTotalTime() - timeElapsed) >= 1.0f)
	{
		float framesPerSeconds = (float)frameCount;
		float frameTime = 1000.0f / framesPerSeconds;

		if (_eAppStatsListener != nullptr)
		{
			_eAppStatsListener->UpdateFramesPerSeconds(framesPerSeconds);
			_eAppStatsListener->UpdateFrameTime(frameTime);
		}

		frameCount = 0;
		timeElapsed += 1.0f;
	}

	if (_eAppStatsListener != nullptr)
	{
		_eAppStatsListener->EndUpdate();
	}
}

void EApp::OnActivate()
{
	_paused = false;
	_eTimer.Resume();
}

void EApp::OnDeactivate()
{
	_paused = true;
	_eTimer.Pause();
}

void EApp::OnMouseDown(WPARAM buttonState, int x, int y)
{
}

void EApp::OnMouseUp(WPARAM buttonState, int x, int y)
{
}

void EApp::OnMouseMove(WPARAM buttonState, int x, int y)
{
}