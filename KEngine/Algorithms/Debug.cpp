#include "Debug.hpp"

namespace ke 
{
	namespace debug
	{

		Benchmark::Benchmark(const std::string& name)
			: m_name(name)
			, m_stopped(false)
		{
			m_start_time = std::chrono::high_resolution_clock::now();
		}

		Benchmark::~Benchmark()
		{
			if (!m_stopped)
				this->Stop();
		}

		void Benchmark::Stop()
		{
			auto end_time = std::chrono::high_resolution_clock::now();

			auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_start_time).time_since_epoch().count();
			auto end = std::chrono::time_point_cast<std::chrono::microseconds>(end_time).time_since_epoch().count();

			std::cout << m_name << ": " << end - start << '\n';

			m_stopped = true;
		}

	} // namespace debug

} // namespace ke
