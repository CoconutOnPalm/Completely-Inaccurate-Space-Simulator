#include "StateControlPanel.hpp"


#define m_upperState_ptr (*m_upperState)


StateControlPanel::StateControlPanel()
	: m_quitting(false)
{

}

StateControlPanel::~StateControlPanel()
{

}

void StateControlPanel::assign(PanelUI* controllers, std::unique_ptr<State>* upperStates, std::unique_ptr<QuitOverlay>* QuitOverlay, SimParamsOverlay* settingsOverlay)
{
	m_controllers = controllers;
	m_upperState = upperStates;
	m_quitOverlay = QuitOverlay;
	m_simParamsOverlay = settingsOverlay;
}

bool StateControlPanel::quittingRequestStatus() const
{
	return m_quitting;
}

void StateControlPanel::updateEvents(const MousePosition& mousePosition, float dt)
{

}

void StateControlPanel::updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event, sf::RenderWindow* window, sf::View* view)
{

	if (m_controllers->at(0)->isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
		(*m_quitOverlay) = std::make_unique<QuitOverlay>(sf::Vector2f(window->getSize()));
	else if (m_controllers->at(1)->isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
	{
		m_simParamsOverlay->activate();
		std::cout << "quack\n";
	}
		//m_upperState_ptr = std::make_unique<SettingsState>(window, view);
	//else if (m_controllers->at(2)->isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
		// do sth
}

void StateControlPanel::updateColors(const sf::Vector2f& mousePosition, const float dt)
{
	auto color_itr = m_colors.begin();

	for (auto& itr : *m_controllers)
	{
		ke::SmoothColorChange(itr.get(), itr->isInvaded(mousePosition), sf::Color::Transparent, sf::Color(0, 0, 0, 64), *color_itr, 256, dt);
		++color_itr;
	}
}

void StateControlPanel::renderBackground(sf::RenderWindow* window)
{
	
}

void StateControlPanel::renderView(sf::RenderWindow* window)
{
	
}

void StateControlPanel::renderWindow(sf::RenderWindow* window)
{
	
}

#undef m_upperState_ptr