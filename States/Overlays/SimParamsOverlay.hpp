#pragma once

#include <States/State.hpp>


struct QuickSettings
{
	QuickSettings() : planet_size(500), star_size(100), multithreading_on(true), less_calculations_mode(false), custom_dt(true), custom_timestep(0.0001) {};

	double star_size;
	double planet_size;

	bool multithreading_on;
	bool less_calculations_mode;

	bool custom_dt;
	float custom_timestep;
};


class SimParamsOverlay
{
public:

	SimParamsOverlay();
	~SimParamsOverlay();


	void assign(sf::RenderWindow* window);

	void initUI();

	void updateEvents(const MousePosition& mousePosition, float dt);
	void updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event);

	void updateColors(const sf::Vector2f& mousePosition, const float dt);

	OverlayQuitCode quitStatus() const;
	void resetQuitStatus();

	QuickSettings& output();

	void render();

	bool active() const;
	void activate();
	void deactivate();

private:

	void saveSettings();
	void restoreSettings();


	sf::RenderWindow* m_window;

	OverlayQuitCode m_quitCode;
	bool m_active;

	QuickSettings m_output;


	ke::Rectangle m_background;
	ke::Rectangle m_shader_background;

	ke::PointBar m_star_scale;
	ke::PointBar m_planet_scale;

	ke::Button m_star_scale_text;
	ke::Button m_planet_scale_text;

	std::array<int, 6> m_sScales;				// star scales
	std::array<int, 6>::iterator m_sScale_itr;	// star scales itr

	std::array<int, 8> m_pScales;				// planet scales
	std::array<int, 8>::iterator m_pSscale_itr;	// planet scales itr


	ke::Switch m_allow_multithreading;
	ke::Switch m_less_calculations_mode;

	ke::Switch m_custom_dt;
	ke::InputButton m_custom_timestep;

	ke::Button m_apply;
	ke::Button m_cancel;


	std::array<ke::Rectangle, 6> m_descriptions;
	std::array<sf::Shader, 3> m_shaders;


	std::array<ke::Colorf, 19> m_colors;
};