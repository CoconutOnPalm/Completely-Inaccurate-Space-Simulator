#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Algor.hpp"

namespace ke
{

	/// <summary>
	/// KEngine Random can generate random numbers and custom seeds
	/// </summary>
	class Random
	{
	public:


		// default consturctor, deleted constructors and deleted operators
		Random();
		Random(const Random&) = delete;
		void operator= (const Random&) = delete;



		////////////////////////////////



		/// <summary>
		/// Typical Singleton Get() function, better not use it
		/// </summary>
		/// <returns>KEngie Random instance</returns>
		static Random& Get();



		////////////////////////////////



		/// <summary>
		/// generates random seed with custom srand() input
		/// </summary>
		/// <param name="seed">custom seed</param>
		static void getnerateSeed(unsigned int seed);


		/// <summary>
		/// generates random seed (srand(time(0)))
		/// </summary>
		static void geterateRandomSeed();


		////////////////


		/// <summary>
		/// sets (KEngine Random member) seed 
		/// </summary>
		/// <param name="seed">given seed</param>
		static void setSeed(unsigned int seed);


		/// <summary>
		/// returns (KEngine Random - member) seed
		/// </summary>
		/// <returns>this->seed</returns>
		static unsigned int getSeed();



		////////////////////////////////



		/// <summary>
		/// draws a number, and then if it's inside chance range, returns true - it's like pack opening system in FIFA, but this one accually works :)
		/// </summary>
		/// <param name="percent">chance in percent (e.g. 69 - there is 69% it will return true)</param>
		/// <returns>if it hits the range - true</returns>
		static bool Chance(float percent);


		/// <summary>
		/// generates random float from the given range
		/// </summary>
		/// <param name="min">lower range</param>
		/// <param name="max">higher range</param>
		/// <returns>random float </returns>
		static float Float(float min, float max);


		/// <summary>
		/// generates random double from the given range
		/// </summary>
		/// <param name="min">lower range</param>
		/// <param name="max">higher range</param>
		/// <returns>random double </returns>
		static double Double(double min, double max);


		/// <summary>
		/// generates random integer from the given range
		/// </summary>
		/// <param name="min">lower range</param>
		/// <param name="max">higher range</param>
		/// <returns>random int </returns>
		static int Int(int min, int max);


		/// <summary>
		/// generates random character from the given range
		/// </summary>
		/// <param name="min">lower range</param>
		/// <param name="max">higher range</param>
		/// <returns>random char </returns>
		static char Char(char min, char max);

		
		////////////////


		/// <summary>
		/// generates random number different that the last one
		/// </summary>
		/// <param name="min">lower range</param>
		/// <param name="max">higher range</param>
		/// <returns>random int</returns>
		static int Unique(int min, int max);


	private:

		int m_last;				// last number geberated by Unique()
		unsigned int m_seed;	// srand seed
	};

} // namespace ke