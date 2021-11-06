#include "SimulationState.hpp"

SimulationState::SimulationState(sf::RenderWindow* sf_window, sf::View* sf_view)
	: State(sf_window, sf_view, SIMULATION)
	, m_next_state(NextState::NONE)
	, m_deltaTime(0.0001)
	, m_outro_time(0)
	, m_running(false)
	, m_time_scale(100000)
	, m_simulation_speed(1.f)
	, m_space_scale(0.0000001)
	, m_star_scale(100)
	, m_planet_scale(500)
	, m_shader_scale(1.0)
	, m_brightness_scale(1.0)
	, m_text_entered(false)
	, m_object_buffer_ready(false)
{
	m_stateMask.create(winSize, { 0, 0 }, ke::Origin::LEFT_TOP, {}, {}, {}, sf::Color::Black);
	m_sm_color.setColor(sf::Color::Black);

	m_overlayMask.create(winSize, { 0, 0 }, ke::Origin::LEFT_TOP, {}, {}, {}, sf::Color::Transparent);
	m_om_color.setColor(sf::Color::Transparent);

	m_shaderMask.create(winSize, { 0, 0 }, ke::Origin::LEFT_TOP, {}, {}, {}, sf::Color::Transparent);

	view->setSize(sf::Vector2f(winSize * 10.f));
	view->setCenter(sf::Vector2f(0, 0));


	m_VDController.assign(&m_symbols, &m_values, &m_units, &m_modifiers, &m_object_name, &m_objects);
	m_VDController.assignScale(m_space_scale, m_planet_scale, m_star_scale);

	m_TimeController.assign(&m_time_menagers);

	m_ObjController.assing(&m_objects, &m_orbit_preview, &m_distance_preview, &m_placed_object);
	m_ObjController.assignScale(m_space_scale, m_planet_scale, m_star_scale, m_shader_scale, m_brightness_scale);

	m_StateControlPanel.assign(&m_state_controllers, &m_upperState, &m_quitOverlay);

	m_ObjectLibraryOverlay = std::make_unique<ObjectLibraryOverlay>();
	m_ObjectLibraryOverlay->assign(window);
	m_ObjectLibraryOverlay->initUI();
	m_ObjectLibraryOverlay->loadObjects();
	

	//m_objIconPanel.assign(&m_iconUI, &m_object_icons);


	m_placed_object.create(100, { 1000, 1000 }, ke::Origin::MIDDLE_MIDDLE, L"", 0, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent);


	/*ke::FileStream fstr;
	fstr.createFile("Data/IconLayouts/test1.slo");
	fstr.open("Data/IconLayouts/test1.slo", std::ios::binary | std::ios::out);

	for (size_t i = 0; i < 16; i++)
	{
		fstr.binWrite((std::string)("TestName1."));
		fstr.binWrite(PLANET);
		fstr.binWrite((double)i * 1e24);
		fstr.binWrite((double)i * 100000);
		fstr.binWrite((std::string)"Textures/Unused/Galaxy1.png");
		fstr.binWrite((std::string)"Textures/Unused/Galaxy1.png");
	}

	FileStorage::Get().linked_icon_layouts_files["test1"] = "Data/IconLayouts/test1.slo";*/

	//m_starShader.loadFromFile("Textures/Shaders/star_shader.frag", sf::Shader::Fragment);
	//m_starShader.setUniform("position", sf::Glsl::Vec2(0, 0));
	//m_starShader.setUniform("basic_a", 1.f);
	//m_test_shader.setUniform("size", 500.f);

	//for (auto& itr : m_object_icons)
		//std::cout << itr->object_class() << '\n';
}


SimulationState::~SimulationState()
{
	view->setSize(winSize);
}



void SimulationState::InitState()
{
	//ke::Button::create(,,);

	m_view_holding.setView(view);

	this->InitSpaceObjects();
	this->InitBackground();
	this->InitTopGUI();
	this->InitTimeGUI();
	this->InitObjDataGUI();

	for (auto& itr : m_project_menagers)
	{
		itr->setOutlineColor(sf::Color::White);
		itr->setOutlineThickness(1);
	}

	for (auto& itr : m_state_controllers)
	{
		itr->setOutlineColor(sf::Color::White);
		itr->setOutlineThickness(1);
	}

	/*for (auto& itr : m_time_menagers)
	{
		itr->setOutlineColor(sf::Color::White);
		itr->setOutlineThickness(1);
	}*/

	for (auto& itr : m_tools)
	{
		itr->setOutlineColor(sf::Color::White);
		itr->setOutlineThickness(1);
	}

	for (auto& itr : m_iconUI)
	{
		itr->setOutlineColor(sf::Color::White);
		itr->setOutlineThickness(1);
	}
}

void SimulationState::InitSpaceObjects()
{
	m_objects.push_back(std::make_unique<CenterOfMass>(view->getSize().y / 64, view->getSize().y / 256));

	double v = std::sqrt(G * 1.989 * std::pow(10, 30) / (au * 0.3));

	m_test_orbits.reserve(5);
	m_test_orbits.emplace_back(std::make_unique<ke::Circle>(au * m_space_scale * 0.9, sf::Vector2f(0, 0), ke::Origin::MIDDLE_MIDDLE, L"", 0, ke::Origin::RIGHT_MIDDLE, sf::Color::Black, sf::Color::White, 30, sf::Color::Blue));
	m_test_orbits.emplace_back(std::make_unique<ke::Circle>(au * m_space_scale * 1.2, sf::Vector2f(0, 0), ke::Origin::MIDDLE_MIDDLE, L"", 0, ke::Origin::RIGHT_MIDDLE, sf::Color::Black, sf::Color::White, 30, sf::Color::Blue));
	m_test_orbits.emplace_back(std::make_unique<ke::Circle>(au * m_space_scale * 2.0, sf::Vector2f(0, 0), ke::Origin::MIDDLE_MIDDLE, L"", 0, ke::Origin::RIGHT_MIDDLE, sf::Color::Black, sf::Color::White, 30, sf::Color::Blue));
	m_test_orbits.emplace_back(std::make_unique<ke::Circle>(au * m_space_scale * 3.14, sf::Vector2f(0, 0), ke::Origin::MIDDLE_MIDDLE, L"", 0, ke::Origin::RIGHT_MIDDLE, sf::Color::Black, sf::Color::White, 30, sf::Color::Blue));
	m_test_orbits.emplace_back(std::make_unique<ke::Circle>(au * m_space_scale * 6.9, sf::Vector2f(0, 0), ke::Origin::MIDDLE_MIDDLE, L"", 0, ke::Origin::RIGHT_MIDDLE, sf::Color::Black, sf::Color::White, 30, sf::Color::Blue));

	//m_objects.push_back(std::make_unique<Planet>(sf::Vector2f(au * m_space_scale * 0.9, 1), L"Earth1", "Textures/AudioIcon.png", 3.972 * std::pow(10, 24), 5370000 * m_space_scale * m_planet_scale, 24));
	//m_objects.push_back(std::make_unique<Planet>(sf::Vector2f(au * m_space_scale * 1.2, 1), L"Earth2", "Textures/AudioIcon.png", 6.972 * std::pow(10, 24), 7370000 * m_space_scale * m_planet_scale, 24));
	//m_objects.push_back(std::make_unique<Star>(sf::Vector2f(10, 10), "Sun", "Textures/AudioIcon.png", 1.989 * std::pow(10, 30), 6.957 * std::pow(10, 8) * m_space_scale * m_star_scale, 24));

	////m_objects.back()->object.physics()->setSpeed(round_orbit_velocity(m_objects.front()->data.mass, au * 0.9), 90);
	////std::cout << m_objects.back()->data.mass << '\n';
	////m_objects.back()->object.physics()->setSpeed(round_orbit_velocity(m_objects.front()->data.mass, au * 1.2), 90);
	//m_objects.push_back(std::make_unique<Planet>(sf::Vector2f(au * m_space_scale * 2, 1), "akbs", "Textures/AudioIcon.png", 5.972 * std::pow(10, 24), 6970000 * m_space_scale * m_planet_scale, 24));
	//m_objects.back()->object.physics()->setSpeed(round_orbit_velocity(m_objects.front()->data.mass, au * 2), 90);
	//m_objects.push_back(std::make_unique<Planet>(sf::Vector2f(au * m_space_scale * 3.14, 1), "Earth4", "Textures/AudioIcon.png", 8.972 * std::pow(10, 24), 6170000 * m_space_scale * m_planet_scale, 24));
	//m_objects.back()->object.physics()->setSpeed(round_orbit_velocity(m_objects.front()->data.mass, au * 3.14), 90);
	//m_objects.push_back(std::make_unique<Planet>(sf::Vector2f(au * m_space_scale * 6.9, 1), "Earth5", "Textures/AudioIcon.png", 12.972 * std::pow(10, 24), 5970000 * m_space_scale * m_planet_scale, 24));
	//m_objects.back()->object.physics()->setSpeed(round_orbit_velocity(m_objects.front()->data.mass, au * 6.9), 90);

	//m_objects.push_back(std::make_unique<Planet>(sf::Vector2f(au * m_space_scale * 10, 1), "Bob", "Textures/AudioIcon.png", 1.898 * std::pow(10, 26), 32700000 * m_space_scale * m_planet_scale, 24));
	//m_objects.back()->object.physics()->setSpeed(std::sqrt(G * 1.989 * std::pow(10, 30) / (au * 10)), 145);

	//int k = 0;
	//for (auto& itr : m_objects)
	//{
	//	itr->setName(std::to_string(k));
	//	k++;
	//	std::cout << itr->name() << '\n';
	//}

	for (auto& itr : m_test_orbits)
		itr->getShape()->setPointCount(314);


	for (auto itr = m_objects.begin() + 1, eoi = m_objects.end(); itr != eoi; ++itr)
		for (auto i = m_objects.begin() + 1; i != eoi; ++i)
			if (itr != i)
			{
				float angle = std::atan(-((*itr)->object.getPosition().y - (*i)->object.getPosition().y) / ((*itr)->object.getPosition().x - (*i)->object.getPosition().x)) * TO_DEG;

				if (((*itr)->object.getPosition().x > (*i)->object.getPosition().x))
					angle += 180;

				(*itr)->object.physics()->addForce((*i)->name(),
					gravitational_force_2((*itr)->data.mass, (*i)->data.mass,
						(std::pow((*itr)->object.getPosition().y - (*i)->object.getPosition().y, 2) + (std::pow((*itr)->object.getPosition().x - (*i)->object.getPosition().x, 2)))) * m_space_scale,
					angle);

				std::cout << "M = " << (*itr)->data.mass << '\n';
				std::cout << "R = " << std::sqrt(std::pow((*itr)->object.getPosition().y - (*i)->object.getPosition().y, 2) + (std::pow((*itr)->object.getPosition().x - (*i)->object.getPosition().x, 2))) << '\n';
				std::cout << "Fg = " << gravitational_force((*itr)->data.mass, (*i)->data.mass,
					std::sqrt(std::pow((*itr)->object.getPosition().y - (*i)->object.getPosition().y, 2) + (std::pow((*itr)->object.getPosition().x - (*i)->object.getPosition().x, 2)))) << '\n';

			}


	sf::Vector2<double> _mr(0, 0);	// Sum of mass * pos
	long double _m = 0;				// total mass

	for (auto itr = m_objects.begin() + 1, eoi = m_objects.end(); itr != eoi; ++itr)
	{
		_mr.x += (*itr)->data.mass * (*itr)->object.getPosition().x;
		_mr.y += (*itr)->data.mass * (*itr)->object.getPosition().y;

		//_mr += (*itr)->data.mass * (*itr)->object.getPosition();

		_m += (*itr)->data.mass;
	}

	std::cout << "mass: " << _m << '\n';

	//m_objects.front()->object.physics()->setMass(_m);
	m_objects.front()->object.setPosition(sf::Vector2f(_mr.x / _m, _mr.y / _m));


	m_selected_object = m_objects.begin();


	int stars_counted = 0;

	for (auto itr = m_objects.begin() + 1, eoi = m_objects.end(); itr != eoi; ++itr)
	{
		if ((*itr)->type() == STAR && stars_counted < 1)
		{
			stars_counted++;
			continue;
		}

		float angle = std::atan(-((*m_selected_object)->object.getPosition().y - (*itr)->object.getPosition().y) / ((*m_selected_object)->object.getPosition().x - (*itr)->object.getPosition().x)) * TO_DEG;

		if (((*m_selected_object)->object.getPosition().x < (*itr)->object.getPosition().x))
			angle += 180;


		(*itr)->object.physics()->setSpeed(round_orbit_velocity((*m_selected_object)->object.physics()->getMass() - (*itr)->data.mass,
			position_to_destance((*m_selected_object)->object.getPosition(), (*itr)->object.getPosition() / static_cast<float>(m_space_scale))), angle - 90);

		//std::cout << angle - 90 << '\n';

		ke::debug::printVector2((*itr)->object.physics()->getSpeed());
	}

	//ke::debug::printVector2(m_objects.at(1)->object.physics()->getSpeed());
	//std::cout << position_to_destance((*m_selected_object)->object.getPosition(), m_objects.at(1)->object.getPosition() / static_cast<float>(m_space_scale)) << '\n';


	//sf::Vector2<double> _mr(0, 0);
	//long double _m = 0;

	//for (auto& itr : m_objects)
	//{
	//	_mr.x += itr->data.mass * itr->object.getPosition().x;
	//	_mr.y += itr->data.mass * itr->object.getPosition().y;

	//	_m += itr->data.mass;
	//}

	//m_mass_center.create(winSize.y, sf::Vector2f(_mr.x / _m, _mr.y / _m), ke::Origin::MIDDLE_MIDDLE, L"", 0, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color::Transparent, winSize.y / 8, sf::Color(128, 128, 128, 192));

}


void SimulationState::InitBackground()
{
	m_backgrounds.reserve(4); // background | top | right | bottom 
	m_backgrounds.emplace_back(std::make_unique<ke::Rectangle>(sf::Vector2f(winSize.x, 5 * winSize.y / 32), sf::Vector2f(0, 0), ke::Origin::LEFT_TOP, L"Completely Inaccurate Space Simulator", winSize.y / 64, ke::Origin::MIDDLE_TOP, sf::Color::Black, sf::Color(255, 255, 255, 128), winSize.y / 360, sf::Color(128, 128, 128, 255)));
	m_backgrounds.emplace_back(std::make_unique<ke::Rectangle>(sf::Vector2f(winSize.x / 5, 7 * winSize.y / 8), sf::Vector2f(winSize.x, 5 * winSize.y / 32), ke::Origin::RIGHT_TOP, L"", 0, ke::Origin::MIDDLE_MIDDLE, sf::Color::Black, sf::Color(255, 255, 255, 128), winSize.y / 360, sf::Color(128, 128, 128, 255)));
	m_backgrounds.emplace_back(std::make_unique<ke::Rectangle>(sf::Vector2f(winSize.x / 5, winSize.y / 32), sf::Vector2f(0, winSize.y), ke::Origin::LEFT_BOTTOM, L"", 0, ke::Origin::MIDDLE_MIDDLE, sf::Color::Black, sf::Color(255, 255, 255, 128), winSize.y / 360, sf::Color(128, 128, 128, 255)));
	m_backgrounds.emplace_back(std::make_unique<ke::Rectangle>(sf::Vector2f(winSize.x / 4 - winSize.y / 360, winSize.y / 32), sf::Vector2f(4 * winSize.x / 5, winSize.y), ke::Origin::RIGHT_BOTTOM, L"", winSize.y / 64, ke::Origin::LEFT_MIDDLE, sf::Color::Black, sf::Color(255, 255, 255, 128), winSize.y / 360, sf::Color(128, 128, 128, 255), 0.f, sf::Text::Bold, sf::Vector2f(winSize.y / 180, 0)));
}


void SimulationState::InitTopGUI()
{
	m_project_menagers.reserve(3); // create new | save | open
	m_project_menagers.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.y / 16, winSize.y / 16), sf::Vector2f(0, winSize.y / 32), ke::Origin::LEFT_TOP, nullptr));
	m_project_menagers.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.y / 16, winSize.y / 16), sf::Vector2f(winSize.y / 16, winSize.y / 32), ke::Origin::LEFT_TOP, nullptr));
	m_project_menagers.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.y / 16, winSize.y / 16), sf::Vector2f(winSize.y / 8, winSize.y / 32), ke::Origin::LEFT_TOP, nullptr));


	m_state_controllers.reserve(3); // Quit to menu | settings | clear
	m_state_controllers.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.y / 16, winSize.y / 16), sf::Vector2f(winSize.x, winSize.y / 32), ke::Origin::RIGHT_TOP, "Textures/StateTextures/Simulation/QuitButton.png"));
	m_state_controllers.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.y / 16, winSize.y / 16), sf::Vector2f(winSize.x - winSize.y / 16, winSize.y / 32), ke::Origin::RIGHT_TOP, nullptr));
	m_state_controllers.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.y / 16, winSize.y / 16), sf::Vector2f(winSize.x - winSize.y / 8, winSize.y / 32), ke::Origin::RIGHT_TOP, nullptr));


	m_tools.reserve(5); // select | select field | delete | soom in | zoom out
	m_tools.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.y / 32, winSize.y / 32), sf::Vector2f(1 * winSize.y / 64, 7 * winSize.y / 64), ke::Origin::LEFT_TOP, nullptr));
	m_tools.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.y / 32, winSize.y / 32), sf::Vector2f(3 * winSize.y / 64, 7 * winSize.y / 64), ke::Origin::LEFT_TOP, nullptr));
	m_tools.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.y / 32, winSize.y / 32), sf::Vector2f(5 * winSize.y / 64, 7 * winSize.y / 64), ke::Origin::LEFT_TOP, nullptr));
	m_tools.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.y / 32, winSize.y / 32), sf::Vector2f(7 * winSize.y / 64, 7 * winSize.y / 64), ke::Origin::LEFT_TOP, nullptr));
	m_tools.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.y / 32, winSize.y / 32), sf::Vector2f(9 * winSize.y / 64, 7 * winSize.y / 64), ke::Origin::LEFT_TOP, nullptr));


	m_iconUI.reserve(3); // main objects | recently used
	m_iconUI.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.y / 16, winSize.y / 16), sf::Vector2f(4 * winSize.y / 16, 1 * winSize.y / 32), ke::Origin::LEFT_TOP, nullptr));
	m_iconUI.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.y / 16, winSize.y / 16), sf::Vector2f(4 * winSize.y / 16, 3 * winSize.y / 32), ke::Origin::LEFT_TOP, nullptr));
	m_iconUI.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.y / 8, winSize.y / 8), sf::Vector2f(21 * winSize.y / 16, 1 * winSize.y / 32), ke::Origin::LEFT_TOP, nullptr));


	const int icon_count = 32;
	m_object_icons.reserve(icon_count + 1);

	m_object_icons.emplace_back(std::make_unique<ObjectIcon>(ke::Settings::EmptyTexturePath(), ke::Settings::EmptyTexturePath(), sf::Vector2f(0, 0), sf::Vector2f(-100, -100), "", ObjectType::UNDEFINED, ObjectClass::CLASS_UNDEFINED, ObjectSubtype::SUBTYPE_UNDEFINED, 1, 0, 0, sf::Vector3f(1.0, 1.0, 1.0)));

	// recently used / obj history
	for (int i = 0; i < icon_count; i++)
		m_object_icons.emplace_back(std::make_unique<ObjectIcon>("Textures/IconTextures/Empty_icon.png", "Textures/IconTextures/Empty_icon.png", sf::Vector2f(winSize.y / 16, winSize.y / 16), sf::Vector2f((5 + ((i < 16) ? i : i - 16)) * winSize.y / 16, ((i < 16) ? 1 : 3) * winSize.y / 32), "OBJECT_NAME", ObjectType::UNDEFINED, ObjectClass::CLASS_UNDEFINED, ObjectSubtype::SUBTYPE_UNDEFINED, 5.972 * std::pow(10, 24), 6370000, 0, sf::Vector3f(1.0, 1.0, 1.0)));

	auto def_obj_itr = m_object_icons.end();


	//int i = 0;
	//m_object_icons.emplace_back(std::make_unique<ObjectIcon>("Textures/IconTextures/ProximaCentauri_icon.png", "Textures/ObjectTextures/ProximaCentauri.png", sf::Vector2f(winSize.y / 16, winSize.y / 16), sf::Vector2f((5 + i) * winSize.y / 16, 3 * winSize.y / 32), "Proxima Centauri: M - type star (red dwarf)", 2.446e+29, 107'280'000, STAR, 100, sf::Vector3f(1.0, 0.0, 0.0))); i++;
	//m_object_icons.emplace_back(std::make_unique<ObjectIcon>("Textures/IconTextures/EpsilonEridani_icon.png", "Textures/ObjectTextures/EpsilonEridani.png", sf::Vector2f(winSize.y / 16, winSize.y / 16), sf::Vector2f((5 + i) * winSize.y / 16, 3 * winSize.y / 32), "Epsilon Eridani: K - type star (orange dwarf)", 1.631e+30, 511'340'000, STAR, 500, sf::Vector3f(1.0, 1.5, 0.0))); i++;
	//m_object_icons.emplace_back(std::make_unique<ObjectIcon>("Textures/IconTextures/Sun_icon.png", "Textures/ObjectTextures/Sun.png", sf::Vector2f(winSize.y / 16, winSize.y / 16), sf::Vector2f((5 + i) * winSize.y / 16, 3 * winSize.y / 32), "Sun: G - type star (yellow dwarf)", 1.98847e+30, 696'340'000, STAR, 1000, sf::Vector3f(1.0, 0.5, 0.5))); i++;
	//m_object_icons.emplace_back(std::make_unique<ObjectIcon>("Textures/IconTextures/UpsilonAndromedae_icon.png", "Textures/ObjectTextures/UpsilonAndromedae.png", sf::Vector2f(winSize.y / 16, winSize.y / 16), sf::Vector2f((5 + i) * winSize.y / 16, 3 * winSize.y / 32), "Upsilon Andromedae / Titawin: F - type star", 2.54e+30, 1'019'993'875, STAR, 1000, sf::Vector3f(1.0, 0.5, 0.5))); i++;
	//m_object_icons.emplace_back(std::make_unique<ObjectIcon>("Textures/IconTextures/Sirius_icon.png", "Textures/ObjectTextures/Sirius.png", sf::Vector2f(winSize.y / 16, winSize.y / 16), sf::Vector2f((5 + i) * winSize.y / 16, 3 * winSize.y / 32), "Sirius: A - type star", 4.24e+30, 1'475'520'000, STAR, 1000, sf::Vector3f(1.0, 0.5, 0.5))); i++;
	//m_object_icons.emplace_back(std::make_unique<ObjectIcon>("Textures/IconTextures/UpsilonOrionis_icon.png", "Textures/ObjectTextures/UpsilonOrionis.png", sf::Vector2f(winSize.y / 16, winSize.y / 16), sf::Vector2f((5 + i) * winSize.y / 16, 3 * winSize.y / 32), "Upsilon Orionis / Thabit: B - type star", 4e+31, 5'011'200'000, STAR, 1000, sf::Vector3f(1.0, 0.5, 0.5))); i++;
	//m_object_icons.emplace_back(std::make_unique<ObjectIcon>("Textures/IconTextures/ZetaOphiuchi_icon.png", "Textures/ObjectTextures/ZetaOphiuchi.png", sf::Vector2f(winSize.y / 16, winSize.y / 16), sf::Vector2f((5 + i) * winSize.y / 16, 3 * winSize.y / 32), "Zeta Ophiuchi: O - type star", 4e+31, 5'916'000'000, STAR, 1000, sf::Vector3f(1.0, 0.5, 0.5))); i++;
	//
	//m_object_icons.emplace_back(std::make_unique<ObjectIcon>("Textures/AudioIcon.png", "Textures/ObjectTextures/Gliese229B.png", sf::Vector2f(winSize.y / 16, winSize.y / 16), sf::Vector2f((5 + i) * winSize.y / 16, 3 * winSize.y / 32), "Gliese 229 B: brown dwarf (T - type)", 6e+28, 35'077'375, STAR, 1000, sf::Vector3f(1.0, 0.5, 0.5))); i++;
	//m_object_icons.emplace_back(std::make_unique<ObjectIcon>("Textures/AudioIcon.png", "Textures/AudioIcon.png", sf::Vector2f(winSize.y / 16, winSize.y / 16), sf::Vector2f((5 + i) * winSize.y / 16, 3 * winSize.y / 32), "Van Maanen 2: white dwarf", 1.34e+30, 9'604'800, STAR, 1000, sf::Vector3f(1.0, 0.5, 0.5))); i++;
	//m_object_icons.emplace_back(std::make_unique<ObjectIcon>("Textures/AudioIcon.png", "Textures/AudioIcon.png", sf::Vector2f(winSize.y / 16, winSize.y / 16), sf::Vector2f((5 + i) * winSize.y / 16, 3 * winSize.y / 32), "Crab Pulsar: neutron star", 2.8e+30, 10'000, STAR, 1000, sf::Vector3f(1.0, 0.5, 0.5))); i++;
	//
	//m_object_icons.emplace_back(std::make_unique<ObjectIcon>("Textures/AudioIcon.png", "Textures/AudioIcon.png", sf::Vector2f(winSize.y / 16, winSize.y / 16), sf::Vector2f((5 + i) * winSize.y / 16, 3 * winSize.y / 32), "Earth", 5.972e+24, 6'371'000, PLANET, 0, sf::Vector3f(1.0, 1.0, 1.0))); i++;
	//m_object_icons.emplace_back(std::make_unique<ObjectIcon>("Textures/AudioIcon.png", "Textures/AudioIcon.png", sf::Vector2f(winSize.y / 16, winSize.y / 16), sf::Vector2f((5 + i) * winSize.y / 16, 3 * winSize.y / 32), "Moon", 7.3477e+22, 1'737'100, PLANET, 0, sf::Vector3f(1.0, 1.0, 1.0))); i++;
	//m_object_icons.emplace_back(std::make_unique<ObjectIcon>("Textures/AudioIcon.png", "Textures/AudioIcon.png", sf::Vector2f(winSize.y / 16, winSize.y / 16), sf::Vector2f((5 + i) * winSize.y / 16, 3 * winSize.y / 32), "Mars", 6.4191e+23, 3'397'000, PLANET, 0, sf::Vector3f(1.0, 1.0, 1.0))); i++;
	//m_object_icons.emplace_back(std::make_unique<ObjectIcon>("Textures/AudioIcon.png", "Textures/AudioIcon.png", sf::Vector2f(winSize.y / 16, winSize.y / 16), sf::Vector2f((5 + i) * winSize.y / 16, 3 * winSize.y / 32), "Jupiter", 1.8987e+27, 71'492'680, PLANET, 0, sf::Vector3f(1.0, 1.0, 1.0))); i++;
	//m_object_icons.emplace_back(std::make_unique<ObjectIcon>("Textures/AudioIcon.png", "Textures/AudioIcon.png", sf::Vector2f(winSize.y / 16, winSize.y / 16), sf::Vector2f((5 + i) * winSize.y / 16, 3 * winSize.y / 32), "Neptune", 1.0244e+26, 24'766'360, PLANET, 0, sf::Vector3f(1.0, 1.0, 1.0))); i++;
	//m_object_icons.emplace_back(std::make_unique<ObjectIcon>("Textures/AudioIcon.png", "Textures/AudioIcon.png", sf::Vector2f(winSize.y / 16, winSize.y / 16), sf::Vector2f((5 + i) * winSize.y / 16, 3 * winSize.y / 32), "International Space Station", 419'725, 109, PLANET, 0, sf::Vector3f(1.0, 1.0, 1.0))); i++;

	m_objIconPanel.assign(&m_iconUI, &m_object_icons, m_ObjectLibraryOverlay.get());


	//ke::FileStream gstream;
	//gstream.createFile("Data/recentlyUsedIcons.glo");
	//gstream.open("Data/recentlyUsedIcons.glo", std::ios::binary | std::ios::out);

	//for (auto itr = m_object_icons.begin(), eoi = m_object_icons.begin() + m_object_icons.size() / 2; itr != eoi; ++itr)
	//{
	//	gstream.binWrite((*itr)->object_name());
	//	gstream.binWrite((*itr)->type());
	//	gstream.binWrite((*itr)->mass());
	//	gstream.binWrite((*itr)->radius());
	//	gstream.binWrite((*itr)->filename());

	//	gstream.binWrite((*itr)->icon.getTexturePath());
	//}

	//gstream.binWrite((std::string)"Default");

	//ke::FileStream fstream;
	////fstream.createFile("Data/IconLayouts/Default.slo");
	//fstream.open("Data/IconLayouts/Default.slo", std::ios::binary | std::ios::out | std::ios::trunc);
	//
	//for (auto itr = m_object_icons.begin() + m_object_icons.size() / 2 + 1, eoi = m_object_icons.end(); itr != eoi; ++itr)
	//{
	//	fstream.binWrite((*itr)->object_name());
	//	fstream.binWrite((*itr)->type());
	//	fstream.binWrite((*itr)->mass());
	//	fstream.binWrite((*itr)->radius());
	//	fstream.binWrite((*itr)->filename());

	//	fstream.binWrite((*itr)->iconFilename());
	//}


	// default
	//for (int i = 0; i < icon_count * 0.5; i++)
		//m_object_icons.emplace_back(std::make_unique<ObjectIcon>("Textures/AudioIcon.png", "Textures/AudioIcon.png", sf::Vector2f(winSize.y / 16, winSize.y / 16), sf::Vector2f((5 + i) * winSize.y / 16, 3 * winSize.y / 32), L"Pu55yLand", 5.972 * std::pow(10, 24), 6370000, PLANET));



	m_icon_inv_iterator = m_object_icons.begin();
	m_icon_iterator = m_object_icons.begin();
	(*m_icon_iterator)->icon.setActiveStatus(false);
}


void SimulationState::InitObjDataGUI()
{
	m_orbit_preview.create(1, { 0, 0 }, ke::Origin::MIDDLE_MIDDLE, L"", (view->getSize().x / winSize.x), ke::Origin::RIGHT_MIDDLE, sf::Color::Transparent, sf::Color(255, 255, 255, 128), view->getSize().y / 256, sf::Color(128, 128, 128, 128), 0, sf::Text::Regular, { 0, 0 });
	m_orbit_preview.setActiveStatus(false);
	m_orbit_preview.getShape()->setPointCount(128);

	m_distance_preview.create({ 1, 1 }, { 0, 0 }, ke::Origin::MIDDLE_MIDDLE, L"0 m", winSize.y / 64, ke::Origin::LEFT_MIDDLE, sf::Color::Transparent, sf::Color(192, 192, 192, 255));
	m_distance_preview.setActiveStatus(false);


	m_object_name.create(sf::Vector2f(m_backgrounds.at(1)->getSize().x, m_backgrounds.at(1)->getSize().y / 16), sf::Vector2f(m_backgrounds.at(1)->getShapeCenter().x, m_backgrounds.at(1)->getShapeCenter().y - m_backgrounds.at(1)->getSize().y * 0.5),
		ke::Origin::MIDDLE_TOP, nullptr, L"", ke::TextScope::ASCII_Everything, 50, 1, winSize.y / 48, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color::White, sf::Color(255, 255, 223, 225), 0, sf::Color::White);


	const size_t symb_vec_size = 9;
	const size_t val_vec_size = 11;
	const size_t unit_vec_size = 9;

	m_symbols.reserve(symb_vec_size);
	m_values.reserve(val_vec_size);
	m_units.reserve(unit_vec_size);


	//ke::Button::create(,,,);
	m_symbols.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getSize().y / 16), sf::Vector2f(winSize.x - m_backgrounds.at(1)->getSize().x, m_backgrounds.at(1)->getShapeCenter().y - m_backgrounds.at(1)->getSize().y * 0.5f + m_backgrounds.at(1)->getSize().y / 16.f * 2.f),
		ke::Origin::LEFT_MIDDLE, nullptr, L"v", winSize.y / 48, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(223, 223, 255, 255), 0, sf::Color::White));
	m_symbols.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getSize().y / 16), sf::Vector2f(winSize.x - m_backgrounds.at(1)->getSize().x, m_backgrounds.at(1)->getShapeCenter().y - m_backgrounds.at(1)->getSize().y * 0.5f + m_backgrounds.at(1)->getSize().y / 16.f * 3.f),
		ke::Origin::LEFT_MIDDLE, nullptr, L"v [ ]", winSize.y / 48, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(223, 223, 255, 255), 0, sf::Color::White));
	m_symbols.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getSize().y / 16), sf::Vector2f(winSize.x - m_backgrounds.at(1)->getSize().x, m_backgrounds.at(1)->getShapeCenter().y - m_backgrounds.at(1)->getSize().y * 0.5f + m_backgrounds.at(1)->getSize().y / 16.f * 4.f),
		ke::Origin::LEFT_MIDDLE, nullptr, L"M", winSize.y / 48, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(223, 223, 255, 255), 0, sf::Color::White));
	m_symbols.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getSize().y / 16), sf::Vector2f(winSize.x - m_backgrounds.at(1)->getSize().x, m_backgrounds.at(1)->getShapeCenter().y - m_backgrounds.at(1)->getSize().y * 0.5f + m_backgrounds.at(1)->getSize().y / 16.f * 5.f),
		ke::Origin::LEFT_MIDDLE, nullptr, L"R", winSize.y / 48, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(223, 223, 255, 255), 0, sf::Color::White));
	m_symbols.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getSize().y / 16), sf::Vector2f(winSize.x - m_backgrounds.at(1)->getSize().x, m_backgrounds.at(1)->getShapeCenter().y - m_backgrounds.at(1)->getSize().y * 0.5f + m_backgrounds.at(1)->getSize().y / 16.f * 6.5f),
		ke::Origin::LEFT_MIDDLE, nullptr, L"g", winSize.y / 48, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(223, 223, 255, 255), 0, sf::Color::White));
	m_symbols.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getSize().y / 16), sf::Vector2f(winSize.x - m_backgrounds.at(1)->getSize().x, m_backgrounds.at(1)->getShapeCenter().y - m_backgrounds.at(1)->getSize().y * 0.5f + m_backgrounds.at(1)->getSize().y / 16.f * 7.5f),
		ke::Origin::LEFT_MIDDLE, nullptr, L"\u03C1", winSize.y / 48, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(223, 223, 255, 255), 0, sf::Color::White, 0, 0, sf::Vector2f(0, 0), ke::Font::Arial_Uni));
	m_symbols.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getSize().y / 16), sf::Vector2f(winSize.x - m_backgrounds.at(1)->getSize().x, m_backgrounds.at(1)->getShapeCenter().y - m_backgrounds.at(1)->getSize().y * 0.5f + m_backgrounds.at(1)->getSize().y / 16.f * 9.f),
		ke::Origin::LEFT_MIDDLE, nullptr, L"ev", winSize.y / 48, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(223, 223, 255, 255), 0, sf::Color::White, 0, 0, sf::Vector2f(0, 0), ke::Font::Arial_Uni));
	m_symbols.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getSize().y / 16), sf::Vector2f(winSize.x - m_backgrounds.at(1)->getSize().x, m_backgrounds.at(1)->getShapeCenter().y - m_backgrounds.at(1)->getSize().y * 0.5f + m_backgrounds.at(1)->getSize().y / 16.f * 10.f),
		ke::Origin::LEFT_MIDDLE, nullptr, L"d", winSize.y / 48, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(223, 223, 255, 255), 0, sf::Color::White, 0, 0, sf::Vector2f(0, 0), ke::Font::Arial_Uni));
	m_symbols.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getSize().y / 16), sf::Vector2f(winSize.x - m_backgrounds.at(1)->getSize().x, m_backgrounds.at(1)->getShapeCenter().y - m_backgrounds.at(1)->getSize().y * 0.5f + m_backgrounds.at(1)->getSize().y / 16.f * 11.f),
		ke::Origin::LEFT_MIDDLE, nullptr, L"D", winSize.y / 48, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(223, 223, 255, 255), 0, sf::Color::White, 0, 0, sf::Vector2f(0, 0), ke::Font::Arial_Uni));


	sf::Event fake_event;
	for (auto& itr : m_symbols)
	{
		itr->setFont(ke::Font::TrebuchetMS);
		itr->update({ 0, 0 }, fake_event, sf::Mouse::Left, nullptr);
	}


	//ke::InputButton::create()
	// scalar velocity, angle
	m_values["VELOCITY"] = (std::make_unique<ke::InputButton>(sf::Vector2f(4 * m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getSize().y / 16), sf::Vector2f(winSize.x - 7 * m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getShapeCenter().y - m_backgrounds.at(1)->getSize().y * 0.5f + m_backgrounds.at(1)->getSize().y / 16.f * 2.f),
		ke::Origin::LEFT_MIDDLE, nullptr, L"", ke::TextScope::Math, 50, 1, winSize.y / 48, ke::Origin::LEFT_MIDDLE, sf::Color::Transparent, sf::Color::White, sf::Color::White, 0, sf::Color::Transparent, sf::Text::Regular, sf::Vector2f(6 * m_backgrounds.at(1)->getSize().x / 128, 0)));
	m_values["V_ANGLE"] = (std::make_unique<ke::InputButton>(sf::Vector2f(2 * m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getSize().y / 16), sf::Vector2f(winSize.x - 3 * m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getShapeCenter().y - m_backgrounds.at(1)->getSize().y * 0.5f + m_backgrounds.at(1)->getSize().y / 16.f * 2.f),
		ke::Origin::LEFT_MIDDLE, nullptr, L"", ke::TextScope::Math, 50, 1, winSize.y / 48, ke::Origin::LEFT_MIDDLE, sf::Color::Transparent, sf::Color::White, sf::Color::White, 0, sf::Color::Transparent, sf::Text::Regular, sf::Vector2f(6 * m_backgrounds.at(1)->getSize().x / 128, 0)));

	// vector velocity
	m_values["VECTOR_VEL_X"] = (std::make_unique<ke::InputButton>(sf::Vector2f(3 * m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getSize().y / 16), sf::Vector2f(winSize.x - 7 * m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getShapeCenter().y - m_backgrounds.at(1)->getSize().y * 0.5f + m_backgrounds.at(1)->getSize().y / 16.f * 3.f),
		ke::Origin::LEFT_MIDDLE, nullptr, L"", ke::TextScope::Math, 50, 1, winSize.y / 48, ke::Origin::LEFT_MIDDLE, sf::Color::Transparent, sf::Color::White, sf::Color::White, 0, sf::Color::Transparent, sf::Text::Regular, sf::Vector2f(6 * m_backgrounds.at(1)->getSize().x / 128, 0)));
	m_values["VECTOR_VEL_Y"] = (std::make_unique<ke::InputButton>(sf::Vector2f(3 * m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getSize().y / 16), sf::Vector2f(winSize.x - 4 * m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getShapeCenter().y - m_backgrounds.at(1)->getSize().y * 0.5f + m_backgrounds.at(1)->getSize().y / 16.f * 3.f),
		ke::Origin::LEFT_MIDDLE, nullptr, L"", ke::TextScope::Math, 50, 1, winSize.y / 48, ke::Origin::LEFT_MIDDLE, sf::Color::Transparent, sf::Color::White, sf::Color::White, 0, sf::Color::Transparent, sf::Text::Regular, sf::Vector2f(6 * m_backgrounds.at(1)->getSize().x / 128, 0)));

	m_values["MASS"] = (std::make_unique<ke::InputButton>(sf::Vector2f(6 * m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getSize().y / 16), sf::Vector2f(winSize.x - 7 * m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getShapeCenter().y - m_backgrounds.at(1)->getSize().y * 0.5f + m_backgrounds.at(1)->getSize().y / 16.f * 4.f),
		ke::Origin::LEFT_MIDDLE, nullptr, L"", ke::TextScope::Math, 50, 1, winSize.y / 48, ke::Origin::LEFT_MIDDLE, sf::Color::Transparent, sf::Color::White, sf::Color::White, 0, sf::Color::Transparent, sf::Text::Regular, sf::Vector2f(6 * m_backgrounds.at(1)->getSize().x / 128, 0)));
	m_values["RADIUS"] = (std::make_unique<ke::InputButton>(sf::Vector2f(6 * m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getSize().y / 16), sf::Vector2f(winSize.x - 7 * m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getShapeCenter().y - m_backgrounds.at(1)->getSize().y * 0.5f + m_backgrounds.at(1)->getSize().y / 16.f * 5.f),
		ke::Origin::LEFT_MIDDLE, nullptr, L"", ke::TextScope::Math, 50, 1, winSize.y / 48, ke::Origin::LEFT_MIDDLE, sf::Color::Transparent, sf::Color::White, sf::Color::White, 0, sf::Color::Transparent, sf::Text::Regular, sf::Vector2f(6 * m_backgrounds.at(1)->getSize().x / 128, 0)));


	m_values["SURFACE_G"] = (std::make_unique<ke::InputButton>(sf::Vector2f(6 * m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getSize().y / 16), sf::Vector2f(winSize.x - 7 * m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getShapeCenter().y - m_backgrounds.at(1)->getSize().y * 0.5f + m_backgrounds.at(1)->getSize().y / 16.f * 6.5f),
		ke::Origin::LEFT_MIDDLE, nullptr, L"", ke::TextScope::Math, 50, 1, winSize.y / 48, ke::Origin::LEFT_MIDDLE, sf::Color::Transparent, sf::Color::White, sf::Color::White, 0, sf::Color::Transparent, sf::Text::Regular, sf::Vector2f(6 * m_backgrounds.at(1)->getSize().x / 128, 0)));
	m_values["DENSITY"] = (std::make_unique<ke::InputButton>(sf::Vector2f(6 * m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getSize().y / 16), sf::Vector2f(winSize.x - 7 * m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getShapeCenter().y - m_backgrounds.at(1)->getSize().y * 0.5f + m_backgrounds.at(1)->getSize().y / 16.f * 7.5f),
		ke::Origin::LEFT_MIDDLE, nullptr, L"", ke::TextScope::Math, 50, 1, winSize.y / 48, ke::Origin::LEFT_MIDDLE, sf::Color::Transparent, sf::Color::White, sf::Color::White, 0, sf::Color::Transparent, sf::Text::Regular, sf::Vector2f(6 * m_backgrounds.at(1)->getSize().x / 128, 0)));


	m_values["ESCAPE_VEL"] = (std::make_unique<ke::InputButton>(sf::Vector2f(6 * m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getSize().y / 16), sf::Vector2f(winSize.x - 7 * m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getShapeCenter().y - m_backgrounds.at(1)->getSize().y * 0.5f + m_backgrounds.at(1)->getSize().y / 16.f * 9.f),
		ke::Origin::LEFT_MIDDLE, nullptr, L"", ke::TextScope::Math, 50, 1, winSize.y / 48, ke::Origin::LEFT_MIDDLE, sf::Color::Transparent, sf::Color::White, sf::Color::White, 0, sf::Color::Transparent, sf::Text::Regular, sf::Vector2f(6 * m_backgrounds.at(1)->getSize().x / 128, 0)));
	m_values["TO_NEAREST_OBJ"] = (std::make_unique<ke::InputButton>(sf::Vector2f(6 * m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getSize().y / 16), sf::Vector2f(winSize.x - 7 * m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getShapeCenter().y - m_backgrounds.at(1)->getSize().y * 0.5f + m_backgrounds.at(1)->getSize().y / 16.f * 10.f),
		ke::Origin::LEFT_MIDDLE, nullptr, L"", ke::TextScope::Math, 50, 1, winSize.y / 48, ke::Origin::LEFT_MIDDLE, sf::Color::Transparent, sf::Color::White, sf::Color::White, 0, sf::Color::Transparent, sf::Text::Regular, sf::Vector2f(6 * m_backgrounds.at(1)->getSize().x / 128, 0)));
	m_values["TO_NEAREST_STAR"] = (std::make_unique<ke::InputButton>(sf::Vector2f(6 * m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getSize().y / 16), sf::Vector2f(winSize.x - 7 * m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getShapeCenter().y - m_backgrounds.at(1)->getSize().y * 0.5f + m_backgrounds.at(1)->getSize().y / 16.f * 11.f),
		ke::Origin::LEFT_MIDDLE, nullptr, L"", ke::TextScope::Math, 50, 1, winSize.y / 48, ke::Origin::LEFT_MIDDLE, sf::Color::Transparent, sf::Color::White, sf::Color::White, 0, sf::Color::Transparent, sf::Text::Regular, sf::Vector2f(6 * m_backgrounds.at(1)->getSize().x / 128, 0)));


	m_units.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getSize().y / 16), sf::Vector2f(winSize.x, m_backgrounds.at(1)->getShapeCenter().y - m_backgrounds.at(1)->getSize().y * 0.5f + m_backgrounds.at(1)->getSize().y / 16.f * 2.f),
		ke::Origin::RIGHT_MIDDLE, nullptr, L"m/s", winSize.y / 64, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(223, 255, 255, 223), 0, sf::Color::White));
	m_units.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getSize().y / 16), sf::Vector2f(winSize.x, m_backgrounds.at(1)->getShapeCenter().y - m_backgrounds.at(1)->getSize().y * 0.5f + m_backgrounds.at(1)->getSize().y / 16.f * 3.f),
		ke::Origin::RIGHT_MIDDLE, nullptr, L"m/s", winSize.y / 64, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(223, 255, 255, 223), 0, sf::Color::White));
	m_units.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getSize().y / 16), sf::Vector2f(winSize.x, m_backgrounds.at(1)->getShapeCenter().y - m_backgrounds.at(1)->getSize().y * 0.5f + m_backgrounds.at(1)->getSize().y / 16.f * 4.f),
		ke::Origin::RIGHT_MIDDLE, nullptr, L"kg", winSize.y / 64, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(223, 255, 255, 223), 0, sf::Color::White));
	m_units.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getSize().y / 16), sf::Vector2f(winSize.x, m_backgrounds.at(1)->getShapeCenter().y - m_backgrounds.at(1)->getSize().y * 0.5f + m_backgrounds.at(1)->getSize().y / 16.f * 5.f),
		ke::Origin::RIGHT_MIDDLE, nullptr, L"m", winSize.y / 64, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(223, 255, 255, 223), 0, sf::Color::White));
	m_units.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getSize().y / 16), sf::Vector2f(winSize.x, m_backgrounds.at(1)->getShapeCenter().y - m_backgrounds.at(1)->getSize().y * 0.5f + m_backgrounds.at(1)->getSize().y / 16.f * 6.5f),
		ke::Origin::RIGHT_MIDDLE, nullptr, L"m/s\u00B2", winSize.y / 64, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(223, 255, 255, 223), 0, sf::Color::White));
	m_units.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getSize().y / 16), sf::Vector2f(winSize.x, m_backgrounds.at(1)->getShapeCenter().y - m_backgrounds.at(1)->getSize().y * 0.5f + m_backgrounds.at(1)->getSize().y / 16.f * 7.5f),
		ke::Origin::RIGHT_MIDDLE, nullptr, L"kg/m\u00B3", winSize.y / 64, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(223, 255, 255, 223), 0, sf::Color::White));
	m_units.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getSize().y / 16), sf::Vector2f(winSize.x, m_backgrounds.at(1)->getShapeCenter().y - m_backgrounds.at(1)->getSize().y * 0.5f + m_backgrounds.at(1)->getSize().y / 16.f * 9.f),
		ke::Origin::RIGHT_MIDDLE, nullptr, L"m/s", winSize.y / 64, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(223, 255, 255, 223), 0, sf::Color::White));
	m_units.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getSize().y / 16), sf::Vector2f(winSize.x, m_backgrounds.at(1)->getShapeCenter().y - m_backgrounds.at(1)->getSize().y * 0.5f + m_backgrounds.at(1)->getSize().y / 16.f * 10.f),
		ke::Origin::RIGHT_MIDDLE, nullptr, L"m", winSize.y / 64, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(223, 255, 255, 223), 0, sf::Color::White));
	m_units.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(m_backgrounds.at(1)->getSize().x / 8, m_backgrounds.at(1)->getSize().y / 16), sf::Vector2f(winSize.x, m_backgrounds.at(1)->getShapeCenter().y - m_backgrounds.at(1)->getSize().y * 0.5f + m_backgrounds.at(1)->getSize().y / 16.f * 11.f),
		ke::Origin::RIGHT_MIDDLE, nullptr, L"m", winSize.y / 64, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color(223, 255, 255, 223), 0, sf::Color::White));


	m_modifiers.reserve(3);
	m_modifiers.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(m_backgrounds.at(1)->getSize().x, m_backgrounds.at(1)->getSize().y / 16), sf::Vector2f(winSize.x, winSize.y - m_backgrounds.at(1)->getSize().y / 8),
		ke::Origin::RIGHT_BOTTOM, nullptr, L"COPY OBJECT", winSize.y / 56, ke::Origin::MIDDLE_MIDDLE, sf::Color(128, 128, 128, 64), sf::Color::White, 0, sf::Color::White));
	m_modifiers.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(m_backgrounds.at(1)->getSize().x, m_backgrounds.at(1)->getSize().y / 16), sf::Vector2f(winSize.x, winSize.y - m_backgrounds.at(1)->getSize().y / 16),
		ke::Origin::RIGHT_BOTTOM, nullptr, L"CHANGE POSITION", winSize.y / 56, ke::Origin::MIDDLE_MIDDLE, sf::Color(128, 128, 128, 64), sf::Color::White, 0, sf::Color::White));
	m_modifiers.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(m_backgrounds.at(1)->getSize().x, m_backgrounds.at(1)->getSize().y / 16), sf::Vector2f(winSize.x, winSize.y),
		ke::Origin::RIGHT_BOTTOM, nullptr, L"DELETE OBJECT", winSize.y / 56, ke::Origin::MIDDLE_MIDDLE, sf::Color(255, 0, 0, 64), sf::Color::White, 0, sf::Color::White));

	for (auto& itr : m_symbols)
		itr->update({}, fake_event, sf::Mouse::Left, nullptr);
	for (auto& itr : m_units)
		itr->update({}, fake_event, sf::Mouse::Left, nullptr);
	for (auto& itr : m_modifiers)
		itr->update({}, fake_event, sf::Mouse::Left, nullptr);
}


void SimulationState::InitTimeGUI()
{
	sf::Texture slowDown_texture;
	sf::Texture speedUp_texture;

	slowDown_texture.loadFromFile("Textures/StateTextures/Simulation/SlowDownButton.png");
	speedUp_texture.loadFromFile("Textures/StateTextures/Simulation/SpeedUpButton.png");

	slowDown_texture.setSmooth(true);
	speedUp_texture.setSmooth(true);

	m_play_texture.loadFromFile("Textures/StateTextures/Simulation/startButton.png");
	m_pause_texture.loadFromFile("Textures/StateTextures/Simulation/stopButton.png");
	m_play_texture.setSmooth(true);
	m_pause_texture.setSmooth(true);


	m_time_menagers.reserve(4); // slow down | play / pause | speed up | time
	m_time_menagers.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.y / 16, winSize.y / 32), sf::Vector2f(0, winSize.y), ke::Origin::LEFT_BOTTOM, &slowDown_texture));
	m_time_menagers.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.y / 32, winSize.y / 32), sf::Vector2f(winSize.y / 16, winSize.y), ke::Origin::LEFT_BOTTOM, &m_play_texture));
	m_time_menagers.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.y / 16, winSize.y / 32), sf::Vector2f(3 * winSize.y / 32, winSize.y), ke::Origin::LEFT_BOTTOM, &speedUp_texture));
	m_time_menagers.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(winSize.y / 8, winSize.y / 32), sf::Vector2f(winSize.x / 5, winSize.y), ke::Origin::RIGHT_BOTTOM, nullptr, L"Time: \u00D71", winSize.y / 48, ke::Origin::LEFT_MIDDLE));
}





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





void SimulationState::reloadState()
{

}





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





void SimulationState::updateEvents(const MousePosition& mousePosition, float dt)
{
	// FEATURE: Quitting simulation

	if (p_quitCode == StateQuitCode::STATE_QUIT)
	{
		ke::SmoothColorChange(&m_stateMask, true, sf::Color::Black, sf::Color::Transparent, m_sm_color, 512, dt);

		m_objIconPanel.saveToFile();

		if (m_sm_color == ke::Colorf(sf::Color::Black))
		{
			switch (m_next_state)
			{
			case NextState::MAIN_MENU:
				states->back() = std::make_unique<MainMenu>(window, view);
				break;
			default:
				ke::throw_error("SimulationState::updateEvents() -> state quitting", "State not found", "ERROR");
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
			case NextState::MAIN_MENU:
				states->back() = std::make_unique<MainMenu>(window, view);
				break;
			default:
				ke::throw_error("SimulationState::updateEvents() -> state quitting", "State not found", "ERROR");
				break;
			}

			states->back()->InitState();
			return;
		}
	}
	else
	{
		m_outro_clock.restart();
		if (ke::SmoothColorChange(&m_stateMask, true, sf::Color::Transparent, sf::Color::Black, m_sm_color, 256, dt))
			m_ObjectLibraryOverlay->updateColors(mousePosition.byWindow, dt);
	}



	////////////////////////////////////////////////////////////////////////////////////////////////



	// FETURE: module & overlay event update

	m_StateControlPanel.updateEvents(mousePosition, dt);
	m_ObjectLibraryOverlay->updateEvents(mousePosition, dt);



	////////////////////////////////////////////////////////////////////////////////////////////////



	// FEATURE: *SIMULATION CORE* - updating simulation

	if (m_running)
	{
		m_deltaTime = dt;

		// FEATURE: centering view to object position
		
		if (m_selected_object != m_objects.begin())
			view->setCenter((*m_selected_object)->object.getPosition());
		else
			m_view_holding.update(mousePosition.byWindow * (view->getSize().x / winSize.x), sf::Mouse::Right);


		// FEATURE: updating objects with Object controller (ObjectController - menager)

		m_ObjController.updateObjects(m_deltaTime, m_time_scale, m_simulation_speed);


		// FEATURE: updating Placed Object preview

		if ((*m_icon_inv_iterator)->icon.isActive() || m_object_buffer_ready)
		{
			if (m_orbit_preview.isActive())
			{
				m_ObjController.updateObjectPreview(m_selected_object, mousePosition, view->getSize(), winSize);
			}
		}


		// FEATURE: updating selected object data

		if (m_selected_object != m_objects.begin())
		{
			m_VDController.updateDynamicData(m_selected_object);
		}
	}
	else
	{
		// FEATURE: view holding update

		m_view_holding.update(mousePosition.byWindow * (view->getSize().x / winSize.x), sf::Mouse::Right);
	}

	

	// FEATURE: filtering objects on screen

	m_onScreen.clear(); // checking objects on screen

	for (auto& itr : m_objects)
		if (itr->type() == STAR)
			if (!ke::isOutsideTheView(&itr->object, view, { view->getSize().y / 8, view->getSize().y / 8 }))
				m_onScreen.push_back(itr.get()); else;
		else
			if (!ke::isOutsideTheView(&itr->object, view, { view->getSize().y / 16, view->getSize().y / 16 }))
				m_onScreen.push_back(itr.get()); else;



	// FEATURE: positionning object shaders

	for (auto& itr : m_objects)
	{
		if (itr->type() == STAR)
		{
			sf::Vector2f position(window->mapCoordsToPixel(sf::Vector2f(itr->object.getPosition())));
			itr->getObjectShader()->setUniform("position", sf::Glsl::Vec2(position.x, -position.y + winSize.y));
			itr->getGlowShader()->setUniform("position", sf::Glsl::Vec2(position.x, -position.y + winSize.y));
		}
	}



	////////////////////////////////////////////////////////////////////////////////////////////////



	// FEATURE: updating space objects clicking properties

	for (auto& itr : m_objects)
	{
		itr->updateClickRadius();
		if (abs(mousePosition.byView.y - itr->object.getPosition().y) < itr->clickRange()->getRadius())
			if (itr->invaded(mousePosition.byView))
				itr->clickRange()->setActiveStatus(true);
			else
				itr->clickRange()->setActiveStatus(false);
		else
			itr->clickRange()->setActiveStatus(false);
	}


	// FEATURE: Setting Placed Object position to mouse position

	if (m_placed_object.isActive())
		m_placed_object.setPosition(mousePosition.byView);



	////////////////////////////////////////////////////////////////////////////////////////////////


	// FEATURE: Updating Cursor in text boxes

	m_object_name.updateCursor();

	for (auto& itr : m_values)
		itr.second->updateCursor();


	// FEATURE: updating Time box colors

	auto color_itr = m_timeGuiColors.begin();

	for (auto& itr : m_time_menagers)
	{
		ke::SmoothColorChange(itr.get(), itr->isInvaded(mousePosition.byWindow), sf::Color(255, 255, 255, 32), sf::Color(255, 255, 255, 0), *color_itr, 128, dt);
		++color_itr;
	}

	ke::SmoothOutlineColorChange(m_backgrounds.at(2).get(), m_backgrounds.at(2)->isInvaded(mousePosition.byWindow), sf::Color(192, 192, 192, 255), sf::Color(128, 128, 128, 255), m_backgrounds_colors.at(2), 128, dt);


	// FEATURE: module color update

	m_VDController.updateColors(mousePosition.byWindow, dt);
	m_objIconPanel.updateColors(mousePosition.byWindow, dt);
	m_StateControlPanel.updateColors(mousePosition.byWindow, dt);
	ke::SmoothOutlineColorChange(m_backgrounds.at(1).get(), m_backgrounds.at(1)->isInvaded(mousePosition.byWindow), sf::Color(192, 192, 192, 255), sf::Color(128, 128, 128, 255), m_backgrounds_colors.at(1), 512, dt);


	// FEATURE: overlays color update

	// ovrl mask update
	ke::SmoothColorChange(&m_overlayMask, m_quitOverlay != nullptr || m_ObjectLibraryOverlay->active(), sf::Color(0, 0, 0, 128), sf::Color::Transparent, m_om_color, 512, dt);

	if (m_quitOverlay != nullptr)
		m_quitOverlay->updateColors(mousePosition.byWindow, dt);

	if (m_ObjectLibraryOverlay->active())
		m_ObjectLibraryOverlay->updateColors(mousePosition.byWindow, dt);
}





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





void SimulationState::updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event)
{
	//	FEATURE: turning off poll events when overlay is active

	if (m_quitOverlay != nullptr)
	{
		m_quitOverlay->updatePollEvents(mousePosition, dt, event);
		
		switch (m_quitOverlay->quitStatus())
		{
		case QUITTING:
			p_quitCode = StateQuitCode::STATE_QUIT;
			m_next_state = MAIN_MENU;
			break;

		case QUITTING_AND_SAVING:
			p_quitCode = StateQuitCode::STATE_QUIT;
			m_next_state = MAIN_MENU;
			// TODO: SAVING
			break;

		case CLOSING_OVRL:
			m_quitOverlay = nullptr;
			break;
		default:
			break;
		}

		return;

	}

	if (m_ObjectLibraryOverlay->active())
	{
		m_ObjectLibraryOverlay->updatePollEvents(mousePosition, dt, event);
		return;
	}


	// FEATURE: quiting simulation

	if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::XButton1)
	{
		p_quitCode = StateQuitCode::STATE_QUIT;
		m_next_state = MAIN_MENU;
	}


	// FEATURE: updating modules & overlays poll events

	m_objIconPanel.updatePollEvents(mousePosition.byWindow, dt, event);
	m_StateControlPanel.updatePollEvents(mousePosition, dt, event, window, view);



	// FEATURE: getting object from Databese (Object Library Overlay)

	if (!m_ObjectLibraryOverlay->active())
	{
		if (m_ObjectLibraryOverlay->quitStatus() == OBJECT_LIBRARY_OverlayQuitStatus::QUITTING_WITHOUT_OBJECT)
		{
			m_ObjectLibraryOverlay->resetQuitStatus();
			m_object_buffer_ready = false; // for safety reasons
		}
		else if (m_ObjectLibraryOverlay->quitStatus() == OBJECT_LIBRARY_OverlayQuitStatus::QUITTING_WITH_OBJECT)
		{
			m_ObjectLibraryOverlay->resetQuitStatus();

			m_objectBuffer = *m_ObjectLibraryOverlay->output();
			m_ObjectLibraryOverlay->resetOutput();
			m_ObjController.createObjectPreview(&m_objectBuffer);

			m_icon_iterator = m_object_icons.begin() + 1; // set to sth that isn't .begin()

			m_placed_object.setActiveStatus(true);
			m_object_buffer_ready = true;
		}
	}


	// FEATURE: adding new object by user from top panel

	if (m_icon_iterator != m_object_icons.begin())
	{
		bool mouse_on_field = true;

		// checking if mouse is on field

		for (auto& itr : m_backgrounds)
			if (itr->isInvaded(mousePosition.byWindow))
				mouse_on_field = false;

		if (mouse_on_field)
		{
			if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
			{
				// checking if user hasn't clicked outside the field

				bool sth_clicked = false;
				for (auto itr = m_objects.begin(), eoi = m_objects.end(); itr != eoi; ++itr)
					if (abs(mousePosition.byView.y - (*itr)->object.getPosition().y) < (*itr)->clickRange()->getRadius())
						if ((*itr)->invaded(mousePosition.byView))
						{
							m_selected_object = itr;
							sth_clicked = true;
							break;
						}


				if (!sth_clicked)
				{
					// checking object name

					std::string name = m_objectBuffer.name();

					m_ObjController.checkName(name);


					// adding object by module

					m_ObjController.addObject(m_selected_object, &m_objectBuffer, mousePosition, view->getSize(), winSize, name);


					// pushing icon to history panel

					m_objIconPanel.pushIcon(m_objectBuffer);


					// Shift -> user can place more than one object 

					if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
					{
						//(*m_icon_iterator)->icon.setActiveStatus(false);

						m_icon_iterator = m_object_icons.begin();
						m_placed_object.setActiveStatus(false);
					}


					// giving object's name to the right panel

					m_object_name.setTextColor(sf::Color::White);
					m_object_name.setText(ke::fixed::stow(name));

					if (m_object_name.getText().size() > 35)
						m_object_name.setCharacterSize(winSize.y / 80);
					else if (m_object_name.getText().size() > 25)
						m_object_name.setCharacterSize(winSize.y / 64);
					else
						m_object_name.setCharacterSize(winSize.y / 48);

					//m_object_name.setEPS(false);


					// turning off previews

					m_orbit_preview.setActiveStatus(false);
					m_distance_preview.setActiveStatus(false);

				}
			}
			else
			{
				// updating object preview

				m_ObjController.updateObjectPreview(m_selected_object, mousePosition, view->getSize(), winSize);
			}
		}
		else
		{
			// turning off previews

			m_orbit_preview.setActiveStatus(false);
			m_distance_preview.setActiveStatus(false);
		}
	}



	// FEATURE: adding new object by user from Database (ObjectLibraryOverlay)

	if (m_object_buffer_ready)
	{
		bool mouse_on_field = true;

		// checking if mouse is on field

		for (auto& itr : m_backgrounds)
			if (itr->isInvaded(mousePosition.byWindow))
				mouse_on_field = false;

		if (mouse_on_field)
		{
			if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
			{
				// checking if user hasn't clicked outside the field

				bool sth_clicked = false;
				for (auto itr = m_objects.begin(), eoi = m_objects.end(); itr != eoi; ++itr)
					if (abs(mousePosition.byView.y - (*itr)->object.getPosition().y) < (*itr)->clickRange()->getRadius())
						if ((*itr)->invaded(mousePosition.byView))
						{
							m_selected_object = itr;
							sth_clicked = true;
							break;
						}


				if (!sth_clicked)
				{
					// checking object name

					std::string name = m_objectBuffer.name();

					m_ObjController.checkName(name);


					// adding object by module

					m_ObjController.addObject(m_selected_object, &m_objectBuffer, mousePosition, view->getSize(), winSize, name);


					// pushing icon to history panel

					m_objIconPanel.pushIcon(m_objectBuffer);


					// Shift -> user can place more than one object 

					if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
					{
						//(*m_icon_iterator)->icon.setActiveStatus(false);

						m_icon_iterator = m_object_icons.begin();
						m_placed_object.setActiveStatus(false);
					}


					// giving object's name to the right panel

					m_object_name.setTextColor(sf::Color::White);
					m_object_name.setText(ke::fixed::stow(name));

					if (m_object_name.getText().size() > 35)
						m_object_name.setCharacterSize(winSize.y / 80);
					else if (m_object_name.getText().size() > 25)
						m_object_name.setCharacterSize(winSize.y / 64);
					else
						m_object_name.setCharacterSize(winSize.y / 48);

					//m_object_name.setEPS(false);


					// turning off previews

					m_orbit_preview.setActiveStatus(false);
					m_distance_preview.setActiveStatus(false);

				}

				m_object_buffer_ready = false; // unloads buffer status
			}
			else
			{
				// updating object preview

				m_ObjController.updateObjectPreview(m_selected_object, mousePosition, view->getSize(), winSize);
			}
		}
		else
		{
			// turning off previews

			m_orbit_preview.setActiveStatus(false);
			m_distance_preview.setActiveStatus(false);
		}
	}




	// FEATURE: deleting object

	if (m_selected_object != m_objects.begin())
	{
		if (m_modifiers.front()->isClicked(sf::Mouse::Left, mousePosition.byWindow, event)) // BUTTON: COPY OBJECT
		{
			// duplicating object

			m_objectBuffer.load(m_selected_object);

			m_ObjController.createObjectPreview(&m_objectBuffer, m_selected_object);

			m_selected_object = m_objects.begin();
			m_placed_object.setActiveStatus(true);
			m_icon_iterator = m_object_icons.begin() + 1;
		}
		else if ((*(m_modifiers.begin() + 1))->isClicked(sf::Mouse::Left, mousePosition.byWindow, event)) // BUTTON: CHANGE POSITION
		{
			// changing object position

			m_objectBuffer.load(m_selected_object);

			m_ObjController.createObjectPreview(&m_objectBuffer, m_selected_object);
			m_ObjController.deleteObject(m_selected_object);
			m_VDController.setEmpty();

			m_selected_object = m_objects.begin();
			m_placed_object.setActiveStatus(true);
			m_icon_iterator = m_object_icons.begin() + 1;
		}
		else if (m_modifiers.back()->isClicked(sf::Mouse::Left, mousePosition.byWindow, event)) // BUTTON: DELETE OBJECT
		{
			// deleting object

			m_ObjController.deleteObject(m_selected_object);
			m_VDController.setEmpty();
		}


		// deleting object using keyboard

		else if (!m_text_entered)
		{
			if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Delete/* || event.key.code == sf::Keyboard::BackSpace*/))
			{
				m_ObjController.deleteObject(m_selected_object);
				m_VDController.setEmpty();
			}
		}
	}


	// FEATURE: restarting selected object

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape && !m_text_entered)
	{
		(*m_selected_object)->clickRange()->setOutlineColor(sf::Color(128, 128, 128, 64));
		m_selected_object = m_objects.begin();
	}



	// FEATURE: checking if icon is invaded

	bool icons_invaded = false;
	for (auto itr = m_object_icons.begin() + 1, eoi = m_object_icons.end(); itr != eoi; ++itr)
		if ((*itr)->icon.isInvaded(mousePosition.byWindow))
		{
			m_icon_inv_iterator = itr;
			icons_invaded = true;
			break;
		}

	if (!icons_invaded)
		m_icon_inv_iterator = m_object_icons.begin();




	// FEATURE: iterating through objects with keyboard

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Tab && event.key.shift && !m_text_entered)
	{
		if (m_selected_object != m_objects.begin())
			--m_selected_object;
		else
			m_selected_object = m_objects.end() - 1;

		m_VDController.loadData(m_selected_object, winSize);
	}
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Tab && !m_text_entered)
	{
		++m_selected_object;

		if (m_selected_object == m_objects.end())
		{
			m_selected_object = m_objects.begin();
			m_VDController.setEmpty();
		}
		else
		{
			m_VDController.loadData(m_selected_object, winSize);
		}
	}




	// FEATURE: updating view holding (click)

	m_view_holding.updateClick(mousePosition.byWindow * (view->getSize().x / winSize.x), sf::Mouse::Right, event);


	// FEATURE: zooming in / out

	if (event.type == sf::Event::MouseWheelScrolled)
	{
		if (event.mouseWheelScroll.delta < 0)
			if (view->getSize().y < 1e+8)
				view->zoom(1.1); else;
		else if (event.mouseWheelScroll.delta > 0)
			view->zoom(0.9);

		//std::cout << view->getSize().y << '\n';

		// updating previews size & properties

		m_orbit_preview.setOutlineThickness(view->getSize().y / 256);
		m_objects.front()->object.setRadius(view->getSize().x / winSize.x * 4);
		m_objects.front()->object.setOutlineThickness(view->getSize().x / winSize.x);


		long double distance = position_to_destance((*m_selected_object)->object.getPosition(), m_placed_object.getPosition()) / m_space_scale;
		std::wstringstream dist_buffer;

		if (m_objects.size() == 1)
			dist_buffer << std::fixed << std::setprecision(2) << " ";
		else if (distance > ly)
			dist_buffer << std::fixed << std::setprecision(2) << distance / ly << " light years";
		else if (distance > au)
			dist_buffer << std::fixed << std::setprecision(2) << distance / au << " au";
		else
			dist_buffer << std::fixed << std::setprecision(2) << distance << " m";

		m_orbit_preview.setPosition((*m_selected_object)->object.getPosition());
		m_orbit_preview.setRadius(distance * m_space_scale);

		m_distance_preview.setPosition(mousePosition.byWindow);
		m_distance_preview.setTextPosition(ke::Origin::LEFT_MIDDLE, { winSize.x / 32 + winSize.x * m_placed_object.getRadius() / view->getSize().x, 0 });
		m_distance_preview.setText(dist_buffer.str());

		for (auto& itr : m_objects)
		{
			//std::cout << view->getSize().y / itr->object.getSize().y << '\n';
			itr->clickRange()->setOutlineThickness(view->getSize().x / winSize.x * 2);
			itr->clickRange()->setRadius(view->getSize().x / winSize.x * 16);


			// shader scaling

			itr->getObjectShader()->setUniform("basic_a", 1.f - itr->object.getSize().y / view->getSize().y);
			//itr->getGlowShader()->setUniform("basic_a", (itr->object.getSize().y / view->getSize().y * 0.75f <= 1) ? itr->object.getSize().y / view->getSize().y * 0.75f : 1.0f);
			itr->getGlowShader()->setUniform("size", itr->object.getSize().y / view->getSize().y * winSize.y * 2.f * m_brightness_scale);


			if (view->getSize().y / itr->object.getSize().y > itr->data.brightness)
			{
				float shader_size = itr->data.brightness - view->getSize().y / itr->object.getSize().y / winSize.y;
				itr->getObjectShader()->setUniform("size",  (shader_size * m_brightness_scale >= 0) ? shader_size * m_brightness_scale : 0);
				//std::cout << "size: " << itr->data.brightness - view->getSize().y / itr->object.getSize().y / winSize.y << '\n';
			}
		}
	}


	// FEATURE: centering view to object

	if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S) && !m_text_entered)
	{
		if (m_selected_object != m_objects.begin())
		{
			view->setSize(sf::Vector2f((*m_selected_object)->object.getRadius() * 16, (*m_selected_object)->object.getRadius() * 9));

			m_orbit_preview.setOutlineThickness(view->getSize().y / 256);
			m_objects.front()->object.setRadius(view->getSize().x / winSize.x * 4);
			m_objects.front()->object.setOutlineThickness(view->getSize().x / winSize.x);

			view->setCenter((*m_selected_object)->object.getPosition());
		}
	}



	if (m_backgrounds.at(0)->isInvaded(mousePosition.byWindow)) // top panel 
	{
		// FEATURE: creating placed object

		if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
		{
			m_icon_iterator = m_object_icons.begin();
			m_placed_object.setActiveStatus(false);
		}

		for (auto itr = m_object_icons.begin() + 1, eoi = m_object_icons.end(); itr != eoi; ++itr)
			if ((*itr)->icon.isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
			{
				m_ObjController.createObjectPreview(&m_objectBuffer, m_selected_object, itr);
				m_icon_iterator = itr;
				m_placed_object.setActiveStatus(true);
				break;
			}
	}
	if (m_backgrounds.at(1)->isInvaded(mousePosition.byWindow)) // data panel
	{
		if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
		{
			for (auto& itr : m_values)
			{
				if (!itr.second->getEPS())
				{
					if (itr.second->isInvaded(mousePosition.byWindow))
					{
						std::wstring text_check = itr.second->getText();

						for (auto& i : text_check)
							if (i == '.' || i == L'\u00B0' || i == ' ')
								i = L'0';

						bool zero = true;
						for (auto& i : text_check)
							if (i != L'0')
								zero = false;

						if (zero)
							itr.second->setText(L"");
					}
				}
				else if (!itr.second->isInvaded(mousePosition.byWindow))
				{
					m_VDController.loadData(m_selected_object, winSize);
				}
			}
		}
	}
	else if (m_backgrounds.at(2)->isInvaded(mousePosition.byWindow)) // time panel
	{
		// FEATURE: changing time using time panel

		if (m_time_menagers.at(1)->isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
			if (m_running)
				m_TimeController.stop(m_running, &m_play_texture);
			else
				m_TimeController.resume(m_running, &m_pause_texture);
		else if (m_time_menagers.at(0)->isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
			m_TimeController.slowDown(m_simulation_speed, 2);
		else if (m_time_menagers.at(2)->isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
			m_TimeController.speedUp(m_simulation_speed, 2);
		else if (m_time_menagers.at(3)->isClicked(sf::Mouse::Right, mousePosition.byWindow, event))
			m_TimeController.slowDown(m_simulation_speed, 2);
		else if (m_time_menagers.at(3)->isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
			m_TimeController.speedUp(m_simulation_speed, 2);
	}
	else // other
	{
		// FEATURE: picking / selecting object with mouse

		bool sth_clicked = false;
		for (auto itr = m_objects.begin(), eoi = m_objects.end(); itr != eoi; ++itr)
			if (abs(mousePosition.byView.y - (*itr)->object.getPosition().y) < (*itr)->clickRange()->getRadius())
				if ((*itr)->clicked(sf::Mouse::Left, mousePosition.byView, event) && m_icon_iterator == m_object_icons.begin())
				{
					(*m_selected_object)->clickRange()->setOutlineColor(sf::Color(128, 128, 128, 64));
					m_selected_object = itr;
					(*m_selected_object)->clickRange()->setOutlineColor(sf::Color(128, 128, 128, 192));
					sth_clicked = true;

					m_VDController.loadData(m_selected_object, winSize);

					break;
				}


		if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left && !sth_clicked && m_icon_iterator == m_object_icons.begin())
		{
			m_selected_object = m_objects.begin();

			//m_object_name.setText(L"");
			//m_object_name.setEPS(false);
			//m_object_name.setCharacterSize(winSize.y / 48);

			m_VDController.setEmpty();
		}
	}





	// FEATURE: manipulating time using keyboard

	if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) && !m_text_entered)
	{
		if (m_running)
			m_TimeController.stop(m_running, &m_play_texture);
		else
			m_TimeController.resume(m_running, &m_pause_texture);
	}
	else if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) && !m_text_entered)
	{
		m_TimeController.slowDown(m_simulation_speed, 2);
	}
	else if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) && !m_text_entered)
	{
		m_TimeController.speedUp(m_simulation_speed, 2);
	}






	// FETURE: text entered status update
	// TODO: optimise

	bool te_buffer = false; // text entered?

	for (auto& itr : m_values)
		if (itr.second->getEPS())
			te_buffer = true;

	if (m_object_name.getEPS())
		te_buffer = true;

	m_text_entered = te_buffer;



	// FEATURE: updating object name display size and changing object name

	if (m_selected_object != m_objects.begin())
	{
		//for (auto& iterator : m_values)
		//	iterator.second->update(mousePosition.byWindow, event, sf::Mouse::Left, view);

		if (m_values["VELOCITY"]->update(mousePosition.byWindow, event, sf::Mouse::Left, view))
			m_TimeController.stop(m_running, &m_play_texture);
		if (m_values["V_ANGLE"]->update(mousePosition.byWindow, event, sf::Mouse::Left, view))
			m_TimeController.stop(m_running, &m_play_texture);
		if (m_values["VECTOR_VEL_X"]->update(mousePosition.byWindow, event, sf::Mouse::Left, view))
			m_TimeController.stop(m_running, &m_play_texture);
		if (m_values["VECTOR_VEL_Y"]->update(mousePosition.byWindow, event, sf::Mouse::Left, view))
			m_TimeController.stop(m_running, &m_play_texture);
		if (m_values["MASS"]->update(mousePosition.byWindow, event, sf::Mouse::Left, view))
			m_TimeController.stop(m_running, &m_play_texture);
		if (m_values["RADIUS"]->update(mousePosition.byWindow, event, sf::Mouse::Left, view))
			m_TimeController.stop(m_running, &m_play_texture);
		if (m_values["SURFACE_G"]->update(mousePosition.byWindow, event, sf::Mouse::Left, view))
			m_TimeController.stop(m_running, &m_play_texture);
		if (m_values["DENSITY"]->update(mousePosition.byWindow, event, sf::Mouse::Left, view))
			m_TimeController.stop(m_running, &m_play_texture);
		if (m_values["ESCAPE_VEL"]->update(mousePosition.byWindow, event, sf::Mouse::Left, view))
			m_TimeController.stop(m_running, &m_play_texture);


		if (m_object_name.update(mousePosition.byWindow, event, sf::Mouse::Left, nullptr) > 0)
		{
			if (m_object_name.getText().size() > 35)
				m_object_name.setCharacterSize(winSize.y / 80);
			else if (m_object_name.getText().size() > 25)
				m_object_name.setCharacterSize(winSize.y / 64);
			else
				m_object_name.setCharacterSize(winSize.y / 48);
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
		{
			m_VDController.checkInputString();
			m_VDController.updateStaticData(m_selected_object, &m_object_name);
		}

	}
	

	// FEATURE: setting object name on object's name preview panel (background_3)

	if (m_icon_inv_iterator != m_object_icons.begin())
		m_backgrounds.at(3)->setText(ke::fixed::stow((*m_icon_inv_iterator)->object_name()));
	else if (m_placed_object.isActive())
		m_backgrounds.at(3)->setText(ke::fixed::stow(m_objectBuffer.name()));
	else if (m_selected_object != m_objects.begin())
		m_backgrounds.at(3)->setText(ke::fixed::stow((*m_selected_object)->name()));
	else
		m_backgrounds.at(3)->setText(L"");
}





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





void SimulationState::renderBackground()
{
	//window->draw(*m_stateBackground.getShape(), &m_test_shader);

	for (auto& itr : m_objects)
	{
		window->draw(*m_shaderMask.getShape(), itr->getObjectShader());
		window->draw(*m_shaderMask.getShape(), itr->getGlowShader());
	}
}


void SimulationState::renderByView()
{
	//for (auto itr = m_test_orbits.rbegin(), eoi = m_test_orbits.rend(); itr != eoi; ++itr)
		//(*itr)->render(window);

	m_orbit_preview.render(window);
	m_placed_object.render(window);




	//if (m_running)
	for (auto& itr : m_onScreen)
		itr->render(window);


	/*else
		for (auto itr = m_objects.rbegin(), eoi = m_objects.rend(); itr != eoi; ++itr)
			(*itr)->render(window);*/

	//m_objects.front()->render(window);
}


void SimulationState::renderByWindow()
{
	m_distance_preview.render(window);


	for (auto& itr : m_backgrounds)
		itr->render(window);

	for (auto& itr : m_project_menagers)
		itr->render(window);

	for (auto& itr : m_state_controllers)
		itr->render(window);

	for (auto& itr : m_time_menagers)
		itr->render(window);

	for (auto& itr : m_tools)
		itr->render(window);

	for (auto& itr : m_iconUI)
		itr->render(window);

	for (auto& itr : m_object_icons)
		itr->icon.render(window);


	m_object_name.render(window);

	for (auto& itr : m_symbols)
		itr->render(window);

	for (auto& itr : m_values)
		itr.second->render(window);

	for (auto& itr : m_units)
		itr->render(window);

	for (auto& itr : m_modifiers)
		itr->render(window);



	m_overlayMask.render(window);

	if (m_quitOverlay != nullptr)
		m_quitOverlay->render(window);

	m_ObjectLibraryOverlay->render();
	

	m_stateMask.render(window);

}
