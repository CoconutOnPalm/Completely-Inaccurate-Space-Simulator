#include "AddSimulationOverlay.hpp"

AddSimulationOverlay::AddSimulationOverlay(const sf::Vector2f& winSize)
	: m_quitCode(OverlayQuitCode::NOT_QUITTING)
	, m_correct(false)
{
	m_mask.create(winSize, { 0, 0 }, ke::Origin::LEFT_TOP, nullptr);
	m_mask.setFillColor(sf::Color(0, 0, 0, 128));

	m_background.create(
		sf::Vector2f(winSize.x / 3.f, winSize.y / 4), winSize / 2.f, ke::Origin::MIDDLE_MIDDLE, nullptr, std::wstring(),
		0, ke::Origin::MIDDLE_MIDDLE, sf::Color(8, 8, 8, 255));

	m_input.create(sf::Vector2f(winSize.x / 4, winSize.y / 16), sf::Vector2f(winSize.x / 2, winSize.y / 2 - winSize.y / 24), ke::Origin::MIDDLE_MIDDLE, nullptr, L"simulation name", ke::TextScope::ASCII_Everything,
		50, 1, winSize.y / 32, ke::Origin::LEFT_MIDDLE, sf::Color(16, 16, 16, 255), sf::Color::White, sf::Color(64, 64, 64, 64), std::ceil(winSize.x / 1920), sf::Color::Transparent,
		sf::Text::Regular, sf::Vector2f(winSize.x / 100, 0));

	m_add.create(
		sf::Vector2f(winSize.x / 12, winSize.y / 32), sf::Vector2f(winSize.x / 2, winSize.y / 2 + winSize.y / 18), ke::Origin::MIDDLE_MIDDLE, nullptr, L"ADD",
		winSize.x / 96, ke::Origin::MIDDLE_MIDDLE, sf::Color(16, 16, 16, 255), sf::Color(128, 128, 128, 128));
}

AddSimulationOverlay::~AddSimulationOverlay()
{

}

void AddSimulationOverlay::updateEvents(const MousePosition& mousePosition, float dt)
{
	m_input.updateCursor();
}

void AddSimulationOverlay::updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event, SaveController* save_controller)
{
	if (!m_background.isInvaded(mousePosition.byWindow) && event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
	{
		m_quitCode = OverlayQuitCode::QUITTING_WITHOUT_OBJECT;
		return;
	}

	if (m_input.update(mousePosition.byWindow, event, sf::Mouse::Left, nullptr))
	{
		std::wstring buffer = m_input.getText();

		for (auto& i : buffer)
			if (i == L' ')
				i = L'_';

		m_input.setText(buffer);

		m_correct = std::filesystem::exists("Data/Simulations/" + ke::fixed::wtos(buffer) + ".sim") && buffer != L"latest_save";
	}

	if (m_input.getEPS())
	{
		if (m_correct)
			m_input.setOutlineColor(sf::Color::Green);
		else
			m_input.setOutlineColor(sf::Color::Red);
	}
	else
	{
		m_input.setOutlineColor(sf::Color::Transparent);
	}




	if (m_add.isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
	{
		if (m_correct)
		{
			std::cout << "size: " << save_controller->m_savedSimulations.size() << '\n';
			save_controller->m_savedSimulations[ke::fixed::wtos(m_input.getText())] = "Data/Simulations/" + ke::fixed::wtos(m_input.getText()) + ".sim";
			std::cout << "size: " << save_controller->m_savedSimulations.size() << '\n';

			State::sfx.play("click");
			m_quitCode = OverlayQuitCode::QUITTING_WITH_OBJECT;
		}
		else
		{
			State::sfx.play("error");
		}
	}
}

void AddSimulationOverlay::updateColors(const sf::Vector2f& mousePosition, const float dt)
{
	auto color_itr = m_colors.begin();
	ke::SmoothColorChange(&m_input, m_input.isInvaded(mousePosition) || m_input.getEPS(), sf::Color(32, 32, 32, 255), sf::Color(16, 16, 16, 255), *color_itr, 128, dt); ++color_itr;
	ke::SmoothColorChange(&m_add, m_add.isInvaded(mousePosition), sf::Color(32, 32, 32, 255), sf::Color(16, 16, 16, 255), *color_itr, 128, dt); ++color_itr;
	ke::SmoothTextColorChange(&m_add, m_add.isInvaded(mousePosition), sf::Color::White, sf::Color(255, 255, 255, 128), *color_itr, 256, dt); ++color_itr;
	//ke::SmoothOutlineColorChange(&m_input, m_input.isInvaded(mousePosition), sf::Color(0, 0, 64, 255), sf::Color(0, 0, 64, 0), *color_itr, 256, dt); ++color_itr;
	
}

OverlayQuitCode AddSimulationOverlay::quitStatus() const
{
	return m_quitCode;
}

std::string AddSimulationOverlay::added_simulation_name() const
{
	return ke::fixed::wtos(m_input.getText());
}

void AddSimulationOverlay::render(sf::RenderWindow* window)
{
	m_mask.render(window);
	m_background.render(window);
	m_input.render(window);
	m_add.render(window);
}
