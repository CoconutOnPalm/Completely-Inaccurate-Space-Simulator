#pragma once


#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <cmath>

#include "RandomGenerator.hpp"
#include "../Structures/Data.hpp"


/// repeats stuff t times - "for (int i = 0; i < 0; i++)" macro
#define keRepeat(t) for (int i = 0; i < t; i++)


namespace ke
{

	/// <summary>
	/// Here you can find some crypto functions
	/// </summary>
	namespace protect
	{

		/// <summary>
		/// Encrypts message with random generated key
		/// </summary>
		/// <seealso>
		/// Decode
		/// </seealso>
		/// <param name="decoded">raw message you want to encrypt</param>
		/// <returns>encrypted message</returns>
		std::string Encrypt(const std::string& decoded);

		/// <summary>
		/// Decodes messaged encrypted with ke::Protect::Encrypt(...) function
		/// </summary>
		/// <seealso>
		/// Encrypt
		/// </seealso>
		/// <param name="encrypted">encrypted message</param>
		/// <returns>decoded message</returns>
		std::string Decode(const std::string& encrypted);


		////////////////////////////////


		/// <summary>
		/// Encrypts message with custom key
		/// </summary>
		/// <seealso>
		/// CustomDecode
		/// </seealso>
		/// <param name="decoded">raw massage you want to encrypt</param>
		/// <param name="key">custom key</param>
		/// <returns>encrypted message</returns>
		std::string CustomEncrypt(const std::string& decoded, int key);

		/// <summary>
		/// Decodes message encrypted with ke::Protect::CustomEncryt(...) function
		/// </summary>
		/// <seealso>
		/// CustomEncrypt
		/// </seealso>
		/// <param name="encrypted">encryted message</param>
		/// <param name="key">custom key (oryginal and given keys must be the same)</param>
		/// <returns>decoded message</returns>
		std::string CustomDecode(const std::string& encrypted, int key);


		////////////////////////////////


		/// <summary>
		/// Encrypts message with custom advanced key
		/// </summary>
		/// <param name="decoded">raw massage you want to encrypt</param>
		/// <param name="key">custom advanced key</param>
		/// <returns>encrypted message</returns>
		std::string AdvancedCustomEncrypt(const std::string& decoded, std::string key);

		/// <summary>
		/// Decodes message encrypted with ke::Protect::AdvancedCustomEncryt(...) function
		/// </summary>
		/// <param name="encrypted">encrypted message</param>
		/// <param name="key">custom advanced key (oryginal and given keys must be the same)</param>
		/// <returns>decoded message</returns>
		std::string AdvancedCustomDecode(const std::string& encrypted, std::string key);

	} // namespace Protect





	////////////////////////////////////////////////////////////////

	// inline and template functions


	/// <summary>
	/// namespace that stores important std functions that didn't exist when they were written, mostly from code::blocks era
	/// </summary>
	namespace fixed
	{

		/// <summary>
		/// Ancient string to wstring from code::blocks era
		/// </summary>
		/// <param name="str">string</param>
		/// <returns>wstring made from string</returns>
		inline std::wstring stow(const std::string& str)
		{
			std::wstring temp(str.begin(), str.end());
			return temp;
		}


		inline std::string wtos(const std::wstring& str)
		{
			std::string temp(str.begin(), str.end());
			return temp;
		}


		////////////////


		/// <summary>
		/// Ancient function from code::blocks era
		/// </summary>
		/// <typeparam name="T">a variable</typeparam>
		/// <param name="n">variable you want to change</param>
		/// <returns>T change to wstring</returns>
		template <typename T>
		inline std::wstring to_wstring(T n)
		{
			std::wstringstream stm;
			stm << n;
			return stm.str();
		}

	} // namespace fixed


	////////////////////////////////



	/// <summary>
	/// Signum math function
	/// </summary>
	/// <typeparam name="T">variable</typeparam>
	/// <param name="val">used variable</param>
	/// <returns>sgn(val)</returns>
	template <typename T>
	inline int sgn(T val)
	{
		return (T(0) < val) - (val < T(0));
	}



	////////////////////////////////



	/// <summary>
	/// prints error to the console without calling exception
	/// </summary>
	/// <param name="function_name">place where error happened</param>
	/// <param name="message">printed error message / description</param>
	/// <param name="error_type">custom error type (ERROR, WARNING, FATAL_ERROR... You can type what you want (even cute bunny!))</param>
	inline void throw_error(const std::string& function_name, const std::string& message, const std::string& error_type = "ERROR")
	{
		std::cout << "[" << error_type << "] in  " << function_name << " :  " << message << '\n';
	}


	////////////////


	/// <summary>
	/// prints note to the console
	/// </summary>
	/// <param name="message">printed note</param>
	inline void print_note(const std::string& message)
	{
		std::cout << " [note]: " << message << '\n';
	}



	////////////////////////////////



	/// <summary>
	/// Radians to Degrees
	/// </summary>
	/// <param name="radians"></param>
	/// <returns>degrees</returns>
	inline float RTD(float radians)
	{
		return radians * TO_DEG;
	}


	/// <summary>
	/// Radians to Degrees
	/// </summary>
	/// <param name="radians"></param>
	/// <returns>degrees</returns>
	inline double RTD(double radians)
	{
		return radians * TO_DEG;
	}



	/// <summary>
	/// Radians to Degrees
	/// </summary>
	/// <typeparam name="T">radians variable type</typeparam>
	/// <param name="radians"></param>
	/// <returns>degrees</returns>
	template <typename T>
	inline double RTD(T radians)
	{
		return radians * TO_DEG;
	}



	////////////////


	/// <summary>
	/// Degrees to Radians
	/// </summary>
	/// <param name="degrees"></param>
	/// <returns>radians</returns>
	inline float DTR(float degrees)
	{
		return degrees * TO_RAD;
	}


	/// <summary>
	/// Degrees to Radians
	/// </summary>
	/// <param name="degrees"></param>
	/// <returns>radians</returns>
	inline double DTR(double degrees)
	{
		return degrees * TO_RAD;
	}


	/// <summary>
	/// Degrees to Radians
	/// </summary>
	/// <typeparam name="T">degrees variable type</typeparam>
	/// <param name="degrees"></param>
	/// <returns>radians</returns>
	template <typename T>
	inline double DTR(T degrees)
	{
		return degrees * TO_RAD;
	}


	////////////////////////////////



	/// <summary>
	/// checks if variable is within the range, and if not, corrects it
	/// </summary>
	/// <typeparam name="T">Variable typename</typeparam>
	/// <typeparam name="Tg">Range typename</typeparam>
	/// <param name="variable">guarded variable</param>
	/// <param name="lRange">lower range</param>
	/// <param name="hRange">higher range</param>
	template <typename T, typename Tg>
	inline bool varGuard(T& variable, Tg lRange, Tg hRange)
	{
		if (variable < lRange)
		{
			variable = lRange;
			return true;
		}

		if (variable > hRange)
		{
			variable = hRange;
			return true;
		}

		return false;
	}



	/// <summary>
	/// checks if variable is in the given range
	/// </summary>
	/// <typeparam name="T">Variable typename</typeparam>
	/// <typeparam name="Tg">Range bounds typename</typeparam>
	/// <param name="variable">checked variable</param>
	/// <param name="lbound">left bound</param>
	/// <param name="rbound">right bound</param>
	/// <returns>if in range -> true</returns>
	template <typename T, typename Tg>
	inline bool inRange(T variable, Tg lbound, Tg rbound)
	{
		return variable > lbound && variable < rbound;
	}



	/// <summary>
	/// checks if variable is in or equal to the given range
	/// </summary>
	/// <typeparam name="T">Variable typename</typeparam>
	/// <typeparam name="Tg">Range bounds typename</typeparam>
	/// <param name="variable">checked variable</param>
	/// <param name="lbound">left bound</param>
	/// <param name="rbound">right bound</param>
	/// <returns>if in or equal the range -> true</returns>
	template <typename T, typename Tg>
	inline bool ionRange(T variable, Tg lbound, Tg rbound)
	{
		return variable >= lbound && variable <= rbound;
	}



	////////////////////////////////



	
	/// <summary>
	/// Converts SFML Vector2<float> to SFML Vector2<double>
	/// </summary>
	/// <param name="vector2">SFML Vector2f</param>
	/// <returns>SFML Vector2<fouble></returns>
	inline sf::Vector2<double> toVec2d(const sf::Vector2f& vector2)
	{
		return sf::Vector2<double>(vector2);
	}


	/// <summary>
	/// Convers two floats to SFML Vecotr2<double>
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <returns>SFML Vector2<double></returns>
	inline sf::Vector2<double> toVec2d(const float x, const float y)
	{
		return sf::Vector2<double>(x, y);
	}


	template <typename T, typename U>
	inline bool areClose(const sf::Vector2<T>& vec1, const sf::Vector2<U>& vec2, double Epsilon = 0.001)
	{
		return (abs(vec1.x - vec2.x) <= Epsilon && abs(vec1.y - vec2.y) <= Epsilon);
	}

} // namespace ke