#pragma once

#include <SFML/Audio.hpp>

#include "../Algorithms/Algor.hpp"

#include <map>


namespace ke
{

	/// <summary>
	/// Structure used to hold sound effect and its parameters
	/// </summary>
	struct SEF
	{
		/// DO NOT USE THAT

		sf::SoundBuffer sBuffer; // SFML sound (buffer)
		float			volume;	 // sound effect volume
		float			pitch;	 // sound effect pitch
		float			offset;	 // sound effect playing offset
	};





	////////////////////////////////////////////////////////////////////////////////////////////////





	/// <summary>
	/// KEngine SoundEffects is a class that holds set (std::map) of sound effect and their parameters
	/// </summary>
	class SoundEffects
	{

	public:


		/// <summary>
		/// SoundEffects default constructor
		/// </summary>
		SoundEffects();


		/// <summary>
		/// SoundEffects constructor
		/// </summary>
		/// <param name="volume">general volume</param>
		SoundEffects(float volume);



		/// <summary>
		/// SoundEffects destructor
		/// </summary>
		~SoundEffects();



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// Adds sound effect to the list
		/// </summary>
		/// <param name="name">custom sound effect name</param>
		/// <param name="file_path">path to sound effect</param>
		/// <param name="volume">sound effect custom volume</param>
		/// <param name="pitch">sound effect custom pitch</param>
		/// <param name="offset">sound effect custom offset</param>
		void addEffect(
			const std::string& name, 
			const std::string& file_path,
			float volume = 100, 
			float pitch = 1.0f, 
			float offset = 0.0f);


		////////////////////////////////


		/// <summary>
		/// removes sound effect from the list
		/// </summary>
		/// <param name="name">sound effect name</param>
		void removeEffect(const std::string& name);



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// plays given sound effect
		/// </summary>
		/// <param name="name">sound effect name</param>
		void play(const std::string& name);


		////////////////////////////////


		/// <summary>
		/// puses currently playing sound effect
		/// </summary>
		void pause();


		////////////////////////////////


		/// <summary>
		/// resuems poused sound effect
		/// </summary>
		void resume();


		////////////////////////////////


		/// <summary>
		/// stops currently playing sound effect
		/// </summary>
		void stop();



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// sets given sound effect volume
		/// </summary>
		/// <param name="volume">sound effect new volume</param>
		/// <param name="name">sound effect name</param>
		void setVolume(float volume, const std::string& name);


		////////////////////////////////


		/// <summary>
		/// sets given sound effect pitch
		/// </summary>
		/// <param name="pitch">sound effect new pitch</param>
		/// <param name="name">sound effect name</param>
		void setPitch(float pitch, const std::string& name);


		////////////////////////////////


		/// <summary>
		/// sets given sound effect playing offset
		/// </summary>
		/// <param name="offset">sound effect new playing offset</param>
		/// <param name="name">sound effect name</param>
		void setOffset(float offset, const std::string& name);



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// multipies current sound effecs' volumes by given volume (warning - very expensive)
		/// </summary>
		/// <param name="volume">sound effect voluem * this parameter</param>
		void setGeneralVolume(float volume);



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// returns SFML sound object
		/// </summary>
		/// <returns>SMFL Sound</returns>
		sf::Sound* getSound();



		/// <summary>
		/// retuns list of sound effects
		/// </summary>
		/// <returns>sound effects list</returns>
		std::map<std::string, SEF>* getEffects();





	private:


		std::map<std::string, SEF> m_sound_effects; // list of sound effects

		sf::Sound m_sound; // SFML sound object
	};


}
