#pragma once

#include <SFML/Graphics.hpp>

namespace ke
{

	/// <summary>
	/// KEngie Vector4 is 4 dimensional vector that has x, y, z and v coordinates
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template <typename T>
	struct Vector4
	{


		/// <summary>
		/// Vector4 default constructor
		/// </summary>
		Vector4();


		/// <summary>
		/// Vector4 constructor
		/// </summary>
		/// <param name="x">x coord</param>
		/// <param name="y">y coord</param>
		/// <param name="z">z coord</param>
		/// <param name="v">v coord</param>
		Vector4(T x, T y, T z, T v);


		/// <summary>
		/// Vector4 copy constructor
		/// </summary>
		/// <param name="other">other Vector4</param>
		Vector4(const Vector4<T>& other);


		/// <summary>
		/// Vector4 copy constructor using 2x SMFL Vector2
		/// </summary>
		/// <param name="first">first vector</param>
		/// <param name="second">second vector</param>
		Vector4(const sf::Vector2<T>& first, const sf::Vector2<T>& second);


		/// <summary>
		/// Vector4 copy constructor using 1x Vector3 and one other variable
		/// </summary>
		/// <param name="other">Vector3</param>
		/// <param name="v">other variable</param>
		Vector4(const sf::Vector3<T>& other, T v);


		
		~Vector4() {};


		/// <summary>
		/// Vector4 operator =
		/// </summary>
		/// <param name="other">other Vector4</param>
		void operator=(const Vector4<T>& other);


		T x, y, z, v; // x, y, z, v coordinates
	};





	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	template <typename T>
	Vector4<T>::Vector4() : x(0), y(0), z(0), v(0) {};


	//////////////////////////


	template <typename T>
	Vector4<T>::Vector4(T x, T y, T z, T v) : x(x), y(y), z(z), v(v) {}


	//////////////////////////


	template <typename T>
	Vector4<T>::Vector4(const Vector4<T>& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		v = other.v;
	}


	//////////////////////////


	template <typename T>
	Vector4<T>::Vector4(const sf::Vector2<T>& first, const sf::Vector2<T>& second)
	{
		x = first.x;
		y = first.y;
		z = second.x;
		v = second.y;
	}


	//////////////////////////


	template <typename T>
	Vector4<T>::Vector4(const sf::Vector3<T>& other, T v)
	{
		this->x = other.x;
		this->y = other.y;
		this->z = other.y;
		this->v = v;
	}



	////////////////////////////////////////////////////



	template <typename T>
	void Vector4<T>::operator=(const Vector4<T>& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		v = other.v;
	}


	
	////////////////////////////////////////////////////



	template <typename T>
	bool operator==(Vector4<T> left, Vector4<T> right)
	{
		return (left.x == right.x &&
			left.y == right.y &&
			left.z == right.z &&
			left.v == right.v);
	}


	//////////////////////////


	template <typename T>
	bool operator!=(Vector4<T> left, Vector4<T> right)
	{
		return !(left == right);
	}


	//////////////////////////


	template <typename T>
	void operator++(Vector4<T>& vector)
	{
		vector.x++;
		vector.y++;
		vector.z++;
		vector.v++;
	}


	//////////////////////////


	template <typename T>
	void operator--(Vector4<T>& vector)
	{
		vector.x--;
		vector.y--;
		vector.z--;
		vector.v--;
	}




	////////////////////////////////////////////////////




	template <typename T, typename T_val>
	void operator+=(Vector4<T>& vector, T_val value)
	{
		vector.x += value;
		vector.y += value;
		vector.z += value;
		vector.v += value;
	}


	//////////////////////////


	template <typename T, typename T_val>
	void operator-=(Vector4<T>& vector, T_val value)
	{
		vector.x -= value;
		vector.y -= value;
		vector.z -= value;
		vector.v -= value;
	}



	////////////////////////////////////////////////////



	template <typename T, typename T_val>
	Vector4<T> operator+(const Vector4<T>& vector, T_val value)
	{
		return Vector4<T>(vector.x + value, vector.y + value, vector.z + value, vector.v + value);
	}


	template <typename T, typename T_val>
	Vector4<T> operator-(const Vector4<T>& vector, T_val value)
	{
		return Vector4<T>(vector.x - value, vector.y - value, vector.z - value, vector.v - value);
	}



	////////////////////////////////////////////////////



	// some typedefs for popular types

	typedef Vector4<float>          Vector4f; // float 
	typedef Vector4<double>         Vector4d; // double 
	typedef Vector4<int>            Vector4i; // int
	typedef Vector4<unsigned int>   Vector4u; // unsigned int
	typedef Vector4<char>           Vector4c; // char


} // namespace ke
