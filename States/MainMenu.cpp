#include "MainMenu.hpp"

MainMenu::MainMenu(sf::RenderWindow* sf_window, sf::View* sf_view)
	: State(sf_window, sf_view, STATE::MAIN_MENU)
	, m_sm_color(sf::Color::Black)
	, m_next_state(STATE::NONE)
	, m_outro_time(0)
{
	view->setCenter(winSize / 2.f);

	m_stateMask.create(winSize, { 0, 0 }, ke::Origin::LEFT_TOP, {}, {}, {}, sf::Color::Black);
}

MainMenu::~MainMenu()
{

}


void MainMenu::InitState()
{
	const int button_count = 4;

	m_stateBackground.create(winSize, { 0, 0 }, ke::Origin::LEFT_TOP, "Textures/StateTextures/MainMenu/background.png");
	m_backgroundMask.create(winSize, { 0, 0 }, ke::Origin::LEFT_TOP, L"", 0, {}, sf::Color(0, 0, 0, 255.f - 255.f * AppSettings::BackgroundBrightness() * 0.01f));


	m_buttons.reserve(button_count);

	m_buttons.emplace_back(std::make_unique<ke::Rectangle>(winSize / 8.f, sf::Vector2f(winSize.x / 8, 2 * winSize.y / 8), ke::Origin::LEFT_TOP, L"START", winSize.y / 32, ke::Origin::LEFT_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 160))); // sf::Color(255, 255, 255, 192)
	m_buttons.emplace_back(std::make_unique<ke::Rectangle>(winSize / 8.f, sf::Vector2f(winSize.x / 8, 3 * winSize.y / 8), ke::Origin::LEFT_TOP, L"SAVED", winSize.y / 32, ke::Origin::LEFT_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 160)));
	m_buttons.emplace_back(std::make_unique<ke::Rectangle>(winSize / 8.f, sf::Vector2f(winSize.x / 8, 4 * winSize.y / 8), ke::Origin::LEFT_TOP, L"SETTINGS", winSize.y / 32, ke::Origin::LEFT_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 160)));
	m_buttons.emplace_back(std::make_unique<ke::Rectangle>(winSize / 8.f, sf::Vector2f(winSize.x / 8, 5 * winSize.y / 8), ke::Origin::LEFT_TOP, L"QUIT", winSize.y / 32, ke::Origin::LEFT_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 160)));

	m_floatcolors.reserve(button_count);

	for (int i = 0; i < button_count; i++)
		m_floatcolors.emplace_back();
}

void MainMenu::reloadState()
{
	m_stateBackground.setSize(winSize);
	m_backgroundMask.setSize(winSize);
	m_stateMask.setSize(winSize);


	int i = 2;
	for (auto& itr : m_buttons)
	{
		itr->setSize(winSize / 8.f);
		itr->setPosition(winSize.x / 8, i * winSize.y / 8);
		itr->setCharacterSize(winSize.y / 32);
		i++;
	}
}


void MainMenu::updateEvents(const MousePosition& mousePosition, float dt)
{
	auto color_itr = m_floatcolors.begin();

	for (auto& itr : m_buttons)
	{
		ke::SmoothTextColorChange(itr.get(), itr->isInvaded(mousePosition.byView), sf::Color::White, sf::Color(255, 255, 255, 160), *color_itr, 256, dt);
		color_itr++;
	}



	if (p_quitCode == StateQuitCode::STATE_QUIT)
	{
		ke::SmoothColorChange(&m_stateMask, true, sf::Color::Black, sf::Color::Transparent, m_sm_color, 512, dt);

		if (m_sm_color == ke::Colorf(sf::Color::Black))
		{
			switch (m_next_state)
			{
			case STATE::SETTINGS:
				states->back() = std::make_unique<SettingsState>(window, view);
				break;
			case STATE::SIM_OPENING:
				states->back() = std::make_unique<OpeningState>(window, view);
				break;
			default:
				ke::throw_error("MainMenu::updateEvents() -> state quitting", "State not found", "ERROR");
				break;
			}

			states->back()->InitState();
			return;
		}


		m_outro_time = m_outro_clock.getElapsedTime().asMilliseconds();

		if (m_outro_time > 10000) // safety guard
		{
			switch (m_next_state)
			{
			case STATE::SETTINGS:
				states->back() = std::make_unique<SettingsState>(window, view);
				break;
			case STATE::SIM_OPENING:
				states->back() = std::make_unique<OpeningState>(window, view);
				break;
			default:
				ke::throw_error("MainMenu::updateEvents() -> state quitting", "State not found", "ERROR");
				break;
			}

			states->back()->InitState();
			return;
		}
	}
	else
	{
		m_outro_clock.restart();
		ke::SmoothColorChange(&m_stateMask, true, sf::Color::Transparent, sf::Color::Black, m_sm_color, 256, dt);
	}
}

void MainMenu::updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event)
{
	if (mousePosition.byView.x > winSize.x * 0.125f && mousePosition.byView.x < winSize.x * 0.25f)
	{
		for (auto& itr : m_buttons)
			itr->update({ 0, 0 }, event, sf::Mouse::Left, nullptr);

		if (m_buttons.at(0)->isClicked(sf::Mouse::Left, mousePosition.byView, event))
		{
			p_quitCode = StateQuitCode::STATE_QUIT;
			m_next_state = STATE::SIM_OPENING;
		}
		else if (m_buttons.at(1)->isClicked(sf::Mouse::Left, mousePosition.byView, event))
		{
			//p_quitCode = StateQuitCode::STATE_QUIT;
			//m_next_state = NextState::SETTINGS;
		}
		else if (m_buttons.at(2)->isClicked(sf::Mouse::Left, mousePosition.byView, event))
		{
			p_quitCode = StateQuitCode::STATE_QUIT;
			m_next_state = STATE::SETTINGS;
		}

		if (m_buttons.at(3)->isClicked(sf::Mouse::Left, mousePosition.byView, event))
			p_quitCode = StateQuitCode::APP_END;
	}
}

void MainMenu::renderBackground()
{
	m_stateBackground.render(window);
	m_backgroundMask.render(window);
}

void MainMenu::renderByView()
{
	for (auto& itr : m_buttons)
		itr->render(window);
}

void MainMenu::renderByWindow()
{
	m_stateMask.render(window);
}

StateQuitCode MainMenu::Quit()
{
	return p_quitCode;
}
