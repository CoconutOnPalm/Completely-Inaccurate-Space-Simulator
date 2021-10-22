#include "ObjectLibraryOverlay.hpp"

#define object_ptr (*m_selected)

ObjectLibraryOverlay::ObjectLibraryOverlay()
	: m_quitStatus(false)
	, m_active(false)
	, m_window(nullptr)
	, m_next_position(0)
	, m_offset(110)
	, m_view_scrolling(false)
	, m_next_vpos(0)
	, m_last_vpos(0)
{
}

ObjectLibraryOverlay::~ObjectLibraryOverlay()
{

}

void ObjectLibraryOverlay::assign(sf::RenderWindow* window)
{
	m_window = window;
}

void ObjectLibraryOverlay::initUI()
{
	sf::Vector2f winsize(m_window->getSize());


	m_background.create(sf::Vector2f(winsize.x * 0.75, winsize.y), winsize * 0.5f, ke::Origin::MIDDLE_MIDDLE, std::wstring(), 0, ke::Origin::MIDDLE_MIDDLE, sf::Color::Black);
	m_top_section.create(sf::Vector2f(winsize.x * 0.75, winsize.y / 9), sf::Vector2f(winsize.x / 2, 0), ke::Origin::MIDDLE_TOP, std::wstring(), 0, ke::Origin::MIDDLE_MIDDLE, sf::Color(8, 8, 8, 255));
	m_right_section.create(sf::Vector2f(winsize.x * 0.2, winsize.y), sf::Vector2f(winsize.x - winsize.x / 8, 0), ke::Origin::RIGHT_TOP, std::wstring(), 0, ke::Origin::MIDDLE_MIDDLE, sf::Color(16, 16, 16, 255));

	m_next_position = winsize.y / 9;


	m_search_box.create(sf::Vector2f(winsize.x * 0.25, winsize.y / 12), sf::Vector2f(winsize.x / 8 + winsize.x / 64, winsize.y / 18), ke::Origin::LEFT_MIDDLE, nullptr,
		L"Search...", ke::TextScope::ASCII_Everything, 50, 1, winsize.y / 32, ke::Origin::LEFT_MIDDLE, sf::Color(32, 32, 32, 255),
		sf::Color::White, sf::Color(64, 64, 64, 255), 0, sf::Color::Transparent, {}, sf::Vector2f(winsize.x * 0.0125, 0));

	// | favourite | by systems |    A-Z    |    Z-A    |
	m_filtering_options[0].create(sf::Vector2f(winsize.x / 64, winsize.x / 64), sf::Vector2f(winsize.x * 0.45, winsize.y / 18), ke::Origin::MIDDLE_MIDDLE, "Textures/StateTextures/Simulation/EmptyStar.png");
	m_filtering_options[1].create(sf::Vector2f(winsize.x / 64, winsize.x / 64), sf::Vector2f(winsize.x * 0.45 + winsize.x * 0.0625, winsize.y / 18), ke::Origin::MIDDLE_MIDDLE, nullptr, std::wstring(), {}, {}, sf::Color::Green);
	m_filtering_options[2].create(sf::Vector2f(winsize.x / 64, winsize.x / 64), sf::Vector2f(winsize.x * 0.45 + winsize.x * 0.1250, winsize.y / 18), ke::Origin::MIDDLE_MIDDLE, nullptr, std::wstring(), {}, {}, sf::Color::Green);
	m_filtering_options[3].create(sf::Vector2f(winsize.x / 64, winsize.x / 64), sf::Vector2f(winsize.x * 0.45 + winsize.x * 0.1875, winsize.y / 18), ke::Origin::MIDDLE_MIDDLE, nullptr, std::wstring(), {}, {}, sf::Color::Green);

	m_add_button.create(sf::Vector2f(winsize.x * 0.16, winsize.y / 12), sf::Vector2f(m_right_section.getShapeCenter().x, winsize.y - winsize.y / 15), ke::Origin::MIDDLE_MIDDLE, nullptr, L"ADD", winsize.y / 18, ke::Origin::MIDDLE_MIDDLE, sf::Color(75, 148, 49, 128), sf::Color(255, 255, 255, 129));
	m_close_button.create(sf::Vector2f(winsize.x * 0.16, winsize.y / 12), sf::Vector2f(m_right_section.getShapeCenter().x, winsize.y / 15), ke::Origin::MIDDLE_MIDDLE, nullptr, L"CLOSE", winsize.y / 18, ke::Origin::MIDDLE_MIDDLE, sf::Color(168, 38, 29, 128), sf::Color(255, 255, 255, 129));

	m_add_button.setTextStyle(sf::Text::Bold);
	m_close_button.setTextStyle(sf::Text::Bold);

	m_add_button.setFont(ke::Font::Calibri);
	m_close_button.setFont(ke::Font::Calibri);


	// | name | mass | radius | type | class | subtype | system name |
	m_object_info[0].create(sf::Vector2f(winsize.x * 0.16, winsize.y / 20), sf::Vector2f(m_right_section.getShapeCenter().x, winsize.y / 5 + 0 * winsize.y / 24 + 0 * winsize.y / 48), ke::Origin::MIDDLE_MIDDLE, nullptr, L"name", winsize.y / 48, ke::Origin::MIDDLE_MIDDLE, sf::Color(32, 32, 32, 128), sf::Color(255, 255, 255, 128));
	m_object_info[1].create(sf::Vector2f(winsize.x * 0.16, winsize.y / 20), sf::Vector2f(m_right_section.getShapeCenter().x, winsize.y / 5 + 2 * winsize.y / 24 + 1 * winsize.y / 48), ke::Origin::MIDDLE_MIDDLE, nullptr, L"mass", winsize.y / 48, ke::Origin::MIDDLE_MIDDLE, sf::Color(32, 32, 32, 128), sf::Color(255, 255, 255, 128));
	m_object_info[2].create(sf::Vector2f(winsize.x * 0.16, winsize.y / 20), sf::Vector2f(m_right_section.getShapeCenter().x, winsize.y / 5 + 3 * winsize.y / 24 + 2 * winsize.y / 48), ke::Origin::MIDDLE_MIDDLE, nullptr, L"radius", winsize.y / 48, ke::Origin::MIDDLE_MIDDLE, sf::Color(32, 32, 32, 128), sf::Color(255, 255, 255, 128));
	m_object_info[3].create(sf::Vector2f(winsize.x * 0.16, winsize.y / 20), sf::Vector2f(m_right_section.getShapeCenter().x, winsize.y / 5 + 5 * winsize.y / 24 + 3 * winsize.y / 48), ke::Origin::MIDDLE_MIDDLE, nullptr, L"class", winsize.y / 48, ke::Origin::MIDDLE_MIDDLE, sf::Color(32, 32, 32, 128), sf::Color(255, 255, 255, 128));
	m_object_info[4].create(sf::Vector2f(winsize.x * 0.16, winsize.y / 20), sf::Vector2f(m_right_section.getShapeCenter().x, winsize.y / 5 + 6 * winsize.y / 24 + 4 * winsize.y / 48), ke::Origin::MIDDLE_MIDDLE, nullptr, L"subtype", winsize.y / 48, ke::Origin::MIDDLE_MIDDLE, sf::Color(32, 32, 32, 128), sf::Color(255, 255, 255, 128));
	m_object_info[5].create(sf::Vector2f(winsize.x * 0.16, winsize.y / 20), sf::Vector2f(m_right_section.getShapeCenter().x, winsize.y / 5 + 8 * winsize.y / 24 + 5 * winsize.y / 48), ke::Origin::MIDDLE_MIDDLE, nullptr, L"system name", winsize.y / 48, ke::Origin::MIDDLE_MIDDLE, sf::Color(32, 32, 32, 128), sf::Color(255, 255, 255, 128));
	//m_object_info[6].create(sf::Vector2f(winsize.x * 0.16, winsize.y / 20), sf::Vector2f(m_right_section.getShapeCenter().x, winsize.y / 5 + 9 * winsize.y / 24 + 6 * winsize.y / 48), ke::Origin::MIDDLE_MIDDLE, nullptr, L"system name", winsize.y / 48, ke::Origin::MIDDLE_MIDDLE, sf::Color(32, 32, 32, 128), sf::Color(255, 255, 255, 128));

	m_GUI_colors.fill(ke::Colorf(255, 255, 255, 192));


	m_hints.create(sf::Vector2f(winsize.x * 0.16, winsize.y / 9), sf::Vector2f(m_right_section.getShapeCenter().x, (m_add_button.getShapeCenter().y + m_object_info.back().getShapeCenter().y) * 0.5), ke::Origin::MIDDLE_MIDDLE, nullptr, L"", winsize.y / 48, ke::Origin::MIDDLE_MIDDLE, sf::Color(32, 32, 32, 128), sf::Color(255, 255, 255, 128));

	m_slider.create(sf::Vector2f(winsize.x / 128, winsize.y - winsize.y / 9), sf::Vector2f(m_background.getShapeCenter().x + m_background.getSize().x * 0.5 - m_right_section.getSize().x, winsize.y),
		winsize.y, ke::Origin::RIGHT_BOTTOM, nullptr, nullptr, sf::Color::White, sf::Color((64, 64, 64, 64)));
}

void ObjectLibraryOverlay::loadObjects()
{
	sf::Vector2f winsize(m_window->getSize());
	sf::Vector2f field_size(m_background.getSize().x - m_right_section.getSize().x - m_slider.getSize().x, winsize.y - m_top_section.getSize().y);

	float field_beg = m_background.getShapeCenter().x - m_background.getSize().x * 0.5; // begginging of the overlay filed
	const int icons_per_row = 10;
	float uniheight = field_size.x / icons_per_row; // height of objects and system names

	m_obj_view.setSize(winsize);
	m_obj_view.setCenter(winsize.x * 0.5, winsize.y * 0.5);

	ke::debug::printVector2(m_obj_view.getSize(), "viewSize");
	ke::debug::printVector2(m_obj_view.getCenter(), "viewCenter");



	for (auto& itr : FileStorage::Get().linked_space_objects_database)
	{
		ke::FileStream loadStr(itr.second, std::ios::in | std::ios::binary);

		if (!loadStr.loaded())
			ke::throw_error("ObjectLibraryOverlay::loadObjects()", "failed to load .sodb file", "FILE ERROR");

		std::string system_name;
		int obj_count;

		loadStr.binRead(system_name);
		loadStr.binRead(obj_count);


		//std::cout << system_name << ", " << obj_count << '\n';

		m_system_names.emplace_back(std::make_unique<ke::Button>(sf::Vector2f(field_size.x, uniheight), sf::Vector2f(field_beg, m_next_position), ke::Origin::LEFT_TOP,
			nullptr, ke::fixed::stow(system_name), field_size.y / 20, ke::Origin::LEFT_MIDDLE, sf::Color::Black, sf::Color::White, 0, sf::Color::Transparent, 0, sf::Text::Bold, sf::Vector2f(field_size.x / 100, uniheight / 10)));

		m_next_position += uniheight;

		m_objects.reserve(obj_count);

		std::string obj_name = "UNDEFINED";
		int type = ObjectType::UNDEFINED;
		int obj_class = ObjectClass::CLASS_UNDEFINED;
		int subtype = ObjectSubtype::SUBTYPE_UNDEFINED;
		long double mass = 1, radius = 1;
		std::string filename = "Textures/AudioIcon.png";
		std::string texture_path = "Textures/AudioIcon.png";
		float brightness = 0;
		sf::Vector3f color(1.0, 1.0, 1.0);

		sf::Vector2f position(field_beg, m_next_position);
		const sf::Vector2f size(field_size.x / icons_per_row, field_size.x / icons_per_row);

		for (int i = 0; i < obj_count; i++)
		{
			position.x = field_beg + (i % (icons_per_row)) * size.x;

			loadStr.binRead(obj_name);
			loadStr.binRead(type);
			loadStr.binRead(obj_class);
			loadStr.binRead(subtype);

			loadStr.binRead(mass);
			loadStr.binRead(radius);

			loadStr.binRead(filename);
			loadStr.binRead(texture_path);

			loadStr.binRead(brightness);
			loadStr.binRead(color.x);
			loadStr.binRead(color.y);
			loadStr.binRead(color.z);

			//std::cout << obj_name << '\n';



			if (i == 0)
			{
				m_system_begining.push_back(m_objects.begin());

				if (m_system_bounds.empty())
				{
					m_system_bounds.push_back(std::make_pair<unsigned int, unsigned int>(0, obj_count - 1));
					//std::cout << system_name << '\n';
					//std::cout << "Dla system_bounds.size() = 0:\n";
					//std::cout << 0 << ' ' << obj_count - 1 << '\n';
				}
				else
				{
					m_system_bounds.push_back(std::make_pair<unsigned int, unsigned int>(m_system_bounds.back().second + 1, m_system_bounds.back().second + obj_count));
					//std::cout << system_name << '\n';
					//std::cout << "Dla system_bounds.size() > 0:\n";
					//std::cout << m_system_bounds.back().second + 1 << ' ' << m_system_bounds.back().second + obj_count << '\n';
				}

			}

			if (i % (icons_per_row) == 0 && i)
			{
				position.y += uniheight;
				//std::cout << i << '\n';
			}

			m_objects.emplace_back(std::make_unique<ObjectIcon>(texture_path, filename, size, position, obj_name, type, obj_class, subtype, mass, radius, brightness, color));
			//m_objects.back()->icon.getTextureShape()->setFillColor(sf::Color(255, 255, 255, 128));

			//ke::debug::printVector2(position, std::to_string(i));
		}

		m_next_position = position.y + uniheight;
	}



	m_obj_colors.reserve(m_objects.size());

	for (int i = 0; i < m_objects.size(); ++i)
		m_obj_colors.push_back(sf::Color::Transparent);

	
	m_slider.setFieldHeight((m_next_position > winsize.y) ? m_next_position :  winsize.y);
	m_slider.setViewPositionShift(0, nullptr);

	m_view_barrier.setView(&m_obj_view);
	m_view_barrier.setBorders(sf::Vector2f(0, 0), sf::Vector2f(winsize.x, m_next_position));

	for (auto& itr : m_objects)
		if (ke::ionRange(itr->icon.getPosition().y, -1.5 * itr->icon.getSize().y, m_window->getSize().y + 1.5 * itr->icon.getSize().y))
			m_on_screen.push_back(itr.get());

	std::cout << m_system_bounds.size() << '\n';
	for (auto& itr : m_system_bounds)
		std::cout << itr.first << ' ' << itr.second << '\n';

	m_selected = m_objects.end();
}

void ObjectLibraryOverlay::updateEvents(const MousePosition& mousePosition, float dt)
{
	m_search_box.updateCursor();
	m_slider.updateSliderPosition(&m_obj_view);


	m_view_barrier.update(mousePosition.byWindow, sf::Mouse::Right);

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Right))
		m_slider.updateSliderPosition(&m_obj_view);
}

void ObjectLibraryOverlay::updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event)
{

	if (!m_background.isInvaded(mousePosition.byWindow) && event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
	{
		m_active = false;
		return;
	}



	m_search_box.update(mousePosition.byWindow, event, sf::Mouse::Left, nullptr);

	m_slider.update(mousePosition.byWindow, event, sf::Mouse::Left, &m_obj_view);
	m_view_barrier.updateClick(mousePosition.byWindow, sf::Mouse::Right, event);

	if (event.type == sf::Event::MouseWheelScrolled)
	{
		if (event.mouseWheelScroll.delta > 0)
		{
			//m_next_vpos -= m_window->getSize().y / 3600;
			//ke::varGuard(m_next_vpos, m_window->getSize().y / 2, m_window->getSize().y / 2);
			m_obj_view.move(0, -static_cast<float>(m_window->getSize().y) / 27);
		}
		else if (event.mouseWheelScroll.delta < 0)
		{
			//m_next_vpos += m_window->getSize().y / 3600;
			//ke::varGuard(m_next_vpos, m_slider.getFieldHeight() - m_window->getSize().y / 2, m_slider.getFieldHeight() - m_window->getSize().y / 2);
			m_obj_view.move(0, m_window->getSize().y / 27);
		}


		// selecting objects that are visible on screen

		m_on_screen.clear();

		int color_itr = 0;
		for (auto& itr : m_objects)
		{
			if (ke::ionRange(itr->icon.getPosition().y, -1.5 * itr->icon.getSize().y, m_window->getSize().y + 1.5 * itr->icon.getSize().y))
				m_on_screen.push_back(itr.get());

			color_itr++;
		}
	}

	ke::ViewHolding(&m_obj_view, sf::Mouse::Middle, mPosView, event, sf::Vector2f(0, 0), sf::Vector2f(m_window->getSize().x, m_slider.getFieldHeight()));



	for (auto itr = m_objects.begin(); itr != m_objects.end(); ++itr)
	{
		if (!ke::ionRange((*itr)->icon.getPosition().y, -1.5 * (*itr)->icon.getSize().y, m_window->getSize().y + 1.5 * (*itr)->icon.getSize().y))
			continue;

		if ((*itr)->icon.isClicked(sf::Mouse::Left, mPosView, event))
		{
			if (m_selected == itr)
			{
				(*m_selected)->icon.setOutlineColor(sf::Color::Transparent);
				(*m_selected)->icon.setOutlineThickness(0);

				m_selected = m_objects.end();
				m_output.load(ObjectType::UNDEFINED, ObjectClass::CLASS_UNDEFINED, ObjectSubtype::SUBTYPE_UNDEFINED, 0.0, 0.0, "__EMPTY", "Textures/AudiIcon.png", "Textures/IconTextures/Empty_icon.png", 0, sf::Vector3f(0.0, 0.0, 0.0));
				updateObjectInfo();
				return;
			}
			else
			{
				if (m_selected != m_objects.end())
				{
					(*m_selected)->icon.setOutlineColor(sf::Color::Transparent);
					(*m_selected)->icon.setOutlineThickness(0);
				}

				m_output.load(**itr);
				m_selected = itr;
				(*m_selected)->icon.setOutlineColor(sf::Color(0, 64, 0, 255));
				(*m_selected)->icon.setOutlineThickness(m_window->getSize().x / 512);
				updateObjectInfo();
			}
		}
	}

}



void ObjectLibraryOverlay::updateColors(const sf::Vector2f& mousePosition, const float dt)
{
	auto GUI_color_itr = m_GUI_colors.begin();

	for (auto& itr : m_object_info)
	{
		ke::SmoothTextColorChange(&itr, itr.isInvaded(mousePosition), sf::Color::White, sf::Color(255, 255, 255, 192), *GUI_color_itr, 511, dt);
		++GUI_color_itr;
	}


	auto obj_color_itr = m_obj_colors.begin();

	for (auto itr = m_on_screen.begin(); itr != m_on_screen.end(); ++itr)
	{
		ke::SmoothColorChange(&(*itr)->icon, (*itr)->icon.isInvaded(mPosView), sf::Color::Transparent, sf::Color(0, 0, 0, 96), *obj_color_itr, 511, dt);
		++obj_color_itr;
	}
}

int ObjectLibraryOverlay::quitStatus() const
{
	return m_quitStatus;
}

void ObjectLibraryOverlay::render()
{
	if (!m_active)
		return;

	m_window->setView(m_window->getDefaultView());

	m_background.render(m_window);


	m_window->setView(m_obj_view);

	for (auto& itr : m_system_names)
		itr->render(m_window);

	for (auto& itr : m_on_screen)
		itr->icon.render(m_window);

	mPosView = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window));


	m_window->setView(m_window->getDefaultView());

	m_top_section.render(m_window);
	m_right_section.render(m_window);

	m_search_box.render(m_window);

	for (auto& itr : m_filtering_options)
		itr.render(m_window);

	m_add_button.render(m_window);
	m_close_button.render(m_window);

	for (auto& itr : m_object_info)
		itr.render(m_window);

	m_hints.render(m_window);

	m_slider.render(m_window);
}

bool ObjectLibraryOverlay::active() const
{
	return m_active;
}

void ObjectLibraryOverlay::activate()
{
	m_active = true;
}

void ObjectLibraryOverlay::deactivate()
{
	m_active = false;
}

ObjectBuffer* ObjectLibraryOverlay::output()
{
	return &m_output;
}


////////////////////////////////


void ObjectLibraryOverlay::updateObjectInfo()
{
	if (m_selected != m_objects.end())
	{
		m_object_info.at(0).setText(ke::fixed::stow(object_ptr->object_name()));

		m_object_info.at(3).setText(ke::fixed::stow(TypeTranslator::getClassName(object_ptr->object_class())));
		m_object_info.at(4).setText(ke::fixed::stow(TypeTranslator::getSubtypeName((object_ptr->subtype()))));
		m_object_info.at(5).setText(findSystemName(m_selected));


		std::wstringstream valstr;
		valstr << std::scientific << std::setprecision(4) << object_ptr->mass() << L" kg";
		m_object_info.at(1).setText(valstr.str());

		valstr.str(std::wstring());
		valstr << std::scientific << std::setprecision(4) << object_ptr->radius() << L" m";
		m_object_info.at(2).setText(valstr.str());
	}
	else
	{
		m_object_info.at(0).setText(L"name");
		m_object_info.at(1).setText(L"mass");
		m_object_info.at(2).setText(L"radius");
		m_object_info.at(3).setText(L"class");
		m_object_info.at(4).setText(L"subtype");
		m_object_info.at(5).setText(L"system name");
	}
}

std::wstring ObjectLibraryOverlay::findSystemName(std::vector<std::unique_ptr<ObjectIcon>>::iterator selected)
{
	for (auto itr = m_system_bounds.begin(); itr != m_system_bounds.end(); ++itr)
	{
		if (ke::ionRange(std::distance(m_objects.begin(), m_selected), itr->first, itr->second))
			return m_system_names.at(std::distance(m_system_bounds.begin(), itr))->getText();
	}

	return L"ERROR: out of range";

	auto system = m_system_begining.begin();

	for (auto itr = m_objects.begin() + 1; itr != m_objects.end(); ++itr)
	{
		if (itr == selected)
			return m_system_names.at(std::distance(m_system_begining.begin(), system))->getText();
	}

	return L"ERROR: out of range";
}
