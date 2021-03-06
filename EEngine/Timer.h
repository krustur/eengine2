#pragma once

namespace EEngine
{
	class Timer
	{
	public:
		explicit Timer();

		void Init();
		void Tick();
		void Pause();
		void Resume();

		float GetTotalTime() const;
		float GetDeltaTime() const;

	private:
		double _secondsPerCounter;
		double _deltaTime;

		__int64 _initTime;
		__int64 _pausedTimeSpan;
		__int64 _pauseTime;
		__int64 _previousTime;
		__int64 _currentTime;

		bool _isPaused;
	};
}