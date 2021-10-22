#include "QuitOverlay.hpp"

QuitOverlay::QuitOverlay(const sf::Vector2f& winSize)
	: m_quitStatus(QS_NOT_QUITTING)
{
	m_button.create(
		sf::Vector2f(winSize.x / 4.f, winSize.y / 5), winSize / 2.f, ke::Origin::MIDDLE_MIDDLE, ke::Settings::EmptyTexturePath(), L"Do you want to quit?", 
		winSize.x / 56.f, ke::Origin::MIDDLE_MIDDLE, sf::Color(8, 8, 8, 255), sf::Color::White, {}, {}, {}, {}, {0, -winSize.y / 32});

	m_buttonColors.fill(sf::Color(16, 16, 16, 255));


	m_buttons["_QUIT"].create(
		sf::Vector2f(winSize.x / 24.f, winSize.y / 32), sf::Vector2f(winSize.x / 2.f - winSize.x / 12.f, winSize.y / 2 + winSize.y / 20), ke::Origin::MIDDLE_MIDDLE, ke::Settings::EmptyTexturePath(), L"QUIT",
		winSize.x / 112.f, ke::Origin::MIDDLE_MIDDLE, sf::Color(16, 16, 16, 255), sf::Color::White);

	m_buttons["_SAVE_N_QUIT"].create(
		sf::Vector2f(winSize.x / 12.f, winSize.y / 32), sf::Vector2f(winSize.x / 2.f, winSize.y / 2 + winSize.y / 20), ke::Origin::MIDDLE_MIDDLE, ke::Settings::EmptyTexturePath(), L"SAVE & QUIT",
		winSize.x / 112.f, ke::Origin::MIDDLE_MIDDLE, sf::Color(16, 16, 16, 255), sf::Color::White);

	m_buttons["_CANCEL"].create(
		sf::Vector2f(winSize.x / 24.f, winSize.y / 32), sf::Vector2f(winSize.x / 2.f + winSize.x / 12.f, winSize.y / 2 + winSize.y / 20), ke::Origin::MIDDLE_MIDDLE, ke::Settings::EmptyTexturePath(), L"CANCEL",
		winSize.x / 112.f, ke::Origin::MIDDLE_MIDDLE, sf::Color(16, 16, 16, 255), sf::Color::White);

	sf::Event fake_event;

	for (auto& itr : m_buttons)
		itr.second.update({}, fake_event, sf::Mouse::Left, nullptr);
}

QuitOverlay::~QuitOverlay()
{

}

void QuitOverlay::updateEvents(const MousePosition& mousePosition, float dt)
{

}

void QuitOverlay::updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event)
{
	// closing by clicking out of the box
	if (!m_button.isInvaded(mousePosition.byWindow) && event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
		m_quitStatus = CLOSING_OVRL;

	else if (m_buttons["_QUIT"].isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
		m_quitStatus = QUITTING;

	else if (m_buttons["_SAVE_N_QUIT"].isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
		m_quitStatus = QUITTING_AND_SAVING;

	else if (m_buttons["_CANCEL"].isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
		m_quitStatus = CLOSING_OVRL;

	//else
		//m_quitStatus = NOT_QUITTING;
}

void QuitOverlay::updateColors(const sf::Vector2f& mousePosition, const float dt)
{
	auto color_itr = m_buttonColors.begin();

	for (auto& itr : m_buttons)
	{
		ke::SmoothColorChange(&itr.second, itr.second.isInvaded(mousePosition), sf::Color(32, 32, 32, 255), sf::Color(16, 16, 16, 255), *color_itr, 256, dt);
		color_itr++;
	}
}

int QuitOverlay::quitStatus() const
{
	return m_quitStatus;
}

void QuitOverlay::render(sf::RenderWindow* window)
{
	m_button.render(window);
	//m_quit_button.render(window);

	for (auto& itr : m_buttons)
		itr.second.render(window);
}
