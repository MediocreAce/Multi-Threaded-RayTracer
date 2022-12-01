#include "Timer.h"


///The constructor requiring the timer's name
Timer::Timer(const char* _name)
	: name(_name)
{
	///Set the start time of the timer
	m_StartTimepoint = std::chrono::high_resolution_clock::now();
}

///The deconstructor which calls stop()
/// Used when a Timer's obect is deleted/out of scope
Timer::~Timer()
{
	stop();
}

///std::cout's the time taken since the timer was created
void Timer::stop()
{
	///Set the end value to the current time
	auto endTimepoint = std::chrono::high_resolution_clock::now();
	///Set start and end timecodes, to long longs
	auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
	auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

	///Calculate the seconds took by subtracting
	/// then dividing to turn into seconds
	auto duration = (end - start) / 1e+6;
	///Convert from seconds to miliseconds
	double ms = duration * 0.001;

	///Log the seconds and miliseconds to the console
	/// (with colors to read easier)
	LOG(B_YELLOW << name << "\t" << B_BLUE << std::setprecision(3) << duration << B_MAGENTA << "s"
		<< B_GREEN << "\t(" << std::setprecision(8) << ms << B_MAGENTA << "ms" << B_GREEN << ")");
}