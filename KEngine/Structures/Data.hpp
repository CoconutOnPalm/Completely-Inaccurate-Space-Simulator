#pragma once

#include <iostream>
#include <string>
#include <sstream>


// variables from windows calculator :)

/// use if you don not have M_PI in cmath
#define PI		3.1415926535897932384626433832795

/// 180 / PI used to convert radians to degrees
#define TO_DEG	57.295779513082320876798154814105

/// PI / 180 used to convert degrees to radians
#define TO_RAD	0.01745329251994329576923690768489


/// sqrt(2)
#define sqrt_2 1.4142135623730950488016887242097

/// sqrt(3)
#define sqrt_3 1.7320508075688772935274463415059




/// <summary>
/// KEngie namespace
/// </summary>
namespace ke
{

	/// <summary>
	/// Enum used for shape origin and text position
	/// </summary>
	enum Origin
	{
		LEFT_TOP,           //  |--------------------------------------------|
		MIDDLE_TOP,         //  | LEFT_TOP      MIDDLE_TOP      RIGHT_TOP    |
		RIGHT_TOP,          //  |                                            |
		LEFT_MIDDLE,        //  |                                            |
		MIDDLE_MIDDLE,      //  | LEFT_MIDDLE   MIDDLE_MIDDLE   RIGHT_MIDDLE |
		RIGHT_MIDDLE,       //  |                                            |
		LEFT_BOTTOM,        //  |                                            |
		MIDDLE_BOTTOM,      //  | LEFT_MIDDLE   MIDDLE_BOTTOM   RIGHT_BOTTOM |
		RIGHT_BOTTOM        //  |--------------------------------------------|
	};


	/// <summary>
	/// Available KEngie fonts in one enum
	/// </summary>
	enum Font
	{
		Arial,
		Arial_Uni,
		Calibri,
		ComicSans,
		CourierNew,
		TimesNewRoman,
		TrebuchetMS,
		Verdana
	};


	/// <summary>
	/// enum used to set which characters can be typed inside InputButton
	/// </summary>
	enum TextScope
	{
		Everything,
		ASCII_Everything, // English letters only
		Letters_PMarks, // letters and punctuation marks (,.;'[]/-=+? etc...)
		Numbers,
		Letters,
		Math,
	};

} // namespace ke