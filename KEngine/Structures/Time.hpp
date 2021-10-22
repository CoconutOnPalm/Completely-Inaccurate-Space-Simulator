#pragma once

#include <iostream>
#include <chrono>
#include <ctime>
#include "../Structures/Data.hpp"


namespace ke
{

	/// <summary>
	/// Timer is class that counts time using hight resolusion std::chrono clock
	/// </summary>
	class Timer
	{
	public:

		/// <summary>
		/// starts the timer if argument is true
		/// </summary>
		/// <param name="start">true - constructor starts timer, otherwise you have to start it by .Stop() method</param>
		Timer(bool start = true);

		/// <summary>
		/// stops the timer if has not benn stopped before
		/// </summary>
		~Timer();


		////////////////////////////////


		/// <summary>
		/// starts the timer manually
		/// </summary>
		void Start();

		/// <summary>
		/// stops the timer
		/// </summary>
		/// <returns>passed time</returns>
		long long Stop();


		/// <summary>
		/// returns the elapsed time from the beginning
		/// </summary>
		/// <remarks>
		/// does the same thing as Stop()
		/// </remarks>
		/// <returns></returns>
		long long getElapsedTime();


		////////////////////////////////


		/// <summary>
		/// returns last stopped time
		/// </summary>
		/// <returns></returns>
		inline long long getTime() const;

		/// <summary>
		/// prints last stopped time
		/// </summary>
		/// <param name="time_name"></param>
		void printTime(const std::string& time_name = "Time");



	private:

		std::chrono::time_point<std::chrono::high_resolution_clock> m_start_time;
		long long m_last_time;
	};


	////////////////////////////////


	inline long long Timer::getTime() const
	{
		return m_last_time;
	}

} // namespace ke