#include "ObjectSelectionPanel.hpp"

ObjectSelectionPanel::ObjectSelectionPanel()
	: m_iconUI(nullptr)
	, m_object_icons(nullptr)
	, m_layout_name("Default")
	, selected_layout(FileStorage::Get().linked_icon_layouts_files.begin())
{
	//ke::FileStream f; f.createFile("Data/recentlyUsedIcons.glo");
	//for (auto& itr : FileStorage::Get().linked_icon_layouts_files)
	//	std::cout << itr.first << ' ' << itr.second << '\n';

	m_icon_colors.fill(ke::Colorf());
}

ObjectSelectionPanel::~ObjectSelectionPanel() {  }

void ObjectSelectionPanel::assign(iconUIvector* UI, iconvector* icons, ObjectLibraryOverlay* objectLibraryOverlay)
{
	m_iconUI = UI;
	m_object_icons = icons;

	fbegin = m_object_icons->begin() + 1;
	sbegin = m_object_icons->begin() + m_object_icons->size() / 2 + 1;

	//std::cout << m_object_icons->size() / 2 << '\n';

	fend = sbegin;
	send = m_object_icons->end();

	this->loadFromFile();

	//for (auto itr = fbegin + 1; itr != fend && itr != fend + 1; itr += 2)
	//{
	//	(*itr)->icon.setTexture("Textures/Unused/Back Arrow.png");
	//	(*itr)->load("Textures/Unused/Back Arrow.png", "Textures/Unused/Back Arrow.png", "LMAO2", 1000, 1000, STAR);
	//}

	m_objectLibraryOverlay = objectLibraryOverlay;
}


void ObjectSelectionPanel::loadFromFile()
{
	ke::FileStream loadstr("Data/recentlyUsedObjects.glo", std::ios::binary | std::ios::in);

	if (!loadstr.loaded())
	{
		ke::throw_error("ObjectSelectionPanel::saveToFile()", "Unable to open Data/recentlyUsedObjects.glo", "FILE ERROR");
		this->setDefaultLayout();
	}


	std::string obj_name = "UNDEFINED";
	int type = ObjectType::UNDEFINED;
	int obj_class = ObjectClass::CLASS_UNDEFINED;
	int subtype = ObjectSubtype::SUBTYPE_UNDEFINED;
	long double mass = 1, radius = 1;
	std::string filename = "Textures/AudioIcon.png";
	std::string texture_path = "Textures/AudioIcon.png";
	float brightness = 0;
	sf::Vector3f color(1.0, 1.0, 1.0);

	for (auto itr = fbegin; itr != fend; ++itr)
	{
		loadstr.binRead(obj_name);
		loadstr.binRead(type);
		loadstr.binRead(obj_class);
		loadstr.binRead(subtype);

		loadstr.binRead(mass);
		loadstr.binRead(radius);

		loadstr.binRead(filename);
		loadstr.binRead(texture_path);

		loadstr.binRead(brightness);
		loadstr.binRead(color.x);
		loadstr.binRead(color.y);
		loadstr.binRead(color.z);


		(*itr)->load(texture_path, filename, obj_name, type, obj_class, subtype, mass, radius, brightness, color);
	}

	loadstr.binRead(m_layout_name);

	this->loadStaticIcons(m_layout_name);
}

void ObjectSelectionPanel::saveToFile()
{
	ke::FileStream savestr("Data/recentlyUsedObjects.glo", std::ios::binary | std::ios::out | std::ios::trunc); // glo = general layout

	if (!savestr.loaded())
	{
		ke::throw_error("ObjectSelectionPanel::saveToFile()", "Unable to open Data/recentlyUsedObjects.glo", "FILE ERROR");
		//this->setDefaultLayout();
		return;
	}


	for (auto itr = fbegin; itr != fend; ++itr)
	{
		savestr.binWrite((*itr)->object_name());
		savestr.binWrite((*itr)->type());
		savestr.binWrite((*itr)->object_class());
		savestr.binWrite((*itr)->subtype());

		savestr.binWrite((*itr)->mass());
		savestr.binWrite((*itr)->radius());
						
		savestr.binWrite((*itr)->filename());
		savestr.binWrite((*itr)->iconFilename());

		savestr.binWrite((*itr)->brightness());
		savestr.binWrite((*itr)->color().x);
		savestr.binWrite((*itr)->color().y);
		savestr.binWrite((*itr)->color().z);
	}

	savestr.binWrite(m_layout_name);
}


void ObjectSelectionPanel::loadStaticIcons(const std::string& layout_name)
{
	ke::FileStream loadstr;

	if (!loadstr.open(FileStorage::Get().linked_icon_layouts_files[layout_name], std::ios::binary | std::ios::in)) // slo = static icon layout
	{
		ke::throw_error("ObjectSelectionPanel::loadStaticIcons()", "Unable to open \'" + FileStorage::Get().linked_icon_layouts_files[layout_name] + "\'", "FILE ERROR");
		//this->setDefaultLayout();
		if (!loadstr.open(FileStorage::Get().linked_icon_layouts_files["Default"], std::ios::binary | std::ios::in))
		{
			ke::throw_error("ObjectSelectionPanel::loadStaticIcons()", "Unable to open Default layout", "FILE CRITICAL ERROR");
			return;
		}
	}

	std::string obj_name = "UNDEFINED";
	int type = ObjectType::UNDEFINED;
	int obj_class = ObjectClass::CLASS_UNDEFINED;
	int subtype = ObjectSubtype::SUBTYPE_UNDEFINED;
	long double mass = 1, radius = 1;
	std::string filename = "Textures/AudioIcon.png";
	std::string texture_path = "Textures/AudioIcon.png";
	float brightness = 0;
	sf::Vector3f color(1.0, 1.0, 1.0);



	for (auto itr = sbegin; itr != send; ++itr)
	{
		loadstr.binRead(obj_name);
		loadstr.binRead(type);
		loadstr.binRead(obj_class);
		loadstr.binRead(subtype);

		loadstr.binRead(mass);
		loadstr.binRead(radius);

		loadstr.binRead(filename);
		loadstr.binRead(texture_path);

		loadstr.binRead(brightness);
		loadstr.binRead(color.x);
		loadstr.binRead(color.y);
		loadstr.binRead(color.z);


		(*itr)->load(texture_path, filename, obj_name, type, obj_class, subtype, mass, radius, brightness, color);
	}
}


void ObjectSelectionPanel::setDefaultLayout()
{
	
}


void ObjectSelectionPanel::pushIcon(const ObjectBuffer& buffer)
{
	bool obj_in_queue = false;

	for (auto itr = fbegin; itr != fend; ++itr)
		if (buffer.name() == (*itr)->object_name())
			obj_in_queue = true;

	if (obj_in_queue)
		return;


	for (auto itr = fend - 1; itr != fbegin; --itr)
		(*(*itr)) = (*(*(itr - 1)));

	std::cout << "icon pushed\n";

	(*fbegin)->load(buffer);
}



void ObjectSelectionPanel::updatePollEvents(const sf::Vector2f& mousePosition, float dt, sf::Event& event)
{
	if (m_iconUI->at(1)->isClicked(sf::Mouse::Left, mousePosition, event)) // bottom icons UI
	{
		State::sfx.play("click");

		++selected_layout;

		if (selected_layout == filestorage.linked_icon_layouts_files.end())
			selected_layout = filestorage.linked_icon_layouts_files.begin();

		this->loadStaticIcons(selected_layout->first);
	}
	else if (m_iconUI->at(1)->isClicked(sf::Mouse::Right, mousePosition, event)) // bottom icons UI
	{
		State::sfx.play("click");

		if (selected_layout == filestorage.linked_icon_layouts_files.begin())
			selected_layout = filestorage.linked_icon_layouts_files.end();

		--selected_layout;

		this->loadStaticIcons(selected_layout->first);
	}
	else if (m_iconUI->at(2)->isClicked(sf::Mouse::Left, mousePosition, event))
	{
		State::sfx.play("click");

		m_objectLibraryOverlay->activate();
	}
}

void ObjectSelectionPanel::updateColors(const sf::Vector2f& mousePosition, const float dt)
{
	auto color_itr = m_icon_colors.begin();

	for (auto& itr : *m_object_icons)
	{
		ke::SmoothColorChange(&itr->icon, itr->icon.isInvaded(mousePosition), sf::Color::Transparent, sf::Color(0, 0, 0, 64), *color_itr, 256, dt);
		++color_itr;
	}

	auto ui_colors = m_UI_colors.begin();

	for (auto& itr : *m_iconUI)
	{
		ke::SmoothColorChange(itr.get(), itr->isInvaded(mousePosition), sf::Color::Transparent, sf::Color(0, 0, 0, 64), *ui_colors, 256, dt);
		++ui_colors;
	}
}
