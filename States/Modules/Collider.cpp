#include "Collider.hpp"

Collider::Collider()
{

}

Collider::~Collider()
{

}

void Collider::assing(ObjectController* object_controller, const sf::Vector2f& winsize, long double space_scale)
{
	m_boom_mask.create(winsize, { 0, 0 }, ke::Origin::LEFT_TOP, L"", 0, ke::Origin::LEFT_TOP, sf::Color::Transparent);
	m_object_controller = object_controller;
	m_space_scale = space_scale;
}

bool Collider::update(std::vector<std::unique_ptr<SpaceObject>>* objects, const float dt, std::vector<std::unique_ptr<SpaceObject>>::iterator& selected_object, const sf::Vector2f& viewsize, const sf::Vector2f& winsize)
{
	// filter possible candidates

	if (objects->size() < 6) // there's no need to filter if objects count is less than x
	{
		for (auto itr = objects->begin() + 1; itr != objects->end(); ++itr)
		{
			for (auto jtr = objects->begin() + 1; jtr != objects->end(); ++jtr)
			{
				if (itr != jtr)
				{
					if (ke::areColliding_CircleCircle(&itr->get()->object, &jtr->get()->object))
					{
						if (itr->get()->type() == ObjectType::STAR && jtr->get()->type() == ObjectType::STAR) // both stars -> make a big booom
						{
							if (itr->get()->objectClass() == ObjectClass::CLASS_BLACK_HOLE || jtr->get()->objectClass() == ObjectClass::CLASS_BLACK_HOLE) // black hole + other thing merging
							{
								int object_subtype;

								m_objects_to_delete.first = itr->get()->name();
								m_objects_to_delete.second = jtr->get()->name();

								if (itr->get()->subtype() == ObjectSubtype::SUBTYPE_SUPERMASSIVE_BH || jtr->get()->subtype() == ObjectSubtype::SUBTYPE_SUPERMASSIVE_BH)
									object_subtype = ObjectSubtype::SUBTYPE_SUPERMASSIVE_BH;
								else object_subtype = ObjectSubtype::SUBTYPE_INTERMEDIATE_SIZE_BH;

								std::string name = itr->get()->name() + " + " + itr->get()->name();
								m_object_controller->checkName(name);

								sf::Vector2f position(itr->get()->object.getPosition());
								long double mass = itr->get()->data.mass + jtr->get()->data.mass;

								ObjectBuffer buffer(ObjectType::STAR, ObjectClass::CLASS_BLACK_HOLE, object_subtype, mass, schwarzschild_radius(mass), name, "Textures/ObjectTextures/Universal/BlackHole.png", "Textures/IconTextures/Universal/BlackHole_icon.png", 0, sf::Vector3f(0, 0, 0));

								m_object_controller->addObject(selected_object, &buffer, position, viewsize, winsize, name);
								objects->back()->object.physics()->setSpeed(0, 0);

								return true;
							}
							else if (itr->get()->objectClass() == ObjectClass::CLASS_NEUTRON_STAR || jtr->get()->objectClass() == ObjectClass::CLASS_NEUTRON_STAR) // kilonova
							{
								// make a huuuuuge boooooom

								m_boom_mask.setFillColor(sf::Color(255, 255, 255, 255));
								m_mask_color.setColor(255, 255, 255, 255);

								m_objects_to_delete.first = itr->get()->name();
								m_objects_to_delete.second = jtr->get()->name();

								std::string name = itr->get()->name() + " + " + itr->get()->name();
								m_object_controller->checkName(name);

								sf::Vector2f position(itr->get()->object.getPosition());
								long double mass = itr->get()->data.mass + jtr->get()->data.mass;

								ObjectBuffer buffer(ObjectType::STAR, ObjectClass::CLASS_BLACK_HOLE, ObjectSubtype::SUBTYPE_STELLAR_SIZE_BH, mass, schwarzschild_radius(mass), name, "Textures/ObjectTextures/Universal/BlackHole.png", "Textures/IconTextures/Universal/BlackHole_icon.png", 0, sf::Vector3f(0, 0, 0));

								m_object_controller->addObject(selected_object, &buffer, position, viewsize, winsize, name);
								objects->back()->object.physics()->setSpeed(0, 0);

								return true;
							}
							else // other pair-instability type supernova
							{
								ObjectBuffer buffer;

								int object_subtype, object_class;

								m_objects_to_delete.first = itr->get()->name();
								m_objects_to_delete.second = jtr->get()->name();



								std::string name = itr->get()->name() + " + " + itr->get()->name();
								m_object_controller->checkName(name);

								sf::Vector2f position(itr->get()->object.getPosition());
								long double mass = itr->get()->data.mass + jtr->get()->data.mass;


								// naaaah I'm not doing every posiible type of collision, noooo way

								if (itr->get()->objectClass() == ObjectClass::CLASS_BROWN_DWARF && jtr->get()->objectClass() == ObjectClass::CLASS_BROWN_DWARF)
								{
									object_class = ObjectClass::CLASS_MAIN_SEQUENCE_STAR;
									object_subtype = ObjectSubtype::SUBTYPE_M;

									buffer = ObjectBuffer(ObjectType::STAR, object_class, object_subtype, mass, solar_radius, name, "Textures/ObjectTextures/Universal/RedDwarf.png", "Textures/IconTextures/Universal/RedDwarf_icon.png", 0, sf::Vector3f(0, 0, 0));
								}
								else if (itr->get()->type() == ObjectType::STAR && itr->get()->type() == ObjectType::STAR)
								{
									object_class = ObjectClass::CLASS_NEUTRON_STAR;
									object_subtype = ObjectSubtype::SUBTYPE_PULSAR;

									m_boom_mask.setFillColor(sf::Color(255, 255, 255, 223));
									m_mask_color.setColor(255, 255, 255, 223);

									buffer = ObjectBuffer(ObjectType::STAR, object_class, object_subtype, mass, 20'000, name, "Textures/ObjectTextures/Universal/Pulsar.png", "Textures/IconTextures/Universal/Pulsar_icon.png", 0, sf::Vector3f(0, 0, 0));
								}
								else // why I am doing this...
								{
									object_class = ObjectClass::CLASS_NEUTRON_STAR;
									object_subtype = ObjectSubtype::SUBTYPE_PULSAR;

									buffer = ObjectBuffer(ObjectType::STAR, object_class, object_subtype, mass, 20'000, name, "Textures/ObjectTextures/Universal/Pulsar.png", "Textures/IconTextures/Universal/Pulsar_icon.png", 0, sf::Vector3f(0, 0, 0));
								}

								//buffer = ObjectBuffer(ObjectType::STAR, object_class, object_subtype, mass, , name, "Textures/ObjectTextures/Universal/NeutronStar.png", "Textures/IconTextures/Universal/NeutronStar_icon.png", 0, sf::Vector3f(0, 0, 0));

								m_object_controller->addObject(selected_object, &buffer, position, viewsize, winsize, name);
								objects->back()->object.physics()->setSpeed(0, 0);

								return true;
							}
						}
						// one of them is a star, the other is a planet
						else if ((itr->get()->type() == ObjectType::PLANET && jtr->get()->type() == ObjectType::STAR))
						{
							m_objects_to_delete.first = itr->get()->name();
							m_objects_to_delete.second = "f0qice0-oqiejc"; // If you name an object like that you're retarded :>

							// should I add speed to the star? naaah
						}
						else if ((itr->get()->type() == ObjectType::STAR && jtr->get()->type() == ObjectType::PLANET))
						{
							m_objects_to_delete.first = jtr->get()->name();
							m_objects_to_delete.second = "f0qice0-oqiejc"; // If you name an object like that you're retarded :>

							// should I add speed to the star? naaah
						}
						else // planet - planet collision
						{
							
						}
					}
				}
			}
		}
	}
	else
	{

	}


	ke::SmoothColorChange(&m_boom_mask, true, sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 255), m_mask_color, sqrt(m_mask_color.a), dt);

	return false;
}

void Collider::renderBoooms(sf::RenderWindow* window)
{
	m_boom_mask.render(window);
}

std::pair<std::string, std::string> Collider::deletedObjects() const
{
	return m_objects_to_delete;
}
