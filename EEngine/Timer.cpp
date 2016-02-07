#include <windows.h>
#include "Timer.h"

namespace EEngine
{
	Timer::Timer() :
		_secondsPerCounter(0.0),
		_deltaTime(-1.0),
		_initTime(0),
		_pausedTimeSpan(0),
		_previousTime(0),
		_currentTime(0),
		_isPaused(false),
		_pauseTime(0)
	{
		__int64 countsPerSec;
		QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
		_secondsPerCounter = 1.0 / (double)countsPerSec;
	}

	float Timer::GetTotalTime()const
	{
		if (_isPaused)
		{
			return (float)(((_pauseTime - _pausedTimeSpan) - _initTime)*_secondsPerCounter);
		}

		return (float)(((_currentTime - _pausedTimeSpan) - _initTime)*_secondsPerCounter);
	}

	float Timer::GetDeltaTime()const
	{
		return (float)_deltaTime;
	}


	void Timer::Init()
	{
		__int64 currentTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

		_initTime = currentTime;
		_previousTime = currentTime;
		_pauseTime = 0;
		_isPaused = false;
	}


	void Timer::Tick()
	{
		if (_isPaused)
		{
			_deltaTime = 0.0;
			return;
		}

		__int64 currentTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
		_currentTime = currentTime;

		_deltaTime = (_currentTime - _previousTime)*_secondsPerCounter;

		_previousTime = _currentTime;

		if (_deltaTime < 0.0)
		{
			_deltaTime = 0.0;
		}
	}

	void Timer::Resume()
	{
		__int64 currentTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

		if (_isPaused)
		{
			_pausedTimeSpan += (currentTime - _pauseTime);

			_previousTime = currentTime;
			_pauseTime = 0;
			_isPaused = false;
		}
	}

	void Timer::Pause()
	{
		if (!_isPaused)
		{
			__int64 currentTime;
			QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

			_pauseTime = currentTime;
			_isPaused = true;
		}
	}
}