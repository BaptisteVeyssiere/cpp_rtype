#ifndef TIMER_HPP_
# define TIMER_HPP_

#include <chrono>

class Timer
{
public:
	Timer();
	~Timer();

private:
	double									speed;
	int										alarm;
	std::chrono::system_clock::time_point	start;
	bool									run;

public:
	void	setAlarm(const int milliseconds);
	bool	checkAlarm() noexcept;
	bool	isRunning() const noexcept;
	void	setSpeed(const double requested_speed);
};

#endif // !TIMER_HPP_