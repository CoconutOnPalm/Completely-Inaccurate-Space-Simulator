#pragma once

//#include "KEngine/Algorithms.hpp"

//#include "States/State.hpp"
//#include "States/SettingsState.hpp"

//#include "Space Objects/Planet.hpp"
//#include "Space Objects/Star.hpp"
//#include "Space Objects/CenterOfMass.hpp"
//#include "Space Objects/ObjectIcon.hpp"
//#include "Space Objects/ObjectBuffer.hpp"
//#include "Equasions/Equasions.hpp"
//#include "Equasions/Constants.hpp"

//#include "States/Global/FileStorage.hpp"

#include "States/Overlays/QuitOverlay.hpp"

#define PanelUI std::vector<std::unique_ptr<ke::Button>>

class QuitOverlay;

class StateControlPanel
{
public:

	StateControlPanel();
	~StateControlPanel();

	void assign(PanelUI* controllers, std::unique_ptr<State>* upperStates, std::unique_ptr<QuitOverlay>* overlay);

	bool quittingRequestStatus() const;

	void updateEvents(const MousePosition& mousePosition, float dt);
	void updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event, sf::RenderWindow* window, sf::View* view);

	void updateColors(const sf::Vector2f& mousePosition, const float dt);


	void renderBackground(sf::RenderWindow* window = nullptr);
	void renderView(sf::RenderWindow* window = nullptr);
	void renderWindow(sf::RenderWindow* window = nullptr);

private:

	PanelUI* m_controllers;
	std::unique_ptr<State>* m_upperState;
	std::unique_ptr<QuitOverlay>* m_quitOverlay;

	bool m_quitting;

};