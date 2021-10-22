#pragma once

#include "SFML/Audio.hpp"
#include "../Algorithms/RandomGenerator.hpp"

#include <vector>


namespace ke
{

	/// <summary>
	/// KEngine Playlist is an object that can hold multiple songs and play them in given order
	/// </summary>
	class Playlist
	{
	public:

		/// <summary>
		/// Playlist default constructor
		/// </summary>
		Playlist();


		/// <summary>
		/// Playlist constructor
		/// </summary>
		/// <param name="volume">playlist starting volume</param>
		Playlist(float volume);


		/// <summary>
		/// Playlist destructor
		/// </summary>
		~Playlist();


		////////////////////////////////


		/// <summary>
		/// adds song to the playlist
		/// </summary>
		/// <param name="filename">path to the song</param>
		void addSong(const std::string& filename);



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// starts playing song from the beggining
		/// </summary>
		void play();


		/// <summary>
		/// puses currently playing song
		/// </summary>
		void pause();


		/// <summary>
		/// resurmes paused song
		/// </summary>
		void resume();


		////////////////////////////////


		/// <summary>
		/// restarts song to the begginging
		/// </summary>
		void restart();


		/// <summary>
		/// restarts playlist and selects the first song
		/// </summary>
		void reset();


		////////////////////////////////


		/// <summary>
		/// skips currnently playing song
		/// </summary>
		void skip();


		/// <summary>
		/// plays previous song
		/// </summary>
		void playPrevious();


		////////////////////////////////


		/// <summary>
		/// is music playing right now>
		/// </summary>
		/// <returns></returns>
		bool playing() const;


		////////////////////////////////


		/// <summary>
		/// sets loop status
		/// </summary>
		/// <param name="enable">true - loop on</param>
		void enableLoop(bool enable);


		/// <summary>
		/// returns loop status
		/// </summary>
		/// <returns>loop status</returns>
		bool loopEnabled() const;



		////////////////////////////////


		/// <summary>
		/// controls automatic playlist playing
		/// </summary>
		void update();


		////////////////////////////////


		/// <summary>
		/// sets playlist volume
		/// </summary>
		/// <param name="volume"></param>
		void setVolume(float volume);


		/// <summary>
		/// sets playlist pitch
		/// </summary>
		/// <param name="pitch"></param>
		void setPitch(float pitch);


		////////////////////////////////


		/// <summary>
		/// randomly generates new song order
		/// </summary>
		void shuffle();



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// returns 
		/// </summary>
		/// <returns>SMFL Music</returns>
		sf::Music* getMusic();


		/// <summary>
		/// returns song list
		/// </summary>
		/// <returns></returns>
		std::vector<std::string>* getFilenames();



	private:

		std::vector<std::string> m_filenames;					// song list
		std::vector<std::string>::iterator m_current_playing;	// currently playing song

		sf::Music m_music; // SMFL music class

		bool m_loop_enabled; // is loop enabled?
	};

} // namespace ke