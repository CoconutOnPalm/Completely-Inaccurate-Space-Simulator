#pragma once

#include "States/State.hpp"
#include "States/Modules/SaveController.hpp"


class SimSavingOverlay
{
public:

	SimSavingOverlay(const sf::Vector2f& winSize, SaveController* save_controller, bool* simulation_running, const  sf::Texture* sim_icon);
	~SimSavingOverlay();

	void updateEvents(const MousePosition& mousePosition, float dt);
	void updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event, std::vector<std::unique_ptr<SpaceObject>>* objects);

	void updateColors(const sf::Vector2f& mousePosition, const float dt);

	OverlayQuitCode quitStatus() const;

	void render(sf::RenderWindow* window);

private:

	SaveController* m_saveController;
	bool* m_simulation_running;
	bool m_was_running;

	bool m_saving_mode; // 1 for saving, 0 for autosaving

	OverlayQuitCode m_quitCode;

	ke::Button m_background;

	ke::InputButton m_name;
	ke::Button m_save;
	ke::Button m_cancel;

	std::array<ke::Colorf, 5> m_buttonColors;

	sf::Image m_simIcon;

};

