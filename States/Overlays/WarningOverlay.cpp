#include "WarningOverlay.hpp"


WarningOverlay::WarningOverlay(const std::wstring& message, const sf::Vector2f& winSize)
	: m_quitCode(OverlayQuitCode::NOT_QUITTING)
{
	m_background.create(
		sf::Vector2f(winSize.x / 4.f, winSize.y / 5), winSize / 2.f, ke::Origin::MIDDLE_MIDDLE, nullptr, message,
		winSize.x / 100.f, ke::Origin::MIDDLE_MIDDLE, sf::Color(8, 8, 8, 255), sf::Color::White, {}, {}, {}, {}, { 0, -winSize.y / 32 });

	m_ok.create(
		sf::Vector2f(winSize.x / 16.f, winSize.y / 32), sf::Vector2f(winSize.x / 2.f + winSize.x / 24, winSize.y / 2 + winSize.y / 20), ke::Origin::MIDDLE_MIDDLE, ke::Settings::EmptyTexturePath(), L"OK",
		winSize.x / 112.f, ke::Origin::MIDDLE_MIDDLE, sf::Color(16, 16, 16, 255), sf::Color::White);

	m_cancel.create(
		sf::Vector2f(winSize.x / 16.f, winSize.y / 32), sf::Vector2f(winSize.x / 2.f - winSize.x / 24, winSize.y / 2 + winSize.y / 20), ke::Origin::MIDDLE_MIDDLE, ke::Settings::EmptyTexturePath(), L"CANCEL",
		winSize.x / 112.f, ke::Origin::MIDDLE_MIDDLE, sf::Color(16, 16, 16, 255), sf::Color::White);
}



WarningOverlay::~WarningOverlay()
{

}

void WarningOverlay::updateEvents(const MousePosition& mousePosition, float dt)
{

}

void WarningOverlay::updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event)
{
	if (!m_background.isInvaded(mousePosition.byWindow) && event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
		m_quitCode = OverlayQuitCode::CANCELING;
	else if (m_cancel.isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
		m_quitCode = OverlayQuitCode::CANCELING;
	else if (m_ok.isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
		m_quitCode = OverlayQuitCode::ACCEPTING;
}

void WarningOverlay::updateColors(const sf::Vector2f& mousePosition, const float dt)
{
	ke::SmoothColorChange(&m_ok, m_ok.isInvaded(mousePosition), sf::Color(32, 32, 32, 255), sf::Color(16, 16, 16, 255), ok_color, 256, dt);
	ke::SmoothColorChange(&m_cancel, m_cancel.isInvaded(mousePosition), sf::Color(32, 32, 32, 255), sf::Color(16, 16, 16, 255), cancel_color, 256, dt);
}

OverlayQuitCode WarningOverlay::quitStatus() const
{
	return m_quitCode;
}

void WarningOverlay::render(sf::RenderWindow* window)
{
	m_background.render(window);
	m_ok.render(window);
	m_cancel.render(window);
}
