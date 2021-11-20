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


	static void setPlanetSize(long double planet_size);
	static long double PlanetSize();

	static void setStarSize(long double star_size);
	static long double StarSize();

	static void setStarShader(bool star_shader);
	static bool StarShader();

	static void setGlowShader(bool glow_shader);
	static bool GlowShader();

	static void setCustomDt(bool custom_dt);
	static bool CustomDt();

	static void setCustomTimeStep(float custom_timestep);
	static float CustomTimeStep();

	static void setSimulationBackgroundImage(int index);
	static int SimulationBackgroundImage();


private:

	// graphics
	sf::Vector2f m_UDWindowSize; // user default window size
	unsigned int m_maxMenuFPS;
	unsigned int m_maxSimFPS;
	int m_windowStyle;
	float m_background_brightnes;
	bool m_vSyncOn;

	// audio
	float m_musicVolume;
	float m_sfxVolume;

	// keybinds

	// simulation
	long double m_planetSize;
	long double m_starSize;
	bool m_starShader;
	bool m_glowShader;
	bool m_custom_dt;
	float m_custom_timestep;
	int m_simulationBackgroundImage;
};