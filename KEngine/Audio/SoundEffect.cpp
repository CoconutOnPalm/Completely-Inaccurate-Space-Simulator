#include "SoundEffect.hpp"

namespace ke
{

	SoundEffects::SoundEffects()
	{

	}


	SoundEffects::SoundEffects(float volume)
	{
		m_sound.setVolume(volume);
	}


	SoundEffects::~SoundEffects()
	{
		m_sound.stop();
	}



	////////////////////////////////////////////////////////////////



	void SoundEffects::addEffect(
		const std::string& name, 
		const std::string& file_path,
		float volume, 
		float pitch, 
		float offset)
	{
		m_sound_effects[name].volume = volume;
		m_sound_effects[name].pitch = pitch;
		m_sound_effects[name].offset = offset;

		if (!m_sound_effects[name].sBuffer.loadFromFile(file_path))
			throw_error("SoundEffects::addEffect(...)", "could not load sound effect", "ERROR");
	}



	////////////////////////////////



	void SoundEffects::removeEffect(const std::string& name)
	{
		if (m_sound_effects.find(name) == m_sound_effects.end())
		{
			throw_error("SoundEffects::removeEffect(..)", "sound effect not found", "ERROR");
			return;
		}

		if (&m_sound_effects[name].sBuffer == (m_sound.getBuffer()))
		{
			m_sound.stop();
			m_sound.resetBuffer();
		}

		m_sound_effects.erase(name);
	}



	////////////////////////////////////////////////////////////////



	void SoundEffects::play(const std::string& name)
	{
		if (m_sound_effects.find(name) == m_sound_effects.end())
		{
			throw_error("SoundEffects::play()", "sound effect not found", "ERROR");
			return;
		}

		m_sound.setVolume(m_sound_effects[name].volume);
		m_sound.setPitch(m_sound_effects[name].pitch);
		m_sound.setPlayingOffset(sf::seconds(m_sound_effects[name].offset));

		m_sound.setBuffer(m_sound_effects[name].sBuffer);
		m_sound.play();
	}


	////////////////////////////////


	void SoundEffects::pause()
	{
			m_sound.pause();
	}


	////////////////////////////////


	void SoundEffects::resume()
	{
		if (m_sound.getStatus() == sf::Sound::Paused)
			m_sound.play();
	}


	////////////////////////////////


	void SoundEffects::stop()
	{
		if (!m_sound.getStatus() == sf::Sound::Stopped)
			m_sound.stop();
	}



	////////////////////////////////////////////////////////////////



	void SoundEffects::setVolume(float volume, const std::string& name)
	{
		if (m_sound_effects.find(name) != m_sound_effects.end())
			m_sound_effects[name].volume = volume;
	}


	////////////////////////////////


	void SoundEffects::setPitch(float pitch, const std::string& name)
	{
		if (m_sound_effects.find(name) != m_sound_effects.end())
			m_sound_effects[name].pitch = pitch;
	}


	////////////////////////////////


	void SoundEffects::setOffset(float offset, const std::string& name)
	{
		if (m_sound_effects.find(name) != m_sound_effects.end())
			m_sound_effects[name].offset = offset;
	}



	////////////////////////////////////////////////////////////////



	void SoundEffects::setGeneralVolume(float volume)
	{
		for (auto itr : m_sound_effects)
			itr.second.volume *= volume;
	}



	////////////////////////////////////////////////////////////////



	sf::Sound* SoundEffects::getSound()
	{
		return &m_sound;
	}


	std::map<std::string, SEF>* SoundEffects::getEffects()
	{
		return &m_sound_effects;
	}

} // namespace ke