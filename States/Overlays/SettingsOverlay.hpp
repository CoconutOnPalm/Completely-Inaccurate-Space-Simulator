#pragma once

#include <States/State.hpp>


class SettingsOverlay
{
public:

	SettingsOverlay();
	~SettingsOverlay();


	void assign(sf::RenderWindow* window, ke::Button* background);

	void initUI();

	void updateEvents(const MousePosition& mousePosition, float dt);
	void updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event);

	void updateColors(const sf::Vector2f& mousePosition, const float dt);

	OverlayQuitCode quitStatus() const;
	void resetQuitStatus();

	void render();

	bool active() const;
	void activate();
	void deactivate();


private:

	std::string index_to_background_texture();

	sf::RenderWindow* m_window;

	OverlayQuitCode m_quitCode;
	bool m_active;

	ke::Rectangle m_background;
	ke::Button * simulation_background;


	ke::PercentageBar m_music_volume;
	ke::PercentageBar m_sfx_volume;

	std::vector<std::unique_ptr<ke::Button>> m_background_images;
	std::vector<std::unique_ptr<ke::Button>>::iterator m_selected_image;
	

	ke::Switch m_vsync;
	ke::PointBar m_simulationFPS;
};