#pragma once

#include <KEngine/Algorithms.hpp>

class AppSettings
{
public:

	AppSettings();
	~AppSettings();

	static AppSettings& Get();


	static bool Init();

	static bool Save();

	static void RestoreDefaults();


	static void setDefaultWindowSize(const sf::Vector2f window_size);
	static sf::Vector2f DefaultWindowSize();

	static void setMaxMenuFPS(unsigned int fps);
	static unsigned int MaxMenuFPS();

	static void setMaxSimulationFPS(unsigned int fps);
	static unsigned int MaxSimulationFPS();

	static void setWindowStyle(int style);
	static int WindowStyle();

	static void setBackgroundBrightness(float brightness);
	static float BackgroundBrightness();

	static void setVSync(float on_off);
	static bool vSync();


	static void setMusicVolume(float volume);
	static float MusicVolume();

	static void setSFXVolume(float volume);
	static float SFXVolume();


private:

	sf::Vector2f m_UDWindowSize; // user default window size
	unsigned int m_maxMenuFPS;
	unsigned int m_maxSimFPS;
	int m_windowStyle;
	float m_background_brightnes;
	bool m_vSyncOn;

	float m_musicVolume;
	float m_sfxVolume;
};