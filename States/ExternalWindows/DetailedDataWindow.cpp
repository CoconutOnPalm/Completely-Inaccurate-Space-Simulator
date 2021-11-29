#include "DetailedDataWindow.hpp"

DetailedDataWindow::DetailedDataWindow()
	: dt(0.f)
	, m_status(ExternalWindowStatus::CLOSED)
	, m_windowHolded(false)
{
	this->initGUI();
}

DetailedDataWindow::~DetailedDataWindow()
{

}

void DetailedDataWindow::Init(SpaceObject* selected_object)
{
	m_status = ExternalWindowStatus::OPENED;

	window.create(sf::VideoMode(1280, 720), "Detailed data: " + selected_object->name(), sf::Style::None);
	window.setFramerateLimit(AppSettings::MaxMenuFPS());
	window.setActive(false);

	sf::Image window_icon;
	window_icon.loadFromFile("res/CISS_winicon.png");
	window.setIcon(window_icon.getSize().x, window_icon.getSize().y, window_icon.getPixelsPtr());

	view.setSize(sf::Vector2f(window.getSize()));
	view.setCenter(view.getSize() / 2.f);
}

void DetailedDataWindow::Load(SpaceObject* selected_object)
{
	if (m_status == ExternalWindowStatus::CLOSED)
		this->Init(selected_object);
	else
		window.setTitle("Detailed data: " + selected_object->name());

	m_titlebar.setText(ke::fixed::stow("Detailed data: " + selected_object->name()));
	
	m_selected_object = selected_object;

	this->loadData();
}




void DetailedDataWindow::initGUI()
{
	sf::Vector2f winsize(1280, 720);

	m_titlebar.create({winsize.x, winsize.y / 32}, { 0,0 }, ke::Origin::LEFT_TOP, nullptr, L"Detailed data", winsize.y / 48, ke::Origin::LEFT_MIDDLE, sf::Color(8, 8, 8, 255), sf::Color(192, 192, 192, 128));
	m_titlebar.setTextPosition(ke::Origin::LEFT_MIDDLE, { winsize.x / 256, 0 });

	m_exitButton.create(winsize / 32.f, { winsize.x, 0 }, ke::Origin::RIGHT_TOP, "Textures/StateTextures/WindowGUI/close.png");


	const float section = winsize.x / 32; // akapit


	m_icon.create({ winsize.x / 16.f, winsize.x / 16.f }, { section, winsize.y / 18 }, ke::Origin::LEFT_TOP, "Textures/IconTextures/SolarSystem/Sun_icon.png");
	//m_icon.setOutlineColor(sf::Color(128, 128, 128, 128));
	//m_icon.setOutlineThickness(winsize.x / 512);

	m_name.create({ winsize.x - winsize.x / 8, winsize.x / 16 }, { winsize.x - section, winsize.y / 18 }, ke::Origin::RIGHT_TOP, nullptr, L"", winsize.x / 32);
	m_name.setTextPosition(ke::Origin::LEFT_MIDDLE, sf::Vector2f(winsize.x / 32, 0));
}


void DetailedDataWindow::loadData()
{
	m_icon.setTexture(m_selected_object->iconFilename());
	m_name.setText(ke::fixed::stow(m_selected_object->name()));
}




////////////////////////////////////////////////////////////////



void DetailedDataWindow::Update()
{
	if (m_status == ExternalWindowStatus::CLOSED)
		return;

	//window.setActive(false);

	//std::thread renderThread(&DetailedDataWindow::Render, this);

	this->UpdateMouse();
	this->UpdateEvents();
	this->Render();
	this->UpdateDeltaTime();

	//renderThread.join();
}

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
			this->End();

		if (m_exitButton.isClicked(sf::Mouse::Left, mPosWindow, event))
			this->End();

		if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
		{
			m_windowHolded = true;
			m_windowCatchDiff = mPosWindow;
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
	window.clear(sf::Color::Black);


	// background
	window.setView(window.getDefaultView());



	// view-depend objects
	window.setView(view);

	m_icon.render(&window);
	m_name.render(&window);

	// top layer
	window.setView(window.getDefaultView());

	m_titlebar.render(&window);
	m_exitButton.render(&window);


	window.setView(view); // DON'T REMOVE IT

	window.display();
}



////////////////////////////////////////////////////////////////



void DetailedDataWindow::UpdateDeltaTime()
{
	dt = _dtClock.restart().asSeconds();
}



////////////////////////////////////////////////////////////////



void DetailedDataWindow::End()
{
	window.close();
	m_status = ExternalWindowStatus::CLOSED;
}

ExternalWindowStatus DetailedDataWindow::status() const
{
	return m_status;
}
