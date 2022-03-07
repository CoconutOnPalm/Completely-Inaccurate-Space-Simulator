#include "SettingsState.hpp"

SettingsState::SettingsState(sf::RenderWindow* sf_window, sf::View* sf_view)
	: State(sf_window, sf_view, STATE::SETTINGS)
	, m_selected_type_id(0)
	, m_last_sel_type_id(0)
	, m_vSyncStatus(AppSettings::vSync())
	, m_view_moving(false)
	, m_window_size_changed(false)
	, m_start_window_size(0)
	, m_current_window_size(0)
	, m_sm_color(sf::Color::Black)
	, m_outro_time(0)
	, m_next_state(STATE::NONE)
{
	//p_quitCode = StateQuitCode::NOT_QUITTING;

	m_view_yPositions.fill(winSize.y / 2);
	m_st_fcolors.fill(ke::Colorf());
	m_settings_manip_colors.fill(sf::Color());
	m_windowSettings_colors.fill(ke::Colorf());
	m_audio_colors.fill(ke::Colorf());

	m_stateMask.create(winSize, { 0, 0 }, ke::Origin::LEFT_TOP, {}, {}, {}, sf::Color::Black);
}





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





SettingsState::~SettingsState()
{
	// window settings

	AppSettings::setMaxMenuFPS(m_maxMenuFPS_bar.getPointCount());
	AppSettings::setMaxSimulationFPS(m_maxSimFPS_bar.getPointCount());
	window->setFramerateLimit(AppSettings::MaxMenuFPS());

	AppSettings::setVSync(m_vSyncStatus);
	window->setVerticalSyncEnabled(m_vSyncStatus);

	AppSettings::setBackgroundBrightness(m_bright_lvl.getPercent());


	// audio settings

	AppSettings::setSFXVolume(m_SFX_volume.getPercent());
	AppSettings::setMusicVolume(m_music_volume.getPercent());

	sfx.setGeneralVolume(AppSettings::SFXVolume());
	music.setVolume(AppSettings::MusicVolume());


	////////////////////////////////


	AppSettings::Save();
}





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





void SettingsState::InitState()
{
	this->InitGenSettGUI();
	this->InitWindowSettings();
	this->InitAudioSettings();
	this->InitSimulationSettings();
	this->InitKeybindsSettings();
}





////////////////////////////////////////////////////////////////////////////////////////////////




void SettingsState::InitGenSettGUI()
{
	const int types_number = 4;
	//const int wSettingsColorsCount = 26;

	sf::Event fake_event;

	m_stateBackground.create(winSize, { 0, 0 }, ke::Origin::LEFT_TOP, "Textures/StateTextures/Settings/background.png");
	m_backgroundMask.create(winSize, { 0, 0 }, ke::Origin::LEFT_TOP, L"", 0, {}, sf::Color(0, 0, 0, 255.f - 255.f * AppSettings::BackgroundBrightness() * 0.01f));


	// SETTINGS GUI


	// window settings types

	m_settings_types.reserve(types_number);

	m_settings_types.emplace_back(std::make_unique<ke::Rectangle>(winSize / 9.f, sf::Vector2f(1 * winSize.x / 9, winSize.y / 18), ke::Origin::LEFT_TOP, L"Window", winSize.y / 32.f, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 255)));
	m_settings_types.emplace_back(std::make_unique<ke::Rectangle>(winSize / 9.f, sf::Vector2f(3 * winSize.x / 9, winSize.y / 18), ke::Origin::LEFT_TOP, L"Audio", winSize.y / 32.f, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 128)));
	//m_settings_types.emplace_back(std::make_unique<ke::Rectangle>(winSize / 9.f, sf::Vector2f(5 * winSize.x / 9, winSize.y / 18), ke::Origin::LEFT_TOP, L"Simulation", winSize.y / 32.f, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 128)));
	//m_settings_types.emplace_back(std::make_unique<ke::Rectangle>(winSize / 9.f, sf::Vector2f(7 * winSize.x / 9, winSize.y / 18), ke::Origin::LEFT_TOP, L"Keybinds", winSize.y / 32.f, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 128)));

	m_selected_type_itr = m_settings_types.begin();

	for (auto& itr : m_settings_types)
		itr->update({ 0, 0 }, fake_event, sf::Mouse::Left, nullptr);


	// back button

	sf::Texture backb_texture;
	backb_texture.loadFromFile("Textures/StateTextures/back_arrow.png");
	backb_texture.setSmooth(true);
	m_back_button.create({ winSize.y / 16, winSize.y / 16 }, { winSize.x / 64, m_settings_types.at(0)->getShapeCenter().y }, ke::Origin::LEFT_MIDDLE, &backb_texture);
	m_back_button.setFillColor(sf::Color(255, 255, 255, 160));


	// separation bar

	m_separation_bar.create({ winSize.x, winSize.y / 576 }, { 0, winSize.y / 4.5f }, ke::Origin::LEFT_MIDDLE, {}, {}, {}, sf::Color(255, 255, 255, 160));


	// slider

	m_slider.create({ winSize.x / 100, winSize.y - winSize.y / 4.5f }, { winSize.x, winSize.y / 4.5f }, viewSize.y * 1.1f, ke::Origin::RIGHT_TOP, nullptr, nullptr, sf::Color(192, 192, 192, 128), sf::Color(128, 128, 128, 128));


	// apply and restore defaults button

	m_apply_button.create({ winSize.x * 0.1f, winSize.y * 0.05f }, { winSize.x / 6.f, 0.95f * winSize.y }, ke::RIGHT_TOP, L"Apply", winSize.y / 32.f, ke::Origin::MIDDLE_MIDDLE, sf::Color(16, 16, 16, 255), sf::Color(192, 192, 192, 192));
	m_restore_def_buttoon.create({ winSize.x * 0.1f, winSize.y * 0.05f }, { winSize.x / 6.f, 0.95f * winSize.y }, ke::LEFT_TOP, L"Restore defaults", winSize.y / 48.f, ke::Origin::MIDDLE_MIDDLE, sf::Color(16, 16, 16, 255), sf::Color(192, 192, 192, 255));
}




////////////////////////////////////////////////////////////////





void SettingsState::InitWindowSettings()
{
	// WINDOW SETTINGS

	sf::Event fake_event;
	auto color_itr = m_windowSettings_colors.begin();
	const unsigned int accessories_count = 11;


	// FPS bars

	m_maxMenuFPS_bar.create({ winSize.x / 6, winSize.y / 24 }, { 0.6f * winSize.x, 4 * winSize.y * 0.1f }, nullptr, AppSettings::MaxMenuFPS(), 30, 240, ke::Origin::LEFT_MIDDLE, sf::Color::Black, sf::Color(255, 255, 255, 160), winSize.y / 450, 0, sf::Color(255, 255, 255, 160), sf::Color::Transparent);;
	m_maxSimFPS_bar.create({ winSize.x / 6, winSize.y / 24 }, { 0.6f * winSize.x, 5 * winSize.y * 0.1f }, nullptr, AppSettings::MaxSimulationFPS(), 120, 960, ke::Origin::LEFT_MIDDLE, sf::Color::Black, sf::Color(255, 255, 255, 160), winSize.y / 450, 0, sf::Color(255, 255, 255, 160), sf::Color::Transparent);;


	// FPS bars accessories

	m_WS_accessories.reserve(accessories_count);

	m_WS_accessories.emplace_back(std::make_unique<ke::Rectangle>(sf::Vector2f(winSize.y / 24.f, winSize.y / 24.f), sf::Vector2f(0.6f * winSize.x, 4 * winSize.y * 0.1f), ke::Origin::RIGHT_MIDDLE, "Textures/StateTextures/Settings/left_arrow.png"));
	m_WS_accessories.emplace_back(std::make_unique<ke::Rectangle>(sf::Vector2f(winSize.y / 24.f, winSize.y / 24.f), sf::Vector2f(23.f * winSize.x / 30, 4 * winSize.y * 0.1f), ke::Origin::LEFT_MIDDLE, "Textures/StateTextures/Settings/right_arrow.png"));
	m_WS_accessories.emplace_back(std::make_unique<ke::Rectangle>(sf::Vector2f(winSize.x / 6.f, winSize.y / 24.f), sf::Vector2f(0.4f * winSize.x, 4 * winSize.y * 0.1f), ke::Origin::RIGHT_MIDDLE, L"Menu FPS limit", winSize.y / 32, ke::Origin::RIGHT_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 160)));
	m_WS_accessories.emplace_back(std::make_unique<ke::Rectangle>(sf::Vector2f(winSize.y / 24.f, winSize.y / 24.f), sf::Vector2f(0.6f * winSize.x, 4 * winSize.y * 0.1f), ke::Origin::LEFT_MIDDLE, std::to_wstring(AppSettings::MaxMenuFPS()), winSize.y / 48, ke::Origin::LEFT_MIDDLE, sf::Color::Transparent, sf::Color::Black, 0, sf::Color::Transparent, 0, sf::Text::Regular, sf::Vector2f(2 * winSize.y / 450, 0)));

	m_WS_accessories.emplace_back(std::make_unique<ke::Rectangle>(sf::Vector2f(winSize.y / 24.f, winSize.y / 24.f), sf::Vector2f(0.6f * winSize.x, 5 * winSize.y * 0.1f), ke::Origin::RIGHT_MIDDLE, "Textures/StateTextures/Settings/left_arrow.png"));
	m_WS_accessories.emplace_back(std::make_unique<ke::Rectangle>(sf::Vector2f(winSize.y / 24.f, winSize.y / 24.f), sf::Vector2f(23.f * winSize.x / 30, 5 * winSize.y * 0.1f), ke::Origin::LEFT_MIDDLE, "Textures/StateTextures/Settings/right_arrow.png"));
	m_WS_accessories.emplace_back(std::make_unique<ke::Rectangle>(sf::Vector2f(winSize.x / 6.f, winSize.y / 24.f), sf::Vector2f(0.4f * winSize.x, 5 * winSize.y * 0.1f), ke::Origin::RIGHT_MIDDLE, L"Simulation FPS limit", winSize.y / 32, ke::Origin::RIGHT_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 160)));
	m_WS_accessories.emplace_back(std::make_unique<ke::Rectangle>(sf::Vector2f(winSize.y / 24.f, winSize.y / 24.f), sf::Vector2f(0.6f * winSize.x, 5 * winSize.y * 0.1f), ke::Origin::LEFT_MIDDLE, std::to_wstring(AppSettings::MaxSimulationFPS()), winSize.y / 48, ke::Origin::LEFT_MIDDLE, sf::Color::Transparent, sf::Color::Black, 0, sf::Color::Transparent, 0, sf::Text::Regular, sf::Vector2f(2 * winSize.y / 450, 0)));

	if (m_maxSimFPS_bar.getPointCount() >= 960)
		m_WS_accessories.at(7)->setText(L"Unlimited");

	// vertical sync status buttons

	m_vSyncOn.create({ winSize.x / 12.f, winSize.y / 24.f }, { 41.f * winSize.x / 60.f, 6.f * winSize.y * 0.1f }, ke::Origin::RIGHT_MIDDLE, L"ON", winSize.y / 48, ke::Origin::MIDDLE_MIDDLE, sf::Color(160, 160, 160, 96), sf::Color::Black);
	m_vSyncOff.create({ winSize.x / 12.f, winSize.y / 24.f }, { 41.f * winSize.x / 60.f, 6.f * winSize.y * 0.1f }, ke::Origin::LEFT_MIDDLE, L"OFF", winSize.y / 48, ke::Origin::MIDDLE_MIDDLE, sf::Color(160, 160, 160, 96), sf::Color::Black);

	if (m_vSyncStatus)
	{
		m_vSyncOn.setFillColor(sf::Color(255, 255, 255, 192));
		m_vSyncOn.setTextStyle(sf::Text::Bold);
	}
	else
	{
		m_vSyncOff.setFillColor(sf::Color(255, 255, 255, 192));
		m_vSyncOff.setTextStyle(sf::Text::Bold);
	}


	// vertical sync buttons accessories

	m_WS_accessories.emplace_back(std::make_unique<ke::Rectangle>(sf::Vector2f(winSize.x / 6, winSize.y / 24), sf::Vector2f(0.4f * winSize.x, 6 * winSize.y * 0.1f), ke::Origin::RIGHT_MIDDLE, L"Vertical Synchronization", winSize.y / 32, ke::Origin::RIGHT_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 160)));



	// bright level bar

	m_bright_lvl.create({ winSize.x / 6.f, winSize.y / 24.f }, winSize.y / 49, { 41.f * winSize.x / 60.f, 7.f * winSize.y * 0.1f }, ke::Origin::MIDDLE_MIDDLE, nullptr, nullptr, sf::Color(160, 160, 160, 255), sf::Color(64, 64, 64, 255));
	m_bright_lvl.setPercent(AppSettings::BackgroundBrightness());


	// bright level accessories 

	m_WS_accessories.emplace_back(std::make_unique<ke::Rectangle>(sf::Vector2f(winSize.x / 6, winSize.y / 24), sf::Vector2f(0.4f * winSize.x, 7 * winSize.y * 0.1f), ke::Origin::RIGHT_MIDDLE, L"Background brightness", winSize.y / 32, ke::Origin::RIGHT_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 160)));



	// window size dropdown list

	m_windowSize_drl.create({ winSize.x / 6.f, winSize.y / 24.f }, { 41.f * winSize.x / 60.f, 8.f * winSize.y * 0.1f }, nullptr, L"Something went wrong :(",
		winSize.y / 48, ke::Origin::MIDDLE_MIDDLE, sf::Color(32, 32, 32, 255), sf::Color(255, 255, 255, 128), 0/*winSize.y / 450*/, sf::Color(255, 255, 255, 192), sf::Text::Bold);
	m_windowSize_drl.addMember(nullptr, L"1024 \u00D7 576", winSize.y / 56, ke::Origin::MIDDLE_MIDDLE, sf::Color(16, 16, 16, 255), sf::Color(160, 160, 160, 255));
	m_windowSize_drl.addMember(nullptr, L"1280 \u00D7 720", winSize.y / 56, ke::Origin::MIDDLE_MIDDLE, sf::Color(16, 16, 16, 255), sf::Color(160, 160, 160, 255));
	m_windowSize_drl.addMember(nullptr, L"1366 \u00D7 768", winSize.y / 56, ke::Origin::MIDDLE_MIDDLE, sf::Color(16, 16, 16, 255), sf::Color(160, 160, 160, 255));
	m_windowSize_drl.addMember(nullptr, L"1600 \u00D7 900", winSize.y / 56, ke::Origin::MIDDLE_MIDDLE, sf::Color(16, 16, 16, 255), sf::Color(160, 160, 160, 255));
	m_windowSize_drl.addMember(nullptr, L"1920 \u00D7 1080", winSize.y / 56, ke::Origin::MIDDLE_MIDDLE, sf::Color(16, 16, 16, 255), sf::Color(160, 160, 160, 255));
	m_windowSize_drl.addMember(nullptr, L"1920 \u00D7 1080 Fullscreen", winSize.y / 56, ke::Origin::MIDDLE_MIDDLE, sf::Color(16, 16, 16, 255), sf::Color(160, 160, 160, 255));

	for (auto& itr : *m_windowSize_drl.getMembers())
		itr->update({ 0, 0 }, fake_event, sf::Mouse::Left, nullptr);


	if (AppSettings::DefaultWindowSize() == sf::Vector2f(1024, 576)) m_windowSize_drl.setMemberAsActive(0);
	if (AppSettings::DefaultWindowSize() == sf::Vector2f(1280, 720)) m_windowSize_drl.setMemberAsActive(1);
	if (AppSettings::DefaultWindowSize() == sf::Vector2f(1366, 768)) m_windowSize_drl.setMemberAsActive(2);
	if (AppSettings::DefaultWindowSize() == sf::Vector2f(1600, 900)) m_windowSize_drl.setMemberAsActive(3);
	if (AppSettings::DefaultWindowSize() == sf::Vector2f(1920, 1080)) m_windowSize_drl.setMemberAsActive(4);
	if (AppSettings::DefaultWindowSize() == sf::Vector2f(1920, 1080)) m_windowSize_drl.setMemberAsActive(5);


	m_start_window_size = m_windowSize_drl.getSelectedID();
	m_current_window_size = m_windowSize_drl.getSelectedID();


	// window size dropdown list accessories

	m_WS_accessories.emplace_back(std::make_unique<ke::Rectangle>(sf::Vector2f(winSize.x / 6, winSize.y / 24), sf::Vector2f(0.4f * winSize.x, 8 * winSize.y * 0.1f), ke::Origin::RIGHT_MIDDLE, L"Window Resolution", winSize.y / 32, ke::Origin::RIGHT_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 160)));
}



////////////////////////////////////////////////////////////////



void SettingsState::InitAudioSettings()
{
	const unsigned int accessories_count = 4;

	m_AS_accessories.reserve(accessories_count);

	m_SFX_volume.create({ winSize.x / 6.f, winSize.y / 24.f }, winSize.y / 49, { winSize.x + 41.f * winSize.x / 64.f, 4.f * winSize.y * 0.1f }, ke::Origin::MIDDLE_MIDDLE, nullptr, nullptr, sf::Color(160, 160, 160, 255), sf::Color(64, 64, 64, 255));
	m_music_volume.create({ winSize.x / 6.f, winSize.y / 24.f }, winSize.y / 49, { winSize.x + 41.f * winSize.x / 64.f, 5.f * winSize.y * 0.1f }, ke::Origin::MIDDLE_MIDDLE, nullptr, nullptr, sf::Color(160, 160, 160, 255), sf::Color(64, 64, 64, 255));

	m_SFX_volume.setPercent(AppSettings::SFXVolume());
	m_music_volume.setPercent(AppSettings::MusicVolume());

	m_AS_accessories.emplace_back(std::make_unique<ke::Rectangle>(sf::Vector2f(winSize.x / 6.f, winSize.y / 24.f), sf::Vector2f(1.4f * winSize.x, 4 * winSize.y * 0.1f), ke::Origin::RIGHT_MIDDLE, L"SFX volume", winSize.y / 32, ke::Origin::RIGHT_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 160)));
	m_AS_accessories.emplace_back(std::make_unique<ke::Rectangle>(sf::Vector2f(winSize.x / 6.f, winSize.y / 24.f), sf::Vector2f(1.4f * winSize.x, 5 * winSize.y * 0.1f), ke::Origin::RIGHT_MIDDLE, L"Music volume", winSize.y / 32, ke::Origin::RIGHT_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 160)));

	sf::Texture audio_icon;
	audio_icon.loadFromFile("Textures/StateTextures/Settings/AudioIcon.png");
	audio_icon.setSmooth(true);

	//ke::Rectangle::create(sf::Vector2f(winSize.y / 24.f, winSize.y / 24.f), sf::Vector2f(winSize.x + 41.f * winSize.x / 64.f + winSize.x / 9.f, 4.f * winSize.y * 0.1f), ke::Origin::LEFT_MIDDLE, &audio_icon);

	m_AS_accessories.emplace_back(std::make_unique<ke::Rectangle>(sf::Vector2f(winSize.y / 24.f, winSize.y / 24.f), sf::Vector2f(winSize.x + 41.f * winSize.x / 64.f + winSize.x / 9.f, 4.f * winSize.y * 0.1f), ke::Origin::LEFT_MIDDLE, &audio_icon));
	m_AS_accessories.back()->setFillColor(sf::Color(255, 255, 255, 160));
	m_AS_accessories.emplace_back(std::make_unique<ke::Rectangle>(sf::Vector2f(winSize.y / 24.f, winSize.y / 24.f), sf::Vector2f(winSize.x + 41.f * winSize.x / 64.f + winSize.x / 9.f, 5.f * winSize.y * 0.1f), ke::Origin::LEFT_MIDDLE, &audio_icon));
	m_AS_accessories.back()->setFillColor(sf::Color(255, 255, 255, 160));
}



////////////////////////////////////////////////////////////////



void SettingsState::InitSimulationSettings()
{

}



////////////////////////////////////////////////////////////////



void SettingsState::InitKeybindsSettings()
{

}





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





void SettingsState::reloadState()
{
	this->reloadGenSettGUI();
	this->reloadWindowSettings();
	this->reloadAudioSettings();
	this->reloadSimulationSettings();
	this->reloadKeybindsSettings();

	this->reloadCharacterSize();
}



////////////////////////////////////////////////////////////////



void SettingsState::reloadGenSettGUI()
{
	switch (m_selected_type_id)
	{
	case 0: view->setCenter(winSize / 2.f); break;
	case 1: view->setCenter(1.5f * winSize.x, winSize.y / 2); break;
	case 2: view->setCenter(2.5f * winSize.x, winSize.y / 2); break;
	case 3: view->setCenter(3.5f * winSize.x, winSize.y / 2); break;
	default:
		view->setCenter(winSize / 2.f);
		break;
	}

	// State backgrounds and state masks

	m_stateBackground.setSize(winSize);
	m_backgroundMask.setSize(winSize);
	m_stateMask.setSize(winSize);

	m_stateBackground.setPosition(0, 0);
	m_backgroundMask.setPosition(0, 0);
	m_stateMask.setPosition(0, 0);


	// settings types 

	int k = 1;
	for (auto& itr : m_settings_types)
	{
		itr->setSize(winSize / 9.f);
		itr->setPosition(k * winSize.x / 9.f, winSize.y / 18.f);
		k += 2;
	}


	// back button

	m_back_button.setSize(winSize.y / 16, winSize.y / 16);
	m_back_button.setPosition(winSize.x / 64, m_settings_types.at(0)->getShapeCenter().y);


	// separation bar

	m_separation_bar.setSize(winSize.x, winSize.y / 576);
	m_separation_bar.setPosition(0, winSize.y / 4.5f);


	// slider

	m_slider.create({ winSize.x / 100, winSize.y - winSize.y / 4.5f }, { winSize.x, winSize.y / 4.5f }, viewSize.y * 1.1f, ke::Origin::RIGHT_TOP, nullptr, nullptr, sf::Color(192, 192, 192, 128), sf::Color(128, 128, 128, 128));


	// apply and restore defaults 

	m_apply_button.setSize({ winSize.x * 0.1f, winSize.y * 0.05f });
	m_restore_def_buttoon.setSize({ winSize.x * 0.1f, winSize.y * 0.05f });

	m_apply_button.setPosition({ winSize.x / 6.f, 0.95f * winSize.y });
	m_restore_def_buttoon.setPosition({ winSize.x / 6.f, 0.95f * winSize.y });


	for (auto& itr : m_view_yPositions)
		itr = winSize.y / 2;
}



////////////////////////////////////////////////////////////////



void SettingsState::reloadWindowSettings()
{
	// FPS bars

	m_maxMenuFPS_bar.setSize({ winSize.x / 6, winSize.y / 24 });
	m_maxSimFPS_bar.setSize({ winSize.x / 6, winSize.y / 24 });

	m_maxMenuFPS_bar.setPosition({ 0.6f * winSize.x, 4 * winSize.y * 0.1f });
	m_maxSimFPS_bar.setPosition({ 0.6f * winSize.x, 5 * winSize.y * 0.1f });


	// vertical sync

	m_vSyncOn.setSize({ winSize.x / 12.f, winSize.y / 24.f });
	m_vSyncOff.setSize({ winSize.x / 12.f, winSize.y / 24.f });

	m_vSyncOn.setPosition({ 41.f * winSize.x / 60.f, 6.f * winSize.y * 0.1f });
	m_vSyncOff.setPosition({ 41.f * winSize.x / 60.f, 6.f * winSize.y * 0.1f });



	// background brightness level

	m_bright_lvl.setSize({ winSize.x / 6.f, winSize.y / 24.f });
	m_bright_lvl.setButtonRadius(winSize.y / 49);
	m_bright_lvl.setPosition({ 41.f * winSize.x / 60.f, 7.f * winSize.y * 0.1f });


	// window size dropdown list

	m_windowSize_drl.getSelected()->setSize({ winSize.x / 6.f, winSize.y / 24.f });
	m_windowSize_drl.getSelected()->setPosition({ 41.f * winSize.x / 60.f, 8.f * winSize.y * 0.1f });

	for (auto& itr : *m_windowSize_drl.getMembers())
		itr->setSize({ winSize.x / 6.f, winSize.y / 24.f });

	m_windowSize_drl.updateMembersPosition();



	// GUI accessories

	m_WS_accessories.at(0)->setSize(winSize.y / 24.f, winSize.y / 24.f);
	m_WS_accessories.at(1)->setSize(winSize.y / 24.f, winSize.y / 24.f);
	m_WS_accessories.at(2)->setSize(winSize.x / 6.f, winSize.y / 24.f);
	m_WS_accessories.at(3)->setSize(winSize.y / 24.f, winSize.y / 24.f);

	m_WS_accessories.at(4)->setSize(winSize.y / 24.f, winSize.y / 24.f);
	m_WS_accessories.at(5)->setSize(winSize.y / 24.f, winSize.y / 24.f);
	m_WS_accessories.at(6)->setSize(winSize.x / 6.f, winSize.y / 24.f);
	m_WS_accessories.at(7)->setSize(winSize.y / 24.f, winSize.y / 24.f);

	m_WS_accessories.at(8)->setSize(winSize.x / 6.f, winSize.y / 24.f);
	m_WS_accessories.at(9)->setSize(winSize.x / 6.f, winSize.y / 24.f);
	m_WS_accessories.at(10)->setSize(winSize.x / 6.f, winSize.y / 24.f);


	m_WS_accessories.at(0)->setPosition(0.6f * winSize.x, 4 * winSize.y * 0.1f);
	m_WS_accessories.at(1)->setPosition(23.f * winSize.x / 30, 4 * winSize.y * 0.1f);
	m_WS_accessories.at(2)->setPosition(0.4f * winSize.x, 4 * winSize.y * 0.1f);
	m_WS_accessories.at(3)->setPosition(0.6f * winSize.x, 4 * winSize.y * 0.1f);

	m_WS_accessories.at(4)->setPosition(0.6f * winSize.x, 5 * winSize.y * 0.1f);
	m_WS_accessories.at(5)->setPosition(23.f * winSize.x / 30, 5 * winSize.y * 0.1f);
	m_WS_accessories.at(6)->setPosition(0.4f * winSize.x, 5 * winSize.y * 0.1f);
	m_WS_accessories.at(7)->setPosition(0.6f * winSize.x, 5 * winSize.y * 0.1f);

	m_WS_accessories.at(8)->setPosition(0.4f * winSize.x, 6 * winSize.y * 0.1f);
	m_WS_accessories.at(9)->setPosition(0.4f * winSize.x, 7 * winSize.y * 0.1f);
	m_WS_accessories.at(10)->setPosition(0.4f * winSize.x, 8 * winSize.y * 0.1f);
}



////////////////////////////////////////////////////////////////



void SettingsState::reloadAudioSettings()
{
	m_SFX_volume.setSize(winSize.x / 6.f, winSize.y / 24.f);
	m_SFX_volume.setButtonRadius(winSize.y / 49);
	m_SFX_volume.setPosition(winSize.x + 41.f * winSize.x / 64.f, 4.f * winSize.y * 0.1f);

	m_music_volume.setSize(winSize.x / 6.f, winSize.y / 24.f);
	m_music_volume.setButtonRadius(winSize.y / 49);
	m_music_volume.setPosition(winSize.x + 41.f * winSize.x / 64.f, 5.f * winSize.y * 0.1f);

	m_AS_accessories.at(0)->setSize(winSize.x / 6.f, winSize.y / 24.f);
	m_AS_accessories.at(1)->setSize(winSize.x / 6.f, winSize.y / 24.f);
	m_AS_accessories.at(2)->setSize(winSize.y / 24.f, winSize.y / 24.f);
	m_AS_accessories.at(3)->setSize(winSize.y / 24.f, winSize.y / 24.f);

	m_AS_accessories.at(0)->setPosition(1.4f * winSize.x, 4 * winSize.y * 0.1f);
	m_AS_accessories.at(1)->setPosition(1.4f * winSize.x, 5 * winSize.y * 0.1f);
	m_AS_accessories.at(2)->setPosition(winSize.x + 41.f * winSize.x / 64.f + winSize.x / 9.f, 4.f * winSize.y * 0.1f);
	m_AS_accessories.at(3)->setPosition(winSize.x + 41.f * winSize.x / 64.f + winSize.x / 9.f, 5.f * winSize.y * 0.1f);
}



////////////////////////////////////////////////////////////////



void SettingsState::reloadSimulationSettings()
{

}



////////////////////////////////////////////////////////////////



void SettingsState::reloadKeybindsSettings()
{

}



////////////////////////////////////////////////////////////////



void SettingsState::reloadCharacterSize()
{
	for (auto& itr : m_settings_types)
		itr->setCharacterSize(winSize.y / 32.f);

	m_apply_button.setCharacterSize(winSize.y / 32.f);
	m_restore_def_buttoon.setCharacterSize(winSize.y / 48.f);


	m_vSyncOn.setCharacterSize(winSize.y / 48);
	m_vSyncOff.setCharacterSize(winSize.y / 48);

	for (auto& itr : *m_windowSize_drl.getMembers())
		itr->setCharacterSize(winSize.y / 56);

	m_windowSize_drl.getSelected()->setCharacterSize(winSize.y / 48);

	m_WS_accessories.at(3)->setCharacterSize(winSize.y / 48);
	m_WS_accessories.at(7)->setCharacterSize(winSize.y / 48);

	m_WS_accessories.at(2)->setCharacterSize(winSize.y / 32);
	m_WS_accessories.at(6)->setCharacterSize(winSize.y / 32);
	m_WS_accessories.at(8)->setCharacterSize(winSize.y / 32);
	m_WS_accessories.at(9)->setCharacterSize(winSize.y / 32);
	m_WS_accessories.at(10)->setCharacterSize(winSize.y / 32);

	m_AS_accessories.at(0)->setCharacterSize(winSize.y / 32.f);
	m_AS_accessories.at(1)->setCharacterSize(winSize.y / 32.f);
}





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





void SettingsState::updateEvents(const MousePosition& mousePosition, float dt)
{
	if (m_view_moving)
	{
		m_view_moving = ke::SmoothViewMove(view, sf::Vector2f(viewSize.x * (0.5f + m_selected_type_id), m_view_yPositions[m_selected_type_id]), sf::Vector2f(viewSize.x * (0.5f + m_last_sel_type_id), m_view_yPositions[m_last_sel_type_id]), 3 * viewSize.x * abs(m_last_sel_type_id - m_selected_type_id), dt);
		m_slider.updateSliderPosition(view);
	}
	else if (m_view_scrolling)
	{
		m_view_scrolling = ke::SmoothViewMove(view, { view->getCenter().x, m_view_next_pos }, { view->getCenter().x, m_view_last_pos }, 384, dt);
		m_slider.updateSliderPosition(view);
	}


	this->genSettColorUpdate(mousePosition, dt);
	this->winSettColorUpdate(mousePosition, dt);
	this->audSettColorUpdate(mousePosition, dt);


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
			default:
				ke::throw_error("SettingsState::updateEvents() -> state quitting", "State not found", "ERROR");
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
			case STATE::MAIN_MENU:
				states->back() = std::make_unique<MainMenu>(window, view, false);
				break;
			default:
				ke::throw_error("SettingsState::updateEvents() -> state quitting", "State not found", "ERROR");
				break;
			}

			states->back()->InitState();
			return;
		}
	}
	else
	{
		m_outro_clock.restart();
		ke::SmoothColorChange(&m_stateMask, true, sf::Color::Transparent, sf::Color::Black, m_sm_color, 128, dt);
	}
}





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





void SettingsState::updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event)
{
	// Quitting

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



	// view scroll

	if (event.type == sf::Event::MouseWheelScrolled)
	{
		if (event.mouseWheelScroll.delta > 0)
		{
			m_view_last_pos = view->getCenter().y;
			m_view_next_pos -= view->getCenter().y * 0.1;

			m_view_scrolling = true;

			//view->move(0, -viewSize.y * 0.05);

			switch (m_selected_type_id)
			{
			case 0:
				ke::varGuard(m_view_next_pos, winSize.y / 2, winSize.y * 0.6f);
				break;
			case 1:
				ke::varGuard(m_view_next_pos, winSize.y / 2, winSize.y * 0.5f);
				break;
			case 2:
				ke::varGuard(m_view_next_pos, winSize.y / 2, winSize.y * 0.5f);
				break;
			case 3:
				ke::varGuard(m_view_next_pos, winSize.y / 2, winSize.y * 0.5f);
				break;

			default:
				ke::varGuard(m_view_next_pos, winSize.y / 2, winSize.y * 0.5f);
				break;
			}
		}
		else if (event.mouseWheelScroll.delta < 0)
		{
			//view->move(0, viewSize.y * 0.05);
			m_view_last_pos = view->getCenter().y;
			m_view_next_pos += view->getCenter().y * 0.1;

			switch (m_selected_type_id)
			{
			case 0:
				ke::varGuard(m_view_next_pos, winSize.y / 2, winSize.y * 0.6f);
				break;
			case 1:
				ke::varGuard(m_view_next_pos, winSize.y / 2, winSize.y * 0.5f);
				break;
			case 2:
				ke::varGuard(m_view_next_pos, winSize.y / 2, winSize.y * 0.5f);
				break;
			case 3:
				ke::varGuard(m_view_next_pos, winSize.y / 2, winSize.y * 0.5f);
				break;

			default:
				ke::varGuard(m_view_next_pos, winSize.y / 2, winSize.y * 0.5f);
				break;
			}

			m_view_scrolling = true;

			/*switch (m_selected_type_id)
			{
			case 0:
				if (view->getCenter().y > window->getSize().y * 0.6f)
				{
					view->setCenter(view->getCenter().x, window->getSize().y * 0.6f);
					m_view_scrolling = false;
				}
				break;
			case 1:
				if (view->getCenter().y > window->getSize().y * 0.5f)
				{
					view->setCenter(view->getCenter().x, window->getSize().y * 0.5f);
					m_view_scrolling = false;
				}
				break;
			case 2:
				if (view->getCenter().y > window->getSize().y * 0.5f)
				{
					view->setCenter(view->getCenter().x, window->getSize().y * 0.5f);
					m_view_scrolling = false;
				}
				break;
			case 3:
				if (view->getCenter().y > window->getSize().y * 0.5f)
				{
					view->setCenter(view->getCenter().x, window->getSize().y * 0.5f);
					m_view_scrolling = false;
				}
				break;

			default:
				if (view->getCenter().y > window->getSize().y * 0.5f)
				{
					view->setCenter(view->getCenter().x, window->getSize().y * 0.5f);
					m_view_scrolling = false;
				}
				break;*/
		}

			//if (view->getCenter().y > window->getSize().y * 0.6f)
				//view->setCenter(view->getCenter().x, window->getSize().y * 0.6f);


		for (auto& itr : *m_windowSize_drl.getMembers())
			itr->update({ 0, 0 }, event, sf::Mouse::Left, nullptr);
	}



	


	// rendering update

	//if (m_view_moving)
	//{
	//	const float view_shift = 100;


	//	m_apply_button.setActiveStatus(!ke::isOutsideTheView(&m_apply_button, view, sf::Vector2f(view_shift, view_shift)));
	//	m_restore_def_buttoon.setActiveStatus(!ke::isOutsideTheView(&m_restore_def_buttoon, view, sf::Vector2f(view_shift, view_shift)));


	//	// window settings

	//	m_maxMenuFPS_bar.setActiveStatus(!ke::isOutsideTheView(&m_maxMenuFPS_bar, view, sf::Vector2f(view_shift, view_shift)));
	//	m_maxSimFPS_bar.setActiveStatus(!ke::isOutsideTheView(&m_maxSimFPS_bar, view, sf::Vector2f(view_shift, view_shift)));

	//	if (ke::isOutsideTheView(m_WS_accessories.front().get(), view, sf::Vector2f(view_shift, view_shift)))
	//		for (auto& itr : m_WS_accessories)
	//			itr->setActiveStatus(false);
	//	else
	//		for (auto& itr : m_WS_accessories)
	//			itr->setActiveStatus(true);

	//	m_vSyncOn.setActiveStatus(!ke::isOutsideTheView(&m_vSyncOn, view, sf::Vector2f(view_shift, view_shift)));
	//	m_vSyncOff.setActiveStatus(!ke::isOutsideTheView(&m_vSyncOff, view, sf::Vector2f(view_shift, view_shift)));

	//	m_bright_lvl.setActiveStatus(!ke::isOutsideTheView(&m_bright_lvl, view, sf::Vector2f(view_shift, view_shift)));

	//	m_windowSize_drl.setActiveStatus(!ke::isOutsideTheView(m_windowSize_drl.getSelected(), view, sf::Vector2f(view_shift, view_shift)));


	//	// audio settings

	//	m_SFX_volume.setActiveStatus(!ke::isOutsideTheView(&m_SFX_volume, view, sf::Vector2f(view_shift, view_shift)));
	//	m_music_volume.setActiveStatus(!ke::isOutsideTheView(&m_music_volume, view, sf::Vector2f(view_shift, view_shift)));

	//	if (ke::isOutsideTheView(m_AS_accessories.front().get(), view, sf::Vector2f(view_shift, view_shift)))
	//		for (auto& itr : m_AS_accessories)
	//			itr->setActiveStatus(false);
	//	else
	//		for (auto& itr : m_AS_accessories)
	//			itr->setActiveStatus(true);
	//}


	// settings types

	if (mousePosition.byView.y > 0 && mousePosition.byView.y < winSize.y / 4.f)
	{
		int i = 0;
		for (auto itr = m_settings_types.begin(), eoi = m_settings_types.end(); itr != eoi; ++itr, i++)
		{
			if ((*itr)->isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
			{
				sfx.play("click");

				m_view_scrolling = false;

				if (m_selected_type_id == i)
				{
					view->setCenter(view->getCenter().x, window->getSize().y / 2);
				}
				else
				{
					m_selected_type_itr = itr;
					m_last_sel_type_id = m_selected_type_id;
					m_selected_type_id = i;
					m_view_yPositions[m_last_sel_type_id] = view->getCenter().y;
					m_view_moving = true;

					switch (m_selected_type_id)
					{
					case 0: m_slider.setFieldHeight(winSize.y * 1.1f); break;
					case 1: m_slider.setFieldHeight(winSize.y * 1.0f); break;
					case 2: m_slider.setFieldHeight(winSize.y * 1.0f); break;
					case 3: m_slider.setFieldHeight(winSize.y * 1.0f); break;

					default:
						m_slider.setFieldHeight(winSize.y * 1.1f); break;
					}
				}
			}
		}

		if (m_back_button.isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
		{
			sfx.play("click");

			p_quitCode = StateQuitCode::STATE_QUIT;
			m_next_state = STATE::MAIN_MENU;
		}
	}



	// slider

	if (mousePosition.byWindow.x > winSize.x * 0.8f)
		m_slider.update(mousePosition.byWindow, event, sf::Mouse::Left, view);
	else
		m_slider.updateSliderPosition(view);



	// apply and restore defaults buttons

	if (mousePosition.byView.y > winSize.y * 0.9f && mousePosition.byView.y < winSize.y)
	{
		// apply button
		if (m_window_size_changed && m_apply_button.isClicked(sf::Mouse::Left, mousePosition.byView, event))
		{
			sfx.play("click");

			sf::Vector2u new_win_size(1920, 1080);

			switch (m_windowSize_drl.getSelectedID())
			{
			case 0: new_win_size = sf::Vector2u(1024, 576);	 AppSettings::setDefaultWindowSize({ 1024, 576 });  AppSettings::setWindowStyle(sf::Style::None); break;
			case 1: new_win_size = sf::Vector2u(1280, 720);	 AppSettings::setDefaultWindowSize({ 1280, 720 });  AppSettings::setWindowStyle(sf::Style::None); break;
			case 2: new_win_size = sf::Vector2u(1366, 768);	 AppSettings::setDefaultWindowSize({ 1366, 768 });  AppSettings::setWindowStyle(sf::Style::None); break;
			case 3: new_win_size = sf::Vector2u(1600, 900);	 AppSettings::setDefaultWindowSize({ 1600, 900 });  AppSettings::setWindowStyle(sf::Style::None); break;
			case 4: new_win_size = sf::Vector2u(1920, 1080); AppSettings::setDefaultWindowSize({ 1920, 1080 }); AppSettings::setWindowStyle(sf::Style::None); break;
			case 5: new_win_size = sf::Vector2u(1920, 1080); AppSettings::setDefaultWindowSize({ 1920, 1080 }); AppSettings::setWindowStyle(sf::Style::Fullscreen); break;
			default:
				break;
			}

			window->create(sf::VideoMode(new_win_size.x, new_win_size.y), "Completely Inacuarate Space Simulator", (m_windowSize_drl.getSelectedID() != 5) ? (sf::Style::None) : (sf::Style::Fullscreen));
			winSize = sf::Vector2f(new_win_size);
			viewSize = sf::Vector2f(new_win_size);
			window->setFramerateLimit(AppSettings::MaxMenuFPS());

			for (auto& itr : *states)
				itr->reloadState();

			m_start_window_size = m_windowSize_drl.getSelectedID();
		}



		// restore defaults butotn

		if (m_restore_def_buttoon.isClicked(sf::Mouse::Left, mousePosition.byView, event))
		{
			sfx.play("click");

			AppSettings::RestoreDefaults();
			AppSettings::Save();

			m_maxMenuFPS_bar.setPointCount(AppSettings::MaxMenuFPS());
			m_maxSimFPS_bar.setPointCount(AppSettings::MaxSimulationFPS());

			m_vSyncStatus = AppSettings::vSync();

			if (m_vSyncStatus)
			{
				m_vSyncOn.setFillColor(sf::Color(255, 255, 255, 192));
				m_vSyncOn.setTextStyle(sf::Text::Bold);
				m_vSyncOff.setTextStyle(sf::Text::Regular);
			}
			else
			{
				m_vSyncOff.setFillColor(sf::Color(255, 255, 255, 192));
				m_vSyncOff.setTextStyle(sf::Text::Bold);
				m_vSyncOn.setTextStyle(sf::Text::Regular);
			}


			m_WS_accessories.at(3)->setText(std::to_wstring(static_cast<unsigned int>(m_maxMenuFPS_bar.getPointCount())));

			if (m_maxMenuFPS_bar.getPointCount() > 30)
				m_WS_accessories.at(3)->setTextColor(sf::Color::Black);
			else
				m_WS_accessories.at(3)->setTextColor(sf::Color::White);


			m_WS_accessories.at(7)->setText(std::to_wstring(static_cast<unsigned int>(m_maxSimFPS_bar.getPointCount())));

			if (m_maxSimFPS_bar.getPointCount() > 30)
				m_WS_accessories.at(7)->setTextColor(sf::Color::Black);
			else
				m_WS_accessories.at(7)->setTextColor(sf::Color::White);



			m_bright_lvl.setPercent(AppSettings::BackgroundBrightness());
			m_backgroundMask.setFillColor(sf::Color(0, 0, 0, 255 - 255 * m_bright_lvl.getPercent() * 0.01f));


			if (AppSettings::DefaultWindowSize() == sf::Vector2f(1024, 576)) m_windowSize_drl.setMemberAsActive(0);
			if (AppSettings::DefaultWindowSize() == sf::Vector2f(1280, 720)) m_windowSize_drl.setMemberAsActive(1);
			if (AppSettings::DefaultWindowSize() == sf::Vector2f(1366, 768)) m_windowSize_drl.setMemberAsActive(2);
			if (AppSettings::DefaultWindowSize() == sf::Vector2f(1600, 900)) m_windowSize_drl.setMemberAsActive(3);
			if (AppSettings::DefaultWindowSize() == sf::Vector2f(1920, 1080)) m_windowSize_drl.setMemberAsActive(4);
			if (AppSettings::DefaultWindowSize() == sf::Vector2f(1920, 1080)) m_windowSize_drl.setMemberAsActive(5);
		}
	}



	// window settings

	if (mousePosition.byView.x > winSize.x * 0.55f && mousePosition.byView.x < winSize.x * 0.8f)
	{
		// FPS bars

		if (mousePosition.byView.y > winSize.y * 0.3f && mousePosition.byView.y < winSize.y * 0.6f)
		{
			// menu FPS

			if (m_maxMenuFPS_bar.isClicked(sf::Mouse::Left, mousePosition.byView, event) || m_WS_accessories.at(1)->isClicked(sf::Mouse::Left, mousePosition.byView, event))
			{
				m_maxMenuFPS_bar.addPoints(30);
				m_WS_accessories.at(3)->setText(std::to_wstring(static_cast<unsigned int>(m_maxMenuFPS_bar.getPointCount())));

				if (m_maxMenuFPS_bar.getPointCount() > 30)
					m_WS_accessories.at(3)->setTextColor(sf::Color::Black);
			}
			else if (m_maxMenuFPS_bar.isClicked(sf::Mouse::Right, mousePosition.byView, event) || m_WS_accessories.at(0)->isClicked(sf::Mouse::Left, mousePosition.byView, event))
			{
				m_maxMenuFPS_bar.subtractPoints(30);
				m_WS_accessories.at(3)->setText(std::to_wstring(static_cast<unsigned int>(m_maxMenuFPS_bar.getPointCount())));

				if (m_maxMenuFPS_bar.getPointCount() <= 31)
					m_WS_accessories.at(3)->setTextColor(sf::Color::White);
			}


			// simulation FPS

			if (m_maxSimFPS_bar.isClicked(sf::Mouse::Left, mousePosition.byView, event) || m_WS_accessories.at(5)->isClicked(sf::Mouse::Left, mousePosition.byView, event))
			{
				m_maxSimFPS_bar.addPoints(120);
				if (m_maxSimFPS_bar.getPointCount() < 960.f)
					m_WS_accessories.at(7)->setText(std::to_wstring(static_cast<unsigned int>(m_maxSimFPS_bar.getPointCount())));
				else
					m_WS_accessories.at(7)->setText(L"Unlimited");


				if (m_maxSimFPS_bar.getPointCount() > 120)
					m_WS_accessories.at(7)->setTextColor(sf::Color::Black);
			}
			else if (m_maxSimFPS_bar.isClicked(sf::Mouse::Right, mousePosition.byView, event) || m_WS_accessories.at(4)->isClicked(sf::Mouse::Left, mousePosition.byView, event))
			{
				m_maxSimFPS_bar.subtractPoints(120);
				m_WS_accessories.at(7)->setText(std::to_wstring(static_cast<unsigned int>(m_maxSimFPS_bar.getPointCount())));

				if (m_maxSimFPS_bar.getPointCount() <= 121)
					m_WS_accessories.at(7)->setTextColor(sf::Color::White);
			}
		}


		if (mousePosition.byView.y > winSize.y * 0.55f && mousePosition.byView.y < winSize.y * 0.65f)
		{
			if (m_vSyncStatus)
			{
				if (m_vSyncOff.isClicked(sf::Mouse::Left, mousePosition.byView, event))
				{
					m_vSyncStatus = !m_vSyncStatus;

					m_vSyncOff.setFillColor(sf::Color(255, 255, 255, 192));
					m_vSyncOff.setTextStyle(sf::Text::Bold);
					m_vSyncOn.setTextStyle(sf::Text::Regular);
				}
			}
			else
			{
				if (m_vSyncOn.isClicked(sf::Mouse::Left, mousePosition.byView, event))
				{
					m_vSyncStatus = !m_vSyncStatus;

					m_vSyncOn.setFillColor(sf::Color(255, 255, 255, 192));
					m_vSyncOn.setTextStyle(sf::Text::Bold);
					m_vSyncOff.setTextStyle(sf::Text::Regular);
				}
			}
		}


		if ((mousePosition.byView.y > winSize.y * 0.65f && mousePosition.byView.y < winSize.y * 0.75f) || m_bright_lvl.isHolded())
			if (m_bright_lvl.update(mousePosition.byView, event, sf::Mouse::Left, nullptr))
				m_backgroundMask.setFillColor(sf::Color(0, 0, 0, 255 - 255 * m_bright_lvl.getPercent() * 0.01f));


		if (mousePosition.byView.y > winSize.y * 0.75f)
		{
			if (m_windowSize_drl.update(mousePosition.byView, event, sf::Mouse::Left, nullptr))
			{
				m_current_window_size = m_windowSize_drl.getSelectedID();
				m_window_size_changed = m_current_window_size != m_start_window_size;
			}
		}
	}



	// audio settings

	if (mousePosition.byView.x > winSize.x * 1.5f && mousePosition.byView.x < winSize.x * 1.8f)
	{
		if ((mousePosition.byView.y > winSize.y * 0.35f && mousePosition.byView.y < winSize.y * 0.5f) || m_SFX_volume.isHolded())
			if (m_SFX_volume.update(mousePosition.byView, event, sf::Mouse::Left, nullptr))
				sfx.setVolume(m_SFX_volume.getPercent(), "Quack");

		if ((mousePosition.byView.y > winSize.y * 0.45f && mousePosition.byView.y < winSize.y * 0.55f) || m_music_volume.isHolded())
			if (m_music_volume.update(mousePosition.byView, event, sf::Mouse::Left, nullptr))
				music.setVolume(m_music_volume.getPercent());


		if (m_AS_accessories.at(2)->isClicked(sf::Mouse::Left, mousePosition.byView, event))
			sfx.play("Quack");

		/*else if (m_AS_accessories.at(3)->isClicked(sf::Mouse::Left, mousePosition.byView, event))
		{
			if (m_test_music.playing())
				m_test_music.skip();

			else
			{
				m_test_music.setVolume(m_music_volume.getPercent());
				m_test_music.play();
			}
		}*/
	}
}





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





void SettingsState::genSettColorUpdate(const MousePosition& mousePosition, const float dt)
{
	auto color_itr = m_st_fcolors.begin();


	// settings types SCC

	for (auto& itr : m_settings_types)
	{
		ke::SmoothTextColorChange(itr.get(), itr->isInvaded(mousePosition.byWindow) || itr.get() == m_selected_type_itr->get(), sf::Color::White, sf::Color(255, 255, 255, 128), *color_itr, 256, dt);
		color_itr++;
	}


	// back button

	ke::SmoothColorChange(&m_back_button, m_back_button.isInvaded(mousePosition.byWindow), sf::Color::White, sf::Color(255, 255, 255, 128), *color_itr, 255, dt);


	// slider

	ke::SmoothColorChange(m_slider.getSlider(), m_slider.isInvaded(mousePosition.byWindow) || m_slider.isHolded(), sf::Color::White, sf::Color(192, 192, 192, 128), m_slider_colorf, 256, dt);

	// apply and restore defaults SCC

	ke::SmoothColorChange(&m_restore_def_buttoon, m_restore_def_buttoon.isInvaded(mousePosition.byView), sf::Color(32, 32, 32, 255), sf::Color(16, 16, 16, 255), m_settings_manip_colors[2], 128, dt);
	ke::SmoothTextColorChange(&m_restore_def_buttoon, m_restore_def_buttoon.isInvaded(mousePosition.byView), sf::Color::White, sf::Color(192, 192, 192, 255), m_settings_manip_colors[3], 128, dt);

	if (m_window_size_changed)
	{
		ke::SmoothColorChange(&m_apply_button, m_apply_button.isInvaded(mousePosition.byView), sf::Color(32, 32, 32, 255), sf::Color(16, 16, 16, 255), m_settings_manip_colors[0], 128, dt);
		ke::SmoothTextColorChange(&m_apply_button, m_apply_button.isInvaded(mousePosition.byView), sf::Color::White, sf::Color(192, 192, 192, 255), m_settings_manip_colors[1], 128, dt);
	}
	else
	{
		ke::SmoothColorChange(&m_apply_button, true, sf::Color(16, 16, 16, 255), sf::Color(32, 32, 32, 255), m_settings_manip_colors[0], 128, dt);
	}
}





void SettingsState::winSettColorUpdate(const MousePosition& mousePosition, const float dt)
{
	// window settings and GUI accessores SCC

	auto ws_color_itr = m_windowSettings_colors.begin();
	auto gui_acc_itr = m_WS_accessories.begin();

	ke::SmoothColorChange(m_maxMenuFPS_bar.getBar(), m_maxMenuFPS_bar.isInvaded(mousePosition.byView) || (*(gui_acc_itr))->isInvaded(mousePosition.byView) || (*(gui_acc_itr + 1))->isInvaded(mousePosition.byView), sf::Color::White, sf::Color(255, 255, 255, 160), *ws_color_itr, 256, dt); ++ws_color_itr;
	ke::SmoothColorChange(gui_acc_itr->get(), (*gui_acc_itr)->isInvaded(mousePosition.byView) || m_maxMenuFPS_bar.isInvaded(mousePosition.byView), sf::Color::White, sf::Color(255, 255, 255, 160), *ws_color_itr, 256, dt); ++ws_color_itr; ++gui_acc_itr;
	ke::SmoothColorChange(gui_acc_itr->get(), (*gui_acc_itr)->isInvaded(mousePosition.byView) || m_maxMenuFPS_bar.isInvaded(mousePosition.byView), sf::Color::White, sf::Color(255, 255, 255, 160), *ws_color_itr, 256, dt); ++ws_color_itr; ++gui_acc_itr;
	ke::SmoothTextColorChange(gui_acc_itr->get(), (*gui_acc_itr)->isInvaded(mousePosition.byView) || m_maxMenuFPS_bar.isInvaded(mousePosition.byView), sf::Color::White, sf::Color(255, 255, 255, 160), *ws_color_itr, 256, dt); ++ws_color_itr; gui_acc_itr += 2;

	ke::SmoothColorChange(m_maxSimFPS_bar.getBar(), m_maxSimFPS_bar.isInvaded(mousePosition.byView) || (*(gui_acc_itr))->isInvaded(mousePosition.byView) || (*(gui_acc_itr + 1))->isInvaded(mousePosition.byView), sf::Color::White, sf::Color(255, 255, 255, 160), *ws_color_itr, 256, dt); ++ws_color_itr;
	ke::SmoothColorChange(gui_acc_itr->get(), (*gui_acc_itr)->isInvaded(mousePosition.byView) || m_maxSimFPS_bar.isInvaded(mousePosition.byView), sf::Color::White, sf::Color(255, 255, 255, 160), *ws_color_itr, 256, dt); ++ws_color_itr; ++gui_acc_itr;
	ke::SmoothColorChange(gui_acc_itr->get(), (*gui_acc_itr)->isInvaded(mousePosition.byView) || m_maxSimFPS_bar.isInvaded(mousePosition.byView), sf::Color::White, sf::Color(255, 255, 255, 160), *ws_color_itr, 256, dt); ++ws_color_itr; ++gui_acc_itr;
	ke::SmoothTextColorChange(gui_acc_itr->get(), (*gui_acc_itr)->isInvaded(mousePosition.byView) || m_maxSimFPS_bar.isInvaded(mousePosition.byView), sf::Color::White, sf::Color(255, 255, 255, 160), *ws_color_itr, 256, dt); ++ws_color_itr; gui_acc_itr += 2;


	ke::SmoothColorChange(&m_vSyncOn, m_vSyncOn.isInvaded(mousePosition.byView), sf::Color::White, sf::Color(255, 255, 255, (m_vSyncStatus) ? 192 : 96), *ws_color_itr, 256, dt); ++ws_color_itr;
	ke::SmoothColorChange(&m_vSyncOff, m_vSyncOff.isInvaded(mousePosition.byView), sf::Color::White, sf::Color(255, 255, 255, (m_vSyncStatus) ? 96 : 192), *ws_color_itr, 256, dt); ++ws_color_itr;
	ke::SmoothTextColorChange(gui_acc_itr->get(), (*gui_acc_itr)->isInvaded(mousePosition.byView) || m_vSyncOff.isInvaded(mousePosition.byView) || m_vSyncOn.isInvaded(mousePosition.byView), sf::Color::White, sf::Color(255, 255, 255, 160), *ws_color_itr, 256, dt); ++ws_color_itr; ++gui_acc_itr;


	ke::SmoothColorChange(&m_bright_lvl, m_bright_lvl.isInvaded(mousePosition.byView) || m_bright_lvl.isHolded(), sf::Color(96, 96, 96, 255), sf::Color(64, 64, 64, 255), *ws_color_itr, 256, dt); ++ws_color_itr;
	ke::SmoothColorChange(m_bright_lvl.getColorButton(), m_bright_lvl.isButtonInvaded(mousePosition.byView) || m_bright_lvl.isHolded(), sf::Color::White, sf::Color(160, 160, 160, 255), *ws_color_itr, 256, dt); ++ws_color_itr;
	ke::SmoothTextColorChange(gui_acc_itr->get(), (*gui_acc_itr)->isInvaded(mousePosition.byView) || m_bright_lvl.isInvaded(mousePosition.byView) || m_bright_lvl.isHolded(), sf::Color::White, sf::Color(255, 255, 255, 160), *ws_color_itr, 256, dt); ++ws_color_itr; ++gui_acc_itr;


	ke::SmoothColorChange(m_windowSize_drl.getSelected(), m_windowSize_drl.getSelected()->isInvaded(mousePosition.byView) || m_windowSize_drl.Expanded(), sf::Color(64, 64, 64, 255), sf::Color(32, 32, 32, 255), *ws_color_itr, 256, dt); ++ws_color_itr;
	ke::SmoothOutlineColorChange(m_windowSize_drl.getSelected(), m_windowSize_drl.getSelected()->isInvaded(mousePosition.byView) || m_windowSize_drl.Expanded(), sf::Color::White, sf::Color(255, 255, 255, 192), *ws_color_itr, 256, dt); ++ws_color_itr;
	ke::SmoothTextColorChange(m_windowSize_drl.getSelected(), m_windowSize_drl.Expanded(), sf::Color::White, sf::Color(255, 255, 255, 192), *ws_color_itr, 256, dt); ++ws_color_itr;

	for (auto itr = m_windowSize_drl.getMembers()->begin(), eoi = m_windowSize_drl.getMembers()->end(); itr != eoi; ++itr)
	{
		ke::SmoothColorChange(itr->get(), (*itr)->isInvaded(mousePosition.byView), sf::Color(32, 32, 32, 255), sf::Color(16, 16, 16, 255), *ws_color_itr, 256, dt);
		ke::SmoothTextColorChange(itr->get(), (*itr)->isInvaded(mousePosition.byView), sf::Color::White, sf::Color(160, 160, 160, 255), *ws_color_itr, 512, dt);
		++ws_color_itr;
	}

	ke::SmoothTextColorChange(gui_acc_itr->get(), (*gui_acc_itr)->isInvaded(mousePosition.byView) || m_windowSize_drl.Expanded() || m_windowSize_drl.getSelected()->isInvaded(mousePosition.byView), sf::Color::White, sf::Color(255, 255, 255, 160), *ws_color_itr, 384, dt); //++ws_color_itr; //++gui_acc_itr;
}





void SettingsState::audSettColorUpdate(const MousePosition& mousePosition, const float dt)
{
	auto as_color_itr = m_audio_colors.begin();
	auto audio_acc_itr = m_AS_accessories.begin();

	ke::SmoothColorChange(&m_SFX_volume, m_SFX_volume.isInvaded(mousePosition.byView) || m_SFX_volume.isHolded(), sf::Color(96, 96, 96, 255), sf::Color(64, 64, 64, 255), *as_color_itr, 256, dt); ++as_color_itr;
	ke::SmoothColorChange(m_SFX_volume.getColorButton(), m_SFX_volume.isButtonInvaded(mousePosition.byView) || m_SFX_volume.isHolded(), sf::Color::White, sf::Color(160, 160, 160, 255), *as_color_itr, 256, dt); ++as_color_itr;
	ke::SmoothTextColorChange(audio_acc_itr->get(), (*audio_acc_itr)->isInvaded(mousePosition.byView) || m_SFX_volume.isInvaded(mousePosition.byView) || m_SFX_volume.isHolded(), sf::Color::White, sf::Color(255, 255, 255, 160), *as_color_itr, 256, dt); ++as_color_itr; ++audio_acc_itr;

	ke::SmoothColorChange(&m_music_volume, m_music_volume.isInvaded(mousePosition.byView) || m_music_volume.isHolded(), sf::Color(96, 96, 96, 255), sf::Color(64, 64, 64, 255), *as_color_itr, 256, dt); ++as_color_itr;
	ke::SmoothColorChange(m_music_volume.getColorButton(), m_music_volume.isButtonInvaded(mousePosition.byView) || m_music_volume.isHolded(), sf::Color::White, sf::Color(160, 160, 160, 255), *as_color_itr, 256, dt); ++as_color_itr;
	ke::SmoothTextColorChange(audio_acc_itr->get(), (*audio_acc_itr)->isInvaded(mousePosition.byView) || m_music_volume.isInvaded(mousePosition.byView) || m_music_volume.isHolded(), sf::Color::White, sf::Color(255, 255, 255, 160), *as_color_itr, 256, dt); ++as_color_itr; ++audio_acc_itr;

	ke::SmoothColorChange(audio_acc_itr->get(), (*audio_acc_itr)->isInvaded(mousePosition.byView), sf::Color::White, sf::Color(255, 255, 255, 160), *as_color_itr, 256, dt); ++as_color_itr; ++audio_acc_itr;
	ke::SmoothColorChange(audio_acc_itr->get(), (*audio_acc_itr)->isInvaded(mousePosition.byView), sf::Color::White, sf::Color(255, 255, 255, 160), *as_color_itr, 256, dt);
}





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





void SettingsState::renderBackground()
{
	//m_stateBackground.render(window);
	m_backgroundMask.render(window);
}





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





void SettingsState::renderByView()
{
	m_maxMenuFPS_bar.render(window);
	m_maxSimFPS_bar.render(window);

	for (auto& itr : m_WS_accessories)
		itr->render(window);

	m_vSyncOn.render(window);
	m_vSyncOff.render(window);

	m_bright_lvl.render(window);

	m_windowSize_drl.render(window);

	m_apply_button.render(window);
	m_restore_def_buttoon.render(window);


	m_SFX_volume.render(window);
	m_music_volume.render(window);

	for (auto& itr : m_AS_accessories)
		itr->render(window);
}





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





void SettingsState::renderByWindow()
{
	for (auto& itr : m_settings_types)
		itr->render(window);

	m_back_button.render(window);
	m_separation_bar.render(window);

	m_slider.render(window);

	m_stateMask.render(window);
}





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





StateQuitCode SettingsState::Quit()
{
	return p_quitCode;
}