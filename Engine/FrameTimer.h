#pragma once

#include <chrono>

class FrameTimer
{
public:
	FrameTimer() = default;
	FrameTimer(const FrameTimer& rhs) = delete;
	FrameTimer& operator=(const FrameTimer& rhs) = delete;
	~FrameTimer() = default;

	float Mark();

private:
	std::chrono::steady_clock::time_point mLast = std::chrono::steady_clock::now();
};

