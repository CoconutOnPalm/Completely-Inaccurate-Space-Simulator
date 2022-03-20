#pragma once

#include "States/State.hpp"
#include "States/Modules/SaveController.hpp"

class AddSimulationOverlay
{
public:

	AddSimulationOverlay(const sf::Vector2f& winSize);
	~AddSimulationOverlay();

	void updateEvents(const MousePosition& mousePosition, float dt);
	void updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event, SaveController* save_controller);

	void updateColors(const sf::Vector2f& mousePosition, const float dt);

	OverlayQuitCode quitStatus() const;
	std::string added_simulation_name() const;

	void render(sf::RenderWindow* window);

private:

	OverlayQuitCode m_quitCode;

	bool m_correct;

	ke::Button m_mask;
	ke::Button m_background;
	ke::InputButton m_input;
	ke::Button m_add;

	std::array<ke::Colorf, 8> m_colors;
};

