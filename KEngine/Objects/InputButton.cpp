#include "InputButton.hpp"

namespace ke
{


	//-------------------------                                                         -------------------------//
	//+++                                                                                                     +++//
	//============== C O N S T R U C T O R S ,   D E S T R U C T O R S   A N D   O P E R A T O R S ==============//
	//+++                                                                                                     +++//
	//-------------------------                                                         -------------------------//





	InputButton::InputButton()
		: m_imp_text(L"")
		, m_def_text(L"")
		, m_text_scope(TextScope::Everything)
		, m_possible_to_ent(false)
		, m_no_lines(0)
		, m_max_char(0)
		, m_max_lines(0)
		, m_text_color(sf::Color::Transparent)
		, m_def_text_color(sf::Color::Transparent)
		, m_flick_time(0)
		, m_created(false)
	{

	}


	////////////////////////////////


	InputButton::InputButton(
		const sf::Vector2f& size,
		const sf::Vector2f& position,
		int origin,
		const sf::Texture* texture,
		const std::wstring& default_text,
		int text_scope,
		unsigned int max_number_of_characters,
		unsigned int max_number_of_lines,
		unsigned int character_size,
		int text_position,
		const sf::Color& object_color,
		const sf::Color& text_color,
		const sf::Color& default_text_color,
		float outline_thickness,
		const sf::Color& outline_color,
		unsigned int text_style,
		const sf::Vector2f& text_shift,
		int font,
		bool acitve)

		: m_imp_text(L"")
		, m_def_text(default_text)
		, m_text_scope(text_scope)
		, m_possible_to_ent(false)
		, m_text_color(text_color)
		, m_def_text_color(default_text_color)
		, m_no_lines(0)
		, m_max_char(max_number_of_characters)
		, m_max_lines(max_number_of_lines)
		, m_flick_time(0)
		, m_created(true)
	{
		m_object.create(size, position, origin, texture, default_text, character_size, text_position, object_color, default_text_color, outline_thickness, outline_color, 0, text_style, text_shift, font, acitve);

		m_cursor.create(
			{ m_object.getSfText()->getLetterSpacing(), static_cast<float>(character_size) },
			{ m_object.getSfText()->getLocalBounds().left + m_object.getSfText()->getLocalBounds().width + m_object.getSfText()->getLetterSpacing(), m_object.getSfText()->getLocalBounds().top + m_object.getSfText()->getLocalBounds().height * 0.5f },
			MIDDLE_MIDDLE, {}, 0, {}, text_color, {}, 0, {}, 0, {}, {}, {}, false);

		if (m_max_char > Settings::MaxStringSize())
		{
			m_max_char = Settings::MaxStringSize();
			throw_error("InputButton::InputButton(...)", "maximum number of characters is greater than MaxStringSize defined in settings", "WARNING");
		}
	}


	////////////////////////////////


	InputButton::InputButton(
		const sf::Vector2f& size,
		const sf::Vector2f& position,
		int origin,
		const std::string& filename,
		const std::wstring& default_text,
		int text_scope,
		unsigned int max_number_of_characters,
		unsigned int max_number_of_lines,
		unsigned int character_size,
		int text_position,
		const sf::Color& object_color,
		const sf::Color& text_color,
		const sf::Color& default_text_color,
		float outline_thickness,
		const sf::Color& outline_color,
		unsigned int text_style,
		const sf::Vector2f& text_shift,
		int font,
		bool acitve)

		: m_imp_text(L"")
		, m_def_text(default_text)
		, m_text_scope(text_scope)
		, m_possible_to_ent(false)
		, m_text_color(text_color)
		, m_def_text_color(default_text_color)
		, m_no_lines(0)
		, m_max_char(max_number_of_characters)
		, m_max_lines(max_number_of_lines)
		, m_flick_time(0)
		, m_created(true)
	{
		m_object.create(size, position, origin, filename, default_text, character_size, text_position, object_color, default_text_color, outline_thickness, outline_color, 0, text_style, text_shift, font, acitve);

		m_cursor.create(
			{ m_object.getSfText()->getLetterSpacing(), static_cast<float>(character_size) },
			{ m_object.getSfText()->getLocalBounds().left + m_object.getSfText()->getLocalBounds().width + m_object.getSfText()->getLetterSpacing(), m_object.getSfText()->getLocalBounds().top + m_object.getSfText()->getLocalBounds().height * 0.5f },
			MIDDLE_MIDDLE, {}, 0, {}, text_color, {}, 0, {}, 0, {}, {}, {}, false);

		if (m_max_char > Settings::MaxStringSize())
		{
			m_max_char = Settings::MaxStringSize();
			throw_error("InputButton::InputButton(...)", "maximum number of characters is greater than MaxStringSize defined in settings", "WARNING");
		}
	}


	////////////////////////////////


	InputButton::~InputButton()
	{
		
	}



	////////////////////////////////////////////////////////////////



	InputButton::InputButton(InputButton& other)

		: m_imp_text(other.getText())
		, m_def_text(other.getDefautText())
		, m_text_scope(other.getTextScope())
		, m_possible_to_ent(false)
		, m_text_color(other.getTextColor())
		, m_def_text_color(other.getDefaultTextColor())
		, m_no_lines(other.getLineNum())
		, m_max_char(other.getMaxCharacterNum())
		, m_max_lines(other.getMaxLineNum())
		, m_flick_time(0)
		, m_created(true)
	{
		m_object = (*other.getObject());

		if (m_max_char > Settings::MaxStringSize())
		{
			m_max_char = Settings::MaxStringSize();
			throw_error("InputButton::InputButton(...)", "maximum number of characters is greater than MaxStringSize defined in settings", "WARNING");
		}
	}


	////////////////////////////////


	InputButton& InputButton::operator= (InputButton& other)
	{
		m_object = (*other.getObject());

		m_text_scope = other.getTextScope();
		m_imp_text = other.getText();
		m_def_text = other.getDefautText();
		m_text_color = other.getTextColor();
		m_def_text_color = other.getDefaultTextColor();

		m_possible_to_ent = false;
		m_no_lines = other.getLineNum();
		m_max_char = other.getMaxCharacterNum();
		m_max_lines = other.getMaxLineNum();

		if (m_max_char > Settings::MaxStringSize())
		{
			m_max_char = Settings::MaxStringSize();
			throw_error("InputButton::operator=", "maximum number of characters is greater than MaxStringSize defined in settings", "WARNING");
		}

		m_flick_time = 0.f;
		m_created = true;

		return *this;
	}



	////////////////////////////////////////////////////////////////



	void InputButton::create(
		const sf::Vector2f& size,
		const sf::Vector2f& position,
		int origin,
		const sf::Texture* texture,
		const std::wstring& default_text,
		int text_scope,
		unsigned int max_number_of_characters,
		unsigned int max_number_of_lines,
		unsigned int character_size,
		int text_position,
		const sf::Color& object_color,
		const sf::Color& text_color,
		const sf::Color& default_text_color,
		float outline_thickness,
		const sf::Color& outline_color,
		unsigned int text_style,
		const sf::Vector2f& text_shift,
		int font,
		bool acitve)
	{
		m_object.create(size, position, origin, texture, default_text, character_size, text_position, object_color, default_text_color, outline_thickness, outline_color, 0, text_style, text_shift, font, acitve);

		m_cursor.create(
			{ m_object.getSfText()->getLetterSpacing(), static_cast<float>(character_size) },
			{ m_object.getSfText()->getLocalBounds().left + m_object.getSfText()->getLocalBounds().width + m_object.getSfText()->getLetterSpacing(), m_object.getSfText()->getLocalBounds().top + m_object.getSfText()->getLocalBounds().height * 0.5f },
			MIDDLE_MIDDLE, {}, 0, {}, text_color, {}, 0, {}, 0, {}, {}, {}, false);

		m_text_scope = text_scope;
		m_def_text = default_text;
		m_text_color = text_color;
		m_def_text_color = default_text_color;

		m_max_char = max_number_of_characters;
		m_max_lines = max_number_of_lines;

		if (m_max_char > Settings::MaxStringSize())
		{
			m_max_char = Settings::MaxStringSize();
			throw_error("InputButton::create(...)", "maximum number of characters is greater than MaxStringSize defined in settings", "WARNING");
		}

		m_flick_time = 0.f;
		m_created = true;
	}


	////////////////////////////////


	void InputButton::create(
		const sf::Vector2f& size,
		const sf::Vector2f& position,
		int origin,
		const std::string& filename,
		const std::wstring& default_text,
		int text_scope,
		unsigned int max_number_of_characters,
		unsigned int max_number_of_lines,
		unsigned int character_size,
		int text_position,
		const sf::Color& object_color,
		const sf::Color& text_color,
		const sf::Color& default_text_color,
		float outline_thickness,
		const sf::Color& outline_color,
		unsigned int text_style,
		const sf::Vector2f& text_shift,
		int font,
		bool acitve)
	{
		m_object.create(size, position, origin, filename, default_text, character_size, text_position, object_color, default_text_color, outline_thickness, outline_color, 0, text_style, text_shift, font, acitve);

		m_cursor.create(
			{ m_object.getSfText()->getLetterSpacing(), static_cast<float>(character_size) },
			{ m_object.getSfText()->getLocalBounds().left + m_object.getSfText()->getLocalBounds().width + m_object.getSfText()->getLetterSpacing(), m_object.getSfText()->getLocalBounds().top + m_object.getSfText()->getLocalBounds().height * 0.5f },
			MIDDLE_MIDDLE, {}, 0, {}, text_color, {}, 0, {}, 0, {}, {}, {}, false);

		m_text_scope = text_scope;
		m_def_text = default_text;
		m_text_color = text_color;
		m_def_text_color = default_text_color;

		m_max_char = max_number_of_characters;
		m_max_lines = max_number_of_lines;

		if (m_max_char > Settings::MaxStringSize())
		{
			m_max_char = Settings::MaxStringSize();
			throw_error("InputButton::create(...)", "maximum number of characters is greater than MaxStringSize defined in settings", "WARNING");
		}

		m_flick_time = 0.f;
		m_created = true;
	}





	//-------------------------                                                         -------------------------//
	//+++                                                                                                     +++//
	//==============                           M O D    F U N C T I O N S                          ==============//
	//+++                                                                                                     +++//
	//-------------------------                                                         -------------------------//





	void InputButton::setPosition(const sf::Vector2f& position)
	{
		m_object.setPosition(position);
	}


	void InputButton::setPosition(float x, float y)
	{
		m_object.setPosition(x, y);
	}


	sf::Vector2f InputButton::getPosition() const
	{
		return m_object.getPosition();
	}



	////////////////////////////////////////////////////////////////



	void InputButton::setSize(const sf::Vector2f& size)
	{
		m_object.setSize(size);
	}


	void InputButton::setSize(float size_x, float size_y)
	{
		m_object.setSize(size_x, size_y);
	}


	sf::Vector2f InputButton::getSize() const
	{
		return m_object.getSize();
	}



	////////////////////////////////////////////////////////////////



	void InputButton::move(const sf::Vector2f& offset)
	{
		m_object.move(offset);
	}


	void InputButton::move(float offset_x, float offset_y)
	{
		m_object.move(offset_x, offset_y);
	}



	////////////////////////////////////////////////////////////////



	void InputButton::setText(const std::wstring& text)
	{
		m_imp_text = text;
		m_object.setText(text);
	}


	std::wstring InputButton::getText() const
	{
		return m_imp_text;
	}



	////////////////////////////////////////////////////////////////



	void InputButton::setDefautText(const std::wstring& default_text)
	{
		m_def_text = default_text;

		if (m_imp_text.empty())
			m_object.setText(m_def_text);
	}


	std::wstring InputButton::getDefautText() const
	{
		return m_def_text;
	}



	////////////////////////////////////////////////////////////////



	void InputButton::setTextScope(int text_scope)
	{
		m_text_scope = text_scope;
	}


	int InputButton::getTextScope() const
	{
		return m_text_scope;
	}



	////////////////////////////////////////////////////////////////



	void InputButton::setOrigin(int origin)
	{
		///changes origin of the KEngine Rectangle
		/**available origins: <br>
		  * RIGHT_TOP     = top right corner <br>
		  * MIDDLE_TOP    = top <br>
		  * LEFT_TOP      = top left corner <br>
		  * RIGHT_MIDDLE  = right side <br>
		  * MIDDLE_MIDDLE = center <br>
		  * LEFT_MIDDLE   = left side <br>
		  * RIGHT_BOTTOM  = bottom right corner <br>
		  * MIDDLE_BOTTOM = bottom <br>
		  * LEFT_BOTTOM   = bottom left corner*/

		m_object.setOrigin(origin);
	}


	int InputButton::getOrigin() const
	{
		///returns origin of the KEngine Rectangle
		/**available origins: <br>
		  * RIGHT_TOP     = top right corner <br>
		  * MIDDLE_TOP    = top <br>
		  * LEFT_TOP      = top left corner <br>
		  * RIGHT_MIDDLE  = right side <br>
		  * MIDDLE_MIDDLE = center <br>
		  * LEFT_MIDDLE   = left side <br>
		  * RIGHT_BOTTOM  = bottom right corner <br>
		  * MIDDLE_BOTTOM = bottom <br>
		  * LEFT_BOTTOM   = bottom left corner*/

		return m_object.getOrigin();
	}



	////////////////////////////////////////////////////////////////



	void InputButton::setRotation(float angle)
	{
		// does nothing, not available here
	}


	void InputButton::rotate(float angle)
	{
		// does nothing, not available here
	}


	float InputButton::getRotation() const
	{
		// does nothing, not available here

		return 0.f;
	}



	////////////////////////////////////////////////////////////////



	void InputButton::setPositionByCenter(const sf::Vector2f& postion)
	{
		m_object.setPositionByCenter(postion);
	}


	sf::Vector2f InputButton::getShapeCenter() const
	{
		return m_object.getShapeCenter();
	}



	////////////////////////////////////////////////////////////////



	void InputButton::setScale(const sf::Vector2f& factors)
	{
		m_object.setScale(factors);
	}


	void InputButton::setScale(float factor_x, float factor_y)
	{
		m_object.setScale(factor_x, factor_y);
	}


	void InputButton::scale(const sf::Vector2f& factors)
	{
		m_object.scale(factors);
	}


	sf::Vector2f InputButton::getScale() const
	{
		return m_object.getScale();
	}



	////////////////////////////////////////////////////////////////



	void InputButton::setTexture(const sf::Texture* texture)
	{
		m_object.setTexture(texture);
	}


	void InputButton::setTexture(const std::string& texture_path)
	{
		m_object.setTexture(texture_path);
	}


	const sf::Texture* InputButton::getTexture() const
	{
		return m_object.getTexture();
	}



	////////////////////////////////////////////////////////////////



	void InputButton::setFillColor(const sf::Color& color)
	{
		m_object.setFillColor(color);
	}


	const sf::Color& InputButton::getFillColor() const
	{
		return m_object.getFillColor();
	}



	////////////////////////////////////////////////////////////////



	void InputButton::setTextColor(const sf::Color& text_color)
	{
		m_text_color = text_color;
	}


	const sf::Color& InputButton::getTextColor() const
	{
		return m_text_color;
	}



	////////////////////////////////////////////////////////////////



	void InputButton::setDefaultTextColor(const sf::Color& text_color)
	{
		m_def_text_color = text_color;
	}


	const sf::Color& InputButton::getDefaultTextColor() const
	{
		return m_def_text_color;
	}



	////////////////////////////////////////////////////////////////



	void InputButton::setOutlineColor(const sf::Color& outline_color)
	{
		m_object.setOutlineColor(outline_color);
	}


	const sf::Color& InputButton::getOutlineColor() const
	{
		return m_object.getOutlineColor();
	}



	////////////////////////////////////////////////////////////////



	void InputButton::setOutlineThickness(float outline_thickness)
	{
		m_object.setOutlineThickness(outline_thickness);
	}


	float InputButton::getOutlineThickness() const
	{
		return m_object.getOutlineThickness();
	}



	////////////////////////////////////////////////////////////////



	void InputButton::setTextPosition(int position, const sf::Vector2f& text_shift)
	{
		///sets KEngine Rectangle's text position and text shift
		/**available origins: <br>
		  * RIGHT_TOP     = top right corner <br>
		  * MIDDLE_TOP    = top <br>
		  * LEFT_TOP      = top left corner <br>
		  * RIGHT_MIDDLE  = right side <br>
		  * MIDDLE_MIDDLE = center <br>
		  * LEFT_MIDDLE   = left side <br>
		  * RIGHT_BOTTOM  = bottom right corner <br>
		  * MIDDLE_BOTTOM = bottom <br>
		  * LEFT_BOTTOM   = bottom left corner*/

		m_object.setTextPosition(position, text_shift);
	}


	int InputButton::getTextPosition() const
	{
		///returns KEngine Rectangle's text position
		/**available origins: <br>
		  * RIGHT_TOP     = top right corner <br>
		  * MIDDLE_TOP    = top <br>
		  * LEFT_TOP      = top left corner <br>
		  * RIGHT_MIDDLE  = right side <br>
		  * MIDDLE_MIDDLE = center <br>
		  * LEFT_MIDDLE   = left side <br>
		  * RIGHT_BOTTOM  = bottom right corner <br>
		  * MIDDLE_BOTTOM = bottom <br>
		  * LEFT_BOTTOM   = bottom left corner*/

		return m_object.getTextPosition();
	}
	


	////////////////////////////////////////////////////////////////



	sf::Vector2f InputButton::getTextShift() const
	{
		return m_object.getTextShift();
	}

	void InputButton::setTextStyle(int style)
	{
		m_object.setTextStyle(style);
	}


	unsigned int InputButton::getTextStyle() const
	{
		return m_object.getTextStyle();
	}



	////////////////////////////////////////////////////////////////



	void InputButton::setFont(int font)
	{
		///sets KEngine Rectangle's font
		/**  available fonts <br>
		  *  airal <br>
		  *  airal unicode <br>
		  *  calimbri <br>
		  *  camic sans <br>
		  *  courier new <br>
		  *  times now roman <br>
		  *  trebuchet MS <br>
		  *  verdana */

		m_object.setFont(font);
	}


	int InputButton::getFont() const
	{
		///returns KEngine Rectangle's font
		/**  available fonts <br>
		  *  airal <br>
		  *  airal unicode <br>
		  *  calimbri <br>
		  *  camic sans <br>
		  *  courier new <br>
		  *  times now roman <br>
		  *  trebuchet MS <br>
		  *  verdana */

		return m_object.getFont();
	}



	////////////////////////////////////////////////////////////////



	void InputButton::setCharacterSize(unsigned int char_size)
	{
		m_object.setCharacterSize(char_size);
	}


	unsigned int InputButton::getCharacterSize() const
	{
		return m_object.getCharacterSize();
	}



	////////////////////////////////////////////////////////////////



	Button* InputButton::getObject()
	{
		return &m_object;
	}


	Rectangle* InputButton::getCursor()
	{
		return &m_cursor;
	}





	//-------------------------                                                         -------------------------//
	//+++                                                                                                     +++//
	//==============          R E N D E R   A N D   B E H A V I O U R   F U N C T I O N S          ==============//
	//+++                                                                                                     +++//
	//-------------------------                                                         -------------------------//





	bool InputButton::isInvaded(const sf::Vector2f& mousePosition) const
	{
		return m_object.isInvaded(mousePosition);
	}



	////////////////////////////////////////////////////////////////



	bool InputButton::isClicked(sf::Mouse::Button button, const sf::Vector2f& mousePosition, sf::Event& event) const
	{
		return m_object.isClicked(button, mousePosition, event);
	}



	////////////////////////////////////////////////////////////////



	bool InputButton::isActive() const
	{
		return m_object.isActive();
	}


	void InputButton::setActiveStatus(bool status)
	{
		this->m_object.setActiveStatus(status);
	}



	////////////////////////////////////////////////////////////////



	void InputButton::setEPS(bool status)
	{
		m_possible_to_ent = status;
	}


	bool InputButton::getEPS() const
	{
		return m_possible_to_ent;
	}



	////////////////////////////////////////////////////////////////



	size_t InputButton::getCharNum()
	{
		return m_imp_text.size();
	}


	unsigned int InputButton::getLineNum()
	{
		return m_no_lines;
	}



	////////////////////////////////////////////////////////////////



	void InputButton::setMaxCharacterNum(unsigned int max_char_num)
	{
		m_max_char = max_char_num;

		if (m_max_char > Settings::MaxStringSize())
		{
			m_max_char = Settings::MaxStringSize();
			throw_error("InputButton::setMaxCharacterNum(...)", "maximum number of characters is greater than MaxStringSize defined in settings", "WARNING");
		}
	}


	unsigned int InputButton::getMaxCharacterNum() const
	{
		return m_max_char;
	}



	////////////////////////////////////////////////////////////////



	void InputButton::setMaxLineNum(unsigned int max_line_num)
	{
		m_max_lines = max_line_num;
	}


	unsigned int InputButton::getMaxLineNum() const
	{
		return m_max_lines;
	}



	////////////////////////////////////////////////////////////////



	float InputButton::update(const sf::Vector2f& mousePosition, sf::Event& event, sf::Mouse::Button button, sf::View* view)
	{
		// Let's just say this works - I'm to tired to repair any bugs

		float retv_buffer = 0.f; // return value

		if (!m_object.isActive())
			return 0.f;

		if (!this->isInvaded(mousePosition) && event.type == sf::Event::MouseButtonPressed && event.key.code == button)
		{
			m_possible_to_ent = false;
			m_cursor.setActiveStatus(false);
			m_cursor_flick_clock.restart();

			//m_object.setText(m_def_text);
			//m_object.setTextColor(m_def_text_color);
		}
		else if (this->isClicked(button, mousePosition, event))
		{
			m_possible_to_ent = true;

			if (m_max_lines == 1)
				m_cursor.setActiveStatus(true);
		}


		if (m_possible_to_ent)
		{
			if (event.type == sf::Event::TextEntered)
			{
				m_cursor_flick_clock.restart();

				if (m_max_lines == 1)
					m_cursor.setActiveStatus(true);

				switch (m_text_scope)
				{
				case Everything:
				{
					if (((event.text.unicode > 32) || event.text.unicode == '\b' || event.text.unicode == ' '))
					{
						if (event.text.unicode == '\b')
						{
							if (!m_imp_text.empty())
							{
								if (m_imp_text.back() == L'\n')
									m_no_lines--;

								m_imp_text.pop_back();
							}
						}
						else if (m_imp_text.size() < m_max_char) // TODO: bug fix with last letter in multiple line text
						{
							if (m_object.getSfText()->getLocalBounds().width <= m_object.getSize().x - m_object.getTextShift().x * 2.f - m_object.getSfText()->getCharacterSize() * m_object.getSfText()->getLetterSpacing() * 0.5f) // 0.5 is unverified
							{
								m_imp_text += event.text.unicode;
							}
							else if (m_no_lines + 1 < m_max_lines)
							{
								m_imp_text.insert(m_imp_text.size() - 1, 1, '\n');
								m_no_lines++;
							}
						}
					}
				}
				break;
				case ASCII_Everything:
				{
					if (((event.text.unicode > 32 && event.text.unicode < 128) || event.text.unicode == '\b' || event.text.unicode == ' '))
					{
						if (event.text.unicode == '\b')
						{
							if (!m_imp_text.empty())
							{
								if (m_imp_text.back() == L'\n')
									m_no_lines--;

								m_imp_text.pop_back();
							}
						}
						else if (m_imp_text.size() < m_max_char) // TODO: bug fix with last letter in multiple line text
						{
							if (m_object.getSfText()->getLocalBounds().width <= m_object.getSize().x - m_object.getTextShift().x * 2.f - m_object.getSfText()->getCharacterSize() * m_object.getSfText()->getLetterSpacing() * 0.5f) // 0.5 is unverified
							{
								m_imp_text += event.text.unicode;
							}
							else if (m_no_lines + 1 < m_max_lines)
							{
								m_imp_text.insert(m_imp_text.size() - 1, 1, '\n');
								m_no_lines++;
							}
						}
					}
				}
				break;

				case Letters_PMarks:
				{
					if ((((event.text.unicode > 32 && event.text.unicode < 48) || (event.text.unicode > 57 && event.text.unicode < 128)) || event.text.unicode == '\b' || event.text.unicode == ' '))
					{
						if (event.text.unicode == '\b')
						{
							if (!m_imp_text.empty())
							{
								if (m_imp_text.back() == L'\n')
									m_no_lines--;

								m_imp_text.pop_back();
							}
						}
						else if (m_imp_text.size() < m_max_char) // TODO: bug fix with last letter in multiple line text
						{
							if (m_object.getSfText()->getLocalBounds().width <= m_object.getSize().x - m_object.getTextShift().x * 2.f - m_object.getSfText()->getCharacterSize() * m_object.getSfText()->getLetterSpacing() * 0.5f) // 0.5 is unverified
							{
								m_imp_text += event.text.unicode;
							}
							else if (m_no_lines + 1 < m_max_lines)
							{
								m_imp_text.insert(m_imp_text.size() - 1, 1, '\n');
								m_no_lines++;
							}
						}
					}
				}
				break;

				case Letters:
				{
					if ((((event.text.unicode > 64 && event.text.unicode < 91) || (event.text.unicode > 97 && event.text.unicode < 122)) || event.text.unicode == '\b' || event.text.unicode == ' '))
					{
						if (event.text.unicode == '\b')
						{
							if (!m_imp_text.empty())
							{
								if (m_imp_text.back() == L'\n')
									m_no_lines--;

								m_imp_text.pop_back();
							}
						}
						else if (m_imp_text.size() < m_max_char) // TODO: bug fix with last letter in multiple line text
						{
							if (m_object.getSfText()->getLocalBounds().width <= m_object.getSize().x - m_object.getTextShift().x * 2.f - m_object.getSfText()->getCharacterSize() * m_object.getSfText()->getLetterSpacing() * 0.5f) // 0.5 is unverified
							{
								m_imp_text += event.text.unicode;
							}
							else if (m_no_lines + 1 < m_max_lines)
							{
								m_imp_text.insert(m_imp_text.size() - 1, 1, '\n');
								m_no_lines++;
							}
						}
					}
				}
				break;

				case Numbers:
				{
					if ((((event.text.unicode > 47 && event.text.unicode < 58)) || event.text.unicode == '\b' || event.text.unicode == ' ' || event.text.unicode == '.'))
					{
						if (event.text.unicode == '\b')
						{
							if (!m_imp_text.empty())
							{
								if (m_imp_text.back() == L'\n')
									m_no_lines--;

								m_imp_text.pop_back();
							}
						}
						else if (m_imp_text.size() < m_max_char) // TODO: bug fix with last letter in multiple line text
						{
							if (m_object.getSfText()->getLocalBounds().width <= m_object.getSize().x - m_object.getTextShift().x * 2.f - m_object.getSfText()->getCharacterSize() * m_object.getSfText()->getLetterSpacing() * 0.5f) // 0.5 is unverified
							{
								m_imp_text += event.text.unicode;
							}
							else if (m_no_lines + 1 < m_max_lines)
							{
								m_imp_text.insert(m_imp_text.size() - 1, 1, '\n');
								m_no_lines++;
							}
						}
					}
				}
				break;

				case Math:
				{
					if ((((event.text.unicode > 39 && event.text.unicode < 63)) || event.text.unicode == '\b' || event.text.unicode == ' ' || event.text.unicode == 'e'))
					{
						if (event.text.unicode == '\b')
						{
							if (!m_imp_text.empty())
							{
								if (m_imp_text.back() == L'\n')
									m_no_lines--;

								m_imp_text.pop_back();
							}
						}
						else if (m_imp_text.size() < m_max_char) // TODO: bug fix with last letter in multiple line text
						{
							if (m_object.getSfText()->getLocalBounds().width <= m_object.getSize().x - m_object.getTextShift().x * 2.f - m_object.getSfText()->getCharacterSize() * m_object.getSfText()->getLetterSpacing() * 0.5f) // 0.5 is unverified
							{
								m_imp_text += event.text.unicode;
							}
							else if (m_no_lines + 1 < m_max_lines)
							{
								m_imp_text.insert(m_imp_text.size() - 1, 1, '\n');
								m_no_lines++;
							}
						}
					}
				}
				break;

				default:
				{
					throw_error("InputButton::update(...)", "Given text scope is incorrect", "ERROR");

					if (((event.text.unicode > 32) || event.text.unicode == '\b' || event.text.unicode == ' '))
					{
						if (event.text.unicode == '\b')
						{
							if (!m_imp_text.empty())
							{
								if (m_imp_text.back() == L'\n')
									m_no_lines--;

								m_imp_text.pop_back();
							}
						}
						else if (m_imp_text.size() < m_max_char) // TODO: bug fix with last letter in multiple line text
						{
							if (m_object.getSfText()->getLocalBounds().width <= m_object.getSize().x - m_object.getTextShift().x * 2.f - m_object.getSfText()->getCharacterSize() * m_object.getSfText()->getLetterSpacing() * 0.5f) // 0.5 is unverified
							{
								m_imp_text += event.text.unicode;
							}
							else if (m_no_lines + 1 < m_max_lines)
							{
								m_imp_text.insert(m_imp_text.size() - 1, 1, '\n');
								m_no_lines++;
							}
						}
					}
				}
				}

				retv_buffer = 1.f;
			}


			if (!m_imp_text.empty())
			{
				if (event.text.unicode == 127)
				{
					while (!m_imp_text.empty())
					{
						if (m_imp_text.back() == 127)
						{
							m_imp_text.pop_back();
							continue;
						}

						if (m_imp_text.back() == L'\n')
							m_no_lines--;

						if (m_imp_text.back() == L'\n' || // could not use ascii bcause it doesn't work (idk why)
							m_imp_text.back() == L'.' ||
							m_imp_text.back() == L',' ||
							m_imp_text.back() == L' ' ||
							m_imp_text.back() == L'/' ||
							m_imp_text.back() == L'!' ||
							m_imp_text.back() == L'?' ||
							m_imp_text.back() == L';' ||
							m_imp_text.back() == L':' ||
							m_imp_text.back() == L'-' ||
							m_imp_text.back() == L'=' ||
							m_imp_text.back() == L'_' ||
							m_imp_text.back() == L'+'
							)
						{
							m_imp_text.pop_back();
							break;
						}
						else
						{
							m_imp_text.pop_back();
						}
					}

					retv_buffer = 2.f;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && event.key.code == sf::Keyboard::C)
				{
					sf::Clipboard::setString(m_imp_text);

					retv_buffer = 3.f;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && event.key.code == sf::Keyboard::X)
				{
					sf::Clipboard::setString(m_imp_text);

					while (!m_imp_text.empty())
						m_imp_text.pop_back();

					retv_buffer = 4.f;
				}
			}


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::V)
			{
				m_imp_text += sf::Clipboard::getString().toWideString();

				m_object.setText(m_imp_text); 

				// not optimized, but well, it works (kinda)
				while (!m_imp_text.empty() && (m_imp_text.size() > m_max_char || m_object.getSfText()->getLocalBounds().width > m_object.getSize().x - m_object.getTextShift().x * 2.f))
				{
					m_imp_text.pop_back();
					m_object.setText(m_imp_text);
				}

				m_object.setTextColor(m_text_color);

				retv_buffer = 5.f;
			}

			m_object.setText(m_imp_text);
			m_object.setTextColor(m_text_color);

			
			if (m_imp_text.empty())
				m_cursor.setPosition(m_object.getSfText()->getGlobalBounds().left, m_object.getSfText()->getGlobalBounds().top + m_object.getSfText()->getGlobalBounds().height * 0.5);
			else
				m_cursor.setPosition(m_object.getSfText()->getGlobalBounds().left + m_object.getSfText()->getGlobalBounds().width + m_object.getSfText()->getLetterSpacing() * 3, m_object.getSfText()->getGlobalBounds().top + m_object.getSfText()->getGlobalBounds().height * 0.5);


		}
		else if (m_imp_text.empty())
		{
			m_object.setText(m_def_text);
			m_object.setTextColor(m_def_text_color);
		}

		return retv_buffer;
	}



	////////////////////////////////////////////////////////////////



	void InputButton::updateCursor()
	{
		m_flick_time = m_cursor_flick_clock.getElapsedTime().asMilliseconds();

		if (m_max_lines == 1 && m_possible_to_ent)
		{
			if (m_flick_time > 500.f)
			{
				m_cursor.setActiveStatus(!m_cursor.isActive());
				m_cursor_flick_clock.restart();
			}
		}
	}



	////////////////////////////////////////////////////////////////



	void InputButton::render(sf::RenderWindow* window)
	{
		if (m_object.isActive())
		{
			m_object.render(window);

			if (m_possible_to_ent)
				m_cursor.render(window);
		}
	}



	////////////////////////////////////////////////////////////////



	bool InputButton::created() const
	{
		return m_created;
	}

} // namespace ke