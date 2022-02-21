#include "OpeningState.hpp"


OpeningState::OpeningState(sf::RenderWindow* sf_window, sf::View* sf_view)
	: State(sf_window, sf_view, STATE::SIM_OPENING)
	, m_sm_color(sf::Color::Black)
	, m_next_state(STATE::NONE)
	, m_outro_time(0)
	, m_simulation_name("empty")
{
	view->setCenter(winSize / 2.f);

	m_stateMask.create(winSize, { 0, 0 }, ke::Origin::LEFT_TOP, {}, {}, {}, sf::Color::Black);
}


OpeningState::~OpeningState()
{

}


void OpeningState::InitState()
{
	m_stateBackground.create(winSize, { 0, 0 }, ke::Origin::LEFT_TOP, "Textures/StateTextures/OpeningState/background.jpg");
	m_backgroundMask.create(winSize, { 0, 0 }, ke::Origin::LEFT_TOP, L"", 0, {}, sf::Color(0, 0, 0, 255.f - 255.f * AppSettings::BackgroundBrightness() * 0.01f));


	sf::Texture backb_texture;
	backb_texture.loadFromFile("Textures/StateTextures/back_arrow.png");
	backb_texture.setSmooth(true);
	m_back_button.create({ winSize.y / 8, winSize.y / 8 }, { 0, 0 }, ke::Origin::LEFT_TOP, &backb_texture);
	m_back_button.setFillColor(sf::Color(255, 255, 255, 128));


	sf::Texture ll_texture; ll_texture.loadFromFile("Textures/StateTextures/OpeningState/LLSI.png");
	ll_texture.setSmooth(true);
	sf::Texture cn_texture; cn_texture.loadFromFile("Textures/StateTextures/OpeningState/CNS.png");
	cn_texture.setSmooth(true);
	sf::Texture ls_texture; ls_texture.loadFromFile("Textures/StateTextures/OpeningState/BS.png");
	ls_texture.setSmooth(true);

	m_load_latest.create({ winSize.x / 5, winSize.y / 2 }, { winSize.x / 4, winSize.y / 2 }, ke::Origin::MIDDLE_MIDDLE, &ll_texture, L"Load latest", winSize.y / 32, ke::Origin::MIDDLE_BOTTOM, sf::Color::Black, sf::Color::White, winSize.y / 360, sf::Color(255, 255, 255, 128), {}, {}, { 0, -winSize.y / 16 });
	m_create_new.create({ winSize.x / 5, winSize.y / 2 }, { winSize.x / 2, winSize.y / 2 }, ke::Origin::MIDDLE_MIDDLE, &cn_texture, L"Create new", winSize.y / 32, ke::Origin::MIDDLE_BOTTOM, sf::Color::Black, sf::Color::White, winSize.y / 360, sf::Color(255, 255, 255, 128), {}, {}, { 0, -winSize.y / 16 });;
	m_load_saved.create({ winSize.x / 5, winSize.y / 2 }, { 3 * winSize.x / 4, winSize.y / 2 }, ke::Origin::MIDDLE_MIDDLE, &ls_texture, L"Browse saved", winSize.y / 32, ke::Origin::MIDDLE_BOTTOM, sf::Color::Black, sf::Color::White, winSize.y / 360, sf::Color(255, 255, 255, 128), {}, {}, { 0, -winSize.y / 16 });;

	//m_load_latest.getTextureShape()->setFillColor(sf::Color::White);
	m_load_latest.reverseRenderOrder();
	m_create_new.reverseRenderOrder();
	m_load_saved.reverseRenderOrder();
}



void OpeningState::reloadState()
{
	m_stateBackground.setSize(winSize);
	m_backgroundMask.setSize(winSize);
	m_stateMask.setSize(winSize);


	m_back_button.setSize(winSize.y / 8, winSize.y / 8);


	m_load_latest.setSize(winSize.x / 5, winSize.y / 2);
	m_create_new.setSize(winSize.x / 5, winSize.y / 2);
	m_load_saved.setSize(winSize.x / 5, winSize.y / 2);

	m_load_latest.setOutlineThickness(winSize.y / 360);
	m_load_saved.setOutlineThickness(winSize.y / 360);
	m_load_saved.setOutlineThickness(winSize.y / 360);

	m_load_latest.setPosition(winSize.x / 4, winSize.y / 2);
	m_create_new.setPosition(winSize.x / 2, winSize.y / 2);
	m_load_saved.setPosition(3 * winSize.x / 4, winSize.y / 2);

	m_load_latest.setCharacterSize(winSize.y / 32);
	m_create_new.setCharacterSize(winSize.y / 32);
	m_load_saved.setCharacterSize(winSize.y / 32);

	m_load_latest.setTextPosition(ke::Origin::MIDDLE_BOTTOM, { 0, -winSize.y / 16 });
	m_create_new.setTextPosition(ke::Origin::MIDDLE_BOTTOM, { 0, -winSize.y / 16 });
	m_load_saved.setTextPosition(ke::Origin::MIDDLE_BOTTOM, { 0, -winSize.y / 16 });
}


void OpeningState::updateEvents(const MousePosition& mousePosition, float dt)
{
	if (p_quitCode == StateQuitCode::STATE_QUIT)
	{
		ke::SmoothColorChange(&m_stateMask, true, sf::Color::Black, sf::Color::Transparent, m_sm_color, 512, dt);

		if (m_sm_color == ke::Colorf(sf::Color::Black))
		{
			switch (m_next_state)
			{
			case STATE::MAIN_MENU:
				states->back() = std::make_unique<MainMenu>(window, view, false);
				break;
			case STATE::SIMULATION:
				states->back() = std::make_unique<SimulationState>(window, view, m_simulation_name);
				break;
			case STATE::SAVED_BROWSER:
				states->back() = std::make_unique<SavedState>(window, view); 
				break;
			default:
				ke::throw_error("OpeningState::updateEvents() -> state quitting", "State not found", "ERROR");
				break;
			}

			ke::debug::Benchmark stateLoadingTime("State loading time");
			states->back()->InitState();
			return;
		}


		m_outro_time = m_outro_clock.getElapsedTime().asMilliseconds();

		if (m_outro_time > 10000) // safety guard
		{
			switch (m_next_state)
			{
			case STATE::MAIN_MENU:
				states->back() = std::make_unique<MainMenu>(window, view, false);
				break;
			case STATE::SIMULATION:
				states->back() = std::make_unique<SimulationState>(window, view, m_simulation_name);
				break;
			case STATE::SAVED_BROWSER:
				states->back() = std::make_unique<SavedState>(window, view);
				break;
			default:
				ke::throw_error("OpeningState::updateEvents() -> state quitting", "State not found", "ERROR");
				break;
			}

			ke::debug::Benchmark stateLoadingTime("State loading time");
			states->back()->InitState();
			//stateLoadingTime.Stop();
			return;
		}
	}
	else
	{
		m_outro_clock.restart();
		ke::SmoothColorChange(&m_stateMask, true, sf::Color::Transparent, sf::Color::Black, m_sm_color, 256, dt);
	}


	ke::SmoothOutlineColorChange(&m_load_latest, m_load_latest.isInvaded(mousePosition.byView), sf::Color::White, sf::Color(255, 255, 255, 128), m_button_colors.at(0), 160, dt);
	ke::SmoothTextColorChange(&m_load_latest, m_load_latest.isInvaded(mousePosition.byView), sf::Color::White, sf::Color(255, 255, 255, 160), m_button_colors.at(1), 160, dt);
	ke::SmoothOutlineColorChange(&m_create_new, m_create_new.isInvaded(mousePosition.byView), sf::Color::White, sf::Color(255, 255, 255, 128), m_button_colors.at(2), 160, dt);
	ke::SmoothTextColorChange(&m_create_new, m_create_new.isInvaded(mousePosition.byView), sf::Color::White, sf::Color(255, 255, 255, 160), m_button_colors.at(2), 160, dt);
	ke::SmoothOutlineColorChange(&m_load_saved, m_load_saved.isInvaded(mousePosition.byView), sf::Color::White, sf::Color(255, 255, 255, 128), m_button_colors.at(4), 160, dt);
	ke::SmoothTextColorChange(&m_load_saved, m_load_saved.isInvaded(mousePosition.byView), sf::Color::White, sf::Color(255, 255, 255, 160), m_button_colors.at(5), 160, dt);
	ke::SmoothColorChange(&m_back_button, m_back_button.isInvaded(mousePosition.byWindow), sf::Color::White, sf::Color(255, 255, 255, 128), m_button_colors.at(6), 255, dt);
}

void OpeningState::updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		p_quitCode = StateQuitCode::STATE_QUIT;
		m_next_state = STATE::MAIN_MENU;
	}
	else if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::XButton1)
	{
		p_quitCode = StateQuitCode::STATE_QUIT;
		m_next_state = STATE::MAIN_MENU;
	}
	else if (m_back_button.isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
	{
		p_quitCode = StateQuitCode::STATE_QUIT;
		m_next_state = STATE::MAIN_MENU;
	}
	else if (m_create_new.isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
	{
		p_quitCode = StateQuitCode::STATE_QUIT;
		m_next_state = STATE::SIMULATION;
		m_simulation_name = "empty";
	}
	else if (m_load_latest.isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
	{
		p_quitCode = StateQuitCode::STATE_QUIT;
		m_next_state = STATE::SIMULATION;
		m_simulation_name = "latest_save";
	}
	else if (m_load_saved.isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
	{
		p_quitCode = StateQuitCode::STATE_QUIT;
		m_next_state = STATE::SAVED_BROWSER;
		m_simulation_name = "latest_save";
	}
}

void OpeningState::renderBackground()
{
	m_stateBackground.render(window);
	m_backgroundMask.render(window);
}

void OpeningState::renderByView()
{

}

void OpeningState::renderByWindow()
{
	m_load_latest.render(window);

	m_back_button.render(window);

	m_create_new.render(window);
	m_load_saved.render(window);
	m_stateMask.render(window);
}