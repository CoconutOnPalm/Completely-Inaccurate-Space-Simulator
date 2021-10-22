#include "DropdownList.hpp"

namespace ke
{

	DropdownList::DropdownList()
		: m_pos_itr(1)
		, m_expaned(false)
		, m_def_pos(0, 0)
		, m_def_color(sf::Color::Transparent)
		, m_def_text_color(sf::Color::Transparent)
		, m_def_out_color(sf::Color::Transparent)
		, m_def_out_thick(0)
		, m_def_text_style(sf::Text::Regular)
		, m_def_font(ke::Font::Arial)
		, m_act_id(-1)
		, m_def_active(false)
		, m_created(false)
	{
		
	}


	////////////////////////////////


	DropdownList::DropdownList(
		const sf::Vector2f& size,
		const sf::Vector2f& position,
		const sf::Texture* default_texture,
		const std::wstring& default_text,
		unsigned int default_character_size,
		int default_text_position,
		const sf::Color& default_object_color,
		const sf::Color& default_text_color,
		float default_outline_thickness,
		const sf::Color& default_outline_color,
		unsigned int default_text_style,
		const sf::Vector2f& default_text_shift,
		int default_font,
		bool expanded,
		bool active)

		: m_expaned(expanded)
		, m_pos_itr(1)
		, m_act_id(-1)
		, m_def_active(active)
		, m_created(true)
	{
		m_selected = std::make_unique<Button>(size, position, MIDDLE_MIDDLE, default_texture, default_text, default_character_size, default_text_position, default_object_color, default_text_color, default_outline_thickness, default_outline_color, 0, default_text_style, default_text_shift, default_font, active);

		int j = m_pos_itr;
		if (m_members.size() >= m_member_pos.size())
			for (; m_pos_itr < j + 10; m_pos_itr++)
				m_member_pos.push_back(m_selected->getPosition().y + m_selected->getSize().y * m_pos_itr);

		m_def_pos = position;
		m_def_color = default_object_color;
		m_def_text_color = default_text_color;
		m_def_out_color = default_outline_color;
		m_def_out_thick = default_outline_thickness;
		m_def_text_style = default_text_style;
		m_def_font = default_font;

		m_member_id.push_back(-1);
	}


	////////////////////////////////


	DropdownList::DropdownList(
		const sf::Vector2f& size,
		const sf::Vector2f& position,
		const std::string& default_texture_filename,
		const std::wstring& default_text,
		unsigned int default_character_size,
		int default_text_position,
		const sf::Color& default_object_color,
		const sf::Color& default_text_color,
		float default_outline_thickness,
		const sf::Color& default_outline_color,
		unsigned int default_text_style,
		const sf::Vector2f& default_text_shift,
		int default_font,
		bool expanded,
		bool active)

		: m_expaned(expanded)
		, m_pos_itr(1)
		, m_act_id(-1)	
		, m_def_active(active)
		, m_created(true)
	{
		m_selected = std::make_unique<Button>(size, position, MIDDLE_MIDDLE, default_texture_filename, default_text, default_character_size, default_text_position, default_object_color, default_text_color, default_outline_thickness, default_outline_color, 0, default_text_style, default_text_shift, default_font, active);

		int j = m_pos_itr;
		if (m_members.size() >= m_member_pos.size())
			for (; m_pos_itr < j + 10; m_pos_itr++)
				m_member_pos.push_back(m_selected->getPosition().y + m_selected->getSize().y * m_pos_itr);

		m_def_pos = position;
		m_def_color = default_object_color;
		m_def_text_color = default_text_color;
		m_def_out_color = default_outline_color;
		m_def_out_thick = default_outline_thickness;
		m_def_text_style = default_text_style;
		m_def_font = default_font;

		m_member_id.push_back(-1);
	}


	////////////////////////////////


	DropdownList::~DropdownList()
	{

	}


	////////////////////////////////


	void DropdownList::create(
		const sf::Vector2f& size,
		const sf::Vector2f& position,
		const sf::Texture* default_texture,
		const std::wstring& default_text,
		unsigned int default_character_size,
		int default_text_position,
		const sf::Color& default_object_color,
		const sf::Color& default_text_color,
		float default_outline_thickness,
		const sf::Color& default_outline_color,
		unsigned int default_text_style,
		const sf::Vector2f& default_text_shift,
		int default_font,
		bool expanded,
		bool active)
	{
		m_selected = std::make_unique<Button>(size, position, MIDDLE_MIDDLE, default_texture, default_text, default_character_size, default_text_position, default_object_color, default_text_color, default_outline_thickness, default_outline_color, 0, default_text_style, default_text_shift, default_font, active);

		m_expaned = expanded;

		m_pos_itr = 1;
		m_def_active = active;
		m_act_id = -1;

		int j = m_pos_itr;
		if (m_members.size() >= m_member_pos.size())
			for (; m_pos_itr < j + 10; m_pos_itr++)
				m_member_pos.push_back(m_selected->getShapeCenter().y + m_selected->getSize().y * m_pos_itr);

		m_def_pos = position;
		m_def_color = default_object_color;
		m_def_text_color = default_text_color;
		m_def_out_color = default_outline_color;
		m_def_out_thick = default_outline_thickness;
		m_def_text_style = default_text_style;
		m_def_font = default_font;

		m_member_id.push_back(-1);

		m_created = true;
	}


	////////////////////////////////


	void DropdownList::create(
		const sf::Vector2f& size,
		const sf::Vector2f& position,
		const std::string& default_texture_filename,
		const std::wstring& default_text,
		unsigned int default_character_size,
		int default_text_position,
		const sf::Color& default_object_color,
		const sf::Color& default_text_color,
		float default_outline_thickness,
		const sf::Color& default_outline_color,
		unsigned int default_text_style,
		const sf::Vector2f& default_text_shift,
		int default_font,
		bool expanded,
		bool active)
	{
		m_selected = std::make_unique<Button>(size, position, MIDDLE_MIDDLE, default_texture_filename, default_text, default_character_size, default_text_position, default_object_color, default_text_color, default_outline_thickness, default_outline_color, 0, default_text_style, default_text_shift, default_font, active);

		m_expaned = expanded;

		m_pos_itr = 1;
		m_def_active = active;
		m_act_id = -1;

		int j = m_pos_itr;
		if (m_members.size() >= m_member_pos.size())
			for (; m_pos_itr < j + 10; m_pos_itr++)
				m_member_pos.push_back(m_selected->getShapeCenter().y + m_selected->getSize().y * m_pos_itr);

		m_def_pos = position;
		m_def_color = default_object_color;
		m_def_text_color = default_text_color;
		m_def_out_color = default_outline_color;
		m_def_out_thick = default_outline_thickness;
		m_def_text_style = default_text_style;
		m_def_font = default_font;

		m_member_id.push_back(-1);

		m_created = true;
	}



	////////////////////////////////////////////////////////////////



	void DropdownList::addMember(
		const sf::Texture* texture,
		const std::wstring& text,
		unsigned int character_size,
		int text_position,
		const sf::Color& object_color,
		const sf::Color& text_color,
		float outline_thickness,
		const sf::Color& outline_color,
		unsigned int text_style,
		const sf::Vector2f& text_shift,
		int font)
	{
		int j = m_pos_itr;
		if (m_members.size() >= m_member_pos.size())
			for (; m_pos_itr < j + 10; m_pos_itr++)
				m_member_pos.push_back(m_selected->getShapeCenter().y + m_selected->getSize().y * m_pos_itr);

		m_member_id.push_back(m_member_id.back() + 1);

		size_t i = m_members.size();
		m_members.push_back(std::make_unique<Button>(m_selected->getSize(), sf::Vector2f(m_selected->getPosition().x, m_member_pos[i]), MIDDLE_MIDDLE, texture, text, character_size, text_position, object_color, text_color, outline_thickness, outline_color, 0, text_style, text_shift, font, m_expaned));
	}


	////////////////////////////////


	void DropdownList::addMember(
		const std::string& filename,
		const std::wstring& text,
		unsigned int character_size,
		int text_position,
		const sf::Color& object_color,
		const sf::Color& text_color,
		float outline_thickness,
		const sf::Color& outline_color,
		unsigned int text_style,
		const sf::Vector2f& text_shift,
		int font)
	{
		int j = m_pos_itr;
		if (m_members.size() >= m_member_pos.size())
			for (; m_pos_itr < j + 10; m_pos_itr++)
				m_member_pos.push_back(m_selected->getShapeCenter().y + m_selected->getSize().y * m_pos_itr);

		size_t i = m_members.size();
		m_members.push_back(std::make_unique<Button>(m_selected->getSize(), sf::Vector2f(m_selected->getPosition().x, m_member_pos[i]), MIDDLE_MIDDLE, filename, text, character_size, text_position, object_color, text_color, outline_thickness, outline_color, 0, text_style, text_shift, font, m_expaned));
	}



	////////////////////////////////////////////////////////////////



	void DropdownList::deleteList()
	{
		m_members.clear();
		m_member_id.clear();
		//this->m_pos_itr = 1;
	}


	////////////////////////////////


	void DropdownList::removeMember(unsigned int member_number)
	{
		if (m_members.size() > 0)
		{
			if (member_number > m_members.size() - 1)
			{
				member_number = m_members.size() - 1;
				throw_error("DropdownList::removeMember(..)", "the given member number is greater than their count", "ERROR");
			}

			m_members.erase(m_members.begin() + member_number);

			m_member_id.erase(m_member_id.begin() + 1 + member_number);

			this->updateMembersPosition();
		}
	}



	void DropdownList::removeMemberByID(int member_id)
	{
		if (m_members.size() > 0)
		{
			for (int i = 1; i < m_member_id.size(); i++)
			{
				if (m_member_id[i] == member_id)
				{
					m_members.erase(m_members.begin() + i - 1);

					m_member_id.erase(m_member_id.begin() + i);

					this->updateMembersPosition();

					break;
				}
			}
		}
	}



	////////////////////////////////////////////////////////////////



	void DropdownList::setMemberAsActive(unsigned int member_number)
	{
		if (member_number > m_members.size() - 1) 
		{
			member_number = m_members.size() - 1;
			throw_error("DropdownList::setMemberAsActive(..)", "given member number is too large", "ERROR");
		}

		*m_selected = *m_members.at(member_number);
		m_selected->setPosition(m_def_pos);
		//m_selected->setTexture(m_members.at(member_number)->getTexture());
		m_selected->setFillColor(m_def_color);
		m_selected->setTextColor(m_def_text_color);
		m_selected->setOutlineColor(m_def_out_color);
		m_selected->setOutlineThickness(m_def_out_thick);
		m_selected->setTextStyle(m_def_text_style);
		m_selected->setFont(m_def_font);

		m_selected->setActiveStatus(m_def_active);

		//int idtr = -1; // member ID iterator

		m_act_id = m_member_id.at(member_number) + 1;
	}



	////////////////////////////////



	void DropdownList::swapMembers(unsigned int mn_1, unsigned int mn_2)
	{
		if (m_members.size() > 0)
		{
			if (mn_1 > +m_members.size() - 1)
			{
				mn_1 = m_members.size() - 1;
				throw_error("DropdownList::swapMembers(..)", "the given member number is greater than their count", "ERROR");
			}

			if (mn_2 > +m_members.size() - 1) 
			{
				mn_2 = m_members.size() - 1;
				throw_error("DropdownList::swapMembers(..)", "the given member number is greater than their count", "ERROR");
			}


			if (mn_1 != mn_2)
			{
				std::swap(m_members.at(mn_1), m_members.at(mn_2));
				this->updateMembersPosition();
			}

			std::swap(m_member_id.at(mn_1 + 1), m_member_id.at(mn_2 + 1));
		}
	}



	////////////////////////////////////////////////////////////////



	std::vector<std::unique_ptr<Button>>* DropdownList::getMembers()
	{
		return &m_members;
	}


	Button* DropdownList::getSelected()
	{
		return m_selected.get();
	}



	////////////////////////////////////////////////////////////////



	void DropdownList::updateMembersPosition()
	{
		m_def_pos = m_selected->getPosition();

		int j = 1;
		for (auto& itr : m_member_pos)
		{
			itr = m_selected->getShapeCenter().y + m_selected->getSize().y * j;
			j++;
		}

		size_t i = 0;

		for (auto itr = m_members.begin(), eoi = m_members.end(); itr != eoi; ++itr, i++)
			(*itr)->setPosition(m_selected->getPosition().x, m_member_pos[i]);
	}



	////////////////////////////////////////////////////////////////



	bool DropdownList::isActive() const
	{
		return m_selected->isActive();
	}


	void DropdownList::setActiveStatus(bool status)
	{
		m_def_active = status;

		m_selected->setActiveStatus(status);

		if (!status)
			for (auto& itr : m_members)
				itr->setActiveStatus(status);
		else if (m_expaned)
			for (auto& itr : m_members)
				itr->setActiveStatus(status);
	}


	////////////////////////////////


	bool DropdownList::Expanded() const
	{
		return m_expaned;
	}


	void DropdownList::setExpandStatus(bool status)
	{
		m_expaned = status;

		for (auto& i : m_members)
			i->setActiveStatus(m_expaned);
	}



	////////////////////////////////////////////////////////////////



	int DropdownList::getSelectedID() const
	{
		return m_act_id;
	}


	const std::vector<int>* DropdownList::getMembersID() const
	{
		return &m_member_id;
	}



	////////////////////////////////////////////////////////////////



	bool DropdownList::update(const sf::Vector2f& mousePosition, sf::Event& event, sf::Mouse::Button button, sf::View* view)
	{
		if (!m_selected->isActive())
			return false;

		if (m_selected->isClicked(button, mousePosition, event))
			m_expaned = !m_expaned;
			//m_expaned = ((m_expaned) ? false : true);

		for (auto& i : m_members)
			i->setActiveStatus(m_expaned);

		m_selected->update(mousePosition, event, button, view);

		if (m_expaned)
		{
			int idtr = 0;
			for (auto& i : m_members)
			{
				if (i->isClicked(button, mousePosition, event))
				{
					sf::Color color_buffer = m_selected->getFillColor();
					sf::Color outline_color_buffer = m_selected->getOutlineColor();
					sf::Color text_color_buffer = m_selected->getTextColor();
					float outline_thickness_buffer = m_selected->getOutlineThickness();

					*m_selected = *i;
					m_selected->setPosition(m_def_pos);
					m_selected->setFillColor(color_buffer);
					m_selected->setTextColor(outline_color_buffer);
					m_selected->setOutlineColor(text_color_buffer);
					m_selected->setOutlineThickness(outline_thickness_buffer);
					m_selected->setTextStyle(m_def_text_style);
					m_selected->setFont(m_def_font);

					//m_selected->setActiveStatus(m_def_active);
					m_act_id = m_member_id.at(idtr + 1);

					i->update(mousePosition, event, button, view);

					m_expaned = true;

					return true;
				}

				i->update(mousePosition, event, button, view);

				idtr++;
			}
		}

		return false;
	}



	////////////////////////////////////////////////////////////////



	void DropdownList::render(sf::RenderWindow* window)
	{
		for (auto& i : m_members)
			i->render(window);

		//m_selected->setActiveStatus(1);
		m_selected->render(window);
	}



	////////////////////////////////////////////////////////////////



	bool DropdownList::created() const
	{
		return m_created;
	}


} // namespace ke