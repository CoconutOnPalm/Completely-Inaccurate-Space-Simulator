#include "SimSavingOverlay.hpp"

SimSavingOverlay::SimSavingOverlay(const sf::Vector2f& winSize, SaveController* save_controller, bool* simulation_running, const sf::Texture* sim_icon)
	: m_quitCode(OverlayQuitCode::NOT_QUITTING)
	, m_simulation_running(nullptr)
	, m_was_running(false)
	, m_saving_mode(true)
{
	m_saveController = save_controller;
	m_simulation_running = simulation_running;
	m_was_running = *m_simulation_running;
	*m_simulation_running = false;

	m_simIcon = sim_icon->copyToImage();
	m_simIcon.flipVertically();

	m_background.create(
		sf::Vector2f(winSize.x / 3.f, winSize.y / 3.5f), winSize / 2.f, ke::Origin::MIDDLE_MIDDLE, nullptr, L"",
		winSize.x / 56.f, ke::Origin::MIDDLE_MIDDLE, sf::Color(8, 8, 8, 255), sf::Color::White, {}, {}, {}, {}, { 0, -winSize.y / 32 });

	m_buttonColors.fill(sf::Color(16, 16, 16, 255));

	m_name.create({ winSize.x / 4, winSize.y / 15 }, { winSize.x / 2, winSize.y / 2 - winSize.y / 64 }, ke::Origin::MIDDLE_BOTTOM, nullptr, L"save name", ke::TextScope::ASCII_Everything, 30, 1, winSize.x / 64, ke::Origin::LEFT_MIDDLE,
		sf::Color(16, 16, 16, 255), sf::Color::White, sf::Color(32, 32, 32, 255), winSize.y / 360, sf::Color(32, 32, 32, 128), sf::Text::Regular, { winSize.x / 100, 0 });

	m_cancel.create(sf::Vector2f(winSize.x / 16.f, winSize.y / 24.f), sf::Vector2f(winSize.x / 2.f - winSize.x / 12.f, winSize.y / 2 + winSize.y / 15), ke::Origin::MIDDLE_MIDDLE, ke::Settings::EmptyTexturePath(), L"CANCEL",
		winSize.x / 96.f, ke::Origin::MIDDLE_MIDDLE, sf::Color(16, 16, 16, 255), sf::Color::White);

	m_save.create(sf::Vector2f(winSize.x / 16.f, winSize.y / 24.f), sf::Vector2f(winSize.x / 2.f + winSize.x / 12.f, winSize.y / 2 + winSize.y / 15), ke::Origin::MIDDLE_MIDDLE, ke::Settings::EmptyTexturePath(), L"SAVE",
		winSize.x / 96.f, ke::Origin::MIDDLE_MIDDLE, sf::Color(16, 16, 16, 255), sf::Color::White);
}

SimSavingOverlay::~SimSavingOverlay()
{
	*m_simulation_running = m_was_running;
}

void SimSavingOverlay::updateEvents(const MousePosition& mousePosition, float dt)
{
	m_name.updateCursor();
}

void SimSavingOverlay::updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event, std::vector<std::unique_ptr<SpaceObject>>* objects)
{
	if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left && !m_background.isInvaded(mousePosition.byWindow))
	{
		m_quitCode = OverlayQuitCode::CLOSING_OVRL;
		return;
	}

	if (m_cancel.isClicked(sf::Mouse::Left, mousePosition.byWindow, event) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
	{
		m_quitCode = OverlayQuitCode::CLOSING_OVRL;
		return;
	}
	else if (m_save.isClicked(sf::Mouse::Left, mousePosition.byWindow, event) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter))
	{
		std::string name = ke::fixed::wtos(m_name.getText());

		if (!name.empty())
		{
			if (name.find('.') == std::string::npos && name.find('/') == std::string::npos && name.find('\\') == std::string::npos && name.find('?') == std::string::npos &&
				name.find('<') == std::string::npos && name.find('>') == std::string::npos && name.find('*') == std::string::npos && name.find('|') == std::string::npos &&
				name.find('"') == std::string::npos && name.find(':') == std::string::npos && name != "empty" && name != "latest_save") // illegal characters
			{

				if (m_saving_mode)
				{
					m_saveController->Save(name, objects);
					m_simIcon.saveToFile("Data/Simulations/SimulationIcons/" + name + ".jpg"); // jpg to save some memory
				}
				else
				{
					m_saveController->AutoSave(name, objects);
				}

				m_quitCode = OverlayQuitCode::CLOSING_OVRL;
			}
		}
		else
			m_quitCode = OverlayQuitCode::CLOSING_OVRL;


	}


	if (m_name.update(mousePosition.byWindow, event, sf::Mouse::Left, nullptr))
	{
		std::wstring textbuffer = m_name.getText();
		std::replace(textbuffer.begin(), textbuffer.end(), L' ', L'_');
		m_name.setText(textbuffer);

		std::string name = ke::fixed::wtos(m_name.getText());

		if (name.empty())
		{
			m_name.setOutlineColor(sf::Color(255, 255, 255, 64));
		}
		else if (name.find('.') != std::string::npos || name.find('/') != std::string::npos || name.find('\\') != std::string::npos || name.find('?') != std::string::npos ||
			name.find('<') != std::string::npos || name.find('>') != std::string::npos || name.find('*') != std::string::npos || name.find('|') != std::string::npos ||
			name.find('"') != std::string::npos || name.find(':') != std::string::npos || name == "empty" || name == "latest_save") // illegal characters
		{
			m_name.setOutlineColor(sf::Color(255, 0, 0, 64));
		}
		else if (m_saveController->file_exists(name))
		{
			m_name.setOutlineColor(sf::Color(0, 0, 255, 64));
			m_save.setText(L"UPDATE");
			m_saving_mode = false;
		}
		else
		{
			m_name.setOutlineColor(sf::Color(0, 255, 0, 64));
			m_save.setText(L"SAVE");
			m_saving_mode = true;
		}
	}
}

void SimSavingOverlay::updateColors(const sf::Vector2f& mousePosition, const float dt)
{
	auto color_itr = m_buttonColors.begin();

	ke::SmoothColorChange(&m_name, m_name.isInvaded(mousePosition) || m_name.getEPS(), sf::Color(24, 24, 24, 255), sf::Color(16, 16, 16, 255), *color_itr, 128, dt); color_itr++;
	ke::SmoothTextColorChange(&m_name, m_name.isInvaded(mousePosition) || m_name.getEPS(), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 128), *color_itr, 256, dt); color_itr++;

	sf::Color target(64, 64, 64, 255);
	sf::Color basic(32, 32, 32, 128);

	if (!m_name.getText().empty())
	{
		if (m_saving_mode)
		{
			target = sf::Color(0, 64, 0, 255);
			basic = sf::Color(0, 32, 0, 128);
		}
		else
		{
			target = sf::Color(32, 32, 64, 255);
			basic = sf::Color(16, 16, 32, 128);
		}
	}


	ke::SmoothOutlineColorChange(&m_name, m_name.isInvaded(mousePosition) || m_name.getEPS(), target, basic, *color_itr, 256, dt); color_itr++;

	ke::SmoothColorChange(&m_cancel, m_cancel.isInvaded(mousePosition), sf::Color(32, 32, 32, 255), sf::Color(16, 16, 16, 255), *color_itr, 256, dt); color_itr++;
	ke::SmoothColorChange(&m_save, m_save.isInvaded(mousePosition), sf::Color(32, 32, 32, 255), sf::Color(16, 16, 16, 255), *color_itr, 256, dt); color_itr++;
}

OverlayQuitCode SimSavingOverlay::quitStatus() const
{
	return m_quitCode;
}

void SimSavingOverlay::render(sf::RenderWindow* window)
{
	m_background.render(window);
	m_name.render(window);
	m_save.render(window);
	m_cancel.render(window);
}
