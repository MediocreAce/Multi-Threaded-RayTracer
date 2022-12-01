#pragma once
///Include the ability to use std::chrono functions
/// used to caluclate accurate timings
#include <chrono>
///Used for std::setprecision
#include <iomanip>
///Used to display timing info to the console
#include "Log.h"


///Class keeps track of how long since the timer was created
/// if used within a scope, will delete itself and display
///  how long that scope took
class Timer
{
private:
	///Timer's name, used to specify between timers
	const char* name;
	///The starting point value
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;

public:
	///The constructor requiring the timer's name
	Timer(const char* _name);
	///The deconstructor which calls stop()
	~Timer();

	///std::cout's the time taken since the timer was created
	void stop();
};