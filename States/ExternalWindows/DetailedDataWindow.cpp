#include "DetailedDataWindow.hpp"

DetailedDataWindow::DetailedDataWindow()
	: dt(0.f)
	, m_status(ExternalWindowStatus::CLOSED)
	, m_windowHolded(false)
	, m_locked(false)
	, m_running(true)
	, m_sizing_mode(WindowSizingMode::NONE)
	, m_window_size_clicked(false)
	, m_default_windowSize(1280, 720)
	, m_maximum_windowSize(1920, 1080)
	, m_minimum_windowSize(640, 360)
{

}

DetailedDataWindow::~DetailedDataWindow()
{

}



void DetailedDataWindow::Run(SpaceObject* selected_object)
{
	m_selected_object = selected_object;

	this->initGUI();
	this->Init(selected_object);
	this->loadData();

	while (window.isOpen())
	{
		if (m_locked)
			continue;

		this->UpdateMouse();
		this->UpdateEvents();
		this->Render();
		this->UpdateDeltaTime();
	}
}


static std::mutex s_endMutex;

void DetailedDataWindow::End()
{
	m_status = ExternalWindowStatus::CLOSED;
	m_running = false;
	window.close();
	std::lock_guard<std::mutex> lock(s_endMutex);
}
	



void DetailedDataWindow::Init(SpaceObject* selected_object)
{
	m_status = ExternalWindowStatus::OPENED;

	window.create(sf::VideoMode(m_default_windowSize.x, m_default_windowSize.y), "Detailed data: " + m_selected_object->name(), sf::Style::None);
	window.setFramerateLimit(AppSettings::MaxMenuFPS());
	window.setActive(false);

	sf::Image window_icon;
	window_icon.loadFromFile("res/CISS_winicon.png");
	window.setIcon(window_icon.getSize().x, window_icon.getSize().y, window_icon.getPixelsPtr());

	view.setSize(sf::Vector2f(window.getSize()));
	view.setCenter(view.getSize() / 2.f);
	
	topView.setSize(m_default_windowSize);
	topView.setCenter(topView.getSize() / 2.f);

	m_cursor_default.loadFromSystem(sf::Cursor::Arrow);
	m_cursor_size_horizontal.loadFromSystem(sf::Cursor::SizeHorizontal);
	m_cursor_size_vertical.loadFromSystem(sf::Cursor::SizeVertical);
	m_cursor_all_at_once.loadFromSystem(sf::Cursor::SizeTopLeftBottomRight);
}



static std::mutex s_loadMutex;


void DetailedDataWindow::UpdateDynamicData(ObjectBuffer buffer)
{
	s_loadMutex.lock();



	s_loadMutex.unlock();
}

void DetailedDataWindow::UpdateStaticData(ObjectBuffer buffer)
{
	s_loadMutex.lock();



	s_loadMutex.unlock();
}



void DetailedDataWindow::lock()
{
	m_locked = true;
}

void DetailedDataWindow::unlock()
{
	m_locked = false;
}

bool DetailedDataWindow::locked()
{
	return m_locked;
}




void DetailedDataWindow::initGUI()
{
	// reset everything

	m_signs.clear();
	m_values.clear();



	// init GUI

	const sf::Vector2f winsize = m_default_windowSize;

	m_titlebar.create({m_maximum_windowSize.x, winsize.y / 32}, { 0,0 }, ke::Origin::LEFT_TOP, nullptr, L"Detailed data", winsize.y / 48, ke::Origin::LEFT_MIDDLE, sf::Color(8, 8, 8, 255), sf::Color(192, 192, 192, 128));
	m_titlebar.setTextPosition(ke::Origin::LEFT_MIDDLE, { winsize.x / 256, 0 });

	m_exitButton.create(winsize / 32.f, { winsize.x, 0 }, ke::Origin::RIGHT_TOP, "Textures/StateTextures/WindowGUI/close.png");
	m_maximizeButton.create(winsize / 32.f, { winsize.x - winsize.x / 32, 0 }, ke::Origin::RIGHT_TOP, "Textures/StateTextures/WindowGUI/maximize.png");
	m_minimizeButton.create(winsize / 32.f, { winsize.x - winsize.x / 16, 0 }, ke::Origin::RIGHT_TOP, "Textures/StateTextures/WindowGUI/minimize.png");


	const float section = winsize.x / 32; // akapit


	m_icon.create({ winsize.x / 16.f, winsize.x / 16.f }, { section, winsize.y / 18 }, ke::Origin::LEFT_TOP, "Textures/IconTextures/SolarSystem/Sun_icon.png");
	//m_icon.setOutlineColor(sf::Color(128, 128, 128, 128));
	//m_icon.setOutlineThickness(winsize.x / 512);

	m_name.create({ winsize.x - winsize.x / 8, winsize.x / 16 }, { winsize.x - section, winsize.y / 18 }, ke::Origin::RIGHT_TOP, nullptr, L"", winsize.x / 32);
	m_name.setTextPosition(ke::Origin::LEFT_MIDDLE, sf::Vector2f(winsize.x / 32, 0));

	m_compartmentBar.create({ m_maximum_windowSize.x, winsize.y / 128 }, { 0, winsize.y / 5 }, ke::Origin::LEFT_MIDDLE, L"", 0, 0, sf::Color(64, 64, 64, 64));


	//m_mass_sign.create(sf::Vector2f(3 * winsize.x / 16, winsize.y / 18), sf::Vector2f(section, winsize.y / 4), ke::Origin::LEFT_MIDDLE, nullptr, L"MASS", winsize.y / 36, ke::Origin::LEFT_MIDDLE);
	//m_mass.create(sf::Vector2f(4.25 * winsize.x / 16 - 0.5 * section, winsize.y / 18), sf::Vector2f(section + winsize.x / 16, winsize.y / 4), ke::Origin::LEFT_MIDDLE, nullptr, L"213769420", winsize.y / 36, ke::Origin::LEFT_MIDDLE);


	std::array<std::wstring, 6> name_order{ L"mass", L"radius", L"average density", L"Surface gravity", L"first space speed", L"second space speed" };
	auto name_itr = name_order.begin();

	const int COLUMN_SIZE = m_minimum_windowSize.x;
	int columns = winsize.x / COLUMN_SIZE;
	sf::Vector2f position(section, winsize.y / 4);

	constexpr int OBJECT_COUNT = 6;
	m_signs.reserve(OBJECT_COUNT);
	m_values.reserve(OBJECT_COUNT);

	for (int i = 0; i < OBJECT_COUNT; i++)
	{
		if (i % columns == 0)
		{
			position.y += m_default_windowSize.y / 16;
			position.x = section;
		}
		else
		{
			position.x += COLUMN_SIZE;
		}

		m_signs.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(3 * winsize.x / 16, winsize.y / 18), position, ke::Origin::LEFT_MIDDLE, nullptr, *name_itr, winsize.y / 36, ke::Origin::LEFT_MIDDLE));
		m_signs.back()->setTextColor(sf::Color(223, 223, 255, 255));
		++name_itr;

		m_values.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(4.25 * winsize.x / 16, winsize.y / 18), sf::Vector2f(position.x + m_signs.front()->getSize().x, position.y), ke::Origin::LEFT_MIDDLE, nullptr, L"QUACK", winsize.y / 36, ke::Origin::LEFT_MIDDLE));
	}


	//window.setSize(sf::Vector2u(m_default_windowSize));
	//this->updateGUI();
}

void DetailedDataWindow::updateGUI()
{
	topView.setSize(sf::Vector2f(window.getSize()));
	topView.setCenter(sf::Vector2f(window.getSize() / 2u));

	view.setSize(sf::Vector2f(window.getSize()));
	view.setCenter(sf::Vector2f(window.getSize() / 2u));


	const sf::Vector2f winsize(window.getSize());

	// just update position

	m_exitButton.setPosition(winsize.x, 0);
	m_maximizeButton.setPosition(winsize.x - m_default_windowSize.x / 32, 0);
	m_minimizeButton.setPosition(winsize.x - m_default_windowSize.x / 16, 0);


	const float section = m_default_windowSize.x / 32; // akapit

	const int COLUMN_SIZE = m_default_windowSize.x / 2;

	int columns = winsize.x / COLUMN_SIZE;
	if (columns == 0) columns = 1; // safety guard

	sf::Vector2f position(section, m_default_windowSize.y / 4);

	constexpr int OBJECT_COUNT = 6;
	m_signs.reserve(OBJECT_COUNT);
	m_values.reserve(OBJECT_COUNT);

	for (int i = 0; i < OBJECT_COUNT; i++)
	{
		if (i % columns == 0)
		{
			position.y += m_default_windowSize.y / 16;
			position.x = section;
		}
		else
		{
			position.x += COLUMN_SIZE;
		}

		m_signs[i]->setPosition(position);
		m_values[i]->setPosition(position.x + m_signs.front()->getSize().x, position.y);
	}
}

void DetailedDataWindow::loadData()
{
	s_loadMutex.lock();
	m_icon.setTexture(m_selected_object->iconFilename());
	m_name.setText(ke::fixed::stow(m_selected_object->name()));

	//std::lock_guard<std::mutex> lock(s_loadMutex);
	s_loadMutex.unlock();
}




////////////////////////////////////////////////////////////////




void DetailedDataWindow::UpdateMouse()
{
	mPosScreen = sf::Vector2f(sf::Mouse::getPosition());
	mPosWindow = sf::Vector2f(sf::Mouse::getPosition(window));
	mPosView = window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

void DetailedDataWindow::UpdateEvents()
{
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			this->End();
			return;
		}

		if (m_exitButton.isClicked(sf::Mouse::Left, mPosWindow, event) || event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
		{
			this->End();
			return;
		}
		else if (m_maximizeButton.isClicked(sf::Mouse::Left, mPosWindow, event))
		{
			RECT desktop;
			const HWND hDesktop = GetDesktopWindow();
			GetWindowRect(hDesktop, &desktop);

			sf::Vector2u wSize(desktop.right, desktop.bottom);

			if (!m_fullscreen_on)
			{
				::ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);
				//window->create(sf::VideoMode(wSize.x, wSize.y), "Completely Inaccurate Space Simulator", sf::Style::None);
				window.create(sf::VideoMode(m_maximum_windowSize.x, m_maximum_windowSize.y), "Detailed data: " + m_selected_object->name(), sf::Style::Fullscreen);
				window.setFramerateLimit(AppSettings::MaxMenuFPS());

				m_fullscreen_on = true;
			}
			else
			{
				window.create(sf::VideoMode(m_default_windowSize.x, m_default_windowSize.y), "Detailed data: " + m_selected_object->name(), sf::Style::None);
				window.setFramerateLimit(AppSettings::MaxMenuFPS());

				m_fullscreen_on = false;
			}

			this->updateGUI();
		}
		else if (m_minimizeButton.isClicked(sf::Mouse::Left, mPosWindow, event))
		{
			::ShowWindow(window.getSystemHandle(), SW_MINIMIZE);
		}


		if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left && ke::inRange(mPosScreen.x - window.getPosition().x, 1u, window.getSize().x - 10u) && ke::inRange(mPosScreen.y - window.getPosition().y, 1u, window.getSize().y - 10u))
		{
			m_windowHolded = true;
			m_windowCatchDiff = mPosWindow;
		}


		if (!m_fullscreen_on)
		{
			if (std::fabs(mPosScreen.x - window.getPosition().x - window.getSize().x) < 10.f && std::fabs(mPosScreen.y - window.getPosition().y - window.getSize().y) < 10.f)
			{
				window.setMouseCursor(m_cursor_all_at_once);

				if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
				{
					m_window_size_clicked = true;
					m_sizing_mode = WindowSizingMode::ALLATONCE;
				}
			}
			else if (std::fabs(mPosScreen.x - window.getPosition().x - window.getSize().x) < 10.f)
			{
				window.setMouseCursor(m_cursor_size_horizontal);

				if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
				{
					m_window_size_clicked = true;
					m_sizing_mode = WindowSizingMode::HORIZONTALLY;
				}
			}
			else if (std::fabs(mPosScreen.y - window.getPosition().y - window.getSize().y) < 10.f)
			{
				window.setMouseCursor(m_cursor_size_vertical);

				if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
				{
					m_window_size_clicked = true;
					m_sizing_mode = WindowSizingMode::VERTICALLY;
				}
			}
			else
			{
				window.setMouseCursor(m_cursor_default);
			}
		}


		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_fullscreen_on)
		{
			if (m_window_size_clicked)
			{
				switch (m_sizing_mode)
				{
				case WindowSizingMode::NONE:
					// do nothing
					break;
				case WindowSizingMode::HORIZONTALLY:

					if (ke::inRange(std::abs(mPosScreen.x - window.getPosition().x), m_minimum_windowSize.x, m_maximum_windowSize.x))
					{
						window.setSize(sf::Vector2u(std::abs(mPosScreen.x - window.getPosition().x), window.getSize().y));
						this->updateGUI();
					}
					break;
				case WindowSizingMode::VERTICALLY:

					if (ke::inRange(std::abs(mPosScreen.y - window.getPosition().y), m_minimum_windowSize.y, m_maximum_windowSize.y))
					{
						window.setSize(sf::Vector2u(window.getSize().x, std::abs(mPosScreen.y - window.getPosition().y)));
						this->updateGUI();
					}
					break;
				case WindowSizingMode::ALLATONCE:

					if (ke::inRange(std::abs(mPosScreen.x - window.getPosition().x), m_minimum_windowSize.x, m_maximum_windowSize.x) &&
						ke::inRange(std::abs(mPosScreen.y - window.getPosition().y), m_minimum_windowSize.y, m_maximum_windowSize.y)) 
					{
						window.setSize(sf::Vector2u(std::abs(mPosScreen.x - window.getPosition().x), std::abs(mPosScreen.y - window.getPosition().y)));
						this->updateGUI();
					}
					break;
				default:
					break;
				}
			}
		}
		else
		{
			m_window_size_clicked = false;
			m_sizing_mode = WindowSizingMode::NONE;
		}
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		m_windowHolded = false;

	if (m_windowHolded)
		window.setPosition(sf::Vector2i(mPosScreen - m_windowCatchDiff));
}



////////////////////////////////////////////////////////////////



void DetailedDataWindow::Render()
{
	window.setActive(false);

	window.clear(sf::Color::Black);


	// background
	window.setView(window.getDefaultView());



	// view-depend objects
	window.setView(view);

	for (auto& itr : m_signs)
		itr->render(&window);

	for (auto& itr : m_values)
		itr->render(&window);


	// top layer
	window.setView(topView);

	m_titlebar.render(&window);
	m_exitButton.render(&window);
	m_maximizeButton.render(&window);
	m_minimizeButton.render(&window);

	m_compartmentBar.render(&window);


	m_icon.render(&window);
	m_name.render(&window);

	window.setView(view); // DON'T REMOVE IT

	window.display();
}



////////////////////////////////////////////////////////////////



void DetailedDataWindow::UpdateDeltaTime()
{
	dt = _dtClock.restart().asSeconds();
}



////////////////////////////////////////////////////////////////



void DetailedDataWindow::Close()
{
	window.setActive(true);
	window.close();

	using namespace std::chrono_literals;

	//std::this_thread::sleep_for(1ms);
	m_status = ExternalWindowStatus::CLOSED;
}

ExternalWindowStatus DetailedDataWindow::status() const
{
	return m_status;
}
