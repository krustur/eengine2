#pragma once

namespace EEngine
{
	class IAppStatsListener
	{
	public:
		virtual ~IAppStatsListener() {}

		virtual void BeginUpdate() = 0;
		virtual void UpdatePausedState(bool paused) = 0;
		virtual void UpdateFramesPerSeconds(float framesPerSeconds) = 0;
		virtual void UpdateFrameTime(float frameTime) = 0;
		virtual void EndUpdate() = 0;
	};
}