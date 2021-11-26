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

	(*m_values)["CLASS"]->setText(ke::fixed::stow(TypeTranslator::getClassName((*selected_object)->objectClass())));
	(*m_values)["SUBTYPE"]->setText(ke::fixed::stow(TypeTranslator::getSubtypeName((*selected_object)->subtype())));

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

		(*selected_object)->object.physics()->setSpeed(vbuff, abuff);


		std::wstringstream wstr;

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


		std::wstringstream back_stream;

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

		std::wstringstream back_stream;

		back_stream << std::fixed << std::setprecision(3) << radius;
		(*m_values)["RADIUS"]->setText(back_stream.str());
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


	ke::SmoothColorChange((m_modifiers->begin())->get(), (*m_modifiers->begin())->isInvaded(mousePosition), sf::Color(128, 128, 128, 64), sf::Color(128, 128, 128, 32), *color_itr, 256, dt);
	++color_itr;
	ke::SmoothColorChange((m_modifiers->begin() + 1)->get(), (*(m_modifiers->begin() + 1))->isInvaded(mousePosition), sf::Color(128, 128, 128, 64), sf::Color(128, 128, 128, 32), *color_itr, 256, dt);
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
	if (m_objects->size() >= 3) // 2 objects + center of mass
	{
		std::wstringstream dist_str;

		auto nearest_object = m_objects->begin();
		auto nearest_star = m_objects->begin();
		long double distance = 1e300;

		if (selected_object == m_objects->end() - 1)
			nearest_object = m_objects->end() - 2;
		else
			nearest_object = selected_object + 1;

		distance = position_to_distance((*selected_object)->object.getPosition(), (*nearest_object)->object.getPosition());


		if (isnan(distance))
			distance = 0;


		distance /= m_space_scale;

		if (distance > ly)
		{
			dist_str << std::fixed << std::setprecision(2) << distance / ly;
			m_units->at(4)->setText(L"ly");
		}
		else if (distance > au)
		{
			dist_str << std::fixed << std::setprecision(2) << distance / au;
			m_units->at(4)->setText(L"au");
		}
		else if (distance > 1000)
		{
			dist_str << std::fixed << std::setprecision(2) << distance / 1000;
			m_units->at(4)->setText(L"km");
		}
		else
		{
			dist_str << std::fixed << std::setprecision(2) << distance;
			m_units->at(4)->setText(L"m");
		}


		std::wstring strbuffer = dist_str.str();

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

		(*m_values)["NEAREST_OBJ"]->setText(strbuffer);

		//dist_str.str(std::wstring());
		//if (min_star_dist > ly)
		//	dist_str << std::fixed << std::setprecision(2) << min_star_dist / ly << " ly";
		//else if (min_star_dist > au)
		//	dist_str << std::fixed << std::setprecision(2) << min_star_dist / au << " au";
		//else
		//	dist_str << std::fixed << std::setprecision(2) << min_star_dist << " m";


		//if ((*selected_object)->type() == STAR)
		//	if ((*m_objects->begin())->getStarCount() <= 1)
		//		(*m_values)["TO_NEAREST_STAR"]->setText(std::wstring());
		//	else
		//		(*m_values)["TO_NEAREST_STAR"]->setText(dist_str.str());
		//else
		//	if ((*m_objects->begin())->getStarCount() < 1)
		//		(*m_values)["TO_NEAREST_STAR"]->setText(std::wstring());
		//	else
		//		(*m_values)["TO_NEAREST_STAR"]->setText(dist_str.str());
	}
	else
	{
		(*m_values)["NEAREST_OBJ"]->setText(std::wstring());
		//(*m_values)["TO_NEAREST_STAR"]->setText(std::wstring());
	}
}
