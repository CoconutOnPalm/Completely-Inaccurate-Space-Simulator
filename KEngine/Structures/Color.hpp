#pragma once

#include <SFML/Graphics.hpp>


namespace ke
{

	/// <summary>
	/// KengineColor is a color representation with variables you want
	/// </summary>
	/// <typeparam name="T">Color type</typeparam>
	template <typename T>
	struct Color
	{


		/// <summary>
		/// Color default constructor
		/// </summary>
		Color();


		/// <summary>
		/// Color costructor
		/// </summary>
		/// <param name="r">red component</param>
		/// <param name="g">green component</param>
		/// <param name="b">blue component</param>
		/// <param name="a">alpha (opacity) component</param>
		Color(T r, T g, T b, T a = 255);


		/// <summary>
		/// Color constructor using SFML color
		/// </summary>
		/// <param name="sf_color">SFML color</param>
		Color(const sf::Color& sf_color);


		/// <summary>
		/// Color destructor
		/// </summary>
		~Color() {};


		/// <summary>
		/// operator = using SFML color
		/// </summary>
		/// <param name="color">SFML color</param>
		void operator=(const sf::Color& color);


		/// <summary>
		/// operator = using KEngie color
		/// </summary>
		/// <param name="color">KEngie color</param>
		void operator=(const Color<T>& color);


		/// <summary>
		/// sets color, works like constructor
		/// </summary>
		/// <param name="r">red component</param>
		/// <param name="g">green component</param>
		/// <param name="b">blue component</param>
		/// <param name="a">alpha (opacity) component</param>
		void setColor(T r = 255, T g = 255, T b = 255, T a = 255);


		/// <summary>
		/// sets color, works like constructor
		/// </summary>
		/// <param name="sf_color">SFML color</param>
		void setColor(const sf::Color& sf_color);


		/// <summary>
		/// returns current color in SFML color repraesentation
		/// </summary>
		/// <returns>SFML color</returns>
		const inline sf::Color& getSFMLColor() const;


		T r, g, b, a; // red, green, blue, alpha (opacity)
	};





	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






	template <typename T>
	Color<T>::Color() : r(0), g(0), b(0), a(0) {};


	template <typename T>
	Color<T>::Color(T r, T g, T b, T a)
		: r(r)
		, g(g)
		, b(b)
		, a(a)
	{

	}


	template <typename T>
	Color<T>::Color(const sf::Color& sf_color)
	{
		this->r = static_cast<T>(sf_color.r);
		this->g = static_cast<T>(sf_color.g);
		this->b = static_cast<T>(sf_color.b);
		this->a = static_cast<T>(sf_color.a);
	}


	//////////////////////////


	template <typename T>
	void Color<T>::setColor(T r, T g, T b, T a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}


	template <typename T>
	void Color<T>::setColor(const sf::Color& sf_color)
	{
		this->r = static_cast<T>(sf_color.r);
		this->g = static_cast<T>(sf_color.g);
		this->b = static_cast<T>(sf_color.b);
		this->a = static_cast<T>(sf_color.a);
	}


	//////////////////////////


	template<typename T>
	inline const sf::Color& Color<T>::getSFMLColor() const
	{
		return sf::Color(r, g, b, a);
	}


	//////////////////////////


	template <typename T>
	void Color<T>::operator=(const sf::Color& color)
	{
		this->r = static_cast<T>(color.r);
		this->g = static_cast<T>(color.g);
		this->b = static_cast<T>(color.b);
		this->a = static_cast<T>(color.a);
	}


	template <typename T>
	void Color<T>::operator=(const Color<T>& color)
	{
		this->r = static_cast<T>(color.r);
		this->g = static_cast<T>(color.g);
		this->b = static_cast<T>(color.b);
		this->a = static_cast<T>(color.a);
	}



	////////////////////////////////////////////////////



	template <typename T>
	bool operator==(const Color<T>& left, const Color<T>& right)
	{
		if (abs(left.r - right.r) <= 0.0001f &&
			abs(left.g - right.g) <= 0.0001f &&
			abs(left.b - right.b) <= 0.0001f &&
			abs(left.a - right.a) <= 0.0001f) 
		return true;

		return false;
	}


	//////////////////////////


	template <typename T>
	bool operator!=(const Color<T>& left, const Color<T>& right)
	{
		return !(left == right);
	}


	//////////////////////////


	template <typename T, typename T_val>
	void operator+=(Color<T>& left, T_val value)
	{
		if (left.r + value <= 255) left.r += value;
		if (left.g + value <= 255) left.g += value;
		if (left.b + value <= 255) left.b += value;
		if (left.a + value <= 255) left.a += value;
	}


	//////////////////////////


	template <typename T, typename T_val>
	void operator-=(Color<T>& left, T_val value)
	{
		if (left.r - value >= 0) left.r -= value;
		if (left.g - value >= 0) left.g -= value;
		if (left.b - value >= 0) left.b -= value;
		if (left.a - value >= 0) left.a -= value;
	}


	//////////////////////////


	template <typename T, typename T_val>
	Color<T> operator+(const Color<T>& left, T_val value)
	{
		Color<T> result;

		if (left.r + value <= 255) result.r = left.r + value;
		if (left.g + value <= 255) result.g = left.g + value;
		if (left.b + value <= 255) result.b = left.b + value;
		if (left.a + value <= 255) result.a = left.a + value;

		return result;
	}


	//////////////////////////


	template <typename T, typename T_val>
	Color<T> operator-(const Color<T>& left, T_val value)
	{
		Color<T> result;

		if (left.r - value >= 0) result.r = left.r - value;
		if (left.g - value >= 0) result.g = left.g - value;
		if (left.b - value >= 0) result.b = left.b - value;
		if (left.a - value >= 0) result.a = left.a - value;

		return result;
	}



	////////////////////////////////////////////////////



	// some typedefs for popular types

	typedef Color<float>         Colorf; // float
	typedef Color<double>        Colord; // double
	typedef Color<int>           Colori; // int
	typedef Color<unsigned int>  Coloru; // unsigned int


} // namespace ke