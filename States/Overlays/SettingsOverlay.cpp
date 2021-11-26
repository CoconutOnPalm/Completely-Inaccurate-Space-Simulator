#include "SettingsOverlay.hpp"

SettingsOverlay::SettingsOverlay()
	: m_quitCode(OverlayQuitCode::NOT_QUITTING)
	, m_active(false)
{

}

SettingsOverlay::~SettingsOverlay()
{

}

void SettingsOverlay::assign(sf::RenderWindow* window, ke::Button* background)
{
	m_window = window;
	simulation_background = background;

	background->setTexture(this->index_to_background_texture());
	if (AppSettings::SimulationBackgroundImage() == 0)
		background->setFillColor(sf::Color::Black);
	if (AppSettings::SimulationBackgroundImage() == 1)
		background->setFillColor(sf::Color(0, 0, 4));
	else
		background->setFillColor(sf::Color(0, 0, 0, 255.f - 255.f * AppSettings::BackgroundBrightness() * 0.01f));
}

void SettingsOverlay::initUI()
{
	sf::Vector2f winsize(m_window->getSize());
	float xShift = winsize.x / 32;
	float yShift(winsize.y / 2 - winsize.y * 0.4);


	m_background.create(sf::Vector2f(winsize.x / 2, winsize.y * 0.8), winsize / 2.f, ke::Origin::MIDDLE_MIDDLE, std::wstring(), 0, 0, sf::Color(8, 8, 8, 255));

	m_music_volume.create(sf::Vector2f(winsize.x / 6, winsize.y / 21), winsize.y / 40, sf::Vector2f(winsize.x / 2 + xShift, yShift + 1 * winsize.y / 10), ke::Origin::LEFT_MIDDLE, "Textures/StateTextures/Simulation/SettingsOverlay/Mars_icon.png",
		ke::Settings::EmptyTexturePath(), sf::Color::Transparent, sf::Color(32, 32, 32, 255));
	m_music_volume.setPercent(AppSettings::MusicVolume());

	m_sfx_volume.create(sf::Vector2f(winsize.x / 6, winsize.y / 21), winsize.y / 40, sf::Vector2f(winsize.x / 2 + xShift, yShift + 2 * winsize.y / 10), ke::Origin::LEFT_MIDDLE, "Textures/StateTextures/Simulation/SettingsOverlay/Moon_icon.png",
		ke::Settings::EmptyTexturePath(), sf::Color::Transparent, sf::Color(32, 32, 32, 255));
	m_sfx_volume.setPercent(AppSettings::MusicVolume());


	m_vsync.create(sf::Vector2f(winsize.x / 18, winsize.y / 21), winsize.y / 40, sf::Vector2f(m_music_volume.getShapeCenter().x, yShift + 3 * winsize.y / 10), ke::Origin::MIDDLE_MIDDLE, "Textures/StateTextures/Simulation/SettingsOverlay/Neptune_icon.png", ke::Settings::EmptyTexturePath(), sf::Color::Transparent, sf::Color(32, 32, 32, 255));
	
	m_simulationFPS.create(sf::Vector2f(winsize.x / 6, winsize.y / 21), sf::Vector2f(winsize.x / 2 + xShift, yShift + 4 * winsize.y / 10), nullptr, AppSettings::MaxSimulationFPS(), 120.0, 960.0, ke::Origin::LEFT_MIDDLE, sf::Color(32, 32, 32, 255), sf::Color(64, 64, 64, 255));

	m_FPS_text.create(sf::Vector2f(winsize.x / 6, winsize.y / 21), sf::Vector2f(winsize.x / 2 + xShift, yShift + 4 * winsize.y / 10), ke::Origin::LEFT_MIDDLE, std::to_wstring(AppSettings::MaxSimulationFPS()), m_simulationFPS.getSize().y / 2,
		ke::Origin::LEFT_MIDDLE, sf::Color::Transparent, sf::Color::White, 0, sf::Color::Transparent, 0, 0, sf::Vector2f(m_simulationFPS.getSize().x / 256, 0));
	

	m_background_brightness.create(sf::Vector2f(winsize.x / 6, winsize.y / 21), winsize.y / 40, sf::Vector2f(winsize.x / 2 + xShift, yShift + 7 * winsize.y / 10), ke::Origin::LEFT_MIDDLE, "Textures/StateTextures/Simulation/SettingsOverlay/Jupiter_icon.png",
		ke::Settings::EmptyTexturePath(), sf::Color::Transparent, sf::Color(32, 32, 32, 255));
	m_background_brightness.setPercent(AppSettings::BackgroundBrightness());


	const float box_size = winsize.x / 30;
	sf::Vector2f box_position(winsize.x / 2 + xShift, yShift + 5 * winsize.y / 10);


	m_background_images.reserve(10);
	m_background_images.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(box_size, box_size), box_position, ke::Origin::LEFT_TOP, ke::Settings::EmptyTexturePath(),												std::wstring(), 0, ke::Origin::MIDDLE_MIDDLE, sf::Color::Black));			box_position.x += box_size;												// black
	m_background_images.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(box_size, box_size), box_position, ke::Origin::LEFT_TOP, ke::Settings::EmptyTexturePath(),												std::wstring(), 0, ke::Origin::MIDDLE_MIDDLE, sf::Color(0, 0, 51, 223)));	box_position.x += box_size;												// dark blue
	m_background_images.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(box_size, box_size), box_position, ke::Origin::LEFT_TOP, "Textures/StateTextures/Simulation/BackgroundIcons/CISS_background_icon.png",	std::wstring(), 0, ke::Origin::MIDDLE_MIDDLE, sf::Color(0, 0, 0, 32)));		box_position.x += box_size;												// CISS background
	m_background_images.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(box_size, box_size), box_position, ke::Origin::LEFT_TOP, "Textures/StateTextures/Simulation/BackgroundIcons/NGC-2442_icon.png",			std::wstring(), 0, ke::Origin::MIDDLE_MIDDLE, sf::Color(0, 0, 0, 32)));		box_position.x += box_size;												// MainMenu
	m_background_images.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(box_size, box_size), box_position, ke::Origin::LEFT_TOP, "Textures/StateTextures/Simulation/BackgroundIcons/NGC-2525_icon.png",			std::wstring(), 0, ke::Origin::MIDDLE_MIDDLE, sf::Color(0, 0, 0, 32)));		box_position.x = winsize.x / 2 + xShift; box_position.y += box_size;	// black
	m_background_images.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(box_size, box_size), box_position, ke::Origin::LEFT_TOP, "Textures/StateTextures/Simulation/BackgroundIcons/Orion_Nebula_icon.png",		std::wstring(), 0, ke::Origin::MIDDLE_MIDDLE, sf::Color(0, 0, 0, 32)));		box_position.x += box_size;												// black
	m_background_images.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(box_size, box_size), box_position, ke::Origin::LEFT_TOP, "Textures/StateTextures/Simulation/BackgroundIcons/Westerlund_2_icon.png",		std::wstring(), 0, ke::Origin::MIDDLE_MIDDLE, sf::Color(0, 0, 0, 32)));		box_position.x += box_size;												// black
	m_background_images.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(box_size, box_size), box_position, ke::Origin::LEFT_TOP, "Textures/StateTextures/Simulation/BackgroundIcons/Whirlpool_Galaxy_icon.png",	std::wstring(), 0, ke::Origin::MIDDLE_MIDDLE, sf::Color(0, 0, 0, 32)));		box_position.x += box_size;												// black
	m_background_images.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(box_size, box_size), box_position, ke::Origin::LEFT_TOP, "Textures/StateTextures/Simulation/BackgroundIcons/NGC-1300_icon.png",			std::wstring(), 0, ke::Origin::MIDDLE_MIDDLE, sf::Color(0, 0, 0, 32)));		box_position.x += box_size;												// black
	m_background_images.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(box_size, box_size), box_position, ke::Origin::LEFT_TOP, "Textures/StateTextures/Simulation/BackgroundIcons/Lagoon_Nebula_icon.png",		std::wstring(), 0, ke::Origin::MIDDLE_MIDDLE, sf::Color(0, 0, 0, 32)));		box_position.x += box_size;												// black


	for (auto& itr : m_background_images)
	{
		itr->setPosition(itr->getShapeCenter());
		itr->setOrigin(ke::Origin::MIDDLE_MIDDLE);
		itr->setSize(itr->getSize() * 0.8f);
	}


	m_selected_image = m_background_images.begin() + AppSettings::SimulationBackgroundImage();

	(*m_selected_image)->setOutlineColor(sf::Color::Cyan);
	(*m_selected_image)->setOutlineThickness(winsize.x / 512);


	m_descriptions[0].create(sf::Vector2f(winsize.x / 6, winsize.y / 21), sf::Vector2f(winsize.x / 2 - xShift, yShift + 1 * winsize.y / 10), ke::Origin::RIGHT_MIDDLE, L"music volume", winsize.x / 64, ke::Origin::RIGHT_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 192));
	m_descriptions[1].create(sf::Vector2f(winsize.x / 6, winsize.y / 21), sf::Vector2f(winsize.x / 2 - xShift, yShift + 2 * winsize.y / 10), ke::Origin::RIGHT_MIDDLE, L"SFX volume", winsize.x / 64, ke::Origin::RIGHT_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 192));
	m_descriptions[2].create(sf::Vector2f(winsize.x / 6, winsize.y / 21), sf::Vector2f(winsize.x / 2 - xShift, yShift + 3 * winsize.y / 10), ke::Origin::RIGHT_MIDDLE, L"background image", winsize.x / 64, ke::Origin::RIGHT_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 192));
	m_descriptions[3].create(sf::Vector2f(winsize.x / 6, winsize.y / 21), sf::Vector2f(winsize.x / 2 - xShift, yShift + 4 * winsize.y / 10), ke::Origin::RIGHT_MIDDLE, L"vertical synchronization", winsize.x / 64, ke::Origin::RIGHT_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 192));
	m_descriptions[4].create(sf::Vector2f(winsize.x / 6, winsize.y / 21), sf::Vector2f(winsize.x / 2 - xShift, yShift + 5.5 * winsize.y / 10), ke::Origin::RIGHT_MIDDLE, L"max FPS in simulation", winsize.x / 64, ke::Origin::RIGHT_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 192));
	m_descriptions[5].create(sf::Vector2f(winsize.x / 6, winsize.y / 21), sf::Vector2f(winsize.x / 2 - xShift, yShift + 7 * winsize.y / 10), ke::Origin::RIGHT_MIDDLE, L"backgroudn brightness", winsize.x / 64, ke::Origin::RIGHT_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 192));
}

void SettingsOverlay::updateEvents(const MousePosition& mousePosition, float dt)
{
	if (!m_active)
		return;

	m_vsync.SmoothSignalChange(m_window->getSize().x, dt);
}

void SettingsOverlay::updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left && !m_background.isInvaded(mousePosition.byWindow))
	{
		m_quitCode = OverlayQuitCode::QUITTING;
		this->deactivate();
	}



	if (m_music_volume.update(mousePosition.byWindow, event, sf::Mouse::Left, nullptr))
	{
		AppSettings::setMusicVolume(m_music_volume.getPercent());
	}
	else if (m_sfx_volume.update(mousePosition.byWindow, event, sf::Mouse::Left, nullptr))
	{
		AppSettings::setSFXVolume(m_sfx_volume.getPercent());
	}


	if (m_vsync.SSC_click_update(mousePosition.byWindow, event, sf::Mouse::Left))
	{
		AppSettings::setVSync(m_vsync.signal());
	}


	if (m_simulationFPS.isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
	{
		m_simulationFPS.addPoints(120);

		std::wstringstream wstr;
		wstr << std::fixed << std::setprecision(0) << m_simulationFPS.getPointCount();

		if (m_simulationFPS.getPointCount() < 960)
			m_FPS_text.setText(wstr.str());
		else
			m_FPS_text.setText(L"Unlimited");

		AppSettings::setMaxSimulationFPS(m_simulationFPS.getPointCount());
	}
	else if (m_simulationFPS.isClicked(sf::Mouse::Right, mousePosition.byWindow, event))
	{
		m_simulationFPS.subtractPoints(120);

		std::wstringstream wstr;
		wstr << std::fixed << std::setprecision(0) << m_simulationFPS.getPointCount();

		m_FPS_text.setText(wstr.str());

		AppSettings::setMaxSimulationFPS(m_simulationFPS.getPointCount());
	}


	for (auto itr = m_background_images.begin(); itr != m_background_images.end(); ++itr)
	{
		if ((*itr)->isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
		{
			(*m_selected_image)->setOutlineThickness(0);
			(*m_selected_image)->setOutlineColor(sf::Color::Transparent);

			m_selected_image = itr;

			(*m_selected_image)->setOutlineThickness(m_window->getSize().x / 512);
			(*m_selected_image)->setOutlineColor(sf::Color::Cyan);

			AppSettings::setSimulationBackgroundImage(std::distance(m_background_images.begin(), itr));
			simulation_background->setTexture(this->index_to_background_texture());

			if (AppSettings::SimulationBackgroundImage() == 0)
				simulation_background->setFillColor(sf::Color::Black);
			if (AppSettings::SimulationBackgroundImage() == 1)
				simulation_background->setFillColor(sf::Color(0, 0, 4));
			else
				simulation_background->setFillColor(sf::Color(0, 0, 0, 255.f - 255.f * AppSettings::BackgroundBrightness() * 0.01f));
		}
	}


	if (m_background_brightness.update(mousePosition.byWindow, event, sf::Mouse::Left, nullptr))
	{
		AppSettings::setBackgroundBrightness(m_background_brightness.getPercent());

		if (AppSettings::SimulationBackgroundImage() != 0 && AppSettings::SimulationBackgroundImage() != 1)
			simulation_background->setFillColor(sf::Color(0, 0, 0, 255.f - 255.f * AppSettings::BackgroundBrightness() * 0.01f));
	}
}

void SettingsOverlay::updateColors(const sf::Vector2f& mousePosition, const float dt)
{
	if (!m_active)
		return;

	auto color_itr = m_colors.begin();

	ke::SmoothColorChange(m_music_volume.getColorButton(), m_music_volume.isInvaded(mousePosition) || m_music_volume.isHolded(), sf::Color::Transparent, sf::Color(0, 0, 0, 32), *color_itr, 256, dt); ++color_itr;
	ke::SmoothColorChange(m_music_volume.getObject(), m_music_volume.isInvaded(mousePosition) || m_music_volume.isHolded(), sf::Color(64, 64, 64, 255), sf::Color(32, 32, 32, 255), *color_itr, 256, dt); ++color_itr;
	ke::SmoothColorChange(m_sfx_volume.getColorButton(), m_sfx_volume.isInvaded(mousePosition) || m_sfx_volume.isHolded(), sf::Color::Transparent, sf::Color(0, 0, 0, 32), *color_itr, 256, dt); ++color_itr;
	ke::SmoothColorChange(m_sfx_volume.getObject(), m_sfx_volume.isInvaded(mousePosition) || m_sfx_volume.isHolded(), sf::Color(64, 64, 64, 255), sf::Color(32, 32, 32, 255), *color_itr, 256, dt); ++color_itr;

	for (auto itr = m_background_images.begin() + 2; itr != m_background_images.end(); ++itr)
	{
		ke::SmoothColorChange(itr->get(), (*itr)->isInvaded(mousePosition), sf::Color::Transparent, sf::Color(0, 0, 0, 32), *color_itr, 256, dt);
		++color_itr;
	}

	ke::SmoothColorChange(m_vsync.getColorButton(), m_vsync.isInvaded(mousePosition), sf::Color::Transparent, sf::Color(0, 0, 0, 32), *color_itr, 256, dt); ++color_itr;
	ke::SmoothColorChange(m_vsync.getObject(), m_vsync.isInvaded(mousePosition), sf::Color(64, 64, 64, 255), sf::Color(32, 32, 32, 255), *color_itr, 256, dt); ++color_itr;
	
	ke::SmoothColorChange(m_simulationFPS.getObject(), m_simulationFPS.isInvaded(mousePosition), sf::Color(64, 64, 64, 255), sf::Color(32, 32, 32, 255), *color_itr, 256, dt); ++color_itr;
	ke::SmoothColorChange(m_simulationFPS.getBar(), m_simulationFPS.isInvaded(mousePosition), sf::Color(128, 128, 128, 255), sf::Color(64, 64, 64, 255), *color_itr, 512, dt); ++color_itr;
	ke::SmoothTextColorChange(&m_FPS_text, m_simulationFPS.isInvaded(mousePosition), sf::Color::White, sf::Color(223, 223, 223, 225), *color_itr, 256, dt);

	ke::SmoothColorChange(m_background_brightness.getColorButton(), m_background_brightness.isInvaded(mousePosition) || m_background_brightness.isHolded(), sf::Color::Transparent, sf::Color(0, 0, 0, 32), *color_itr, 256, dt); ++color_itr;
	ke::SmoothColorChange(m_background_brightness.getObject(), m_background_brightness.isInvaded(mousePosition) || m_background_brightness.isHolded(), sf::Color(64, 64, 64, 255), sf::Color(32, 32, 32, 255), *color_itr, 256, dt); ++color_itr;
}


OverlayQuitCode SettingsOverlay::quitStatus() const
{
	return m_quitCode;
}

void SettingsOverlay::resetQuitStatus()
{
	m_quitCode = OverlayQuitCode::NOT_QUITTING;
}

void SettingsOverlay::render()
{
	if (!m_active)
		return;

	m_background.render(m_window);

	for (auto& itr : m_descriptions)
		itr.render(m_window);

	m_music_volume.render(m_window);
	m_sfx_volume.render(m_window);
	m_vsync.render(m_window);
	m_simulationFPS.render(m_window);
	m_FPS_text.render(m_window);

	for (auto itr = m_background_images.begin(); itr != m_background_images.end(); ++itr)
		if (itr != m_selected_image)
			(*itr)->render(m_window);

	(*m_selected_image)->render(m_window);

	m_background_brightness.render(m_window);
}

bool SettingsOverlay::active() const
{
	return m_active;
}

void SettingsOverlay::activate()
{
	m_active = true;
	this->resetQuitStatus();
}

void SettingsOverlay::deactivate()
{
	m_active = false;

	m_window->setFramerateLimit(AppSettings::MaxSimulationFPS());
	m_window->setVerticalSyncEnabled(AppSettings::vSync());
}

std::string SettingsOverlay::index_to_background_texture()
{
	switch (AppSettings::SimulationBackgroundImage())
	{
	case 0:
		return ke::Settings::EmptyTexturePath();
	case 1:
		return ke::Settings::EmptyTexturePath();
	case 2:
		return "Textures/StateTextures/Simulation/Backgrounds/CISS_background.png";
	case 3:
		return "Textures/StateTextures/Simulation/Backgrounds/NGC-2442.png";
	case 4:
		return "Textures/StateTextures/Simulation/Backgrounds/NGC-2525.png";
	case 5:
		return "Textures/StateTextures/Simulation/Backgrounds/Orion_Nebula.png";
	case 6:
		return "Textures/StateTextures/Simulation/Backgrounds/Westerlund_2.png";
	case 7:
		return "Textures/StateTextures/Simulation/Backgrounds/Whirlpool_Galaxy.png";
	case 8:
		return "Textures/StateTextures/Simulation/Backgrounds/NGC-1300.png";
	case 9:
		return "Textures/StateTextures/Simulation/Backgrounds/Lagoon_Nebula.png";
	default:
		break;
	}
}
