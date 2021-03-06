#pragma once

#include <windows.h>

namespace bengine
{
	class Timer
	{
	private:
		LARGE_INTEGER _start;
		double _frequency;

	public:
		Timer()
		{
			LARGE_INTEGER frequency;
			QueryPerformanceFrequency(&frequency);
			_frequency = 1.0f / frequency.QuadPart;
			QueryPerformanceCounter(&_start);
		}

		inline void reset()
		{
			QueryPerformanceCounter(&_start);
		}

		inline float elapsed()
		{
			LARGE_INTEGER current;
			QueryPerformanceCounter(&current);
			unsigned __int64 cycles = current.QuadPart - _start.QuadPart;
			return (float)(cycles * _frequency);
		}
	};
}
