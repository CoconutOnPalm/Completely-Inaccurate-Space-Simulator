#include "VisibleDataController.hpp"

VisibleDataController::VisibleDataController()
	: m_objects(nullptr)
	, m_symbols(nullptr)
	, m_values(nullptr)
	, m_units(nullptr)
	, m_modifiers(nullptr)
	, m_space_scale(0.0000001)
	, m_star_scale(100)
	, m_planet_scale(500)
{
	m_colors.reserve(15);

	for (size_t i = 0; i < 15; i++)
		m_colors.push_back(sf::Color::Transparent);
}

VisibleDataController::~VisibleDataController()
{

}


void VisibleDataController::assign(std::vector<std::unique_ptr<ke::Button>>* symbols, std::unordered_map<std::string, std::unique_ptr<ke::InputButton>>* values, std::vector<std::unique_ptr<ke::Button>>* units, std::vector<std::unique_ptr<ke::Button>>* modifiers, ke::InputButton* object_name, objvector* objects)
{
	m_symbols = symbols;
	m_values = values;
	m_units = units;
	m_modifiers = modifiers;
	m_objects = objects;
	m_object_name = object_name;
}

void VisibleDataController::assignScale(long double space_scale, long double planet_scale, long double star_scale)
{
	m_space_scale = space_scale;
	m_planet_scale = planet_scale;
	m_star_scale = star_scale;
}


void VisibleDataController::loadData(objvector::iterator selected_object, const sf::Vector2f& winSize)
{
	m_object_name->setText(ke::fixed::stow((*selected_object)->name()));

	if (m_object_name->getText().size() > 35)
		m_object_name->setCharacterSize(winSize.y / 80);
	else if (m_object_name->getText().size() > 25)
		m_object_name->setCharacterSize(winSize.y / 64);
	else
		m_object_name->setCharacterSize(winSize.y / 48);


	std::wstringstream data_stream;

	double speedbuff = position_to_distance((*selected_object)->object.physics()->getSpeed(), sf::Vector2f(0, 0));
	float anglebuff = std::atan(-(*selected_object)->object.physics()->getSpeed().y / (*selected_object)->object.physics()->getSpeed().x) * TO_DEG;

	if ((*selected_object)->object.physics()->getSpeed().x < 0)
		anglebuff += 180;

	if (anglebuff < 0)
		anglebuff = 360 + anglebuff;


	if (!isnan(speedbuff))
		data_stream << std::fixed << std::setprecision(3) << speedbuff;
	else data_stream << 0;
	(*m_values)["VELOCITY"]->setText(data_stream.str());

	data_stream.str(std::wstring());
	if (!isnan(anglebuff))
		data_stream << std::fixed << std::setprecision(1) << anglebuff << L"\u00B0";
	else data_stream << L"0\u00B0";
	(*m_values)["V_ANGLE"]->setText(data_stream.str());


	data_stream.str(std::wstring());
	if (!isnan((*selected_object)->object.physics()->getSpeed().x))
		data_stream << std::fixed << std::setprecision(3) << (*selected_object)->object.physics()->getSpeed().x;
	else data_stream << 0;
	(*m_values)["VECTOR_VEL_X"]->setText(data_stream.str());

	data_stream.str(std::wstring());
	if (!isnan((*selected_object)->object.physics()->getSpeed().y))
		data_stream << std::fixed << std::setprecision(3) << (*selected_object)->object.physics()->getSpeed().y;
	else data_stream << 0;
	(*m_values)["VECTOR_VEL_Y"]->setText(data_stream.str());


	data_stream.str(std::wstring());
	data_stream << std::fixed << std::setprecision(3) << std::scientific << (*selected_object)->object.physics()->getMass();
	(*m_values)["MASS"]->setText(data_stream.str());


	long double scale = m_planet_scale;

	switch ((*selected_object)->type())
	{
	case STAR:
		scale = m_star_scale;
		break;

	default:
		break;
	}

	data_stream.str(std::wstring());
	data_stream << std::fixed << std::setprecision(3) << (*selected_object)->data.radius;
	(*m_values)["RADIUS"]->setText(data_stream.str());


	data_stream.str(std::wstring());
	data_stream << std::fixed << std::setprecision(3) << surface_gravity((*selected_object)->object.physics()->getMass(), (*selected_object)->data.radius);
	(*m_values)["SURFACE_G"]->setText(data_stream.str());


	data_stream.str(std::wstring());
	data_stream << std::fixed << std::setprecision(3) << std::scientific << ((*selected_object)->object.physics()->getMass() / Volume((*selected_object)->data.radius));
	(*m_values)["DENSITY"]->setText(data_stream.str());


	data_stream.str(std::wstring());
	data_stream << std::fixed << std::setprecision(3) << second_space_speed((*selected_object)->object.physics()->getMass(), (*selected_object)->data.radius);
	(*m_values)["ESCAPE_VEL"]->setText(data_stream.str());


	this->updateDistanceBlocks(selected_object);
}


void VisibleDataController::setEmpty()
{
	for (auto& itr : *m_values)
	{
		itr.second->setText(std::wstring());
		itr.second->setEPS(false);
	}

	m_object_name->setText(std::wstring());
	m_object_name->setEPS(false);
}


void VisibleDataController::updateStaticData(objvector::iterator selected_object, ke::InputButton* object_name)
{
	if (object_name->getEPS())
	{
		std::string old_name = (*selected_object)->name();
		std::string new_name = ke::fixed::wtos(object_name->getText());

		int name_num = 1;
		for (auto itr = m_objects->begin() + 1, eoi = m_objects->end(); itr != eoi; ++itr)
		{
			if (new_name == (*itr)->name())
			{
				name_num++;

				if (name_num == 2)
					new_name += "  ";

				new_name.pop_back();

				if (new_name.back() != ' ')
					new_name.pop_back();

				new_name += (std::to_string(name_num));
				itr = m_objects->begin() + 1;
			}
		}


		(*selected_object)->setName(new_name);

		for (auto itr = m_objects->begin() + 1, eoi = m_objects->end(); itr != eoi; ++itr)
		{
			if (itr != selected_object)
			{
				sf::Vector2<double> force = (*itr)->object.physics()->getForce(old_name);
				(*itr)->object.physics()->removeForce(old_name);
				(*itr)->object.physics()->addForce(new_name, force);
			}
		}

		object_name->setText(ke::fixed::stow(new_name));
	}


	if ((*m_values)["VELOCITY"]->getEPS() || (*m_values)["V_ANGLE"]->getEPS())
	{
		std::wstringstream conversion;
		double vbuff = 0;
		double abuff = 0;

		if ((*m_values)["VELOCITY"]->getText() == std::wstring())
			vbuff = 0;
		else if ((*m_values)["V_ANGLE"]->getText() == std::wstring())
			abuff = 0;
		else
		{

			conversion << (*m_values)["VELOCITY"]->getText();
			conversion >> vbuff;

			//conversion.str(std::wstring());
			std::wstring temp = (*m_values)["V_ANGLE"]->getText();
			if (!temp.empty())
				if (temp.back() == L'\u00B0')
					temp.pop_back();

			std::wstringstream astream;
			astream.str(temp);
			astream >> abuff;
		}
		//std::wcout << "temp: " << temp << L'\n' << "abuff: " << abuff << '\n';

		(*selected_object)->object.physics()->setSpeed(vbuff, abuff);


		std::wstringstream wstr;

		//conversion.str(std::wstring());
		if (vbuff == 0 || abuff == 0)
			wstr << 0;
		else wstr << std::fixed << std::setprecision(3) << vbuff;
		(*m_values)["VELOCITY"]->setText(wstr.str());

		wstr.str(std::wstring());
		if (vbuff == 0 || abuff == 0)
			wstr << 0 << L"\u00B0";
		else wstr << std::fixed << std::setprecision(1) << abuff << L"\u00B0";
		(*m_values)["V_ANGLE"]->setText(wstr.str());

		wstr.str(std::wstring());
		if (vbuff == 0 || abuff == 0)
			wstr << 0;
		else wstr << std::fixed << std::setprecision(3) << (*selected_object)->object.physics()->getSpeed().x;
		(*m_values)["VECTOR_VEL_X"]->setText(wstr.str());

		wstr.str(std::wstring());
		if (vbuff == 0 || abuff == 0)
			wstr << 0;
		else wstr << std::fixed << std::setprecision(3) << (*selected_object)->object.physics()->getSpeed().y;
		(*m_values)["VECTOR_VEL_Y"]->setText(wstr.str());
	}

	if ((*m_values)["VECTOR_VEL_X"]->getEPS() || (*m_values)["VECTOR_VEL_Y"]->getEPS())
	{
		std::wstringstream conversion;
		sf::Vector2<double> vbuff;

		conversion << (*m_values)["VECTOR_VEL_X"]->getText();
		conversion >> vbuff.x;

		std::wstringstream wc;
		//conversion.str(std::wstring());
		wc << (*m_values)["VECTOR_VEL_Y"]->getText();
		wc >> vbuff.y;


		(*selected_object)->object.physics()->setSpeed(vbuff);

		float anglebuff = std::atan(-vbuff.y / vbuff.x) * TO_DEG;

		if (vbuff.x < 0)
			anglebuff += 180;

		if (anglebuff < 0)
			anglebuff = 360 + anglebuff;


		std::wstringstream wstr;

		//conversion.str(std::wstring());
		wstr << std::fixed << std::setprecision(3) << std::sqrt(vbuff.x * vbuff.x + vbuff.y * vbuff.y);
		(*m_values)["VELOCITY"]->setText(wstr.str());

		wstr.str(std::wstring());
		if (!isnan(anglebuff))
			wstr << std::fixed << std::setprecision(1) << anglebuff << L"\u00B0";
		else wstr << L"0\u00B0";
		(*m_values)["V_ANGLE"]->setText(wstr.str());

		wstr.str(std::wstring());
		wstr << std::fixed << std::setprecision(3) << vbuff.x;
		(*m_values)["VECTOR_VEL_X"]->setText(wstr.str());

		wstr.str(std::wstring());
		wstr << std::fixed << std::setprecision(3) << vbuff.y;
		(*m_values)["VECTOR_VEL_Y"]->setText(wstr.str());
	}


	if ((*m_values)["MASS"]->getEPS())
	{
		std::wstringstream data_stream;
		long double mass;
		data_stream << (*m_values)["MASS"]->getText();
		data_stream >> mass;
		std::cout << mass << '\n';

		// TODO: schwardshild radius and black hole convertion

		(*selected_object)->object.physics()->setMass(mass);
		(*selected_object)->data.mass = mass;
		(*selected_object)->updatePhysicalData();


		std::wstringstream corr_stream;

		corr_stream << std::fixed << std::setprecision(3) << surface_gravity((*selected_object)->object.physics()->getMass(), (*selected_object)->data.radius);
		(*m_values)["SURFACE_G"]->setText(corr_stream.str());

		corr_stream.str(std::wstring());
		corr_stream << std::fixed << std::setprecision(3) << std::scientific << (*selected_object)->object.physics()->getMass() / Volume((*selected_object)->data.radius);
		(*m_values)["DENSITY"]->setText(corr_stream.str());

		corr_stream.str(std::wstring());
		corr_stream << std::fixed << std::setprecision(3) << second_space_speed((*selected_object)->object.physics()->getMass(), (*selected_object)->data.radius);
		(*m_values)["ESCAPE_VEL"]->setText(corr_stream.str());


		std::wstringstream back_stream;

		//data_stream.str(std::wstring());
		back_stream << std::fixed << std::setprecision(3) << std::scientific << mass;
		(*m_values)["MASS"]->setText(back_stream.str());
	}

	if ((*m_values)["RADIUS"]->getEPS())
	{
		std::wstringstream data_stream;
		long double radius;
		data_stream << (*m_values)["RADIUS"]->getText();
		data_stream >> radius;

		// TODO: schwardshild radius and black hole convertion


		switch ((*selected_object)->type())
		{
		case PLANET:
			(*selected_object)->object.setRadius(radius * m_space_scale * m_planet_scale);
			(*selected_object)->data.radius = radius;
			(*selected_object)->updatePhysicalData();
			break;
		case STAR:
			(*selected_object)->object.setRadius(radius * m_space_scale * m_star_scale);
			(*selected_object)->data.radius = radius;
			(*selected_object)->updatePhysicalData();
			break;
		default:
			ke::throw_error("VisibleDataController::updateStaticData(...)", "incorrect object type", "ERROR");
			break;
		}


		std::wstringstream corr_stream;

		corr_stream << std::fixed << std::setprecision(3) << surface_gravity((*selected_object)->object.physics()->getMass(), radius);
		(*m_values)["SURFACE_G"]->setText(corr_stream.str());

		corr_stream.str(std::wstring());
		corr_stream << std::fixed << std::setprecision(3) << std::scientific << (*selected_object)->object.physics()->getMass() / Volume(radius);
		(*m_values)["DENSITY"]->setText(corr_stream.str());

		corr_stream.str(std::wstring());
		corr_stream << std::fixed << std::setprecision(3) << second_space_speed((*selected_object)->object.physics()->getMass(), radius);
		(*m_values)["ESCAPE_VEL"]->setText(corr_stream.str());

		std::wstringstream back_stream;

		back_stream << std::fixed << std::setprecision(3) << radius;
		(*m_values)["RADIUS"]->setText(back_stream.str());
	}


	if ((*m_values)["SURFACE_G"]->getEPS())
	{
		if ((*m_values)["SURFACE_G"]->getText() == std::wstring())
			return;

		std::wstringstream data_stream;
		long double surfg;
		data_stream << (*m_values)["SURFACE_G"]->getText();
		data_stream >> surfg;

		long double new_mass = surfg * (*selected_object)->data.radius * (*selected_object)->data.radius / G;
		(*selected_object)->object.physics()->setMass(new_mass);
		(*selected_object)->data.mass = new_mass;
		(*selected_object)->updatePhysicalData();

		// TODO: schwardshild radius and black hole convertion


		std::wstringstream corr_stream;

		corr_stream << std::fixed << std::setprecision(3) << std::scientific << new_mass;
		(*m_values)["MASS"]->setText(corr_stream.str());

		corr_stream.str(std::wstring());
		corr_stream << std::fixed << std::setprecision(3) << std::scientific << new_mass / Volume((*selected_object)->data.radius);
		(*m_values)["DENSITY"]->setText(corr_stream.str());

		corr_stream.str(std::wstring());
		corr_stream << std::fixed << std::setprecision(3) << second_space_speed(new_mass, (*selected_object)->data.radius);
		(*m_values)["ESCAPE_VEL"]->setText(corr_stream.str());


		std::wstringstream back_stream;

		back_stream << std::fixed << std::setprecision(3) << surfg;
		(*m_values)["SURFACE_G"]->setText(back_stream.str());
	}

	if ((*m_values)["DENSITY"]->getEPS())
	{
		if ((*m_values)["DENSITY"]->getText() == std::wstring())
			return;

		std::wstringstream data_stream;
		long double density;
		data_stream << (*m_values)["DENSITY"]->getText();
		data_stream >> density;

		long double new_mass = density * Volume((*selected_object)->data.radius);
		(*selected_object)->object.physics()->setMass(new_mass);
		(*selected_object)->data.mass = new_mass;
		(*selected_object)->updatePhysicalData();

		// TODO: schwardshild radius and black hole convertion


		std::wstringstream corr_stream;

		corr_stream << std::fixed << std::setprecision(3) << std::scientific << new_mass;
		(*m_values)["MASS"]->setText(corr_stream.str());

		corr_stream.str(std::wstring());
		corr_stream << std::fixed << std::setprecision(3) << surface_gravity(new_mass, (*selected_object)->data.radius);
		(*m_values)["SURFACE_G"]->setText(corr_stream.str());

		corr_stream.str(std::wstring());
		corr_stream << std::fixed << std::setprecision(3) << second_space_speed(new_mass, (*selected_object)->data.radius);
		(*m_values)["ESCAPE_VEL"]->setText(corr_stream.str());


		std::wstringstream back_stream;

		back_stream << std::fixed << std::setprecision(3) << density;
		(*m_values)["DENSITY"]->setText(back_stream.str());
	}


	if ((*m_values)["ESCAPE_VEL"]->getEPS())
	{
		std::wstringstream data_stream;
		long double escape_velocity;
		data_stream << (*m_values)["ESCAPE_VEL"]->getText();
		data_stream >> escape_velocity;

		long double new_mass = escape_velocity * escape_velocity * (*selected_object)->data.radius / (2 * G);
		(*selected_object)->object.physics()->setMass(new_mass);
		(*selected_object)->data.mass = new_mass;
		(*selected_object)->updatePhysicalData();

		// TODO: schwardshild radius and black hole convertion


		std::wstringstream corr_stream;

		corr_stream << std::fixed << std::setprecision(3) << std::scientific << new_mass;
		(*m_values)["MASS"]->setText(corr_stream.str());

		corr_stream.str(std::wstring());
		corr_stream << std::fixed << std::setprecision(3) << surface_gravity(new_mass, (*selected_object)->data.radius);
		(*m_values)["SURFACE_G"]->setText(corr_stream.str());


		std::wstringstream back_stream;

		back_stream << std::fixed << std::setprecision(3) << escape_velocity;
		(*m_values)["ESCAPE_VEL"]->setText(back_stream.str());
	}
}


void VisibleDataController::updateDynamicData(objvector::iterator selected_object)
{
	std::wstringstream data_stream;

	double speedbuff = position_to_distance((*selected_object)->object.physics()->getSpeed(), sf::Vector2f(0, 0));
	float anglebuff = std::atan(-(*selected_object)->object.physics()->getSpeed().y / (*selected_object)->object.physics()->getSpeed().x) * TO_DEG;

	if ((*selected_object)->object.physics()->getSpeed().x < 0)
		anglebuff += 180;

	if (anglebuff < 0)
		anglebuff = 360 + anglebuff;

	//data_stream.str(std::wstring());
	if (speedbuff > 0)
		data_stream << std::fixed << std::setprecision(3) << speedbuff;
	else data_stream << 0;
	(*m_values)["VELOCITY"]->setText(data_stream.str());

	data_stream.str(std::wstring());
	if (speedbuff > 0 && !isnan(anglebuff))
		data_stream << std::fixed << std::setprecision(1) << anglebuff << L"\u00B0";
	else data_stream << L"0\u00B0";
	(*m_values)["V_ANGLE"]->setText(data_stream.str());

	data_stream.str(std::wstring());
	data_stream << std::fixed << std::setprecision(3) << (*selected_object)->object.physics()->getSpeed().x;
	(*m_values)["VECTOR_VEL_X"]->setText(data_stream.str());

	data_stream.str(std::wstring());
	data_stream << std::fixed << std::setprecision(3) << (*selected_object)->object.physics()->getSpeed().y;
	(*m_values)["VECTOR_VEL_Y"]->setText(data_stream.str());


	this->updateDistanceBlocks(selected_object);
}

void VisibleDataController::updateColors(const sf::Vector2f& mousePosition, const float dt)
{
	auto color_itr = m_colors.begin();

	ke::SmoothColorChange(m_object_name, m_object_name->isInvaded(mousePosition) || m_object_name->getEPS(), sf::Color(255, 255, 255, 32), sf::Color::Transparent, *color_itr, 1024, dt);
	++color_itr;

	for (auto& itr : *m_values)
	{
		ke::SmoothColorChange(itr.second.get(), itr.second->isInvaded(mousePosition) || itr.second->getEPS(), sf::Color(255, 255, 255, 32), sf::Color::Transparent, *color_itr, 1024, dt);
		++color_itr;
	}


	ke::SmoothColorChange((m_modifiers->begin())->get(), (*m_modifiers->begin())->isInvaded(mousePosition), sf::Color(255, 255, 255, 64), sf::Color(255, 255, 255, 32), *color_itr, 256, dt);
	++color_itr;
	ke::SmoothColorChange((m_modifiers->begin() + 1)->get(), (*(m_modifiers->begin() + 1))->isInvaded(mousePosition), sf::Color(255, 255, 255, 64), sf::Color(255, 255, 255, 32), *color_itr, 256, dt);
	++color_itr;
	ke::SmoothColorChange((m_modifiers->begin() + 2)->get(), (*(m_modifiers->begin() + 2))->isInvaded(mousePosition), sf::Color(255, 0, 0, 64), sf::Color(255, 0, 0, 32), *color_itr, 256, dt);
	++color_itr;
}


void VisibleDataController::checkInputString()
{
	std::wstring text_check;

	for (auto& itr : *m_values)
	{
		text_check = itr.second->getText();

		for (auto& i : text_check)
			if (i == ',')
				i = '.';

		itr.second->setText(text_check);
	}
}


void VisibleDataController::updateDistanceBlocks(objvector::iterator selected_object)
{
	if (m_objects->size() >= 3)
	{
		std::wstringstream dist_str;

		auto nearest_object = m_objects->begin();
		auto nearest_star = m_objects->begin();
		long double min_obj_dist = 1e300;
		long double min_star_dist = 1e300;

		if (selected_object == m_objects->end() - 1)
			nearest_object = m_objects->end() - 2;
		else
			nearest_object = selected_object + 1;

		min_obj_dist = position_to_distance((*selected_object)->object.getPosition(), (*nearest_object)->object.getPosition());

		for (auto itr = m_objects->begin(), eoi = m_objects->end(); itr != eoi; ++itr)
		{
			if (itr != selected_object)
			{
				if ((*itr)->type() == STAR)
				{
					if (position_to_distance((*selected_object)->object.getPosition(), (*itr)->object.getPosition()) < min_star_dist)
					{
						nearest_star = itr;
						min_star_dist = position_to_distance((*selected_object)->object.getPosition(), (*itr)->object.getPosition());
					}
				}
				if (position_to_distance((*selected_object)->object.getPosition(), (*itr)->object.getPosition()) < min_obj_dist)
				{
					nearest_object = itr;
					min_obj_dist = position_to_distance((*selected_object)->object.getPosition(), (*itr)->object.getPosition());
				}
			}
		}


		min_obj_dist /= m_space_scale;
		min_star_dist /= m_space_scale;


		//dist_str.str(std::wstring());
		if (min_obj_dist > ly)
			dist_str << std::fixed << std::setprecision(2) << min_obj_dist / ly << " ly";
		else if (min_obj_dist > au)
			dist_str << std::fixed << std::setprecision(2) << min_obj_dist / au << " au";
		else
			dist_str << std::fixed << std::setprecision(2) << min_obj_dist << " m";

		(*m_values)["TO_NEAREST_OBJ"]->setText(dist_str.str());

		dist_str.str(std::wstring());
		if (min_star_dist > ly)
			dist_str << std::fixed << std::setprecision(2) << min_star_dist / ly << " ly";
		else if (min_star_dist > au)
			dist_str << std::fixed << std::setprecision(2) << min_star_dist / au << " au";
		else
			dist_str << std::fixed << std::setprecision(2) << min_star_dist << " m";


		if ((*selected_object)->type() == STAR)
			if ((*m_objects->begin())->getStarCount() <= 1)
				(*m_values)["TO_NEAREST_STAR"]->setText(std::wstring());
			else
				(*m_values)["TO_NEAREST_STAR"]->setText(dist_str.str());
		else
			if ((*m_objects->begin())->getStarCount() < 1)
				(*m_values)["TO_NEAREST_STAR"]->setText(std::wstring());
			else
				(*m_values)["TO_NEAREST_STAR"]->setText(dist_str.str());
	}
	else
	{
		(*m_values)["TO_NEAREST_OBJ"]->setText(std::wstring());
		(*m_values)["TO_NEAREST_STAR"]->setText(std::wstring());
	}
}
