#include "Debug.hpp"

namespace ke 
{
	namespace debug
	{

		Benchmark::Benchmark(const std::string& name)
			: m_name(name)
		{
			m_start_time = std::chrono::high_resolution_clock::now();
		}

		Benchmark::~Benchmark()
		{
		}

		void Benchmark::Stop()
		{
			auto end_time = std::chrono::high_resolution_clock::now();

			auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_start_time).time_since_epoch().count();
			auto end = std::chrono::time_point_cast<std::chrono::microseconds>(end_time).time_since_epoch().count();

			std::cout << m_name << ": " << end - start << '\n';
		}

	} // namespace debug

} // namespace ke
