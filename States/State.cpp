#include "State.hpp"

State::State(sf::RenderWindow* sf_window, sf::View* sf_view, STATE current_state)
	: p_quitCode(StateQuitCode::NOT_QUITTING)
{
	window = sf_window;
	view = sf_view;

	winSize = sf::Vector2f(window->getSize());
	viewSize = view->getSize();

	p_current_state = current_state;

	if (p_current_state != STATE::SIMULATION)
		window->setFramerateLimit(AppSettings::MaxMenuFPS());
	else
		window->setFramerateLimit(AppSettings::MaxSimulationFPS());
}



sf::RenderWindow* State::window;
sf::View* State::view;

sf::Vector2f State::winSize;
sf::Vector2f State::viewSize;

std::vector<std::unique_ptr<State>>* State::states;

STATE State::p_current_state;

ke::Playlist State::music;
ke::SoundEffects State::sfx;

std::future<void> State::m_music_thread;



State::~State()
{
	
}

void State::LoadStaticData(static std::vector<std::unique_ptr<State>>* states_vec)
{
	states = states_vec;
}

StateQuitCode State::Quit()
{
	return p_quitCode;
}

void State::loadMusic()
{
	std::ifstream musicstr("Audio/playlist.txt");

	if (!musicstr.is_open())
	{
		ke::throw_error("State::loadMusic()", "could not find playlist file");
		return;
	}

	size_t playlist_size;
	musicstr >> playlist_size;

	std::string path;

	for (size_t i = 0; i < playlist_size + 1; i++)
	{
		std::getline(musicstr, path);
		music.addSong(path);

		//std::cout << path << '\n';
	}

	ke::Random::generateRandomSeed();

	music.setVolume(AppSettings::MusicVolume());
	music.shuffle();
	music.enableLoop(true);
	music.play();
	music.pause();

	for (auto& itr : *music.getFilenames())
		std::cout << itr << '\n';
	
	/*auto playlist_update = []() { while (1) { music.update(); std::this_thread::sleep_for(std::chrono::milliseconds(2000)); } };

	std::thread music_thread(playlist_update);
	music_thread.detach();*/

	//m_music_thread = std::async(std::launch::async, function);
}

void State::loadSFX()
{
	std::ifstream sfxstr("Audio/sfxlist.txt");

	if (!sfxstr.is_open())
	{
		ke::throw_error("State::loadSFX()", "could not find sfxlist file");
		return;
	}

	size_t playlist_size;
	sfxstr >> playlist_size;

	std::string name;
	std::string path;

	for (size_t i = 0; i < playlist_size; i++)
	{
		sfxstr >> name >> path;
		sfx.addEffect(name, path);
	}

	sfx.setGeneralVolume(AppSettings::SFXVolume());
}
