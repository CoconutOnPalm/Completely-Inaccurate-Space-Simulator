#include "Time.hpp"

namespace ke
{

	Timer::Timer(bool start)
	{
		m_last_time = 0;

		if (start)
			m_start_time = std::chrono::high_resolution_clock::now();
	}


	//////////////////////////


	Timer::~Timer()
	{
		this->Stop();
	}


	////////////////////////////////////////////////////


	void Timer::Start()
	{
		m_start_time = std::chrono::high_resolution_clock::now();
	}


	//////////////////////////


	long long Timer::Stop()
	{
		auto end_time = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_start_time).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(end_time).time_since_epoch().count();

		m_last_time = end - start;
		return m_last_time;
	}


	//////////////////////////


	long long Timer::getElapsedTime()
	{
		auto end_time = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_start_time).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(end_time).time_since_epoch().count();

		m_last_time = end - start;
		return m_last_time;
	}


	////////////////////////////////////////////////////


	void Timer::printTime(const std::string& time_name)
	{
		std::cout << time_name << ": " << m_last_time << '\n';
	}


} // namespace ke