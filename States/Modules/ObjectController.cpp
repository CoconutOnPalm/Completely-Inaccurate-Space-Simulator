#include "ObjectController.hpp"

ObjectController::ObjectController()
	: m_objects(nullptr)
	, m_orbit_preview(nullptr)
	, m_distance_preview(nullptr)
	, m_placed_object(nullptr)
	, m_space_scale(0.0000001)
	, m_star_scale(100)
	, m_planet_scale(500)
	, m_shader_scale(1)
	, m_brightness_scale(1) {}

ObjectController::~ObjectController() {}


void ObjectController::assign(objvector* objects, ke::Circle* orbit_preview, ke::Rectangle* distance_preview, ke::Circle* placed_object)
{
	m_objects = objects;
	m_orbit_preview = orbit_preview;
	m_distance_preview = distance_preview;
	m_placed_object = placed_object;
}


void ObjectController::assignScale(long double space_scale, long double planet_scale, long double star_scale, float shader_scale, float brightness_scale)
{
	m_space_scale = space_scale;
	m_planet_scale = planet_scale;
	m_star_scale = star_scale;
	m_shader_scale = shader_scale;
	m_brightness_scale = brightness_scale;
}


void ObjectController::addObject(objvector::iterator& selected_object, ObjectBuffer* object_data, const sf::Vector2f& position, const sf::Vector2f& viewSize, const sf::Vector2f& winSize, const std::string& name)
{
	size_t iter_pos = std::distance(m_objects->begin(), selected_object);

	switch (object_data->type())
	{
	case STAR:
		m_objects->push_back(std::make_unique<Star>(position, name, object_data->filename(), object_data->iconFilename(), object_data->objectClass(), object_data->subtype(), object_data->mass(),
			object_data->radius() * m_space_scale * m_star_scale, 0, viewSize.x / winSize.x * 16, viewSize.x / winSize.x * 2, sf::Vector2<double>(0, 0), object_data->brightness(), object_data->color()));
		m_objects->back()->data.radius = object_data->radius();

		break;
	case PLANET:
		m_objects->push_back(std::make_unique<Planet>(position, name, object_data->filename(), object_data->iconFilename(), object_data->objectClass(), object_data->subtype(), object_data->mass(),
			object_data->radius() * m_space_scale * m_planet_scale, 0, viewSize.x / winSize.x * 16, viewSize.x / winSize.x * 2, sf::Vector2<double>(0, 0), object_data->brightness(), object_data->color()));
		m_objects->back()->data.radius = object_data->radius();

		break;
	default:
		m_objects->push_back(std::make_unique<Star>(position, name, object_data->filename(), object_data->iconFilename(), object_data->objectClass(), object_data->subtype(), object_data->mass(),
			object_data->radius() * m_space_scale * m_star_scale, 0, viewSize.x / winSize.x * 16, viewSize.x / winSize.x * 2, sf::Vector2<double>(0, 0), object_data->brightness(), object_data->color()));
		m_objects->back()->data.radius = object_data->radius();
		ke::throw_error("ObjectController::addObject(...)", "incorrect object type", "ERROR");
		break;
	}

	//std::cout << object_data->objectClass() << ' ' << object_data->subtype() << '\n';
	//std::cout << m_objects->back()->objectClass() << ' ' << m_objects->back()->subtype() << '\n';

	// TODO: bug ze trzeba tego uzywac a nie w konstruktorze robic ^
	m_objects->back()->clickRange()->setOutlineThickness(viewSize.x / winSize.x * 2);
	m_objects->back()->clickRange()->setRadius(viewSize.x / winSize.x * 16);


	selected_object = m_objects->begin() + iter_pos; // changing iterator when vector is resized



	// TODO: dodaæ strulture ze skalami;

		//m_objects->back()->getObjectShader()->setUniform("basic_a", 1.f - m_objects->back()->object.getSize().y / viewSize.y);


	m_objects->back()->getObjectShader()->setUniform("basic_a", 1.f - m_objects->back()->object.getSize().y / viewSize.y);


	m_objects->back()->getGlowShader()->setUniform("size", m_objects->back()->object.getSize().y / viewSize.y * winSize.y * 2.f * m_brightness_scale);


	if (viewSize.y / m_objects->back()->object.getSize().y > m_objects->back()->data.brightness)
	{
		float shader_size = m_objects->back()->data.brightness - viewSize.y / m_objects->back()->object.getSize().y / winSize.y;

		m_objects->back()->getObjectShader()->setUniform("size", (shader_size * shader_size * m_brightness_scale >= 0) ? shader_size * m_brightness_scale : 0);
	}



	//if (m_selected_object != m_objects->begin())

	for (auto itr = m_objects->begin() + 1, eoi = m_objects->end() - 1; itr != eoi; ++itr)
	{
		float angle = std::atan(-(m_objects->back()->object.getPosition().y - (*itr)->object.getPosition().y) / (m_objects->back()->object.getPosition().x - (*itr)->object.getPosition().x)) * TO_DEG;

		if ((m_objects->back()->object.getPosition().x > (*itr)->object.getPosition().x))
			angle += 180;

		m_objects->back()->object.physics()->addForce((*itr)->name(),
			gravitational_force_2(m_objects->back()->data.mass, (*itr)->data.mass,
				(std::pow(m_objects->back()->object.getPosition().y - (*itr)->object.getPosition().y, 2) + (std::pow(m_objects->back()->object.getPosition().x - (*itr)->object.getPosition().x, 2)))) * m_space_scale,
			angle);
	}

	for (auto itr = m_objects->begin() + 1, eoi = m_objects->end() - 1; itr != eoi; ++itr)
	{
		float angle = std::atan(-((*itr)->object.getPosition().y - m_objects->back()->object.getPosition().y) / ((*itr)->object.getPosition().x) - m_objects->back()->object.getPosition().x) * TO_DEG;

		if ((m_objects->back()->object.getPosition().x < (*itr)->object.getPosition().x))
			angle += 180;

		(*itr)->object.physics()->addForce(m_objects->back()->name(),
			gravitational_force_2(m_objects->back()->data.mass, (*itr)->data.mass,
				(std::pow((*itr)->object.getPosition().y - m_objects->back()->object.getPosition().y, 2) + (std::pow((*itr)->object.getPosition().x - m_objects->back()->object.getPosition().x, 2)))) * m_space_scale,
			angle);
	}


	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
	{

		float angle = std::atan(-((*selected_object)->object.getPosition().y - m_objects->back()->object.getPosition().y) / ((*selected_object)->object.getPosition().x - m_objects->back()->object.getPosition().x)) * TO_DEG;

		if ((m_objects->back()->object.getPosition().x > (*selected_object)->object.getPosition().x))
			angle += 180;


		m_objects->back()->object.physics()->setSpeed(round_orbit_velocity((*selected_object)->data.mass,
			position_to_distance((*selected_object)->object.getPosition(), m_objects->back()->object.getPosition()) / m_space_scale), angle - 90);

		if (isnan(m_objects->back()->object.physics()->getSpeed().x) || isnan(m_objects->back()->object.physics()->getSpeed().y))
			m_objects->back()->object.physics()->setSpeed(sf::Vector2<double>(0, 0));



		/*if (selected_object != m_objects->begin())
		{
			ke::debug::printVector2(m_objects->back()->object.physics()->getSpeed(), "orbiting object");
			ke::debug::printVector2((*selected_object)->object.physics()->getSpeed(), "orbited object");
			ke::debug::printVector2(m_objects->back()->object.physics()->getSpeed() + (*selected_object)->object.physics()->getSpeed(), "combined");
		}*/

		if (selected_object != m_objects->begin())
			m_objects->back()->object.physics()->setSpeed(sf::Vector2<double>(m_objects->back()->object.physics()->getSpeed() + (*selected_object)->object.physics()->getSpeed()));
	}
}

void ObjectController::createObjectPreview(ObjectBuffer* object_data, objvector::iterator selected_object, iconvector::iterator selected_icon)
{
	//object_data->load(*selected_icon->get());

	switch (object_data->type())
	{
	case PLANET:
		m_placed_object->setRadius(object_data->radius() * m_space_scale * m_planet_scale);
		//(*selected_object)->data.radius = object_data->radius();
		//(*selected_object)->updatePhysicalData();
		break;
	case STAR:
		m_placed_object->setRadius(object_data->radius() * m_space_scale * m_star_scale);
		//(*selected_object)->data.radius = object_data->radius();
		//(*selected_object)->updatePhysicalData();
		break;
	default:
		ke::throw_error("ObjectController::createObjectPreview(...) - 1", "incorrect object type", "ERROR");
		break;
	}

	m_placed_object->setTexture(object_data->filename());
	m_placed_object->setFillColor(sf::Color(255, 255, 255, 128));
}

void ObjectController::createObjectPreview(ObjectBuffer* object_data, objvector::iterator selected_object)
{
	// used to copy objet

	// copying object
	object_data->load(selected_object);

	std::cout << (*selected_object)->name() << '\n';

	switch (object_data->type())
	{
	case PLANET:
		m_placed_object->setRadius(object_data->radius() * m_space_scale * m_planet_scale);
		//(*selected_object)->data.radius = object_data->radius();
		(*selected_object)->updatePhysicalData();
		break;
	case STAR:
		m_placed_object->setRadius(object_data->radius() * m_space_scale * m_star_scale);
		//(*selected_object)->data.radius = object_data->radius();
		(*selected_object)->updatePhysicalData();
		break;
	default:
		ke::throw_error("ObjectController::createObjectPreview(...) - 2", "incorrect object type", "ERROR");
		break;
	}

	m_placed_object->setTexture(object_data->filename());
	m_placed_object->setFillColor(sf::Color(255, 255, 255, 128));
}

void ObjectController::createObjectPreview(ObjectBuffer* object_data)
{
	// NOTE: object_data is loaded here

	switch (object_data->type())
	{
	case PLANET:
		m_placed_object->setRadius(object_data->radius() * m_space_scale * m_planet_scale);
		//(*selected_object)->data.radius = object_data->radius();
		//(*selected_object)->updatePhysicalData(); ???
		break;
	case STAR:
		m_placed_object->setRadius(object_data->radius() * m_space_scale * m_star_scale);
		//(*selected_object)->data.radius = object_data->radius();
		//(*selected_object)->updatePhysicalData(); ???
		break;
	default:
		ke::throw_error("ObjectController::createObjectPreview(...) - 3", "incorrect object type", "ERROR");
		break;
	}

	m_placed_object->setTexture(object_data->filename());
	m_placed_object->setFillColor(sf::Color(255, 255, 255, 128));
}

void ObjectController::deleteObject(objvector::iterator& selected_object)
{
	for (auto itr = m_objects->begin() + 1, eoi = m_objects->end(); itr != eoi; ++itr)
		if (itr != selected_object)
			(*itr)->object.physics()->removeForce((*selected_object)->name());

	m_objects->erase(selected_object);
	selected_object = m_objects->begin();
}


static void calculateForce(std::vector<std::unique_ptr<SpaceObject>>* m_objects, std::vector<std::unique_ptr<SpaceObject>>::iterator itr, std::vector<std::unique_ptr<SpaceObject>>::iterator eoi, long double m_space_scale)
{
	for (auto i = m_objects->begin() + 1; i != eoi; ++i)
	{
		if (itr != i)
		{
			if (AppSettings::LessCalculationsMode())
			{
				if (gravitational_force((*itr)->data.mass, (*i)->data.mass, position_to_distance((*itr)->object.getPosition(), (*i)->object.getPosition()) / m_space_scale) > 10e17)
				{
					float angle = std::atan(-((*itr)->object.getPosition().y - (*i)->object.getPosition().y) / ((*itr)->object.getPosition().x - (*i)->object.getPosition().x)) * TO_DEG;

					if (((*itr)->object.getPosition().x > (*i)->object.getPosition().x))
						angle += 180;

					(*itr)->object.physics()->modifyForce((*i)->name(),
						gravitational_force_2((*itr)->object.physics()->getMass(), (*i)->object.physics()->getMass(),
							(std::pow((*itr)->object.getPosition().y - (*i)->object.getPosition().y, 2) + (std::pow((*itr)->object.getPosition().x - (*i)->object.getPosition().x, 2)))) * m_space_scale,
						angle);
				}
			}
			else
			{
				float angle = std::atan(-((*itr)->object.getPosition().y - (*i)->object.getPosition().y) / ((*itr)->object.getPosition().x - (*i)->object.getPosition().x)) * TO_DEG;

				if (((*itr)->object.getPosition().x > (*i)->object.getPosition().x))
					angle += 180;

				(*itr)->object.physics()->modifyForce((*i)->name(),
					gravitational_force_2((*itr)->object.physics()->getMass(), (*i)->object.physics()->getMass(),
						(std::pow((*itr)->object.getPosition().y - (*i)->object.getPosition().y, 2) + (std::pow((*itr)->object.getPosition().x - (*i)->object.getPosition().x, 2)))) * m_space_scale,
					angle);
			}
		};
	}
}


void ObjectController::updateObjects(float dt, unsigned int time_scale, float sim_speed)
{

	m_calculationThreads.clear(); // clearing threads to prevent mamory leaks


	if (!AppSettings::MultithreadingAllowed())
	{
		for (auto itr = m_objects->begin() + 1, eoi = m_objects->end(); itr != eoi; ++itr)
		{
			for (auto i = m_objects->begin() + 1; i != eoi; ++i)
			{
				if (itr != i)
				{
					if (AppSettings::LessCalculationsMode()) // using less calculations can improve performance by ~3 time (but it depends on several circumstances)
					{
						if (gravitational_force((*itr)->data.mass, (*i)->data.mass, position_to_distance((*itr)->object.getPosition(), (*i)->object.getPosition()) / m_space_scale) > 10e17)
						{
							float angle = std::atan(-((*itr)->object.getPosition().y - (*i)->object.getPosition().y) / ((*itr)->object.getPosition().x - (*i)->object.getPosition().x)) * TO_DEG;

							if (((*itr)->object.getPosition().x > (*i)->object.getPosition().x))
								angle += 180;

							(*itr)->object.physics()->modifyForce((*i)->name(),
								gravitational_force_2((*itr)->object.physics()->getMass(), (*i)->object.physics()->getMass(),
									(std::pow((*itr)->object.getPosition().y - (*i)->object.getPosition().y, 2) + (std::pow((*itr)->object.getPosition().x - (*i)->object.getPosition().x, 2)))) * m_space_scale,
								angle);
						}
					}
					else
					{
						float angle = std::atan(-((*itr)->object.getPosition().y - (*i)->object.getPosition().y) / ((*itr)->object.getPosition().x - (*i)->object.getPosition().x)) * TO_DEG;

						if (((*itr)->object.getPosition().x > (*i)->object.getPosition().x))
							angle += 180;

						(*itr)->object.physics()->modifyForce((*i)->name(),
							gravitational_force_2((*itr)->object.physics()->getMass(), (*i)->object.physics()->getMass(),
								(std::pow((*itr)->object.getPosition().y - (*i)->object.getPosition().y, 2) + (std::pow((*itr)->object.getPosition().x - (*i)->object.getPosition().x, 2)))) * m_space_scale,
							angle);
					}
				}
			}
		}


		for (auto& itr : *m_objects)
			itr->update(dt * m_space_scale * time_scale * sim_speed);



		sf::Vector2<double> _mr(0, 0);	// Sum of mass * pos
		long double _m = 0;				// total mass

		for (auto itr = m_objects->begin() + 1, eoi = m_objects->end(); itr != eoi; ++itr)
		{
			_mr.x += (*itr)->data.mass * (*itr)->object.getPosition().x;
			_mr.y += (*itr)->data.mass * (*itr)->object.getPosition().y;

			_m += (*itr)->data.mass;
		}

		m_objects->front()->object.setPosition(sf::Vector2f(_mr.x / _m, _mr.y / _m));


	}
	else
	{
		//MULTITHREADING IMPROVES PERFORMANCE HERE BY AROUND 10 TIMES

		for (auto itr = m_objects->begin() + 1, eoi = m_objects->end(); itr != eoi; ++itr)
		{
			m_calculationThreads.push_back(std::async(std::launch::async | std::launch::deferred, calculateForce, m_objects, itr, eoi, m_space_scale));
		}


		for (auto& itr : *m_objects)
			itr->update(dt * m_space_scale * time_scale * sim_speed);



		sf::Vector2<double> _mr(0, 0);	// Sum of mass * pos
		long double _m = 0;				// total mass

		for (auto itr = m_objects->begin() + 1, eoi = m_objects->end(); itr != eoi; ++itr)
		{
			_mr.x += (*itr)->data.mass * (*itr)->object.getPosition().x;
			_mr.y += (*itr)->data.mass * (*itr)->object.getPosition().y;

			_m += (*itr)->data.mass;
		}

		m_objects->front()->object.setPosition(sf::Vector2f(_mr.x / _m, _mr.y / _m));

	}
}

void ObjectController::updateObjectPreview(objvector::iterator selected_object, const MousePosition& mousePosition, const sf::Vector2f& viewSize, const sf::Vector2f& winSize)
{
	long double distance = position_to_distance((*selected_object)->object.getPosition(), m_placed_object->getPosition()) / m_space_scale;
	std::wstringstream dist_buffer;

	if (m_objects->size() == 1 || sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) || selected_object == m_objects->begin())
		dist_buffer << std::fixed << std::setprecision(2) << "";
	else if (distance > ly)
		dist_buffer << std::fixed << std::setprecision(3) << distance / ly << " light years";
	else if (distance > au)
		dist_buffer << std::fixed << std::setprecision(2) << distance / au << " au";
	else if (distance > 1000)
		dist_buffer << std::fixed << std::setprecision(2) << distance / 1000 << " km";
	else
		dist_buffer << std::fixed << std::setprecision(2) << distance << " m";


	// adding spaces to numbers (e.g. 1234567.89 -> 1 234 567.89)

	std::wstring strbuffer = dist_buffer.str();

	if (strbuffer.size() > 6)
	{
		size_t ipos = strbuffer.find(L'.');

		if (ipos != std::string::npos)
		{
			short counter = 0;

			while (ipos != 0)
			{
				if (counter % 3 == 0 && counter)
				{
					strbuffer.insert(strbuffer.begin() + ipos, ' ');
					counter = 1;
				}
				else
				{
					counter++;
				}

				ipos--;
			}
		}
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
	{
		m_orbit_preview->setActiveStatus(false);
		m_distance_preview->setActiveStatus(false);
	}
	else
	{
		m_orbit_preview->setActiveStatus(true);
		m_distance_preview->setActiveStatus(true);
	}


	m_orbit_preview->setPosition((*selected_object)->object.getPosition());
	m_orbit_preview->setRadius(distance * m_space_scale);

	m_distance_preview->setPosition(mousePosition.byWindow);
	m_distance_preview->setTextPosition(ke::Origin::LEFT_MIDDLE, { winSize.x / 32 + winSize.x * m_placed_object->getRadius() / viewSize.x, 0 });
	m_distance_preview->setText(strbuffer);
}


void ObjectController::checkName(std::string& name)
{
	int name_num = 1;
	for (auto itr = m_objects->begin() + 1, eoi = m_objects->end(); itr != eoi; ++itr)
	{
		if (name == (*itr)->name())
		{
			name_num++;

			if (name_num == 2)
				name += "   ";

			name.pop_back();

			if (name.back() != ' ')
				name.pop_back();
			if (name.back() != ' ')
				name.pop_back();

			name += (std::to_string(name_num));

			itr = m_objects->begin() + 1; // reset loop
		}
	}
}
