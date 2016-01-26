#pragma once
class IEAppStatsListener
{
public:
	virtual ~IEAppStatsListener() {}

	virtual void BeginUpdate() = 0;
	virtual void UpdateFramesPerSeconds(float framesPerSeconds) = 0;
	virtual void UpdateFrameTime(float frameTime) = 0;
	virtual void EndUpdate() = 0;
};