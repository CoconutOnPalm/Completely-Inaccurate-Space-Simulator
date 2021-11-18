//#pragma once
//
//#include <States/State.hpp>
//
//
//class SimParamsOverlay
//{
//public:
//
//	SimParamsOverlay();
//	~SimParamsOverlay();
//
//
//	void assign(sf::RenderWindow* window);
//
//	void initUI();
//
//	void updateEvents(const MousePosition& mousePosition, float dt);
//	void updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event);
//
//	void updateColors(const sf::Vector2f& mousePosition, const float dt);
//
//	OverlayQuitCode quitStatus() const;
//	void resetQuitStatus();
//
//	void render();
//
//	bool active() const;
//	void activate();
//	void deactivate();
//
//private:
//
//	void saveSettings();
//	void restoreSettings();
//
//
//	sf::RenderWindow* m_window;
//
//	OverlayQuitCode m_quitCode;
//	bool m_active;
//
//	ke::Rectangle m_background;
//	ke::Rectangle m_shader_background;
//
//	ke::PointBar m_star_scale;
//	ke::PointBar m_planet_scale;
//
//	ke::Button m_star_scale_text;
//	ke::Button m_planet_scale_text;
//
//	std::array<int, 6> m_sScales;				// star scales
//	std::array<int, 6>::iterator m_sScale_itr;	// star scales itr
//												
//	std::array<int, 8> m_pScales;				// planet scales
//	std::array<int, 8>::iterator m_pSscale_itr;	// planet scales itr
//
//
//	ke::Switch m_star_shader;
//	ke::Switch m_glow_shader;
//
//	ke::Switch m_custom_dt;
//	ke::InputButton m_custom_timestep;
//
//	ke::Button m_apply;
//	ke::Button m_cancel;
//
//
//	std::array<ke::Rectangle, 6> m_descriptions;
//	std::array<sf::Shader, 3> m_shaders;
//
//
//	std::array<ke::Colorf, 19> m_colors;
//};
//
