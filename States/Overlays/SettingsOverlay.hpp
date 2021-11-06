#pragma once

#include <States/State.hpp>



struct QuickSettings
{
	QuickSettings() : planet_size(500), star_size(100), star_shader(true), glow_shader(true), default_dt(true), dt(0.0001) {};

	double planet_size;
	double star_size;

	bool star_shader;
	bool glow_shader;

	bool default_dt;
	float dt;
};


class SettingsOverlay
{
public:

	SettingsOverlay();
	~SettingsOverlay();


	void assign(sf::RenderWindow* window);

	void initUI();

	void loadObjects();

	void updateEvents(const MousePosition& mousePosition, float dt);
	void updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event);

	void updateColors(const sf::Vector2f& mousePosition, const float dt);

	QuickSettings& output();

	void render();

private:

	sf::RenderWindow* m_window;

	int m_quitStatus;
	bool m_active;

	QuickSettings m_output;
};

