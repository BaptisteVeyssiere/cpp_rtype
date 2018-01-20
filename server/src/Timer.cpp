#include <stdexcept>
#include "Timer.hpp"

Timer::Timer()
	: speed(1.0), alarm(0), start(std::chrono::system_clock::now()), run(false)
{
}

Timer::~Timer()
{}

void	Timer::setAlarm(const int milliseconds)
{
	if (this->run)
		throw std::logic_error("Alarm is already on");
	this->start = std::chrono::system_clock::now();
	this->alarm = milliseconds / this->speed;
	this->run = true;
}

bool	Timer::checkAlarm() noexcept
{
	if (!this->run)
		return (false);
	auto current = std::chrono::system_clock::now();
	auto ms_ellapsed = std::chrono::duration_cast<std::chrono::milliseconds>(current - this->start);
	if (ms_ellapsed.count() >= this->alarm)
	{
		this->run = false;
		return (true);
	}
	return (false);
}

bool	Timer::isRunning() const noexcept
{
	return (this->run == true ? true : false);
}

void	Timer::setSpeed(const double requested_speed)
{
	if (requested_speed > 0 && !this->run)
		this->speed = requested_speed;
	else if (this->run)
		throw std::logic_error("Alarm is already on");
	else
		throw std::logic_error("Invalid null or negative speed");
}