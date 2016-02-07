#include "App.h"

#include <sstream>
#include <iostream>

#include "Logger.h"

namespace EEngine
{
	App::App(HINSTANCE hInstance, HWND windowHandle) :
		_hInstance(hInstance),
		_windowHandle(windowHandle),
		_logger(L"App"),
		_renderer(windowHandle),
		_timer(Timer()),
		_paused(false),
		_effect(nullptr),
		_appStatsListener(nullptr)
	{
	}

	App::~App()
	{
	}

	void App::Init()
	{
		_renderer.Init();
	}

	int App::Run()
	{
		MSG message = { 0 };

		_timer.Init();

		while (message.message != WM_QUIT)
		{
			if (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
			else
			{
				_timer.Tick();

				UpdateStats();

				if (!_paused)
				{
					if (_effect != nullptr)
					{
						_effect->UpdateScene(_timer.GetDeltaTime());
						_effect->DrawScene();
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

	Renderer * App::GetRenderer()
	{
		return &_renderer;
	}

	void App::SetEffect(IEffect *effect)
	{
		_effect = effect;
	}

	void App::SetAppStatsListener(IAppStatsListener *appStatsListener)
	{
		_appStatsListener = appStatsListener;
	}

	void App::UpdateStats()
	{
		if (_appStatsListener != nullptr)
		{
			_appStatsListener->BeginUpdate();
			_appStatsListener->UpdatePausedState(_paused);
		}

		static int frameCount = 0;
		static float timeElapsed = 0.0f;

		frameCount++;

		if ((_timer.GetTotalTime() - timeElapsed) >= 1.0f)
		{
			float framesPerSeconds = (float)frameCount;
			float frameTime = 1000.0f / framesPerSeconds;

			if (_appStatsListener != nullptr)
			{
				_appStatsListener->UpdateFramesPerSeconds(framesPerSeconds);
				_appStatsListener->UpdateFrameTime(frameTime);
			}

			frameCount = 0;
			timeElapsed += 1.0f;
		}

		if (_appStatsListener != nullptr)
		{
			_appStatsListener->EndUpdate();
		}
	}

	void App::OnActivate()
	{
		_paused = false;
		_timer.Resume();
	}

	void App::OnDeactivate()
	{
		_paused = true;
		_timer.Pause();
	}

	void App::OnMouseDown(WPARAM buttonState, int x, int y)
	{
	}

	void App::OnMouseUp(WPARAM buttonState, int x, int y)
	{
	}

	void App::OnMouseMove(WPARAM buttonState, int x, int y)
	{
	}

	void App::OnResize(int width, int height) {}
}