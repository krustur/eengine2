#include <windows.h>
#include "ETimer.h"

ETimer::ETimer() :
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

float ETimer::GetTotalTime()const
{
	if (_isPaused)
	{
		return (float)(((_pauseTime - _pausedTimeSpan) - _initTime)*_secondsPerCounter);
	}

	return (float)(((_currentTime - _pausedTimeSpan) - _initTime)*_secondsPerCounter);
}

float ETimer::GetDeltaTime()const
{
	return (float)_deltaTime;
}


void ETimer::Init()
{
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	_initTime = currTime;
	_previousTime = currTime;
	_pauseTime = 0;
	_isPaused = false;
}


void ETimer::Tick()
{
	if (_isPaused)
	{
		_deltaTime = 0.0;
		return;
	}

	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	_currentTime = currTime;

	_deltaTime = (_currentTime - _previousTime)*_secondsPerCounter;

	_previousTime = _currentTime;

	if (_deltaTime < 0.0)
	{
		_deltaTime = 0.0;
	}
}

void ETimer::Resume()
{
	__int64 startTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);
	
	if (_isPaused)
	{
		_pausedTimeSpan += (startTime - _pauseTime);

		_previousTime = startTime;
		_pauseTime = 0;
		_isPaused = false;
	}
}

void ETimer::Paus()
{
	if (!_isPaused)
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		_pauseTime = currTime;
		_isPaused = true;
	}
}
