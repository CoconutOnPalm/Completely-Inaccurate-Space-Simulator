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
