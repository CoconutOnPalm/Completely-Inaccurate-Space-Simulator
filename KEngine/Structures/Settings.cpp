#include "Settings.hpp"

namespace ke
{

	Settings::Settings()
	{
		// you have to initialize Setting manually or with generel KEngine Init() / CutomInit() functions
	}

	Settings::~Settings()
	{
		bool success = true;
		FileStream filestream;
		if (!filestream.open("KEngine/Sources/Data/keSettings.bin", std::ios::out | std::ios::binary | std::ios::trunc))
		{
			throw_error("Settings::Save()", "could not open settings file - setting to defaults", "ERROR");
			success = false;
		}

		if (!filestream.binWrite(Get().m_max_string_size))					success = false;
		if (!filestream.binWrite(Get().m_modify_str_when_fstream_failed))	success = false;
		if (!filestream.binWrite(Get().m_physics_accuracy))					success = false;
		if (!filestream.binWrite(Get().m_min_abs_mass))						success = false;
		if (!filestream.binWrite(Get().m_default_font_path))				success = false;
		if (!filestream.binWrite(Get().m_empty_texture_path))				success = false;
		if (!filestream.binWrite(Get().m_empty_FHD_texture_path))			success = false;
		if (!filestream.binWrite(Get().m_default_texture_color.r))			success = false;
		if (!filestream.binWrite(Get().m_default_texture_color.g))			success = false;
		if (!filestream.binWrite(Get().m_default_texture_color.b))			success = false;
		if (!filestream.binWrite(Get().m_default_texture_color.a))			success = false;
		if (!filestream.binWrite(Get().m_unknown_texture_path_name))		success = false;

		if (!success)
			throw_error("Settings::Save()", "something went wrong while saving data into keSettings.bin", "ERROR");
	}



	////////////////////////////////////////////////////



	bool ke::Settings::Init()
	{
		Get().m_max_string_size = 10000;
		Get().m_modify_str_when_fstream_failed = false;
		Get().m_physics_accuracy = 0.0001;
		Get().m_min_abs_mass = 0.0001;
		Get().m_default_font_path = "KEngine/Sources/Data/fontpaths.txt";
		Get().m_empty_texture_path = "KEngine/Sources/empty_texture.png";
		Get().m_empty_FHD_texture_path = "KEngine/Sources/empty_texture_FullHD.png";
		Get().m_default_texture_color = sf::Color::Black;
		Get().m_unknown_texture_path_name = "KE_UNKNOWN";
		
		bool success = true;

		FileStream filestream;
		if (!filestream.open("KEngine/Sources/Data/keSettings.bin", std::ios::in | std::ios::binary))
		{
			throw_error("Settings::Init()", "could not open keSettings.bin file - setting to defaults", "ERROR");
			success = false;
		}

		filestream.seekg(0);

		if (!filestream.binRead(Get().m_max_string_size))					success = false;
		if (!filestream.binRead(Get().m_modify_str_when_fstream_failed))	success = false;
		if (!filestream.binRead(Get().m_physics_accuracy))					success = false;
		if (!filestream.binRead(Get().m_min_abs_mass))						success = false;
		if (!filestream.binRead(Get().m_default_font_path))					success = false;
		if (!filestream.binRead(Get().m_empty_texture_path))				success = false;
		if (!filestream.binRead(Get().m_empty_FHD_texture_path))			success = false;
		if (!filestream.binRead(Get().m_default_texture_color.r))			success = false;
		if (!filestream.binRead(Get().m_default_texture_color.g))			success = false;
		if (!filestream.binRead(Get().m_default_texture_color.b))			success = false;
		if (!filestream.binRead(Get().m_default_texture_color.a))			success = false;
		if (!filestream.binRead(Get().m_unknown_texture_path_name))			success = false;

		if (!success)
			throw_error("Settings::Init()", "something went wrong ehile reading data from keSettings.bin", "ERROR");

		return success;
	}



	////////////////////////////////////////////////////



	bool Settings::Save()
	{
		bool success = true;
		FileStream filestream;
		if (!filestream.open("KEngine/Sources/Data/keSettings.bin", std::ios::out | std::ios::binary | std::ios::trunc))
		{
			throw_error("Settings::Save()", "could not open settings file - setting to defaults", "ERROR");
			success = false;
		}

		if (!filestream.binWrite(Get().m_max_string_size))					success = false;
		if (!filestream.binWrite(Get().m_modify_str_when_fstream_failed))	success = false;
		if (!filestream.binWrite(Get().m_physics_accuracy))					success = false;
		if (!filestream.binWrite(Get().m_min_abs_mass))						success = false;
		if (!filestream.binWrite(Get().m_default_font_path))				success = false;
		if (!filestream.binWrite(Get().m_empty_texture_path))				success = false;
		if (!filestream.binWrite(Get().m_empty_FHD_texture_path))			success = false;
		if (!filestream.binWrite(Get().m_default_texture_color.r))			success = false;
		if (!filestream.binWrite(Get().m_default_texture_color.g))			success = false;
		if (!filestream.binWrite(Get().m_default_texture_color.b))			success = false;
		if (!filestream.binWrite(Get().m_default_texture_color.a))			success = false;
		if (!filestream.binWrite(Get().m_unknown_texture_path_name))		success = false;

		if (!success)
			throw_error("Settings::Save()", "something went wrong ehile saving data into keSettings.bin", "ERROR");

		return success;
	}



	////////////////////////////////////////////////////



	void Settings::restoreDefaults()
	{
		Get().m_max_string_size = 10000;
		Get().m_modify_str_when_fstream_failed = false;
		Get().m_physics_accuracy = 0.0001;
		Get().m_min_abs_mass = 0.0001;
		Get().m_default_font_path = "KEngine/Sources/Data/fontpaths.txt";
		Get().m_empty_texture_path = "KEngine/Sources/empty_texture.png";
		Get().m_empty_FHD_texture_path = "KEngine/Sources/empty_texture_FullHD.png";
		Get().m_default_texture_color = sf::Color::White;
		Get().m_unknown_texture_path_name = "KE_UNKNOWN";
	}



	////////////////////////////////////////////////////



	Settings& Settings::Get()
	{
		static Settings instance;
		return instance;
	}


	void Settings::setMaxStringSize(unsigned int max_string_size)
	{
		Get().m_max_string_size = max_string_size;
	}


	//////////////////////////


	unsigned int Settings::MaxStringSize()
	{
		return Get().m_max_string_size;
	}


	void Settings::setModifyingStringWhenFStreamFailed(bool modify)
	{
		Get().m_modify_str_when_fstream_failed = modify;
	}


	//////////////////////////


	bool Settings::ModifyStringWhenFstreamFailed()
	{
		return Get().m_modify_str_when_fstream_failed;
	}


	void Settings::setPhysicsAccuracy(float accuracity)
	{
		Get().m_physics_accuracy = accuracity;
	}


	//////////////////////////


	float Settings::PhysicsAccuracy()
	{
		return Get().m_physics_accuracy;
	}


	void Settings::setMinimumAbsoluteMass(float mass)
	{
		Get().m_min_abs_mass = mass;
	}


	//////////////////////////


	float Settings::MinimumAbsoluteMass()
	{
		return Get().m_min_abs_mass;
	}


	void Settings::setDefaultFontPath(const std::string& def_font_path)
	{
		Get().m_default_font_path = def_font_path;
	}


	//////////////////////////


	std::string Settings::DefaultFontPath()
	{
		return Get().m_default_font_path;
	}


	void Settings::setEmptyTexturePath(const std::string& filename)
	{
		Get().m_empty_texture_path = filename;
	}


	//////////////////////////


	std::string Settings::EmptyTexturePath()
	{
		return Get().m_empty_texture_path;
	}

	void Settings::setEmptyFHDTexturePath(const std::string& filename)
	{
		Get().m_empty_FHD_texture_path = filename;
	}

	std::string Settings::EmptyFHDTexturePath()
	{
		return Get().m_empty_FHD_texture_path;
	}


	void Settings::setDefaultTextureColor(const sf::Color& color)
	{
		Get().m_default_texture_color = color;
	}


	//////////////////////////


	void Settings::setDefaultTextureColor(const Colorf& color)
	{
		Get().m_default_texture_color = color.getSFMLColor();
	}


	const sf::Color& Settings::DefaultTextureColor()
	{
		return Get().m_default_texture_color;
	}


	//////////////////////////


	void Settings::setUnknownTexturePathName(const std::string& name)
	{
		Get().m_unknown_texture_path_name = name;
	}

	std::string Settings::UnknownTexturePathName()
	{
		return Get().m_unknown_texture_path_name;
	}


} // namespace ke