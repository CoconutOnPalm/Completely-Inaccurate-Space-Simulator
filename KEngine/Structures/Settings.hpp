#pragma once

#include "Color.hpp"
#include "../Algorithms/Debug.hpp"
#include "../Algorithms/FileStream.hpp"

namespace ke
{

	/// <summary>
	/// KEngine Settings is a singleton that menages KEngie setting (LMAO)
	/// </summary>
	class Settings
	{
	public:

		// default consturctor, deleted constructors and deleted operators
		Settings();
		~Settings();
		Settings(const Settings&) = delete;
		void operator=(const Settings&) = delete;


		////////////////////////////////////////////////////


		/// <summary>
		/// Inits Settings (loads from file), used in KEngie::Init()
		/// </summary>
		/// <returns>if succeed - true</returns>
		static bool Init();


		//////////////////////////


		/// <summary>
		/// Saves current settings to file
		/// </summary>
		/// <returns></returns>
		static bool Save();


		//////////////////////////


		/// <summary>
		/// restores default settings
		/// </summary>
		static void restoreDefaults();



		////////////////////////////////////////////////////



		/// <summary>
		/// returns Settings instance
		/// </summary>
		/// <returns>Settings class instance</returns>
		static Settings& Get();



		////////////////////////////////////////////////////



		/// <summary>
		/// Sets maximum character size in FileStream and InputButton class
		/// </summary>
		/// <param name="max_string_size">maximum string length</param>
		static void setMaxStringSize(unsigned int max_string_size);


		/// <summary>
		/// returns maximum string size
		/// </summary>
		/// <returns>maximum string length</returns>
		static unsigned int MaxStringSize();


		////////////////////////////////////////////////////


		/// <summary>
		/// if set to true, modifies failed string to "_0" in FileStream::binRead()
		/// </summary>
		/// <param name="modify"></param>
		static void setModifyingStringWhenFStreamFailed(bool modify);


		/// <summary>
		/// returns if string can be modified after FileStream::binRead() fails
		/// </summary>
		/// <returns></returns>
		static bool ModifyStringWhenFstreamFailed();


		////////////////////////////////////////////////////


		/// <summary>
		/// Sets KEngine Physics Accuracy
		/// </summary>
		/// <param name="accuracity">physics accuracy</param>
		static void setPhysicsAccuracy(float accuracity);


		/// <summary>
		/// returns KEngine Physics accuracy
		/// </summary>
		/// <returns>Physics accuracy</returns>
		static float PhysicsAccuracy();


		////////////////////////////////////////////////////


		/// <summary>
		/// sets minimum object mass in KEngine Physics to avoid dividing by 0
		/// </summary>
		/// <param name="mass">minimum mass</param>
		static void setMinimumAbsoluteMass(float mass);


		/// <summary>
		/// returns minimum object mass
		/// </summary>
		/// <returns>minimum object mass</returns>
		static float MinimumAbsoluteMass();


		////////////////////////////////////////////////////


		/// <summary>
		/// sets path to font file list
		/// </summary>
		/// <param name="def_font_path">font list filename</param>
		static void setDefaultFontPath(const std::string& def_font_path);


		/// <summary>
		/// returns path to font file list
		/// </summary>
		/// <returns>font list filename</returns>
		static std::string DefaultFontPath();


		////////////////////////////////////////////////////


		/// <summary>
		/// sets path of default texture (nullptr texture)
		/// </summary>
		/// <param name="filename">default texture filename</param>
		static void setEmptyTexturePath(const std::string& filename);


		/// <summary>
		/// returns path to default texture (nullptr texture)
		/// </summary>
		/// <returns>default texture filename</returns>
		static std::string EmptyTexturePath();


		/// <summary>
		/// sets path of FullHD empty texture
		/// </summary>
		/// <param name="filename">FullHD empty texture filename</param>
		static void setEmptyFHDTexturePath(const std::string& filename);


		/// <summary>
		/// returns path to FullHD empty texture
		/// </summary>
		/// <returns>FullHD empty texture filename</returns>
		static std::string EmptyFHDTexturePath();


		////////////////////////////////////////////////////


		/// <summary>
		/// sets default textured shape color
		/// </summary>
		/// <param name="color">SFML color</param>
		static void setDefaultTextureColor(const sf::Color& color); // SFML color



		/// <summary>
		/// sets default textured shape color
		/// </summary>
		/// <param name="color">KEngine color</param>
		static void setDefaultTextureColor(const Colorf& color);	// KEngie color



		/// <summary>
		/// returns default textured shape color
		/// </summary>
		/// <returns>SFML color</returns>
		static const sf::Color& DefaultTextureColor();


		////////////////////////////////////////////////////


		/// <summary>
		/// sets texure path when it's unknown
		/// </summary>
		/// <param name="name">default texture path name</param>
		static void setUnknownTexturePathName(const std::string& name);



		/// <summary>
		/// returns sets texure path when it's unknown
		/// </summary>
		/// <returns>default texture path</returns>
		static std::string UnknownTexturePathName();


		////////////////////////////////////////////////////



	private:

		unsigned int	m_max_string_size;					// default: 10000										- maximum string size
		bool			m_modify_str_when_fstream_failed;	// default: false										- modify string to error message or leave it as it was
		float			m_physics_accuracy;					// default: 0.0001										- minimum value which acceleration must achieve ot to be rounded to 0 0
		float			m_min_abs_mass;						// default: 0.0001										- when mass is equal to 0, it is turned into that value
		std::string		m_default_font_path;				// default: "KEngine/Sources/Data/fontpaths.txt"		- default path to fonts (fontpaths.txt)
		std::string		m_empty_texture_path;				// default: "KEngine/Sources/empty_texture.png"			- default path to empty texture
		std::string		m_empty_FHD_texture_path;			// default: "KEngine/Sources/empty_texture_FullHD.png"	- default path to empty FullHD texture (1920 x 1080 transparent)
		sf::Color		m_default_texture_color;			// default: sf::Color::Black							- default color for textured object
		std::string		m_unknown_texture_path_name;		// default: "KE_UNKNOWN"								- unknown texture path default name
	};

} // namespace ke