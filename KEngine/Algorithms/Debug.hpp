#pragma once

#include <iostream>
#include <chrono>


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

#include <Windows.h>

namespace ke
{

	/// <summary>
	/// namespace that stores thigs that help with console debugging
	/// </summary>
	namespace debug
	{

		/// <summary>
		/// sets console cursor position
		/// </summary>
		/// <param name="x">positon in the given column</param>
		/// <param name="y">column</param>
		inline void gotoxy(int x = 0, int y = 0)
		{
			COORD c = { x, y };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
		}

	} // namespace debug

} // namespace ke

#endif


namespace ke 
{
	namespace debug
	{

		/// <summary>
		/// helps with measuring time of any operations
		/// </summary>
		class Benchmark
		{
		public:

			/// <summary>
			/// Starts timer
			/// </summary>
			/// <param name="name">name printed with time</param>
			Benchmark(const std::string& name = "Elapsed time");

			~Benchmark();

			/// <summary>
			/// Stops timer and prints the time
			/// </summary>
			void Stop();

		private:

			std::chrono::time_point<std::chrono::high_resolution_clock> m_start_time;
			std::string m_name;
			bool m_stopped;
		};



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// prints SFML 2D vector
		/// </summary>
		/// <remarks>
		/// it can be anything, but it has to have .x and .y members
		/// </remarks>
		/// <typeparam name="T">2D vector class</typeparam>
		/// <param name="vector">2D vector</param>
		/// <param name="vector_name">name printed with vector coords</param>
		template <typename T>
		inline void printVector2(const T& vector, const std::string& vector_name = "Vector2")
		{
			std::cout << vector_name << ": x: " << vector.x << "  y: " << vector.y << '\t' << " | " << '\t' <<
				vector.x << ' ' << vector.y << '\n';
		}


		////////////////////////////////


		/// <summary>
		/// prints SFML 3D vector
		/// </summary>
		/// <remarks>
		/// it can be anything, but it has to have .x, .y and .z members
		/// </remarks>
		/// <typeparam name="T">3D vector class</typeparam>
		/// <param name="vector">3D vector</param>
		/// <param name="vector_name">name printed with vector coords</param>
		template <typename T>
		inline void printVector3(const T& vector, const std::string& vector_name = "Vector3")
		{
			std::cout << vector_name << ": x: " << vector.x << "  y: " << vector.y << "  z: " << vector.z << '\t' << " | " << '\t' <<
				vector.x << ' ' << vector.y << ' ' << vector.z << '\n';
		}


		////////////////////////////////


		/// <summary>
		/// prints KEngie or SFML color
		/// </summary>
		/// <typeparam name="T">color class</typeparam>
		/// <param name="color">KEngie, SFML or cusotm class color</param>
		/// <param name="color_name">name printed with color</param>
		template <typename T>
		inline void printColor(const T& color, const std::string& color_name = "Color")
		{
			std::cout << color_name << ": R: " << static_cast<float>(color.r) << "  " << "G: " << static_cast<float>(color.g) << "  " << "B: " << static_cast<float>(color.b) << "  " << "A: " << static_cast<float>(color.a) << '\t' << " | " << '\t' <<
				static_cast<float>(color.r) << ' ' << static_cast<float>(color.g) << ' ' << static_cast<float>(color.b) << ' ' << static_cast<float>(color.a) << '\n';
		}


		////////////////////////////////


		/// <summary>
		/// prints SFML 4D vector
		/// </summary>
		/// <remarks>
		/// it can be anything, but it has to have .x, .y, .z and .v members
		/// </remarks>
		/// <typeparam name="T">4D vector class</typeparam>
		/// <param name="vector">4D vector</param>
		/// <param name="vector_name">name printed with vector coords</param>
		template <typename T>
		inline void printVector4(const T& vector, const std::string& vector_name = "Vector4")
		{
			std::cout << vector_name << ": x: " << vector.x << "  y: " << vector.y << "  z: " << vector.z << "  v: " << vector.v << '\t' << " | " << '\t' <<
				vector.x << ' ' << vector.y << ' ' << vector.z << ' ' << vector.v << '\n';
		}

	} // namespace debug

} // namespace ke