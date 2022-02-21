#include "MainMenu.hpp"

MainMenu::MainMenu(sf::RenderWindow* sf_window, sf::View* sf_view, bool with_animation)
	: State(sf_window, sf_view, STATE::MAIN_MENU)
	, m_sm_color(sf::Color::Black)
	, m_next_state(STATE::NONE)
	, m_outro_time(0)
	, m_current_point_1(40)
	, m_current_point_2(50)
	, m_animation_finished(!with_animation)
	, m_quitting_app(false)
	, point_count_multiplier(2)
{
	view->setCenter(winSize / 2.f);

	m_stateMask.create(winSize, { 0, 0 }, ke::Origin::LEFT_TOP, {}, {}, {}, sf::Color::Black);
}

MainMenu::~MainMenu()
{

}


void MainMenu::InitState()
{


	m_stateBackground.create(winSize, { 0, 0 }, ke::Origin::LEFT_TOP, "Textures/StateTextures/Simulation/Backgrounds/NGC-2525.png");
	m_backgroundMask.create(winSize, { 0, 0 }, ke::Origin::LEFT_TOP, L"", 0, {}, sf::Color(0, 0, 0, 255.f - 255.f * AppSettings::BackgroundBrightness() * 0.01f));
	m_menu_logo.create(winSize, { 0, 0 }, ke::Origin::LEFT_TOP, "Textures/StateTextures/MainMenu/menu ciss logo.png");
	m_menu_logo.setFillColor(sf::Color(255, 255, 255, 0));


	m_start_button.create(winSize.y / 5, sf::Vector2f(winSize.x / 5, winSize.y / 4), ke::Origin::MIDDLE_MIDDLE, "Textures/StateTextures/MainMenu/Sun.png");


	m_orbit_1.setPointCount(360 * point_count_multiplier);
	m_orbit_2.setPointCount(360 * point_count_multiplier);

	m_orbit_1.setRadius(winSize.y / 2.75);
	m_orbit_2.setRadius(winSize.y / 1.5);

	m_orbit_1.setOrigin(m_orbit_1.getRadius(), m_orbit_1.getRadius());
	m_orbit_1.setPosition(sf::Vector2f(winSize.x / 5, winSize.y / 4));

	m_orbit_2.setOrigin(m_orbit_2.getRadius(), m_orbit_2.getRadius());
	m_orbit_2.setPosition(sf::Vector2f(winSize.x / 5, winSize.y / 4));
	/*
	m_orbit_1.setOutlineColor(sf::Color::Red);
	m_orbit_1.setOutlineThickness(10);
	m_orbit_1.setFillColor(sf::Color::Transparent);

	m_orbit_2.setOutlineColor(sf::Color::Red);
	m_orbit_2.setOutlineThickness(10);
	m_orbit_2.setFillColor(sf::Color::Transparent);
	 */

	
	if (m_animation_finished)
	{
		m_settings_button.create(winSize.y / 12, m_orbit_1.getPoint(0) + m_orbit_1.getPosition(), ke::Origin::MIDDLE_MIDDLE, "Textures/StateTextures/MainMenu/settings.png");
		m_quitButton.create(winSize.y / 10, m_orbit_2.getPoint(0) + m_orbit_2.getPosition(), ke::Origin::MIDDLE_MIDDLE, "Textures/StateTextures/MainMenu/quit.png");
	}
	else
	{
		m_settings_button.create(winSize.y / 12, sf::Vector2f(winSize.x / 2.7683, winSize.y / 1.6740), ke::Origin::MIDDLE_MIDDLE, "Textures/StateTextures/MainMenu/settings.png");
		m_quitButton.create(winSize.y / 10, sf::Vector2f(winSize.x / 1.3734, winSize.y / 1.1224), ke::Origin::MIDDLE_MIDDLE, "Textures/StateTextures/MainMenu/quit.png");

		m_settings_button.setPosition(sf::Vector2f(winSize.x / 2.7683, winSize.y / 1.6740));
		m_quitButton.setPosition(sf::Vector2f(winSize.x / 1.3734, winSize.y / 1.1224));
	}



	const sf::Vector2f P(winSize * 0.5f);

	ke::debug::Benchmark b;

	for (auto& itr : m_hyperspace_jump)
	{
		itr.resize(2);
		itr.setPrimitiveType(sf::PrimitiveType::Lines);

		itr[0].color = sf::Color(0, 255, 255, 0);
		itr[1].color = sf::Color(0, 255, 255, 0);

		itr[0].position = sf::Vector2f(ke::Random::Float(-winSize.x, 2 * winSize.x), ke::Random::Float(-winSize.y, 2 * winSize.y));

		//float length = ke::Random::Float(winSize.x / 20, winSize.x / 10);

		//float angle = std::atan(-(itr[0].position.y - P.y) / (itr[0].position.x - P.x)) * TO_DEG;

		//if ((P.x > itr[0].position.x))
		//	angle += 180;

		//std::cout << angle;

		//float m = std::sqrt((itr[0].position.x - P.x) * (itr[0].position.x - P.x) + (itr[0].position.y - P.y) * (itr[0].position.y - P.y)); // distance from itr[0] to P

		//itr[1].position = sf::Vector2f(m * sin(angle * TO_RAD), m * cos(angle * TO_RAD));

		itr[1].position = P;
	}


	m_star_shader.loadFromFile("Textures/Shaders/glow.frag", sf::Shader::Fragment);
	m_star_shader.setUniform("size", winSize.y / 3);
	m_star_shader.setUniform("basic_a", 0.8f);
	m_star_shader.setUniform("position", sf::Glsl::Vec2(m_start_button.getShapeCenter().x, winSize.y - m_start_button.getShapeCenter().y));
	m_star_shader.setUniform("color", sf::Glsl::Vec3(0.8, 0.7, 0.0));



	m_sfx.setGeneralVolume(AppSettings::SFXVolume());
	m_sfx.addEffect("Hyperspace jump", "Audio/hyperspace jump.wav");
}

void MainMenu::reloadState()
{
	m_stateBackground.setSize(winSize);
	m_backgroundMask.setSize(winSize);
	m_stateMask.setSize(winSize);


	/*int i = 2;
	for (auto& itr : m_buttons)
	{
		itr->setSize(winSize / 8.f);
		itr->setPosition(winSize.x / 8, i * winSize.y / 8);
		itr->setCharacterSize(winSize.y / 32);
		i++;
	}*/
}


void MainMenu::updateEvents(const MousePosition& mousePosition, float dt)
{
	/*auto color_itr = m_floatcolors.begin();

	for (auto& itr : m_buttons)
	{
		ke::SmoothTextColorChange(itr.get(), itr->isInvaded(mousePosition.byView), sf::Color::White, sf::Color(255, 255, 255, 160), *color_itr, 256, dt);
		color_itr++;
	}*/



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
		if (!m_quitting_app)
			m_outro_clock.restart();
		ke::SmoothColorChange(&m_stateMask, true, sf::Color::Transparent, sf::Color::Black, m_sm_color, 256, dt);
	}

	if (!m_animation_finished)
	{
		if (m_current_point_1 < 130 * point_count_multiplier)
		{
			ke::SmoothMove(&m_settings_button, m_orbit_1.getPoint(m_current_point_1 + 1), m_orbit_1.getPoint(m_current_point_1), (130 * point_count_multiplier - m_current_point_1) * 10, dt);

			if (ke::areClose(m_settings_button.getPosition(), m_orbit_1.getPoint(m_current_point_1 + 1)))
				m_current_point_1++;
		}
		else
		{
			if (!m_animation_finished)
			{
				ke::debug::printVector2(m_settings_button.getPosition(), "settigns");
				ke::debug::printVector2(m_quitButton.getPosition(), "quit");
			}
			m_animation_finished = true;
		}
		if (m_current_point_2 < 110 * point_count_multiplier)
		{
			ke::SmoothMove(&m_quitButton, m_orbit_2.getPoint(m_current_point_2 + 1), m_orbit_2.getPoint(m_current_point_2), (110 * point_count_multiplier - m_current_point_2) * 10, dt);

			if (ke::areClose(m_quitButton.getPosition(), m_orbit_2.getPoint(m_current_point_2 + 1)))
				m_current_point_2++;
		}
	}
	else
	{

		m_settings_button.setPosition(sf::Vector2f(winSize.x / 2.7683, winSize.y / 1.6740));
		m_quitButton.setPosition(sf::Vector2f(winSize.x / 1.3734, winSize.y / 1.1224));
	}


	if (m_animation_finished)
	{
		ke::SmoothColorChange(&m_menu_logo, true, sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 0), m_colors.back(), 128, dt);
	}

	if (m_quitting_app)
	{
		m_outro_time = m_outro_clock.getElapsedTime().asMilliseconds();

		//std::cout << m_outro_time << '\n';

		if (m_outro_time > 3000)
		{
			p_quitCode = StateQuitCode::APP_END;
			return;
		}

		if (m_outro_time > 600)
		{
			//m_stateMask.setFillColor(sf::Color::Black);
			m_stateMask.setFillColor(sf::Color::White);
			m_stateMask.setTexture("res/CISS_Logo.png");
		}

		float alpha = m_outro_time / 4;

		if (alpha > 255)
			alpha = 255;

		for (auto& itr : m_hyperspace_jump)
		{
			itr[0].color = sf::Color(0, 255, 255, alpha);
			itr[1].color = sf::Color(0, 255, 255, alpha);
		}
	}

	auto color_itr = m_colors.begin();

	ke::SmoothColorChange(&m_start_button, m_start_button.isInvaded(mousePosition.byView), sf::Color::White, sf::Color(255, 255, 255, 128), *color_itr, 256, dt); ++color_itr;
	ke::SmoothColorChange(&m_settings_button, m_settings_button.isInvaded(mousePosition.byView), sf::Color::White, sf::Color(255, 255, 255, 128), *color_itr, 256, dt); ++color_itr;
	ke::SmoothColorChange(&m_quitButton, m_quitButton.isInvaded(mousePosition.byView), sf::Color::White, sf::Color(255, 255, 255, 128), *color_itr, 256, dt); ++color_itr;
}

void MainMenu::updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event)
{
	if (m_start_button.isClicked(sf::Mouse::Left, mousePosition.byView, event))
	{
		p_quitCode = StateQuitCode::STATE_QUIT;
		m_next_state = STATE::SIM_OPENING;
	}
	else if (m_settings_button.isClicked(sf::Mouse::Left, mousePosition.byView, event))
	{
		p_quitCode = StateQuitCode::STATE_QUIT;
		m_next_state = STATE::SETTINGS;
	}
	else if (!m_quitting_app)
	{
		if (m_quitButton.isClicked(sf::Mouse::Left, mousePosition.byView, event))
		{
			m_quitting_app = true;
			m_outro_time = 0;
			m_outro_clock.restart();

			m_stateMask.setFillColor(sf::Color(0, 255, 255, 128));
			m_menu_logo.setActiveStatus(false);

			m_sfx.play("Hyperspace jump");
		}
	}
}

void MainMenu::renderBackground()
{
	m_stateBackground.render(window);
	m_backgroundMask.render(window);
	window->draw(*m_backgroundMask.getShape(), &m_star_shader);
	m_menu_logo.render(window);
}

void MainMenu::renderByView()
{
	/*for (auto& itr : m_buttons)
		itr->render(window);*/
		//window->draw(m_orbit_1);
		//window->draw(m_orbit_2);

	m_start_button.render(window);
	m_settings_button.render(window);
	m_quitButton.render(window);
}

void MainMenu::renderByWindow()
{
	if (m_quitting_app)
		for (auto& itr : m_hyperspace_jump)
			window->draw(itr);

	m_stateMask.render(window);
}

StateQuitCode MainMenu::Quit()
{
	return p_quitCode;
}
