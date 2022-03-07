#include "EquasionSelectionOverlay.hpp"

EquasionSelectionOverlay::EquasionSelectionOverlay(const sf::Vector2f& winSize)
	: m_quitCode(OverlayQuitCode::NOT_QUITTING)
	, m_selected(AppSettings::getGForceEquasion())
{
	m_background.create(
		sf::Vector2f(winSize.x / 4.f, winSize.y / 5), winSize / 2.f, ke::Origin::MIDDLE_MIDDLE, nullptr, std::wstring(),
		0, ke::Origin::MIDDLE_MIDDLE, sf::Color(8, 8, 8, 255));

	m_ok.create(
		sf::Vector2f(winSize.x / 16.f, winSize.y / 32), sf::Vector2f(winSize.x / 2.f + winSize.x / 24, winSize.y / 2 + winSize.y / 20), ke::Origin::MIDDLE_MIDDLE, ke::Settings::EmptyTexturePath(), L"OK",
		winSize.x / 112.f, ke::Origin::MIDDLE_MIDDLE, sf::Color(16, 16, 16, 255), sf::Color::White);

	m_cancel.create(
		sf::Vector2f(winSize.x / 16.f, winSize.y / 32), sf::Vector2f(winSize.x / 2.f - winSize.x / 24, winSize.y / 2 + winSize.y / 20), ke::Origin::MIDDLE_MIDDLE, ke::Settings::EmptyTexturePath(), L"CANCEL",
		winSize.x / 112.f, ke::Origin::MIDDLE_MIDDLE, sf::Color(16, 16, 16, 255), sf::Color::White);


	m_r2.create(sf::Vector2f(winSize.x / 16.f, winSize.y / 16), sf::Vector2f(winSize.x / 2.f, winSize.y / 2 - winSize.y / 24), ke::Origin::MIDDLE_MIDDLE, "Textures/StateTextures/Simulation/EquasionSelectionOverlay/F_rr.png", std::wstring(),
		winSize.x / 112.f, ke::Origin::MIDDLE_MIDDLE, sf::Color(0, 0, 0, 32), sf::Color::White);

	m_r.create(sf::Vector2f(winSize.x / 16.f, winSize.y / 16), sf::Vector2f(winSize.x / 2.f - winSize.x / 24, winSize.y / 2 - winSize.y / 24), ke::Origin::RIGHT_MIDDLE, "Textures/StateTextures/Simulation/EquasionSelectionOverlay/F_r.png", std::wstring(),
		winSize.x / 112.f, ke::Origin::MIDDLE_MIDDLE, sf::Color(0, 0, 0, 32), sf::Color::White);

	m_r3.create(sf::Vector2f(winSize.x / 16.f, winSize.y / 16), sf::Vector2f(winSize.x / 2.f + winSize.x / 24, winSize.y / 2 - winSize.y / 24), ke::Origin::LEFT_MIDDLE, "Textures/StateTextures/Simulation/EquasionSelectionOverlay/F_rrr.png", std::wstring(),
		winSize.x / 112.f, ke::Origin::MIDDLE_MIDDLE, sf::Color(0, 0, 0, 32), sf::Color::White);

	if (m_selected == 1)
	{
		m_r.setOutlineThickness(1);
		m_r.setOutlineColor(sf::Color(64, 64, 64, 255));
	}
	else if (m_selected == 2)
	{
		m_r2.setOutlineThickness(1);
		m_r2.setOutlineColor(sf::Color(64, 64, 64, 255));
	}
	else if (m_selected == 3)
	{
		m_r3.setOutlineThickness(1);
		m_r3.setOutlineColor(sf::Color(64, 64, 64, 255));
	}
	else
	{
		m_r2.setOutlineThickness(1);
		m_r2.setOutlineColor(sf::Color(64, 64, 64, 255));
	}
}

EquasionSelectionOverlay::~EquasionSelectionOverlay()
{

}

void EquasionSelectionOverlay::updateEvents(const MousePosition& mousePosition, float dt)
{

}

void EquasionSelectionOverlay::updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event)
{
	if (!m_background.isInvaded(mousePosition.byWindow) && event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
	{
		m_quitCode = OverlayQuitCode::CANCELING;
	}
	else if (m_cancel.isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
	{
		State::sfx.play("click");

		m_quitCode = OverlayQuitCode::CANCELING;
	}
	else if (m_ok.isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
	{
		State::sfx.play("click");

		AppSettings::setGForceEquasion(m_selected);
		m_quitCode = OverlayQuitCode::ACCEPTING;
	}

	if (m_r.isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
	{
		//State::sfx.play("click");

		m_r.setOutlineThickness(1);
		m_r.setOutlineColor(sf::Color(64, 64, 64, 255));
		m_selected = 1;

		m_r2.setOutlineColor(sf::Color::Transparent);
		m_r3.setOutlineColor(sf::Color::Transparent);
	}
	else if (m_r2.isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
	{
		//State::sfx.play("click");

		m_r2.setOutlineThickness(1);
		m_r2.setOutlineColor(sf::Color(64, 64, 64, 255));
		m_selected = 2;

		m_r.setOutlineColor(sf::Color::Transparent);
		m_r3.setOutlineColor(sf::Color::Transparent);
	}
	else if (m_r3.isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
	{
		//State::sfx.play("click");

		m_r3.setOutlineThickness(1);
		m_r3.setOutlineColor(sf::Color(64, 64, 64, 255));
		m_selected = 3;

		m_r.setOutlineColor(sf::Color::Transparent);
		m_r2.setOutlineColor(sf::Color::Transparent);
	}
}

void EquasionSelectionOverlay::updateColors(const sf::Vector2f& mousePosition, const float dt)
{
	auto color_itr = m_colors.begin();

	ke::SmoothColorChange(&m_ok, m_ok.isInvaded(mousePosition), sf::Color(32, 32, 32, 255), sf::Color(16, 16, 16, 255), *color_itr, 256, dt); ++color_itr;
	ke::SmoothColorChange(&m_cancel, m_cancel.isInvaded(mousePosition), sf::Color(32, 32, 32, 255), sf::Color(16, 16, 16, 255), *color_itr, 256, dt); ++color_itr;
	
	ke::SmoothColorChange(&m_r, m_r.isInvaded(mousePosition), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 32), *color_itr, 256, dt); ++color_itr;
}

OverlayQuitCode EquasionSelectionOverlay::quitStatus() const
{
	return m_quitCode;
}

void EquasionSelectionOverlay::render(sf::RenderWindow* window)
{
	m_background.render(window);
	m_ok.render(window);
	m_cancel.render(window);
	m_r.render(window);
	m_r2.render(window);
	m_r3.render(window);
}
