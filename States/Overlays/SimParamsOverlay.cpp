#include "SimParamsOverlay.hpp"

SimParamsOverlay::SimParamsOverlay()
	: m_active(false)
	, m_quitCode(OverlayQuitCode::NOT_QUITTING)
{

}

SimParamsOverlay::~SimParamsOverlay()
{

}

void SimParamsOverlay::assign(sf::RenderWindow* window)
{
	m_window = window;
}

void SimParamsOverlay::initUI()
{
	sf::Vector2f winsize(m_window->getSize());
	float xShift = winsize.x / 32;
	float yShift(winsize.y / 2 - winsize.y * 0.4);


	m_sScales = { 1, 2, 10, 50, 100, 200 };
	m_pScales = { 1, 2, 10, 50, 100, 200, 500, 1000 };

	m_sScale_itr = m_sScales.begin();
	m_pSscale_itr = m_pScales.begin();

	for (auto itr = m_sScales.begin(); itr != m_sScales.end(); ++itr)
	{
		if (*itr == AppSettings::StarSize())
		{
			m_sScale_itr = itr;
			break;
		}
	}

	for (auto itr = m_pScales.begin(); itr != m_pScales.end(); ++itr)
	{
		if (*itr == AppSettings::PlanetSize())
		{
			m_pSscale_itr = itr;
			break;
		}
	}

	std::cout << *m_sScale_itr << ' ' << *m_pSscale_itr << '\n';


	m_background.create(sf::Vector2f(winsize.x / 2, winsize.y * 0.8), winsize / 2.f, ke::Origin::MIDDLE_MIDDLE, std::wstring(), 0, 0, sf::Color(8, 8, 8, 255));
	m_shader_background.create(winsize, { 0, 0 }, ke::Origin::LEFT_TOP, nullptr);

	for (auto& itr : m_shaders)
	{
		itr.loadFromFile("Textures/Shaders/glow.frag", sf::Shader::Fragment);
		itr.setUniform("size", winsize.y / 21);
		itr.setUniform("basic_a", 0.8f);
	}




	m_star_scale.create(sf::Vector2f(winsize.x / 6, winsize.y / 21), sf::Vector2f(winsize.x / 2 + xShift, yShift + 1 * winsize.y / 10), nullptr, AppSettings::StarSize(), 1, 200, ke::Origin::LEFT_MIDDLE, sf::Color(32, 32, 32, 255), sf::Color(64, 64, 64, 255));
	m_planet_scale.create(sf::Vector2f(winsize.x / 6, winsize.y / 21), sf::Vector2f(winsize.x / 2 + xShift, yShift + 2 * winsize.y / 10), nullptr, AppSettings::PlanetSize(), 1, 1000, ke::Origin::LEFT_MIDDLE, sf::Color(32, 32, 32, 255), sf::Color(64, 64, 64, 255));

	std::wstringstream wstr1; wstr1 << L'\u00D7' << std::fixed << m_star_scale.getPointCount();
	m_star_scale_text.create(sf::Vector2f(winsize.x / 6, winsize.y / 21), sf::Vector2f(winsize.x / 2 + xShift, yShift + 1 * winsize.y / 10), ke::Origin::LEFT_MIDDLE, nullptr, wstr1.str(), winsize.x / 96, ke::Origin::RIGHT_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 255));
	m_star_scale_text.setTextPosition(ke::Origin::RIGHT_MIDDLE, sf::Vector2f(-winsize.x / 128, 0));

	std::wstringstream wstr2; wstr2 << L'\u00D7' << std::fixed << m_planet_scale.getPointCount();
	m_planet_scale_text.create(sf::Vector2f(winsize.x / 6, winsize.y / 21), sf::Vector2f(winsize.x / 2 + xShift, yShift + 2 * winsize.y / 10), ke::Origin::LEFT_MIDDLE, nullptr, wstr2.str(), winsize.x / 96, ke::Origin::RIGHT_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 255));
	m_planet_scale_text.setTextPosition(ke::Origin::RIGHT_MIDDLE, sf::Vector2f(-winsize.x / 128, 0));


	m_allow_multithreading.create(sf::Vector2f(winsize.x / 18, winsize.y / 21), winsize.y / 42, sf::Vector2f(m_star_scale.getShapeCenter().x, yShift + 3 * winsize.y / 10), ke::Origin::MIDDLE_MIDDLE, "Textures/StateTextures/Simulation/SimParamsOverlay/Sun_icon.png", ke::Settings::EmptyTexturePath(), sf::Color::Transparent, sf::Color(32, 32, 32, 255));
	m_less_calculations_mode.create(sf::Vector2f(winsize.x / 18, winsize.y / 21), winsize.y / 42, sf::Vector2f(m_star_scale.getShapeCenter().x, yShift + 4 * winsize.y / 10), ke::Origin::MIDDLE_MIDDLE, "Textures/StateTextures/Simulation/SimParamsOverlay/EpsilonEridani_icon.png", ke::Settings::EmptyTexturePath(), sf::Color::Transparent, sf::Color(32, 32, 32, 255));

	m_custom_dt.create(sf::Vector2f(winsize.x / 18, winsize.y / 21), winsize.y / 42, sf::Vector2f(m_star_scale.getShapeCenter().x, yShift + 5 * winsize.y / 10), ke::Origin::MIDDLE_MIDDLE, "Textures/StateTextures/Simulation/SimParamsOverlay/ProximaCentauri_icon.png", ke::Settings::EmptyTexturePath(), sf::Color::Transparent, sf::Color(32, 32, 32, 255));
	m_custom_timestep.create(sf::Vector2f(winsize.x / 6, winsize.y / 21), sf::Vector2f(winsize.x / 2 + xShift, yShift + 6 * winsize.y / 10), ke::Origin::LEFT_MIDDLE, nullptr, L"timestep in ms", ke::TextScope::Numbers, 20, 1, winsize.x / 100, ke::Origin::LEFT_MIDDLE, sf::Color(32, 32, 32, 255), sf::Color::White, sf::Color(96, 96, 96, 255), {}, {}, {}, sf::Vector2f(winsize.x / 100, 0));


	m_descriptions[0].create(sf::Vector2f(winsize.x / 6, winsize.y / 21), sf::Vector2f(winsize.x / 2 - xShift, yShift + 1 * winsize.y / 10), ke::Origin::RIGHT_MIDDLE, L"Star scale", winsize.x / 64, ke::Origin::RIGHT_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 192));
	m_descriptions[1].create(sf::Vector2f(winsize.x / 6, winsize.y / 21), sf::Vector2f(winsize.x / 2 - xShift, yShift + 2 * winsize.y / 10), ke::Origin::RIGHT_MIDDLE, L"Planet scale", winsize.x / 64, ke::Origin::RIGHT_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 192));
	m_descriptions[2].create(sf::Vector2f(winsize.x / 6, winsize.y / 21), sf::Vector2f(winsize.x / 2 - xShift, yShift + 3 * winsize.y / 10), ke::Origin::RIGHT_MIDDLE, L"Allow multithreading", winsize.x / 64, ke::Origin::RIGHT_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 192));
	m_descriptions[3].create(sf::Vector2f(winsize.x / 6, winsize.y / 21), sf::Vector2f(winsize.x / 2 - xShift, yShift + 4 * winsize.y / 10), ke::Origin::RIGHT_MIDDLE, L"Use less calculations", winsize.x / 64, ke::Origin::RIGHT_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 192));
	m_descriptions[4].create(sf::Vector2f(winsize.x / 6, winsize.y / 21), sf::Vector2f(winsize.x / 2 - xShift, yShift + 5 * winsize.y / 10), ke::Origin::RIGHT_MIDDLE, L"Custom timestep", winsize.x / 64, ke::Origin::RIGHT_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 192));
	m_descriptions[5].create(sf::Vector2f(winsize.x / 6, winsize.y / 21), sf::Vector2f(winsize.x / 2 - xShift, yShift + 6 * winsize.y / 10), ke::Origin::RIGHT_MIDDLE, L"Custom timestep value", winsize.x / 64, ke::Origin::RIGHT_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 192));


	m_apply.create(sf::Vector2f(winsize.x / 8, winsize.y / 18), sf::Vector2f(winsize.x / 2 + xShift, yShift + 7 * winsize.y / 10), ke::Origin::LEFT_TOP, nullptr, L"APPLY", winsize.x / 64, ke::Origin::MIDDLE_MIDDLE, sf::Color(32, 255, 32, 64), sf::Color(255, 255, 255, 128));
	m_cancel.create(sf::Vector2f(winsize.x / 8, winsize.y / 18), sf::Vector2f(winsize.x / 2 - xShift, yShift + 7 * winsize.y / 10), ke::Origin::RIGHT_TOP, nullptr, L"CANCEL", winsize.x / 64, ke::Origin::MIDDLE_MIDDLE, sf::Color(255, 32, 32, 64), sf::Color(255, 255, 255, 128));

	this->restoreSettings();


	m_shaders[0].setUniform("position", sf::Glsl::Vec2(m_allow_multithreading.getButtonCenter().x, m_window->getSize().y - m_allow_multithreading.getButtonCenter().y));
	m_shaders[0].setUniform("color", sf::Glsl::Vec3(0.8, 0.7, 0.0));
	m_shaders[1].setUniform("position", sf::Glsl::Vec2(m_less_calculations_mode.getButtonCenter().x, m_window->getSize().y - m_less_calculations_mode.getButtonCenter().y));
	m_shaders[1].setUniform("color", sf::Glsl::Vec3(0.8, 0.5, 0.0));
	m_shaders[2].setUniform("position", sf::Glsl::Vec2(m_custom_dt.getButtonCenter().x, m_window->getSize().y - m_custom_dt.getButtonCenter().y));
	m_shaders[2].setUniform("color", sf::Glsl::Vec3(1.0, 0.2, 0.0));
}


void SimParamsOverlay::updateEvents(const MousePosition& mousePosition, float dt)
{
	if (!m_active)
		return;

	if (m_allow_multithreading.SmoothSignalChange(m_window->getSize().x, dt))
		m_shaders[0].setUniform("position", sf::Glsl::Vec2(m_allow_multithreading.getButtonCenter().x, m_window->getSize().y - m_allow_multithreading.getButtonCenter().y));

	if (m_less_calculations_mode.SmoothSignalChange(m_window->getSize().x, dt))
		m_shaders[1].setUniform("position", sf::Glsl::Vec2(m_less_calculations_mode.getButtonCenter().x, m_window->getSize().y - m_less_calculations_mode.getButtonCenter().y));

	if (m_custom_dt.SmoothSignalChange(m_window->getSize().x, dt))
		m_shaders[2].setUniform("position", sf::Glsl::Vec2(m_custom_dt.getButtonCenter().x, m_window->getSize().y - m_custom_dt.getButtonCenter().y));


	if (m_custom_dt.getSignal())
		m_custom_timestep.updateCursor();
}

void SimParamsOverlay::updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event)
{
	if (m_star_scale.isClicked(sf::Mouse::Left, mousePosition.byWindow, event) && m_sScale_itr != m_sScales.end() - 1)
	{
		std::wstringstream wstr;
		wstr << L'\u00D7' << std::fixed << *(m_sScale_itr + 1);
		m_star_scale_text.setText(wstr.str());

		m_star_scale.setPointCount(*(m_sScale_itr + 1));
		m_sScale_itr++;
	}
	else if (m_star_scale.isClicked(sf::Mouse::Right, mousePosition.byWindow, event) && m_sScale_itr != m_sScales.begin())
	{
		std::wstringstream wstr;
		wstr << L'\u00D7' << std::fixed << *(m_sScale_itr - 1);
		m_star_scale_text.setText(wstr.str());

		m_star_scale.setPointCount(*(m_sScale_itr - 1));
		m_sScale_itr--;
	}
	else if (m_planet_scale.isClicked(sf::Mouse::Left, mousePosition.byWindow, event) && m_pSscale_itr != m_pScales.end() - 1)
	{
		std::wstringstream wstr;
		wstr << L'\u00D7' << std::fixed << *(m_pSscale_itr + 1);
		m_planet_scale_text.setText(wstr.str());

		m_planet_scale.setPointCount(*(m_pSscale_itr + 1));
		m_pSscale_itr++;
	}
	else if (m_planet_scale.isClicked(sf::Mouse::Right, mousePosition.byWindow, event) && m_pSscale_itr != m_pScales.begin())
	{
		std::wstringstream wstr;
		wstr << L'\u00D7' << std::fixed << *(m_pSscale_itr - 1);
		m_planet_scale_text.setText(wstr.str());

		m_planet_scale.setPointCount(*(m_pSscale_itr - 1));
		m_pSscale_itr--;
	}


	if (m_allow_multithreading.SSC_click_update(mousePosition.byWindow, event, sf::Mouse::Left))
	{

	}

	if (m_less_calculations_mode.SSC_click_update(mousePosition.byWindow, event, sf::Mouse::Left))
	{
		//m_shader_background.setActiveStatus(m_less_calculations_mode.getSignal());
	}


	if (m_custom_dt.SSC_click_update(mousePosition.byWindow, event, sf::Mouse::Left))
	{
		m_custom_timestep.setEPS(m_custom_dt.getSignal());
		m_custom_timestep.setFillColor(sf::Color(32, 32, 32, 255));
		m_custom_timestep.setTextColor(sf::Color(92, 92, 92, 255));
		m_custom_timestep.setText(std::to_wstring(AppSettings::CustomTimeStep()));

		m_colors[9] = sf::Color(32, 32, 32, 255);
		m_colors[10] = sf::Color(92, 92, 92, 255);
	}


	if (m_custom_dt.getSignal())
		m_custom_timestep.update(mousePosition.byWindow, event, sf::Mouse::Left, nullptr);



	if (m_apply.isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
	{
		State::sfx.play("click");

		m_quitCode = OverlayQuitCode::CHANGING_SETTINGS;

		this->saveSettings();
		this->deactivate();
	}
	else if (m_cancel.isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
	{
		State::sfx.play("click");

		m_quitCode = OverlayQuitCode::QUITTING;

		this->restoreSettings();
		this->deactivate();
	}
}

void SimParamsOverlay::updateColors(const sf::Vector2f& mousePosition, const float dt)
{
	if (!m_active)
		return;

	auto itr = m_colors.begin();

	ke::SmoothColorChange(m_star_scale.getObject(), m_star_scale.isInvaded(mousePosition), sf::Color(64, 64, 64, 255), sf::Color(32, 32, 32, 255), *itr, 128, dt); ++itr;
	ke::SmoothColorChange(m_star_scale.getBar(), m_star_scale.isInvaded(mousePosition), sf::Color(128, 128, 128, 255), sf::Color(64, 64, 64, 255), *itr, 256, dt); ++itr;
	ke::SmoothTextColorChange(&m_star_scale_text, m_star_scale.isInvaded(mousePosition), sf::Color::White, sf::Color(192, 192, 192, 192), *itr, 255, dt); ++itr;

	ke::SmoothColorChange(m_planet_scale.getObject(), m_planet_scale.isInvaded(mousePosition), sf::Color(64, 64, 64, 255), sf::Color(32, 32, 32, 255), *itr, 128, dt); ++itr;
	ke::SmoothColorChange(m_planet_scale.getBar(), m_planet_scale.isInvaded(mousePosition), sf::Color(128, 128, 128, 255), sf::Color(64, 64, 64, 255), *itr, 256, dt); ++itr;
	ke::SmoothTextColorChange(&m_planet_scale_text, m_planet_scale.isInvaded(mousePosition), sf::Color::White, sf::Color(192, 192, 192, 192), *itr, 255, dt); ++itr;

	ke::SmoothColorChange(&m_allow_multithreading, m_allow_multithreading.isInvaded(mousePosition), sf::Color(64, 64, 64, 255), sf::Color(32, 32, 32, 255), *itr, 128, dt); ++itr;
	ke::SmoothColorChange(&m_less_calculations_mode, m_less_calculations_mode.isInvaded(mousePosition), sf::Color(64, 64, 64, 255), sf::Color(32, 32, 32, 255), *itr, 128, dt); ++itr;

	ke::SmoothColorChange(&m_custom_dt, m_custom_dt.isInvaded(mousePosition), sf::Color(64, 64, 64, 255), sf::Color(32, 32, 32, 255), *itr, 128, dt); ++itr;

	if (m_custom_dt.getSignal())
	{
		ke::SmoothColorChange(&m_custom_timestep, m_custom_timestep.isInvaded(mousePosition) || m_custom_timestep.getEPS(), sf::Color(64, 64, 64, 255), sf::Color(32, 32, 32, 255), *itr, 128, dt); ++itr;
		ke::SmoothTextColorChange(&m_custom_timestep, m_custom_timestep.isInvaded(mousePosition) || m_custom_timestep.getEPS(), sf::Color::White, sf::Color(96, 96, 96, 255), *itr, 384, dt); ++itr;
	}
	else
	{
		ke::SmoothColorChange(&m_custom_timestep, true, sf::Color(32, 32, 32, 128), sf::Color(32, 32, 32, 255), *itr, 256, dt); ++itr;
		ke::SmoothTextColorChange(&m_custom_timestep, true, sf::Color(96, 96, 96, 128), sf::Color(96, 96, 96, 255), *itr, 256, dt); ++itr;
	}


	ke::SmoothColorChange(&m_apply, m_apply.isInvaded(mousePosition), sf::Color(32, 255, 32, 255), sf::Color(32, 255, 32, 128), *itr, 255, dt); ++itr;
	ke::SmoothTextColorChange(&m_apply, m_apply.isInvaded(mousePosition), sf::Color::White, sf::Color(255, 255, 255, 128), *itr, 255, dt); ++itr;
	ke::SmoothColorChange(&m_cancel, m_cancel.isInvaded(mousePosition), sf::Color(255, 32, 32, 255), sf::Color(255, 32, 32, 128), *itr, 255, dt); ++itr;
	ke::SmoothTextColorChange(&m_cancel, m_cancel.isInvaded(mousePosition), sf::Color::White, sf::Color(255, 255, 255, 128), *itr, 255, dt); ++itr;
}

OverlayQuitCode SimParamsOverlay::quitStatus() const
{
	return m_quitCode;
}

void SimParamsOverlay::resetQuitStatus()
{
	m_quitCode = OverlayQuitCode::NOT_QUITTING;
}

QuickSettings& SimParamsOverlay::output()
{
	return m_output;
}

void SimParamsOverlay::render()
{
	if (!m_active)
		return;

	m_background.render(m_window);

	m_star_scale.render(m_window);
	m_star_scale_text.render(m_window);
	m_planet_scale.render(m_window);
	m_planet_scale_text.render(m_window);

	m_allow_multithreading.render(m_window);
	m_less_calculations_mode.render(m_window);

	m_custom_dt.render(m_window);
	m_custom_timestep.render(m_window);

	for (auto& itr : m_descriptions)
		itr.render(m_window);

	if (m_shader_background.isActive())
		for (auto& itr : m_shaders)
			m_window->draw(*m_shader_background.getShape(), &itr);

	m_apply.render(m_window);
	m_cancel.render(m_window);
}

bool SimParamsOverlay::active() const
{
	return m_active;
}

void SimParamsOverlay::activate()
{
	m_quitCode = OverlayQuitCode::NOT_QUITTING;

	m_active = true;
	this->restoreSettings();
}

void SimParamsOverlay::deactivate()
{
	m_active = false;
}


void SimParamsOverlay::saveSettings()
{
	AppSettings::setStarSize(static_cast<long double>(m_star_scale.getPointCount()));
	AppSettings::setPlanetSize(static_cast<long double>(m_planet_scale.getPointCount()));
	AppSettings::setMultithreadingStatus(m_allow_multithreading.getSignal());
	AppSettings::setCalculationMode(m_less_calculations_mode.getSignal());
	AppSettings::setCustomDt(m_custom_dt.getSignal());

	std::wstringstream wstream; float buffer;
	wstream << m_custom_timestep.getText();
	wstream >> buffer;
	AppSettings::setCustomTimeStep(buffer);


	m_output.planet_size = AppSettings::PlanetSize();
	m_output.star_size = AppSettings::StarSize();
	m_output.multithreading_on = AppSettings::MultithreadingAllowed();
	m_output.less_calculations_mode = AppSettings::LessCalculationsMode();
	m_output.custom_dt = AppSettings::CustomDt();
	m_output.custom_timestep = AppSettings::CustomTimeStep();
}

void SimParamsOverlay::restoreSettings()
{
	m_output.planet_size = AppSettings::PlanetSize();
	m_output.star_size = AppSettings::StarSize();
	m_output.multithreading_on = AppSettings::MultithreadingAllowed();
	m_output.less_calculations_mode = AppSettings::LessCalculationsMode();
	m_output.custom_dt = AppSettings::CustomDt();
	m_output.custom_timestep = AppSettings::CustomTimeStep();


	m_star_scale.setPointCount(AppSettings::StarSize());
	m_planet_scale.setPointCount(AppSettings::PlanetSize());
	m_allow_multithreading.setSignal(AppSettings::MultithreadingAllowed());
	m_less_calculations_mode.setSignal(AppSettings::LessCalculationsMode());
	m_custom_dt.setSignal(AppSettings::CustomDt());
	m_custom_timestep.setText(std::to_wstring(AppSettings::CustomTimeStep()));


	std::wstringstream wstream1;
	wstream1 << L'\u00D7' << std::fixed << static_cast<int>(AppSettings::StarSize());
	m_star_scale_text.setText(wstream1.str());

	std::wstringstream wstream2;
	wstream2 << L'\u00D7' << std::fixed << static_cast<int>(AppSettings::PlanetSize());
	m_planet_scale_text.setText(wstream2.str());
}
