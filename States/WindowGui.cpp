#include "WindowGui.hpp"

WindowGui::WindowGui(sf::RenderWindow* sf_window, sf::View* sf_view)
	: State(sf_window, sf_view, STATE::NONE)
	, m_windowStatus((AppSettings::WindowStyle() != sf::Style::Fullscreen) ? false : true)
	, m_windowCatchDiff(0, 0)
{
	//p_quitCode = StateQuitCode::NOT_QUITTING;
}

WindowGui::~WindowGui()
{

}


void WindowGui::InitState()
{
	sf::Texture closeButtonTexture;
	closeButtonTexture.loadFromFile("Textures/StateTextures/WindowGUI/close.png");
	closeButtonTexture.setSmooth(true);

	m_close.create(winSize / 32.f, { winSize.x, 0 }, ke::Origin::RIGHT_TOP, &closeButtonTexture, L"", 0, 0, sf::Color(255, 255, 255, 0));
	m_maximize.create(winSize / 32.f, { winSize.x - winSize.x / 32.f, 0 }, ke::Origin::RIGHT_TOP, "Textures/StateTextures/WindowGUI/maximize.png", L"", 0, 0, sf::Color(255, 255, 255, 0));
	m_minimize.create(winSize / 32.f, { winSize.x - winSize.x / 16.f, 0 }, ke::Origin::RIGHT_TOP, "Textures/StateTextures/WindowGUI/minimize.png", L"", 0, 0, sf::Color(255, 255, 255, 0));

	m_mousePosVis.create({ 20, 10 }, { 0, 0 }, ke::Origin::MIDDLE_BOTTOM, L"0, 0", 10);
}

void WindowGui::reloadState()
{
	m_close.setSize(winSize / 32.f);
	m_maximize.setSize(winSize / 32.f);
	m_minimize.setSize(winSize / 32.f);

	m_close.setPosition(winSize.x, 0);
	m_maximize.setPosition(winSize.x - winSize.x / 32.f, 0);
	m_minimize.setPosition(winSize.x - winSize.x / 16.f, 0);

	view->setSize(winSize);
	view->setCenter(view->getSize() / 2.f);

	//m_stateMask.setSize(winSize);
	//m_stateMask.setPosition(0, 0);
}


void WindowGui::updateEvents(const MousePosition& mousePosition, float dt)
{
	ke::SmoothColorChange(&m_close, m_close.isInvaded(mousePosition.byWindow), sf::Color(255, 255, 255, 32), sf::Color(255, 255, 255, 0), m_closecolor, 128, dt);
	ke::SmoothColorChange(&m_maximize, m_maximize.isInvaded(mousePosition.byWindow), sf::Color(255, 255, 255, 32), sf::Color(255, 255, 255, 0), m_maximcolor, 128, dt);
	ke::SmoothColorChange(&m_minimize, m_minimize.isInvaded(mousePosition.byWindow), sf::Color(255, 255, 255, 32), sf::Color(255, 255, 255, 0), m_minmimcolor, 128, dt);

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		m_windowHolded = false;

	//if (mousePosition.byWindow.y <= window->getSize().y * 0.03125) // div by 32
	//{
	//	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	//	{
	//		sf::Vector2f catchDiffBuffer = mousePosition.byWindow;
	//		window->setPosition(sf::Vector2i(mousePosition.byScreen + mousePosition.byWindow));
	//	}
	//}

	if (m_windowHolded && !m_windowStatus)
		window->setPosition(sf::Vector2i(mousePosition.byScreen - m_windowCatchDiff));
}

void WindowGui::updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LSystem) && sf::Keyboard::isKeyPressed(sf::Keyboard::M))
		::ShowWindow(window->getSystemHandle(), SW_MINIMIZE);


	if (mousePosition.byWindow.y < winSize.y / 32.f)
	{
		if (m_close.isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
			p_quitCode = StateQuitCode::APP_END;


		else if (m_minimize.isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
			::ShowWindow(window->getSystemHandle(), SW_MINIMIZE);

		else if (m_maximize.isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
		{
			RECT desktop;
			const HWND hDesktop = GetDesktopWindow();
			GetWindowRect(hDesktop, &desktop);

			sf::Vector2u wSize(desktop.right, desktop.bottom);

			if (!m_windowStatus && winSize != sf::Vector2f(1920, 1080)) // fullscreen
			{
				::ShowWindow(window->getSystemHandle(), SW_MAXIMIZE);
				window->create(sf::VideoMode(wSize.x, wSize.y), "Completely Inaccurate Space Simulator", sf::Style::None);
				winSize = sf::Vector2f(wSize);
				viewSize = sf::Vector2f(wSize);
				m_windowStatus = true;

				if (p_current_state != STATE::SIMULATION)
					window->setFramerateLimit(AppSettings::MaxMenuFPS());
				else
					window->setFramerateLimit(AppSettings::MaxSimulationFPS());
			}
			else // normal
			{
				window->create(sf::VideoMode(AppSettings::DefaultWindowSize().x, AppSettings::DefaultWindowSize().y), "Completely Inaccurate Space Simulator", sf::Style::None);
				m_windowStatus = false;
				winSize = AppSettings::DefaultWindowSize();
				viewSize = AppSettings::DefaultWindowSize();

				if (p_current_state != STATE::SIMULATION)
					window->setFramerateLimit(AppSettings::MaxMenuFPS());
				else
					window->setFramerateLimit(AppSettings::MaxSimulationFPS());
			}

			for (auto& itr : *states)
				itr->reloadState();
		}


		if (mousePosition.byWindow.x < winSize.x - winSize.x / 16.f && m_windowStatus != sf::Style::Fullscreen && winSize != sf::Vector2f(1920, 1080))
		{
			if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
			{
				m_windowHolded = true;
				m_windowCatchDiff = mousePosition.byWindow;
			}
		}
	}


	m_mousePosVis.setText(std::to_wstring(mousePosition.byView.x) + L' ' + std::to_wstring(mousePosition.byView.y));
	m_mousePosVis.setPosition(mousePosition.byWindow);
}

void WindowGui::renderBackground()
{
}

void WindowGui::renderByView()
{

}

void WindowGui::renderByWindow()
{
	m_close.render(window);
	m_maximize.render(window);
	m_minimize.render(window);

	//m_mousePosVis.render(window);
}

StateQuitCode WindowGui::Quit()
{
	return p_quitCode;
}
