#include "ObjectLibraryOverlay.hpp"

#define object_ptr (*m_selected)

ObjectLibraryOverlay::ObjectLibraryOverlay()
	: m_quitStatus(false)
	, m_active(false)
	, m_window(nullptr)
	, m_icons_per_row(10)
	, m_next_position(0)
	, m_sorting_type(OBJECT_LIRARY_SORTING_BY::SYSTEMS)
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

	m_output.load(ObjectType::UNDEFINED, ObjectClass::CLASS_UNDEFINED, ObjectSubtype::SUBTYPE_UNDEFINED, 0.0, 0.0, "__EMPTY", "Textures/AudiIcon.png", "Textures/IconTextures/Empty_icon.png", 0, sf::Vector3f(0.0, 0.0, 0.0));


	m_background.create(sf::Vector2f(winsize.x * 0.75, winsize.y), winsize * 0.5f, ke::Origin::MIDDLE_MIDDLE, std::wstring(), 0, ke::Origin::MIDDLE_MIDDLE, sf::Color::Black);
	m_top_section.create(sf::Vector2f(winsize.x * 0.75, winsize.y / 9), sf::Vector2f(winsize.x / 2, 0), ke::Origin::MIDDLE_TOP, std::wstring(), 0, ke::Origin::MIDDLE_MIDDLE, sf::Color(8, 8, 8, 255));
	m_right_section.create(sf::Vector2f(winsize.x * 0.2, winsize.y), sf::Vector2f(winsize.x - winsize.x / 8, 0), ke::Origin::RIGHT_TOP, std::wstring(), 0, ke::Origin::MIDDLE_MIDDLE, sf::Color(16, 16, 16, 255));

	m_next_position = winsize.y / 9;


	m_search_box.create(sf::Vector2f(winsize.x * 0.38, winsize.y / 15), sf::Vector2f(winsize.x / 8 + winsize.x / 64, winsize.y / 18), ke::Origin::LEFT_MIDDLE, nullptr,
		L"Search...", ke::TextScope::ASCII_Everything, 50, 1, winsize.y / 32, ke::Origin::LEFT_MIDDLE, sf::Color(32, 32, 32, 255),
		sf::Color::White, sf::Color(92, 92, 92, 255), 0, sf::Color::Transparent, {}, sf::Vector2f(winsize.x * 0.0125, 0));

	// | favourite | by systems |    A-Z    |    Z-A    |
	//m_filtering_options[0].create(sf::Vector2f(winsize.x / 64, winsize.x / 64), sf::Vector2f(winsize.x * 0.53, winsize.y / 18), ke::Origin::MIDDLE_MIDDLE, "Textures/StateTextures/Simulation/EmptyStar.png");
	m_filtering_options[0].create(sf::Vector2f(winsize.x / 60, winsize.x / 60), sf::Vector2f(winsize.x * 0.53 + winsize.x * 0.03125, winsize.y / 18), ke::Origin::MIDDLE_MIDDLE, "Textures/StateTextures/Simulation/SortingBySystemsIcon.png");
	m_filtering_options[1].create(sf::Vector2f(winsize.x / 60, winsize.x / 60), sf::Vector2f(winsize.x * 0.53 + winsize.x * 0.06250, winsize.y / 18), ke::Origin::MIDDLE_MIDDLE, "Textures/StateTextures/Simulation/SortingByAZIcon.png");
	m_filtering_options[2].create(sf::Vector2f(winsize.x / 60, winsize.x / 60), sf::Vector2f(winsize.x * 0.53 + winsize.x * 0.09375, winsize.y / 18), ke::Origin::MIDDLE_MIDDLE, "Textures/StateTextures/Simulation/SortingByZAIcon.png");

	m_filtering_options.at(0).getTextureShape()->setFillColor(sf::Color(255, 255, 128, 255));


	m_add_button.create(sf::Vector2f(winsize.x * 0.16, winsize.y / 12), sf::Vector2f(m_right_section.getShapeCenter().x, winsize.y - winsize.y / 15), ke::Origin::MIDDLE_MIDDLE, nullptr, L"ADD", winsize.y / 18, ke::Origin::MIDDLE_MIDDLE, sf::Color(32, 192, 32, 128), sf::Color(255, 255, 255, 129));
	m_close_button.create(sf::Vector2f(winsize.x * 0.16, winsize.y / 12), sf::Vector2f(m_right_section.getShapeCenter().x, winsize.y / 15), ke::Origin::MIDDLE_MIDDLE, nullptr, L"CLOSE", winsize.y / 18, ke::Origin::MIDDLE_MIDDLE, sf::Color(192, 32, 32, 128), sf::Color(255, 255, 255, 129));

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

	//m_GUI_colors.fill(ke::Colorf(255, 255, 255, 192));


	m_quick_info.create(sf::Vector2f(winsize.x * 0.16, winsize.y / 9), sf::Vector2f(m_right_section.getShapeCenter().x, (m_add_button.getShapeCenter().y + m_object_info.back().getShapeCenter().y) * 0.5), ke::Origin::MIDDLE_MIDDLE, nullptr, L"", winsize.y / 48, ke::Origin::LEFT_MIDDLE, sf::Color(32, 32, 32, 128), sf::Color::White, {}, {}, {}, {}, sf::Vector2f(winsize.x * 0.0032, 0));

	m_slider.create(sf::Vector2f(winsize.x / 128, winsize.y - winsize.y / 9), sf::Vector2f(m_background.getShapeCenter().x + m_background.getSize().x * 0.5 - m_right_section.getSize().x, winsize.y),
		winsize.y, ke::Origin::RIGHT_BOTTOM, nullptr, nullptr, sf::Color(255, 255, 255, 128), sf::Color((32, 32, 32, 32)));
}

void ObjectLibraryOverlay::loadObjects()
{
	sf::Vector2f winsize(m_window->getSize());
	sf::Vector2f field_size(m_background.getSize().x - m_right_section.getSize().x - m_slider.getSize().x, winsize.y - m_top_section.getSize().y);

	float field_beg = m_background.getShapeCenter().x - m_background.getSize().x * 0.5; // begginging of the overlay filed
	float uniheight = field_size.x / m_icons_per_row; // height of objects and system names

	m_obj_view.setSize(winsize);
	m_obj_view.setCenter(winsize.x * 0.5, winsize.y * 0.5);

	ke::debug::printVector2(m_obj_view.getSize(), "viewSize");
	ke::debug::printVector2(m_obj_view.getCenter(), "viewCenter");

	std::vector<std::pair<std::string, std::string>> systems;

	for (auto& itr : FileStorage::Get().linked_space_objects_database)
		systems.push_back(std::make_pair(itr.first, itr.second));

	// sorting systems by name
	std::sort(systems.begin(), systems.end());



	for (auto& itr : systems)
	{
		ke::FileStream loadStr(itr.second, std::ios::in | std::ios::binary);

		if (!loadStr.loaded())
			ke::throw_error("ObjectLibraryOverlay::loadObjects()", "failed to load .sodb file", "FILE ERROR");

		std::string system_name;
		int obj_count;

		loadStr.binRead(system_name);
		loadStr.binRead(obj_count);


		std::cout << system_name << ", " << obj_count << '\n';

		m_system_names.emplace_back(std::make_unique<SystemNameTile>(sf::Vector2f(field_size.x, uniheight), sf::Vector2f(field_beg, m_next_position), ke::Origin::LEFT_TOP,
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
		const sf::Vector2f size(uniheight, uniheight);

		for (int i = 0; i < obj_count; i++)
		{
			position.x = field_beg + (i % (m_icons_per_row)) * size.x;

			loadStr.binRead(obj_name);
			loadStr.binRead(type);
			loadStr.binRead(obj_class);
			loadStr.binRead(subtype);

			loadStr.binRead(mass);
			loadStr.binRead(radius);

			loadStr.binRead(filename);
			loadStr.binRead(texture_path);

			//std::cout << '\t' << texture_path << '\n';

			loadStr.binRead(brightness);
			loadStr.binRead(color.x);
			loadStr.binRead(color.y);
			loadStr.binRead(color.z);


			if (i % (m_icons_per_row) == 0 && i)
				position.y += uniheight;

			m_objects.emplace_back(std::make_unique<Tile>(texture_path, filename, size, position, obj_name, type, obj_class, subtype, mass, radius, brightness, color, system_name));
		}

		m_next_position = position.y + uniheight;
	}



	m_obj_colors.reserve(m_objects.size());

	for (int i = 0; i < m_objects.size(); ++i)
		m_obj_colors.push_back(sf::Color::Transparent);


	m_slider.setFieldHeight((m_next_position > winsize.y) ? m_next_position : winsize.y);
	m_slider.setViewPositionShift(0, nullptr);

	m_view_barrier.setView(&m_obj_view);
	m_view_barrier.setBorders(sf::Vector2f(0, 0), sf::Vector2f(winsize.x, m_next_position));

	for (auto itr = m_objects.begin(); itr != m_objects.end(); ++itr)
		if (ke::ionRange((*itr)->Icon().icon.getPosition().y, -1.5 * (*itr)->Icon().icon.getSize().y, m_window->getSize().y + 1.5 * (*itr)->Icon().icon.getSize().y))
			m_on_screen.push_back(itr);

	m_selected = m_objects.end();
	m_invaded_icon = m_objects.end();


	m_sorted_object_order.reserve(m_objects.size());
	int _i = 0;

	for (auto& itr : m_objects)
	{
		m_sorted_object_order.push_back(std::make_pair(_i, itr->name()));
		_i++;
	}
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
		m_quitStatus = OBJECT_LIBRARY_OverlayQuitStatus::QUITTING_WITHOUT_OBJECT;
		this->deactivate();
		return;
	}
	else if (m_close_button.isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
	{
		m_quitStatus = OBJECT_LIBRARY_OverlayQuitStatus::QUITTING_WITHOUT_OBJECT;
		m_output.load(ObjectType::UNDEFINED, ObjectClass::CLASS_UNDEFINED, ObjectSubtype::SUBTYPE_UNDEFINED, 0.0, 0.0, "__EMPTY", "Textures/AudioIcon.png", "Textures/IconTextures/Empty_icon.png", 0, sf::Vector3f(0.0, 0.0, 0.0));
		this->deactivate();
		return;
	}


	if (m_filtering_options.at(0).isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
	{
		m_sorting_type = OBJECT_LIRARY_SORTING_BY::SYSTEMS;
		this->updateSystemSorting();

		m_filtering_options.at(0).getTextureShape()->setFillColor(sf::Color(255, 255, 128, 255));
		m_filtering_options.at(1).getTextureShape()->setFillColor(sf::Color(255, 255, 255, 255));
		m_filtering_options.at(2).getTextureShape()->setFillColor(sf::Color(255, 255, 255, 255));
	}
	else if (m_filtering_options.at(1).isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
	{
		m_sorting_type = OBJECT_LIRARY_SORTING_BY::A_Z;
		this->updateAZSorting();

		m_filtering_options.at(0).getTextureShape()->setFillColor(sf::Color(255, 255, 255, 255));
		m_filtering_options.at(1).getTextureShape()->setFillColor(sf::Color(255, 255, 128, 255));
		m_filtering_options.at(2).getTextureShape()->setFillColor(sf::Color(255, 255, 255, 255));
	}
	else if (m_filtering_options.at(2).isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
	{
		m_sorting_type = OBJECT_LIRARY_SORTING_BY::Z_A;
		this->updateZASorting();

		m_filtering_options.at(0).getTextureShape()->setFillColor(sf::Color(255, 255, 255, 255));
		m_filtering_options.at(1).getTextureShape()->setFillColor(sf::Color(255, 255, 255, 255));
		m_filtering_options.at(2).getTextureShape()->setFillColor(sf::Color(255, 255, 128, 255));
	}
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Tab)
	{
		m_search_box.setEPS(true);
	}

	// sorting update

	if (ke::inRange(m_search_box.update(mousePosition.byWindow, event, sf::Mouse::Left, nullptr) - 1, -0.01, 0.01) ||	// equal to 1
		ke::inRange(m_search_box.update(mousePosition.byWindow, event, sf::Mouse::Left, nullptr) - 1, 0.99, 1.01))		// equal to 2
	{
		m_filter = ke::fixed::wtos(m_search_box.getText());

		std::transform(m_filter.begin(), m_filter.end(), m_filter.begin(),
			[](unsigned char c) { return std::tolower(c); });

		//std::cout << "filter: " << m_filter << '\n';
		this->updateObjectPosition();

		// updating objects on screen
		m_on_screen.clear();

		for (auto itr = m_objects.begin(); itr != m_objects.end(); ++itr)
		{
			if ((*itr)->Icon().icon.isActive())
				if (ke::ionRange((*itr)->Icon().icon.getPosition().y, -1.5 * (*itr)->Icon().icon.getSize().y, m_window->getSize().y + 1.5 * (*itr)->Icon().icon.getSize().y))
					m_on_screen.push_back(itr);
		}
	}

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

		for (auto itr = m_objects.begin(); itr != m_objects.end(); ++itr)
		{
			if ((*itr)->Icon().icon.isActive())
				if (ke::ionRange((*itr)->Icon().icon.getPosition().y, -1.5 * (*itr)->Icon().icon.getSize().y, m_window->getSize().y + 1.5 * (*itr)->Icon().icon.getSize().y))
					m_on_screen.push_back(itr);
		}
	}

	ke::ViewHolding(&m_obj_view, sf::Mouse::Middle, mPosView, event, sf::Vector2f(0, 0), sf::Vector2f(m_window->getSize().x, m_slider.getFieldHeight()));



	for (auto& itr : m_on_screen)
	{
		if (!ke::ionRange((*itr)->Icon().icon.getPosition().y, -1.5 * (*itr)->Icon().icon.getSize().y, m_window->getSize().y + 1.5 * (*itr)->Icon().icon.getSize().y))
			continue;

		if ((*itr)->Icon().icon.isClicked(sf::Mouse::Left, mPosView, event))
		{
			if (m_selected == itr)
			{
				(*m_selected)->Icon().icon.setOutlineColor(sf::Color::Transparent);
				(*m_selected)->Icon().icon.setOutlineThickness(0);

				m_selected = m_objects.end();
				m_output.load(ObjectType::UNDEFINED, ObjectClass::CLASS_UNDEFINED, ObjectSubtype::SUBTYPE_UNDEFINED, 0.0, 0.0, "__EMPTY", "Textures/AudiIcon.png", "Textures/IconTextures/Empty_icon.png", 0, sf::Vector3f(0.0, 0.0, 0.0));
				updateObjectInfo();
				return;
			}
			else
			{
				if (m_selected != m_objects.end())
				{
					(*m_selected)->Icon().icon.setOutlineColor(sf::Color::Transparent);
					(*m_selected)->Icon().icon.setOutlineThickness(0);
				}

				m_output.load((**itr).Icon());
				m_selected = itr;
				(*m_selected)->Icon().icon.setOutlineColor(sf::Color(0, 64, 0, 255));
				(*m_selected)->Icon().icon.setOutlineThickness(m_window->getSize().x / 512);
				updateObjectInfo();
			}
		}
	}

	if (m_add_button.isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
	{
		if (m_output.name() != "__EMPTY")
		{
			m_quitStatus = OBJECT_LIBRARY_OverlayQuitStatus::QUITTING_WITH_OBJECT;
			this->deactivate();
			return;
		}
	}


	for (auto& itr : m_on_screen)
	{
		if ((*itr)->Icon().icon.isInvaded(mPosView))
		{
			m_invaded_icon = itr;
			m_quick_info.setText(ke::fixed::stow((*itr)->Icon().object_name() + "\n\n" + TypeTranslator::getClassName((*itr)->Icon().object_class())));
			break;
		}

		m_quick_info.setText(std::wstring());
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

	ke::SmoothColorChange(&m_add_button, m_add_button.isInvaded(mousePosition), sf::Color(32, 255, 32, 128), sf::Color(32, 192, 32, 128), *GUI_color_itr, 512, dt); ++GUI_color_itr;
	ke::SmoothTextColorChange(&m_add_button, m_add_button.isInvaded(mousePosition), sf::Color::White, sf::Color(255, 255, 255, 128), *GUI_color_itr, 1024, dt); ++GUI_color_itr;
	ke::SmoothColorChange(&m_close_button, m_close_button.isInvaded(mousePosition), sf::Color(255, 32, 32, 128), sf::Color(192, 32, 32, 128), *GUI_color_itr, 512, dt); ++GUI_color_itr;
	ke::SmoothTextColorChange(&m_close_button, m_close_button.isInvaded(mousePosition), sf::Color::White, sf::Color(255, 255, 255, 128), *GUI_color_itr, 1024, dt); ++GUI_color_itr;

	ke::SmoothColorChange(m_slider.getSlider(), m_slider.getSlider()->isInvaded(mousePosition) || m_slider.isHolded(), sf::Color::White, sf::Color(255, 255, 255, 128), *GUI_color_itr, 2048, dt); ++GUI_color_itr;
	ke::SmoothColorChange(m_slider.getSliderTrack(), m_slider.getSliderTrack()->isInvaded(mousePosition) || m_slider.isHolded(), sf::Color(48, 48, 48, 48), sf::Color(32, 32, 32, 32), *GUI_color_itr, 256, dt); ++GUI_color_itr;


	for (auto& itr : m_filtering_options)
	{
		ke::SmoothColorChange(&itr, itr.isInvaded(mousePosition), sf::Color::Transparent, sf::Color(0, 0, 0, 96), *GUI_color_itr, 511, dt);
		++GUI_color_itr;
	}


	auto obj_color_itr = m_obj_colors.begin();

	for (auto itr = m_on_screen.begin(); itr != m_on_screen.end(); ++itr)
	{
		ke::SmoothColorChange(&(**itr)->Icon().icon, (**itr)->Icon().icon.isInvaded(mPosView), sf::Color::Transparent, sf::Color(0, 0, 0, 96), *obj_color_itr, 511, dt);
		++obj_color_itr;
	}
}

int ObjectLibraryOverlay::quitStatus() const
{
	return m_quitStatus;
}

void ObjectLibraryOverlay::resetQuitStatus()
{
	m_quitStatus = OL_NOT_QUITTING;
}

void ObjectLibraryOverlay::render()
{
	if (!m_active)
		return;

	m_window->setView(m_window->getDefaultView());

	m_background.render(m_window);


	m_window->setView(m_obj_view);

	for (auto& itr : m_system_names)
		itr->Button().render(m_window);

	for (auto& itr : m_on_screen)
		(*itr)->Icon().icon.render(m_window);

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

	m_quick_info.render(m_window);

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

	if (m_selected != m_objects.end())
	{
		(*m_selected)->Icon().icon.setOutlineColor(sf::Color::Transparent);
		(*m_selected)->Icon().icon.setOutlineThickness(0);
		m_selected = m_objects.end();
	}

	this->updateObjectInfo();
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
		m_object_info.at(0).setText(ke::fixed::stow(object_ptr->Icon().object_name()));

		m_object_info.at(3).setText(ke::fixed::stow(TypeTranslator::getClassName(object_ptr->Icon().object_class())));
		m_object_info.at(4).setText(ke::fixed::stow(TypeTranslator::getSubtypeName((object_ptr->Icon().subtype()))));
		m_object_info.at(5).setText(ke::fixed::stow(object_ptr->systemName()));


		std::wstringstream valstr;
		valstr << std::scientific << std::setprecision(4) << object_ptr->Icon().mass() << L" kg";
		m_object_info.at(1).setText(valstr.str());

		valstr.str(std::wstring());
		valstr << std::scientific << std::setprecision(4) << object_ptr->Icon().radius() << L" m";
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


void ObjectLibraryOverlay::updateObjectPosition()
{
	switch (m_sorting_type)
	{
	case OBJECT_LIRARY_SORTING_BY::SYSTEMS:
	{
		this->updateSystemSorting();
	}
	break;

	case OBJECT_LIRARY_SORTING_BY::A_Z:
	{
		this->updateAZSorting();
	}
	break;

	case OBJECT_LIRARY_SORTING_BY::Z_A:
	{
		this->updateZASorting();
	}
	break;

	default:
	{
		ke::throw_error("ObjectLibraryOverlay::updateObjectPosition()", "reached *default* statement", "WARNING");
		this->updateSystemSorting();
	}
	break;
	}
}

void ObjectLibraryOverlay::updateSystemSorting()
{
	for (auto& itr : m_system_names)
		itr->Button().setActiveStatus(true);


	if (m_filter.empty())
	{
		for (auto& itr : m_objects)
		{
			itr->Icon().icon.setPosition(itr->defaultPosition());
			itr->Icon().icon.setActiveStatus(true);
		}

		for (auto& itr : m_system_names)
		{
			itr->Button().setPosition(itr->defaultPosition());
		}
	}
	else
	{
		sf::Vector2f field_size(m_background.getSize().x - m_right_section.getSize().x - m_slider.getSize().x, m_window->getSize().y - m_top_section.getSize().y);
		float field_beg = m_background.getShapeCenter().x - m_background.getSize().x * 0.5; // begginging of the overlay filed
		float uniheight = field_size.x / m_icons_per_row; // height of objects and system names

		std::string system_name = m_objects.front()->systemName();
		auto system_itr = m_system_names.begin();
		sf::Vector2f position = (*system_itr)->Button().getPosition();

		position.y += uniheight;
		int i = 0;

		// position.x = field_beg + (i % (icons_per_row)) * size.x;
		//
		// if (i % (icons_per_row) == 0 && i)
		//		position.y += uniheight;

		for (auto& itr : m_objects)
		{
			if (itr->systemName() != system_name)
			{
				system_name = itr->systemName();
				system_itr++;
				(*system_itr)->Button().setPosition(field_beg, position.y + uniheight);
				position = (*system_itr)->Button().getPosition();
				position.y += uniheight;
				i = 0;
			}

			std::string objName_buffer = itr->Icon().object_name();
			std::transform(objName_buffer.begin(), objName_buffer.end(), objName_buffer.begin(),
				[](unsigned char c) { return std::tolower(c); });

			if (!objName_buffer.compare(0, m_filter.size(), m_filter)) // IDK why I have to !negate it, but it works and I'm not touching it
			{
				position.x = field_beg + (i % (m_icons_per_row)) * uniheight;

				if (i % (m_icons_per_row) == 0 && i)
					position.y += uniheight;

				itr->Icon().icon.setActiveStatus(true);
				itr->Icon().icon.setPosition(position);

				i++;
			}
			else
			{
				//itr->Icon().icon.setPosition(-100, -100);
				itr->Icon().icon.setActiveStatus(false);
			}
		}
	}
}

void ObjectLibraryOverlay::updateAZSorting()
{
	for (auto& itr : m_system_names)
		itr->Button().setActiveStatus(false);


	sf::Vector2f field_size(m_background.getSize().x - m_right_section.getSize().x - m_slider.getSize().x, m_window->getSize().y - m_top_section.getSize().y);
	float field_beg = m_background.getShapeCenter().x - m_background.getSize().x * 0.5; // begginging of the overlay filed
	float uniheight = field_size.x / m_icons_per_row; // height of objects and system names


	//auto itr = m_default_object_order
	//for (auto itr = m_objects.begin())

	std::sort(m_sorted_object_order.begin(), m_sorted_object_order.end(), [](const std::pair<int, std::string>& p1, const std::pair<int, std::string>& p2) { return p1.second < p2.second; });

	if (m_filter.empty())
	{
		sf::Vector2f position(field_beg, m_system_names.front()->defaultPosition().y);

		int i = 0;
		for (auto& itr : m_sorted_object_order)
		{
			m_objects[itr.first]->Icon().icon.setActiveStatus(true);

			position.x = field_beg + (i % (m_icons_per_row)) * uniheight;

			if (i % (m_icons_per_row) == 0 && i)
				position.y += uniheight;


			m_objects[itr.first]->Icon().icon.setPosition(position);

			i++;
		}
	}
	else
	{
		sf::Vector2f position(field_beg, m_system_names.front()->defaultPosition().y);


		int i = 0;
		for (auto& itr : m_sorted_object_order)
		{
			std::string objName_buffer = m_objects[itr.first]->Icon().object_name();
			std::transform(objName_buffer.begin(), objName_buffer.end(), objName_buffer.begin(),
				[](unsigned char c) { return std::tolower(c); });

			if (!objName_buffer.compare(0, m_filter.size(), m_filter)) // IDK why I have to !negate it, but it works and I'm not touching it
			{
				position.x = field_beg + (i % (m_icons_per_row)) * uniheight;

				if (i % (m_icons_per_row) == 0 && i)
					position.y += uniheight;

				m_objects[itr.first]->Icon().icon.setActiveStatus(true);
				m_objects[itr.first]->Icon().icon.setPosition(position);

				i++;
			}
			else
			{
				//itr->Icon().icon.setPosition(-100, -100);
				m_objects[itr.first]->Icon().icon.setActiveStatus(false);
			}
		}
	}
}

void ObjectLibraryOverlay::updateZASorting()
{
	for (auto& itr : m_system_names)
		itr->Button().setActiveStatus(false);


	sf::Vector2f field_size(m_background.getSize().x - m_right_section.getSize().x - m_slider.getSize().x, m_window->getSize().y - m_top_section.getSize().y);
	float field_beg = m_background.getShapeCenter().x - m_background.getSize().x * 0.5; // begginging of the overlay filed
	float uniheight = field_size.x / m_icons_per_row; // height of objects and system names


	//auto itr = m_default_object_order
	//for (auto itr = m_objects.begin())

	std::sort(m_sorted_object_order.begin(), m_sorted_object_order.end(), [](const std::pair<int, std::string>& p1, const std::pair<int, std::string>& p2) { return p1.second > p2.second; });

	if (m_filter.empty())
	{
		sf::Vector2f position(field_beg, m_system_names.front()->defaultPosition().y);

		int i = 0;
		for (auto& itr : m_sorted_object_order)
		{
			m_objects[itr.first]->Icon().icon.setActiveStatus(true);

			position.x = field_beg + (i % (m_icons_per_row)) * uniheight;

			if (i % (m_icons_per_row) == 0 && i)
				position.y += uniheight;


			m_objects[itr.first]->Icon().icon.setPosition(position);

			i++;
		}
	}
	else
	{
		sf::Vector2f position(field_beg, m_system_names.front()->defaultPosition().y);


		int i = 0;
		for (auto& itr : m_sorted_object_order)
		{
			std::string objName_buffer = m_objects[itr.first]->Icon().object_name();
			std::transform(objName_buffer.begin(), objName_buffer.end(), objName_buffer.begin(),
				[](unsigned char c) { return std::tolower(c); });

			if (!objName_buffer.compare(0, m_filter.size(), m_filter)) // IDK why I have to !negate it, but it works and I'm not touching it
			{
				position.x = field_beg + (i % (m_icons_per_row)) * uniheight;

				if (i % (m_icons_per_row) == 0 && i)
					position.y += uniheight;

				m_objects[itr.first]->Icon().icon.setActiveStatus(true);
				m_objects[itr.first]->Icon().icon.setPosition(position);

				i++;
			}
			else
			{
				//itr->Icon().icon.setPosition(-100, -100);
				m_objects[itr.first]->Icon().icon.setActiveStatus(false);
			}
		}
	}
}

//std::wstring ObjectLibraryOverlay::findSystemName(std::vector<std::unique_ptr<Tile>>::iterator selected)
//{
//	for (auto itr = m_system_bounds.begin(); itr != m_system_bounds.end(); ++itr)
//	{
//		if (ke::ionRange(std::distance(m_objects.begin(), m_selected), itr->first, itr->second))
//			return m_system_names.at(std::distance(m_system_bounds.begin(), itr))->getText();
//	}
//
//	return L"ERROR: out of range";
//
//	auto system = m_system_begining.begin();
//
//	for (auto itr = m_objects.begin() + 1; itr != m_objects.end(); ++itr)
//	{
//		if (itr == selected)
//			return m_system_names.at(std::distance(m_system_begining.begin(), system))->getText();
//	}
//
//	return L"ERROR: out of range";
//}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




Tile::Tile(const std::string& icon_filename, const std::string& object_filename, const sf::Vector2f& size, const sf::Vector2f& position, const std::string& obj_name, int type, int _class, int subtype, long double obj_mass, long double obj_radius, float brightness, const sf::Vector3f& color, std::string system_name)
	: m_icon(icon_filename, object_filename, size, position, obj_name, type, _class, subtype, obj_mass, obj_radius, brightness, color)
{
	m_system_name = system_name;
	m_default_position = position;
}

Tile::~Tile()
{

}

sf::Vector2f Tile::defaultPosition() const
{
	return m_default_position;
}

std::string Tile::systemName() const
{
	return m_system_name;
}

std::string Tile::name() const
{
	return m_icon.object_name();
}

ObjectIcon& Tile::Icon()
{
	return m_icon;
}

SystemNameTile::SystemNameTile(const sf::Vector2f& size, const sf::Vector2f& position, int origin, const sf::Texture* texture, const std::wstring& text, unsigned int character_size, int text_position, const sf::Color& object_color, const sf::Color& text_color, float outline_thickness, const sf::Color& outline_color, float rotation, unsigned int text_style, const sf::Vector2f& text_shift)
	: m_tile(size, position, origin, texture, text, character_size, text_position, object_color, text_color, outline_thickness, outline_color, rotation, text_style, text_shift)
{
	m_str_name = ke::fixed::wtos(text);
	m_default_position = position;
}

SystemNameTile::~SystemNameTile()
{

}

ke::Button& SystemNameTile::Button()
{
	return m_tile;
}

std::string& SystemNameTile::name()
{
	return m_str_name;
}

sf::Vector2f SystemNameTile::defaultPosition() const
{
	return m_default_position;
}
