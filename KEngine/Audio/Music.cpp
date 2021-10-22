#include "Music.hpp"

namespace ke
{

	Playlist::Playlist()
		: m_loop_enabled(true)
	{

	}


	Playlist::Playlist(float volume)
		: m_loop_enabled(true)
	{
		m_music.setVolume(volume);
	}


	Playlist::~Playlist()
	{
		m_music.stop();
	}


	////////////////////////////////


	void Playlist::addSong(const std::string& filename)
	{
		m_filenames.push_back(filename);

		m_current_playing = m_filenames.begin();
	}



	////////////////////////////////////////////////////////////////



	void Playlist::play()
	{
		if (!m_music.openFromFile(*m_current_playing))
		{
			throw_error("Playlist::play()", "could not open music file", "ERROR");
			return;
		}

		m_music.play();
	}


	////////////////////////////////


	void Playlist::pause()
	{
		m_music.pause();
	}


	////////////////////////////////


	void Playlist::resume()
	{
		if (m_music.getStatus() == sf::Music::Paused)
			m_music.play();
	}


	////////////////////////////////


	void Playlist::restart()
	{
		m_music.stop();

		this->play();
	}


	////////////////////////////////


	void Playlist::reset()
	{
		m_music.stop();
		m_current_playing = m_filenames.begin();
	}


	////////////////////////////////


	void Playlist::update()
	{
		if (m_music.getStatus() != sf::Music::Playing && m_music.getStatus() != sf::Music::Paused)
			this->skip();
	}


	////////////////////////////////


	void Playlist::skip()
	{
		if (m_current_playing + 1 != m_filenames.end())
			m_current_playing++;
		else
			m_current_playing = m_filenames.begin();

		if (m_loop_enabled)
			this->play();
		else
			m_music.stop();
	}


	////////////////////////////////


	bool Playlist::playing() const
	{
		return m_music.getStatus() == sf::Music::Playing;
	}


	////////////////////////////////


	void Playlist::enableLoop(bool enable)
	{
		m_loop_enabled = enable;
	}


	bool Playlist::loopEnabled() const
	{
		return m_loop_enabled;
	}


	////////////////////////////////


	void Playlist::playPrevious()
	{
		if (m_current_playing != m_filenames.begin())
			m_current_playing--;
		else
			m_current_playing = m_filenames.end() - 1;

		this->play();
	}


	////////////////////////////////


	void Playlist::setVolume(float volume)
	{
		m_music.setVolume(volume);
	}


	////////////////////////////////


	void Playlist::setPitch(float pitch)
	{
		m_music.setPitch(pitch);
	}


	////////////////////////////////


	void Playlist::shuffle()
	{
		int n = 0;

		for (auto& i : m_filenames)
		{
			int r = ke::Random::Int(n, m_filenames.size() - 1);
			swap(i, m_filenames[r]);
			n++;
		}
	}


	////////////////////////////////


	sf::Music* Playlist::getMusic()
	{
		return &m_music;
	}


	std::vector<std::string>* Playlist::getFilenames()
	{
		return &m_filenames;
	}

} // namespace ke