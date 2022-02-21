#include "Intro.hpp"

IntroState::IntroState(sf::RenderWindow* sf_window, sf::View* sf_view)
	: State(sf_window, sf_view, STATE::INTRO)
	, m_sm_color(sf::Color::Black)
	, m_time(0)
	, m_pause_time(0)
	, m_intro_on(true)
{
	p_quitCode = StateQuitCode::NOT_QUITTING;

	sf::Texture logo;
	//logo.loadFromFile("KEngine/Sources/Logos/ReversedKEngineLogo.png");
	logo.loadFromFile("res/CISS_Logo.png");

	logo.setSmooth(true);

	m_state_mask.create(winSize, { 0, 0 }, ke::Origin::LEFT_TOP, L"", 0, ke::Origin::MIDDLE_MIDDLE, sf::Color::Black);
	m_shader_mask.create(winSize, { 110, 110 }, ke::Origin::LEFT_TOP, L"", 0, ke::Origin::MIDDLE_MIDDLE, sf::Color::Black);
	m_KEngine_LOGO.create(winSize, { 0, 0 }, ke::Origin::LEFT_TOP, &logo);

	m_shader.loadFromFile("Textures/Shaders/intro_shader.frag", sf::Shader::Fragment);
	m_shader.setUniform("position", sf::Glsl::Vec2(-static_cast<float>(window->getSize().x) * 0.25f, window->getSize().y));
	//m_shader.setUniform("position", sf::Glsl::Vec2(static_cast<float>(sf_window->getSize().x), static_cast<float>(sf_window->getSize().y * 0.5f)));
	m_shader.setUniform("size", sf_window->getSize().x * 0.9f);
	m_shader.setUniform("color", sf::Glsl::Vec3(1.0, 1.0, 1.0));
}

IntroState::~IntroState()
{

}


void IntroState::InitState()
{

}

void IntroState::reloadState()
{
	m_shader_mask.setSize(winSize);
	m_state_mask.setSize(winSize);
	m_KEngine_LOGO.setSize(winSize);

	//m_shader.setUniform("position", sf::Glsl::Vec2(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y * 0.5f)));
	//m_shader.setUniform("position", sf::Glsl::Vec2(static_cast<float>(window->getSize().x) - m_time * 0.5, static_cast<float>(window->getSize().y) - m_time * 0.5));
	//m_shader.setUniform("position", sf::Glsl::Vec2(m_time * 0.5f, window->getSize().y));
	//m_shader.setUniform("position", sf::Glsl::Vec2(-static_cast<float>(window->getSize().x) * 0.5f + m_time * 0.5f, window->getSize().y));
	m_shader.setUniform("position", sf::Glsl::Vec2(-static_cast<float>(window->getSize().x) * 0.5f + m_time * 0.5f * window->getSize().x / 1600, window->getSize().y));
	m_shader.setUniform("size", window->getSize().x * 0.9f);
	m_shader.setUniform("color", sf::Glsl::Vec3(1.0, 1.0, 1.0));
}


void IntroState::updateEvents(const MousePosition& mousePosition, float dt)
{
	m_time = m_clock.getElapsedTime().asMilliseconds();

	//m_shader.setUniform("position", sf::Glsl::Vec2(static_cast<float>(window->getSize().x) - m_time * (winSize.x / 1920) * 0.4, static_cast<float>(window->getSize().y) - m_time * (winSize.y / 1080) * 0.4));
	m_shader.setUniform("position", sf::Glsl::Vec2(-static_cast<float>(window->getSize().x) * 0.5f + m_time * 0.5f * window->getSize().x / 1600, window->getSize().y));

	if (m_time > 420 * 2)
	{
		if (m_intro_on)
		{
			m_intro_on = ke::SmoothColorChange(&m_state_mask, true, sf::Color::Transparent, sf::Color::Black, m_sm_color, 256, dt);
		}
		else
		{
			m_pause_time = m_pause_clock.getElapsedTime().asMilliseconds();

			if (m_pause_time > 2137 * 2)
			{
				ke::SmoothColorChange(&m_state_mask, true, sf::Color::Black, sf::Color::Transparent, m_sm_color, 256, dt);

				if (m_sm_color == ke::Colorf(sf::Color::Black))
				{
					states->back() = std::make_unique<MainMenu>(window, view, true);
					states->back()->InitState();
					return;
				}
			}

			if (m_pause_time > 10000) // safety guard
			{
				states->back() = std::make_unique<MainMenu>(window, view, true);
				states->back()->InitState();
				return;
			}
		}
	}
}

void IntroState::updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		states->back() = std::make_unique<MainMenu>(window, view, true);
		states->back()->InitState();
		return;
	}
}


void IntroState::renderBackground()
{

}

void IntroState::renderByView()
{

}

void IntroState::renderByWindow()
{
	//window->draw(*m_KEngine_LOGO.getShape(), &m_shader);
	window->draw(*m_shader_mask.getShape(), &m_shader);
	m_KEngine_LOGO.render(window);
	m_state_mask.render(window);
	//window->draw(*m_state_mask.getShape(), &m_shader);
}


StateQuitCode IntroState::Quit()
{
	return p_quitCode;
}





////////////////////////////////////////////////////////////////


void IS_start_intro_closing(State& iState)
{
	iState.p_quitCode = StateQuitCode::ANIMATION_OUTRO;
}
