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
	this->End();
}


static long double s_space_scale = 0.000001;


void DetailedDataWindow::Run(SpaceObject* selected_object, ObjectBuffer buffer, long double space_scale)
{
	s_space_scale = space_scale;

	m_windowHolded = false;
	m_locked = false;
	m_running = true;
	m_sizing_mode = WindowSizingMode::NONE;
	m_window_size_clicked = false;

	m_selected_object = selected_object;

	this->initGUI();
	this->Init(selected_object);
	this->loadData(selected_object);
	this->UpdateStaticData(buffer);
	//this->UpdateDynamicData(buffer);

	while (window.isOpen() && m_running)
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
	this->lock();
	window.close();
	m_status = ExternalWindowStatus::CLOSED;
	m_running = false;
	std::lock_guard<std::mutex> lock(s_endMutex);
}


static std::mutex s_ptrMutex;
void DetailedDataWindow::updateObjectPointer(SpaceObject* selected_object)
{
	s_ptrMutex.lock();
	//this->lock();
	m_selected_object = selected_object;
	//this->unlock();
	s_ptrMutex.unlock();
}




void DetailedDataWindow::Init(SpaceObject* selected_object)
{
	m_status = ExternalWindowStatus::OPENED;

	m_selected_object = selected_object;

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



static std::mutex s_staticLoadMutex, s_dynamicLockMutex;


void DetailedDataWindow::UpdateDynamicData(std::vector<ForceData> data)
{
	s_dynamicLockMutex.lock();
	m_force_data = data;
	s_dynamicLockMutex.unlock();
}

void DetailedDataWindow::UpdateStaticData(ObjectBuffer buffer)
{
	s_staticLoadMutex.lock();

	std::wstringstream datastream;

	datastream << std::setprecision(10) << std::scientific << buffer.mass();
	m_values[0]->setText(datastream.str());


	datastream.str(std::wstring());
	datastream << std::setprecision(10) << std::scientific << buffer.radius();
	m_values[1]->setText(datastream.str());


	long double density = buffer.mass() / Volume(buffer.radius());
	if (isnan(density))
		density = 0;

	datastream.str(std::wstring());
	datastream << std::setprecision(10) << std::scientific << density;
	m_values[2]->setText(datastream.str());


	long double surface_g = surface_gravity(buffer.mass(), buffer.radius());
	if (isnan(surface_g))
		surface_g = 0;

	datastream.str(std::wstring());
	datastream << std::setprecision(10) << std::scientific << surface_g;
	m_values[3]->setText(datastream.str());


	long double fss = first_space_speed(buffer.mass(), buffer.radius());
	if (isnan(fss))
		fss = 0;

	datastream.str(std::wstring());
	datastream << std::setprecision(10) << std::scientific << fss;
	m_values[4]->setText(datastream.str());


	long double sss = second_space_speed(buffer.mass(), buffer.radius());
	if (isnan(sss))
		sss = 0;

	datastream.str(std::wstring());
	datastream << std::setprecision(10) << std::scientific << sss;
	m_values[5]->setText(datastream.str());


	s_staticLoadMutex.unlock();
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

	m_titlebar.create({ m_maximum_windowSize.x, winsize.y / 32 }, { 0,0 }, ke::Origin::LEFT_TOP, nullptr, L"Detailed data", winsize.y / 48, ke::Origin::LEFT_MIDDLE, sf::Color(8, 8, 8, 255), sf::Color(192, 192, 192, 128));
	m_titlebar.setTextPosition(ke::Origin::LEFT_MIDDLE, { winsize.x / 256, 0 });

	m_exitButton.create(winsize / 32.f, { winsize.x, 0 }, ke::Origin::RIGHT_TOP, "Textures/StateTextures/WindowGUI/close.png");
	m_maximizeButton.create(winsize / 32.f, { winsize.x - winsize.x / 32, 0 }, ke::Origin::RIGHT_TOP, "Textures/StateTextures/WindowGUI/maximize.png");
	m_minimizeButton.create(winsize / 32.f, { winsize.x - winsize.x / 16, 0 }, ke::Origin::RIGHT_TOP, "Textures/StateTextures/WindowGUI/minimize.png");



	//m_slider.create(sf::Vector2f(winsize.x / 100, 4 * winsize.y / 5), winsize, winsize.y, ke::Origin::RIGHT_BOTTOM, nullptr, nullptr, sf::Color(16, 16, 16, 64), sf::Color(32, 32, 32, 64));



	const float section = winsize.x / 32; // akapit


	m_icon_background.create({ m_maximum_windowSize.x, winsize.y / 5 }, { 0, 0 }, ke::Origin::LEFT_TOP, L"", 0, {}, sf::Color::Black);

	m_icon.create({ winsize.x / 16.f, winsize.x / 16.f }, { section, winsize.y / 18 }, ke::Origin::LEFT_TOP, "Textures/IconTextures/SolarSystem/Sun_icon.png");
	//m_icon.setOutlineColor(sf::Color(128, 128, 128, 128));
	//m_icon.setOutlineThickness(winsize.x / 512);

	m_name.create({ winsize.x - winsize.x / 8, winsize.x / 16 }, { winsize.x - section, winsize.y / 18 }, ke::Origin::RIGHT_TOP, nullptr, L"", winsize.x / 32);
	m_name.setTextPosition(ke::Origin::LEFT_MIDDLE, sf::Vector2f(winsize.x / 32, 0));

	m_compartmentBar.create({ m_maximum_windowSize.x, winsize.y / 128 }, { 0, winsize.y / 5 }, ke::Origin::LEFT_MIDDLE, L"", 0, 0, sf::Color(64, 64, 64, 64));


	//m_mass_sign.create(sf::Vector2f(3 * winsize.x / 16, winsize.y / 18), sf::Vector2f(section, winsize.y / 4), ke::Origin::LEFT_MIDDLE, nullptr, L"MASS", winsize.y / 36, ke::Origin::LEFT_MIDDLE);
	//m_mass.create(sf::Vector2f(4.25 * winsize.x / 16 - 0.5 * section, winsize.y / 18), sf::Vector2f(section + winsize.x / 16, winsize.y / 4), ke::Origin::LEFT_MIDDLE, nullptr, L"213769420", winsize.y / 36, ke::Origin::LEFT_MIDDLE);


	std::array<std::wstring, 6> name_order{ L"mass", L"radius", L"average density", L"Surface gravity", L"first space speed", L"second space speed" };
	std::array<std::string, 6> unit_filenames{
		"Textures/StateTextures/Simulation/DetailedDataWindow/kg.png",
		"Textures/StateTextures/Simulation/DetailedDataWindow/m.png",
		"Textures/StateTextures/Simulation/DetailedDataWindow/kgm3.png",
		"Textures/StateTextures/Simulation/DetailedDataWindow/ms2.png",
		"Textures/StateTextures/Simulation/DetailedDataWindow/ms.png",
		"Textures/StateTextures/Simulation/DetailedDataWindow/ms.png" };

	auto name_itr = name_order.begin();
	auto unit_itr = unit_filenames.begin();

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

		m_values.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(4.25 * winsize.x / 16 - winsize.y / 18, winsize.y / 18), sf::Vector2f(position.x + m_signs.front()->getSize().x, position.y), ke::Origin::LEFT_MIDDLE, nullptr, L"QUACK", winsize.y / 36, ke::Origin::LEFT_MIDDLE));
		m_units.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winsize.y / 18, winsize.y / 18), sf::Vector2f(position.x + m_signs.front()->getSize().x + m_values.front()->getSize().x, position.y), ke::Origin::LEFT_MIDDLE, *unit_itr, L"", winsize.y / 36, ke::Origin::LEFT_MIDDLE));
		++unit_itr;

		m_signs.back()->setFillColor(sf::Color(32, 32, 32, 32));
		m_values.back()->setFillColor(sf::Color(32, 32, 32, 32));
		m_units.back()->setFillColor(sf::Color(32, 32, 32, 32));
	}


	//window.setSize(sf::Vector2u(m_default_windowSize));
	//this->updateGUI();

	//m_view_holder.setView(&view);
	//m_view_holder.setBorders(ke::Vector4f(0.f, 0.f, winsize.x, winsize.y));
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

	sf::Vector2f data_position(section, m_default_windowSize.y / 4);

	constexpr int OBJECT_COUNT = 6;
	m_signs.reserve(OBJECT_COUNT);
	m_values.reserve(OBJECT_COUNT);

	for (int i = 0; i < OBJECT_COUNT; i++)
	{
		if (i % columns == 0)
		{
			data_position.y += m_default_windowSize.y / 16;
			data_position.x = section;
		}
		else
		{
			data_position.x += COLUMN_SIZE;
		}

		m_signs[i]->setPosition(data_position);
		m_values[i]->setPosition(data_position.x + m_signs.front()->getSize().x, data_position.y);
		m_units[i]->setPosition(data_position.x + m_signs.front()->getSize().x + m_values.front()->getSize().x, data_position.y);
	}


	if (m_force_data_blocks.size() > 0)
	{
		sf::Vector2f force_data_position(section, m_values.back()->getPosition().y + winsize.y / 16);

		for (int i = 0; i < m_force_data.size(); i++)
		{
			m_force_data_blocks[i]->updatePosition(force_data_position, winsize);

			if (winsize.x < m_default_windowSize.x - 0.01) // -0.01 for safety
				force_data_position.y += winsize.x / 4;
			else
				force_data_position.y += winsize.x / 8;
		}
	}


	//m_slider.setSize(winsize.x / 100, 4 * winsize.y / 5);
	//m_slider.setPosition(winsize);
	//m_slider.setFieldHeight(m_force_data_blocks.back()->getPosition().y + winsize.y / 16);

	//m_view_holder.setBorders(ke::Vector4f(0.f, 0.f, winsize.x, m_force_data_blocks.back()->getPosition().y + winsize.y / 16));
}

void DetailedDataWindow::loadData(SpaceObject* selected_object)
{
	if (selected_object == nullptr)
	{
		s_staticLoadMutex.lock();
		m_icon.setTexture(ke::Settings::EmptyTexturePath());
		m_name.setText(std::wstring());
		s_staticLoadMutex.unlock();
		return;
	}

	m_selected_object = selected_object;

	s_staticLoadMutex.lock();
	this->lock();
	m_icon.setTexture(selected_object->iconFilename());
	m_name.setText(ke::fixed::stow(selected_object->name()));

	this->unlock();
	s_staticLoadMutex.unlock();
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



		if (event.type == sf::Event::MouseWheelScrolled)
			if (event.mouseWheelScroll.delta < 0)
				view.move(0, window.getSize().y * 0.1f);
			else if (event.mouseWheelScroll.delta > 0)
				view.move(0, window.getSize().y * -0.1f);


		//m_slider.update(mPosWindow, event, sf::Mouse::Left, &view);
		//m_slider.updateSliderPosition(&view);
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		m_windowHolded = false;

	if (m_windowHolded)
		window.setPosition(sf::Vector2i(mPosScreen - m_windowCatchDiff));


	if ((m_force_data_blocks.size() > 1 && window.getSize().x < m_default_windowSize.x) || (m_force_data_blocks.size() > 4 && window.getSize().x >= m_default_windowSize.x))
	{
		//if (m_force_data_blocks.size() > 1)
		if (view.getCenter().y - view.getSize().y / 2 < -1)
		{
			view.setCenter(sf::Vector2f(window.getSize() / 2u));
		}
		else if (view.getCenter().y + view.getSize().y / 2 >= m_force_data_blocks.back()->getPosition().y + window.getSize().y / 8)
		{
			view.setCenter(sf::Vector2f(window.getSize().x / 2, m_force_data_blocks.back()->getPosition().y + window.getSize().y / 8 - view.getSize().y / 2));
		}
	}
	else
	{
		view.setCenter(sf::Vector2f(window.getSize() / 2u));
	}

	if (m_selected_object == nullptr)
	{
		std::cout << "nullptr\n";
		return;
	}

	sf::Vector2f force_data_position(m_default_windowSize.x / 32, m_values.back()->getPosition().y + window.getSize().y / 16);

	for (int i = 0; i < m_force_data_blocks.size(); i++)
	{
		m_force_data_blocks[i]->updatePosition(force_data_position, sf::Vector2f(window.getSize()));

		if (window.getSize().x < m_default_windowSize.x - 0.01) // -0.01 for safety
			force_data_position.y += window.getSize().y / 4;
		else
			force_data_position.y += window.getSize().y / 8;
	}



	if (m_force_data.size() > 0)
	{
		if (m_force_data_blocks.size() > m_force_data.size())
			m_force_data_blocks.clear();


		if (m_force_data_blocks.size() < m_force_data.size())
		{
			m_force_data_blocks.clear();

			for (int i = 0; i < m_force_data.size(); i++)
				m_force_data_blocks.push_back(std::make_unique<DistanceBlock>(sf::Vector2f(), m_default_windowSize));
		}

		for (int i = 0; i < m_force_data_blocks.size(); i++)
		{
			m_force_data_blocks[i]->update(m_selected_object, m_force_data[i]);
		}
	}


	// color update

	auto color_itr = m_colors.begin();

	ke::SmoothColorChange(&m_exitButton, m_exitButton.isInvaded(mPosWindow), sf::Color(255, 255, 255, 32), sf::Color(255, 255, 255, 0), *color_itr, 256, dt); ++color_itr;
	ke::SmoothColorChange(&m_minimizeButton, m_minimizeButton.isInvaded(mPosWindow), sf::Color(255, 255, 255, 32), sf::Color(255, 255, 255, 0), *color_itr, 256, dt); ++color_itr;
	ke::SmoothColorChange(&m_maximizeButton, m_maximizeButton.isInvaded(mPosWindow), sf::Color(255, 255, 255, 32), sf::Color(255, 255, 255, 0), *color_itr, 256, dt); ++color_itr;


	for (int i = 0; i < m_signs.size(); i++)
	{
		if (m_signs[i]->isInvaded(mPosView) || m_values[i]->isInvaded(mPosView) || m_units[i]->isInvaded(mPosView))
		{
			ke::SmoothColorChange(m_signs[i].get(), true, sf::Color(64, 64, 64, 64), sf::Color(32, 32, 32, 32), *color_itr, 256, dt); ++color_itr;
			ke::SmoothColorChange(m_values[i].get(), true, sf::Color(64, 64, 64, 64), sf::Color(32, 32, 32, 32), *color_itr, 256, dt); ++color_itr;
			ke::SmoothColorChange(m_units[i].get(), true, sf::Color(64, 64, 64, 64), sf::Color(32, 32, 32, 32), *color_itr, 256, dt); ++color_itr;
		}
		else
		{
			ke::SmoothColorChange(m_signs[i].get(), false, sf::Color(64, 64, 64, 64), sf::Color(32, 32, 32, 32), *color_itr, 256, dt); ++color_itr;
			ke::SmoothColorChange(m_values[i].get(), false, sf::Color(64, 64, 64, 64), sf::Color(32, 32, 32, 32), *color_itr, 256, dt); ++color_itr;
			ke::SmoothColorChange(m_units[i].get(), false, sf::Color(64, 64, 64, 64), sf::Color(32, 32, 32, 32), *color_itr, 256, dt); ++color_itr;
		}
	}


	//for (auto& itr : m_signs)
	//{
	//	ke::SmoothColorChange(itr.get(), itr->isInvaded(mPosView), sf::Color(32, 32, 32, 64), sf::Color(32, 32, 32, 32), *color_itr, 255, dt);
	//	++color_itr;
	//}

	//for (auto& itr : m_values)
	//{
	//	ke::SmoothColorChange(itr.get(), itr->isInvaded(mPosView), sf::Color(32, 32, 32, 64), sf::Color(32, 32, 32, 32), *color_itr, 255, dt);
	//	++color_itr;
	//}

	//for (auto& itr : m_units)
	//{
	//	ke::SmoothColorChange(itr.get(), itr->isInvaded(mPosView), sf::Color(32, 32, 32, 64), sf::Color(32, 32, 32, 32), *color_itr, 255, dt);
	//	++color_itr;
	//}
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


	for (auto& itr : m_force_data_blocks)
		itr->render(&window);


	for (auto& itr : m_signs)
		itr->render(&window);

	for (auto& itr : m_values)
		itr->render(&window);

	for (auto& itr : m_units)
		itr->render(&window);


	// top layer
	window.setView(topView);

	m_icon_background.render(&window);

	m_titlebar.render(&window);
	m_exitButton.render(&window);
	m_maximizeButton.render(&window);
	m_minimizeButton.render(&window);

	m_compartmentBar.render(&window);

	m_icon.render(&window);
	m_name.render(&window);

	//m_slider.render(&window);

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







////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////







DistanceBlock::DistanceBlock(const sf::Vector2f& position, const sf::Vector2f& winsize)
	: m_active(true)
{
	m_objectName.create({ 1920.f, winsize.y / 16 }, position, ke::Origin::LEFT_TOP, nullptr, L" -> ", winsize.y / 27, ke::Origin::LEFT_MIDDLE, sf::Color(64, 64, 64, 32));

	sf::Vector2f block_position(position.x, position.y + winsize.y / 16);

	m_distance_sign.create({ 2.f * winsize.x / 16, winsize.y / 18.f }, block_position, ke::Origin::LEFT_TOP, nullptr, L"distance", winsize.y / 36, ke::Origin::LEFT_MIDDLE, sf::Color(32, 32, 32, 32));
	m_distance.create({ 5.25f * winsize.x / 16, winsize.y / 18.f }, { block_position.x + m_distance_sign.getSize().x, block_position.y }, ke::Origin::LEFT_TOP, nullptr, L"QUACK", winsize.y / 36, ke::Origin::LEFT_MIDDLE, sf::Color(32, 32, 32, 32));


	if (winsize.x >= 1280)
		block_position.x += winsize.x / 2;
	else
		block_position.y += winsize.y / 18;


	m_force_sign.create({ 2 * winsize.x / 16, winsize.y / 18 }, block_position, ke::Origin::LEFT_TOP, nullptr, L"force", winsize.y / 36, ke::Origin::LEFT_MIDDLE, sf::Color(32, 32, 32, 32));
	m_force.create({ 5.25f * winsize.x / 16, winsize.y / 18 }, { block_position.x + m_force_sign.getSize().x, block_position.y }, ke::Origin::LEFT_TOP, nullptr, L"QUACK", winsize.y / 36, ke::Origin::LEFT_MIDDLE, sf::Color(32, 32, 32, 32));
}

DistanceBlock::~DistanceBlock()
{

}

void DistanceBlock::updatePosition(const sf::Vector2f& position, const sf::Vector2f& winsize)
{
	m_objectName.setPosition(position);

	sf::Vector2f block_position(position.x, position.y + winsize.y / 16);


	m_distance_sign.setPosition(block_position);
	m_distance.setPosition(block_position.x + m_distance_sign.getSize().x, block_position.y);

	if (winsize.x >= 1280 - 0.01) // -0.01 for safety
		block_position.x += m_distance_sign.getSize().x + m_distance.getSize().x;
	else
		block_position.y += winsize.y / 18;

	m_force_sign.setPosition(block_position);
	m_force.setPosition(block_position.x + m_force_sign.getSize().x, block_position.y);
}

sf::Vector2f DistanceBlock::getPosition() const
{
	return m_objectName.getPosition();
}

void DistanceBlock::update(const SpaceObject* selected_object, const ForceData& refered_object)
{
	if (!m_active)
		return;

	m_objectName.setText(ke::fixed::stow(refered_object.name));


	long double distance = position_to_distance(selected_object->object.getPosition(), refered_object.position) / s_space_scale;

	//std::cout << "distance: " << distance << '\n';

	if (isnan(distance))
		distance = 0;

	std::wstringstream dist_buffer;

	if (distance > ly)
		dist_buffer << std::fixed << std::setprecision(3) << distance / ly << " ly";
	else if (distance > au)
		dist_buffer << std::fixed << std::setprecision(2) << distance / au << " au";
	else if (distance > 1000)
		dist_buffer << std::fixed << std::setprecision(2) << distance / 1000 << " km";
	else
		dist_buffer << std::fixed << std::setprecision(2) << distance << " m";

	m_distance.setText(dist_buffer.str());


	std::wstringstream datastream;

	datastream << std::setprecision(5) << std::scientific << gravitational_force(selected_object->data.mass, refered_object.mass, distance) << L" N";

	m_force.setText(datastream.str());
}

void DistanceBlock::setActive(bool active)
{
	m_active = active;
}

bool DistanceBlock::active() const
{
	return m_active;
}

void DistanceBlock::render(sf::RenderWindow* window)
{
	if (!m_active)
		return;

	m_objectName.render(window);
	m_distance_sign.render(window);
	m_distance.render(window);
	m_force_sign.render(window);
	m_force.render(window);
}
