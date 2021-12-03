#include "AppSettings.hpp"

AppSettings::AppSettings()
{
	
}

AppSettings::~AppSettings()
{
	Get().Save();
}

AppSettings& AppSettings::Get()
{
	static AppSettings instance;
	return instance;
}

bool AppSettings::Init()
{
	Get().m_UDWindowSize = sf::Vector2f(1280, 720);
	Get().m_maxMenuFPS = 60;
	Get().m_maxSimFPS = 480;
	Get().m_windowStyle = 0;
	Get().m_background_brightnes = 20;
	Get().m_vSyncOn = false;

	Get().m_musicVolume = 100;
	Get().m_sfxVolume = 100;

	Get().m_planetSize = 500.;
	Get().m_starSize = 100.;
	Get().m_multithreading_allowed = true;
	Get().m_less_calculations_mode = false;
	Get().m_custom_dt = false;
	Get().m_custom_timestep = 0.0001;
	Get().m_simulationBackgroundImage = 0;

	Get().m_glowShader = true;
	Get().m_starShader = true;

	ke::FileStream settings("Data/settings.bin", std::ios::in | std::ios::binary);

	settings.binRead(Get().m_UDWindowSize.x);
	settings.binRead(Get().m_UDWindowSize.y);
	settings.binRead(Get().m_maxMenuFPS);
	settings.binRead(Get().m_maxSimFPS);
	settings.binRead(Get().m_windowStyle);
	settings.binRead(Get().m_background_brightnes);
	settings.binRead(Get().m_vSyncOn);

	settings.binRead(Get().m_musicVolume);
	settings.binRead(Get().m_sfxVolume);

	settings.binRead(Get().m_planetSize);
	settings.binRead(Get().m_starSize);
	settings.binRead(Get().m_multithreading_allowed);
	settings.binRead(Get().m_less_calculations_mode);
	settings.binRead(Get().m_custom_dt);
	settings.binRead(Get().m_custom_timestep);
	settings.binRead(Get().m_simulationBackgroundImage);

	settings.binRead(Get().m_starShader);
	settings.binRead(Get().m_glowShader);

	return true;
}

bool AppSettings::Save()
{
	ke::FileStream settings;
	bool success = settings.open("Data/settings.bin", std::ios::out | std::ios::binary);

	settings.binWrite(Get().m_UDWindowSize.x);
	settings.binWrite(Get().m_UDWindowSize.y);
	settings.binWrite(Get().m_maxMenuFPS);
	settings.binWrite(Get().m_maxSimFPS);
	settings.binWrite(Get().m_windowStyle);
	settings.binWrite(Get().m_background_brightnes);
	settings.binWrite(Get().m_vSyncOn);

	settings.binWrite(Get().m_musicVolume);
	settings.binWrite(Get().m_sfxVolume);

	settings.binWrite(Get().m_planetSize);
	settings.binWrite(Get().m_starSize);
	settings.binWrite(Get().m_multithreading_allowed);
	settings.binWrite(Get().m_less_calculations_mode);
	settings.binWrite(Get().m_custom_dt);
	settings.binWrite(Get().m_custom_timestep);
	settings.binWrite(Get().m_simulationBackgroundImage);

	settings.binWrite(Get().m_starShader);
	settings.binWrite(Get().m_glowShader);

	return success;
}

void AppSettings::RestoreDefaults()
{
	Get().m_UDWindowSize = sf::Vector2f(1280, 720);
	Get().m_maxMenuFPS = 60;
	Get().m_maxSimFPS = 480;
	Get().m_windowStyle = 0;
	Get().m_background_brightnes = 20;
	Get().m_vSyncOn = false;

	Get().m_musicVolume = 100;
	Get().m_sfxVolume = 100;

	Get().m_planetSize = 500.;
	Get().m_starSize = 100.;
	Get().m_multithreading_allowed = true;
	Get().m_less_calculations_mode = false;
	Get().m_custom_dt = false;
	Get().m_custom_timestep = 0.0001;
	Get().m_simulationBackgroundImage = 0;

	Get().m_glowShader = true;
	Get().m_starShader = true;
}

void AppSettings::setDefaultWindowSize(const sf::Vector2f window_size)
{
	Get().m_UDWindowSize = window_size;
}

sf::Vector2f AppSettings::DefaultWindowSize()
{
	return Get().m_UDWindowSize;
}

void AppSettings::setMaxMenuFPS(unsigned int fps)
{
	Get().m_maxMenuFPS = fps;
}

unsigned int AppSettings::MaxMenuFPS()
{
	return Get().m_maxMenuFPS;
}

void AppSettings::setMaxSimulationFPS(unsigned int fps)
{
	Get().m_maxSimFPS = fps;
}

unsigned int AppSettings::MaxSimulationFPS()
{
	return Get().m_maxSimFPS;
}

void AppSettings::setWindowStyle(int style)
{
	Get().m_windowStyle = style;
}

int AppSettings::WindowStyle()
{
	return Get().m_windowStyle;
}

void AppSettings::setBackgroundBrightness(float brightness)
{
	Get().m_background_brightnes = brightness;
}

float AppSettings::BackgroundBrightness()
{
	return Get().m_background_brightnes;
}

void AppSettings::setVSync(float on_off)
{
	Get().m_vSyncOn = on_off;
}

bool AppSettings::vSync()
{
	return Get().m_vSyncOn;
}

void AppSettings::setMusicVolume(float volume)
{
	Get().m_musicVolume = volume;
}

float AppSettings::MusicVolume()
{
	return Get().m_musicVolume;
}

void AppSettings::setSFXVolume(float volume)
{
	Get().m_sfxVolume = volume;
}

float AppSettings::SFXVolume()
{
	return Get().m_sfxVolume;
}

void AppSettings::setPlanetSize(long double planet_size)
{
	Get().m_planetSize = planet_size;
}

long double AppSettings::PlanetSize()
{
	return Get().m_planetSize;
}

void AppSettings::setStarSize(long double star_size)
{
	Get().m_starSize = star_size;
}

long double AppSettings::StarSize()
{
	return Get().m_starSize;
}

void AppSettings::setStarShader(bool star_shader)
{
	Get().m_starShader = star_shader;
}

bool AppSettings::StarShader()
{
	return Get().m_starShader;
}

void AppSettings::setMultithreadingStatus(bool status)
{
	Get().m_multithreading_allowed = status;
}

bool AppSettings::MultithreadingAllowed()
{
	return Get().m_multithreading_allowed;
}

void AppSettings::setCalculationMode(bool onoff)
{
	Get().m_less_calculations_mode = onoff;
}

bool AppSettings::LessCalculationsMode()
{
	return Get().m_less_calculations_mode;
}

void AppSettings::setGlowShader(bool glow_shader)
{
	Get().m_glowShader = glow_shader;
}

bool AppSettings::GlowShader()
{
	return Get().m_glowShader;
}

void AppSettings::setCustomDt(bool custom_dt)
{
	Get().m_custom_dt = custom_dt;
}

bool AppSettings::CustomDt()
{
	return Get().m_custom_dt;
}

void AppSettings::setTrailsEnabled(bool trails)
{
	Get().m_trails = trails;
}

bool AppSettings::TrailsEnabled()
{
	return Get().m_trails;
}

void AppSettings::setCustomTimeStep(float custom_timestep)
{
	Get().m_custom_timestep = custom_timestep;
}

float AppSettings::CustomTimeStep()
{
	return Get().m_custom_timestep;
}

void AppSettings::setSimulationBackgroundImage(int index)
{
	Get().m_simulationBackgroundImage = index;
}

int AppSettings::SimulationBackgroundImage()
{
	return Get().m_simulationBackgroundImage;
}
