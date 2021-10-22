#include "Bar.hpp"

namespace ke
{





	// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
	// \ \ \ \ \ \ \
	//
	//  P  E  R  C  E  N  T  A  G  E    % 
	//
	// / / / / / / /
	// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =









	//-------------------------                                                         -------------------------//
	//+++                                                                                                     +++//
	//============== C O N S T R U C T O R S ,   D E S T R U C T O R S   A N D   O P E R A T O R S ==============//
	//+++                                                                                                     +++//
	//-------------------------                                                         -------------------------//





	PercentageBar::PercentageBar()
		: m_shift(0.f)
		, m_holded(false)
		, m_catchDiff(0)
	{

	}


	////////////////////////////////


	PercentageBar::PercentageBar(
		const sf::Vector2f& size,
		float button_radius,
		const sf::Vector2f& position,
		int origin,
		const sf::Texture* button_texture,
		const sf::Texture* object_texture,
		const sf::Color& button_color,
		const sf::Color& object_color,
		float button_outline_thickness,
		const sf::Color& button_outline_color,
		float object_outline_thickness,
		const sf::Color& object_outline_color,
		bool active)

		: m_shift(0.f)
		, m_holded(false)
		, m_catchDiff(0)
	{
		m_object.create(size, position, origin, object_texture, L"", 0, MIDDLE_MIDDLE, object_color, sf::Color::Transparent, object_outline_thickness, object_outline_color, sf::Text::Regular, sf::Vector2f(0, 0), Arial, active);
		m_texture_button.create(button_radius, sf::Vector2f(m_object.getShapeCenter().x - (size.x - size.y) / 2, m_object.getShapeCenter().y), MIDDLE_MIDDLE, button_texture, active);
		m_color_button.create(button_radius, sf::Vector2f(m_object.getShapeCenter().x - (size.x - size.y) / 2, m_object.getShapeCenter().y), MIDDLE_MIDDLE, L"", 0, MIDDLE_MIDDLE, button_color, sf::Color::Transparent, button_outline_thickness, button_outline_color, 0.f, sf::Text::Regular, sf::Vector2f(0, 0), Arial, active);
	}



	PercentageBar::PercentageBar(
		const sf::Vector2f& size,
		float button_radius,
		const sf::Vector2f& position,
		int origin,
		const std::string& button_texture_path,
		const std::string& object_texture_path,
		const sf::Color& button_color,
		const sf::Color& object_color,
		float button_outline_thickness,
		const sf::Color& button_outline_color,
		float object_outline_thickness,
		const sf::Color& object_outline_color,
		bool active)

		: m_shift(0.f)
		, m_holded(false)
		, m_catchDiff(0)
	{
		m_object.create(size, position, origin, object_texture_path, L"", 0, MIDDLE_MIDDLE, object_color, sf::Color::Transparent, object_outline_thickness, object_outline_color, sf::Text::Regular, sf::Vector2f(0, 0), Arial, active);
		m_texture_button.create(button_radius, sf::Vector2f(m_object.getShapeCenter().x - (size.x - size.y) / 2, m_object.getShapeCenter().y), MIDDLE_MIDDLE, button_texture_path, active);
		m_color_button.create(button_radius, sf::Vector2f(m_object.getShapeCenter().x - (size.x - size.y) / 2, m_object.getShapeCenter().y), MIDDLE_MIDDLE, L"", 0, MIDDLE_MIDDLE, button_color, sf::Color::Transparent, button_outline_thickness, button_outline_color, 0.f, sf::Text::Regular, sf::Vector2f(0, 0), Arial, active);
	}


	////////////////////////////////


	PercentageBar::~PercentageBar()
	{

	}



	////////////////////////////////////////////////////////////////



	PercentageBar::PercentageBar(PercentageBar& other)
		: m_shift(0.f)
		, m_holded(false)
		, m_catchDiff(0)
	{
		m_texture_button = (*other.getTextureButton());
		m_color_button = (*other.getColorButton());
		m_object = (*other.getObject());
	}


	////////////////////////////////


	PercentageBar& PercentageBar::operator= (PercentageBar& other)
	{
		m_texture_button = (*other.getTextureButton()); 
		m_color_button = (*other.getColorButton()); 
		m_object = (*other.getObject()); 

		m_shift = other.getShift();
		m_holded = false;
		m_catchDiff = 0.f;

		return *this;
	}



	////////////////////////////////////////////////////////////////



	void PercentageBar::create(
		const sf::Vector2f& size,
		float button_radius,
		const sf::Vector2f& position,
		int origin,
		const sf::Texture* button_texture,
		const sf::Texture* object_texture,
		const sf::Color& button_color,
		const sf::Color& object_color,
		float button_outline_thickness,
		const sf::Color& button_outline_color,
		float object_outline_thickness,
		const sf::Color& object_outline_color,
		bool active)
	{
		m_object.create(size, position, origin, object_texture, L"", 0, MIDDLE_MIDDLE, object_color, sf::Color::Transparent, object_outline_thickness, object_outline_color, sf::Text::Regular, sf::Vector2f(0, 0), Arial, active);
		m_texture_button.create(button_radius, sf::Vector2f(m_object.getShapeCenter().x - (size.x - size.y) / 2, m_object.getShapeCenter().y), MIDDLE_MIDDLE, button_texture, active);
		m_color_button.create(button_radius, sf::Vector2f(m_object.getShapeCenter().x - (size.x - size.y) / 2, m_object.getShapeCenter().y), MIDDLE_MIDDLE, L"", 0, MIDDLE_MIDDLE, button_color, sf::Color::Transparent, button_outline_thickness, button_outline_color, 0.f, sf::Text::Regular, sf::Vector2f(0, 0), Arial, active);

		m_shift = 0.f;
		m_holded = false;
		m_catchDiff = 0.f;
	}



	void PercentageBar::create(
		const sf::Vector2f& size,
		float button_radius,
		const sf::Vector2f& position,
		int origin,
		const std::string& button_texture_path,
		const std::string& object_texture_path,
		const sf::Color& button_color,
		const sf::Color& object_color,
		float button_outline_thickness,
		const sf::Color& button_outline_color,
		float object_outline_thickness,
		const sf::Color& object_outline_color,
		bool active)
	{
		m_object.create(size, position, origin, object_texture_path, L"", 0, MIDDLE_MIDDLE, object_color, sf::Color::Transparent, object_outline_thickness, object_outline_color, sf::Text::Regular, sf::Vector2f(0, 0), Arial, active);
		m_texture_button.create(button_radius, sf::Vector2f(m_object.getShapeCenter().x - (size.x - size.y) / 2, m_object.getShapeCenter().y), MIDDLE_MIDDLE, button_texture_path, active);
		m_color_button.create(button_radius, sf::Vector2f(m_object.getShapeCenter().x - (size.x - size.y) / 2, m_object.getShapeCenter().y), MIDDLE_MIDDLE, L"", 0, MIDDLE_MIDDLE, button_color, sf::Color::Transparent, button_outline_thickness, button_outline_color, 0.f, sf::Text::Regular, sf::Vector2f(0, 0), Arial, active);

		m_shift = 0.f;
		m_holded = false;
		m_catchDiff = 0.f;
	}





	//-------------------------                                                         -------------------------//
	//+++                                                                                                     +++//
	//==============                           M O D    F U N C T I O N S                          ==============//
	//+++                                                                                                     +++//
	//-------------------------                                                         -------------------------//





	void PercentageBar::setPosition(const sf::Vector2f& position)
	{
		m_object.setPosition(position);

		m_texture_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x - (m_object.getButton()->getSize().x * m_object.getScale().x) / 2 + m_shift * m_object.getScale().x, getShapeCenter().y));
		m_color_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x - (m_object.getButton()->getSize().x * m_object.getScale().x) / 2 + m_shift * m_object.getScale().x, getShapeCenter().y));
	}


	void PercentageBar::setPosition(float x, float y)
	{
		m_object.setPosition(x, y);

		m_texture_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x - (m_object.getButton()->getSize().x * m_object.getScale().x) / 2 + m_shift * m_object.getScale().x, getShapeCenter().y));
		m_color_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x - (m_object.getButton()->getSize().x * m_object.getScale().x) / 2 + m_shift * m_object.getScale().x, getShapeCenter().y));
	}


	sf::Vector2f PercentageBar::getPosition() const
	{
		return m_object.getPosition();
	}



	////////////////////////////////////////////////////////////////



	void PercentageBar::setSize(const sf::Vector2f& size)
	{
		m_shift = m_shift * (size.x - size.y) / (m_object.getButton()->getSize().x * m_object.getScale().x);

		m_object.setSize(size);

		m_texture_button.setPosition(m_object.getShapeCenter().x - (m_object.getButton()->getSize().x * m_object.getScale().x) / 2 + m_shift * m_object.getScale().x, m_object.getShapeCenter().y);
		m_color_button.setPosition(m_object.getShapeCenter().x - (m_object.getButton()->getSize().x * m_object.getScale().x) / 2 + m_shift * m_object.getScale().x, m_object.getShapeCenter().y);
	}


	void PercentageBar::setSize(float size_x, float size_y)
	{
		m_shift = m_shift * (size_x - size_y) / (m_object.getButton()->getSize().x * m_object.getScale().x);

		m_object.setSize(size_x, size_y);

		m_texture_button.setPosition(m_object.getShapeCenter().x - (m_object.getButton()->getSize().x * m_object.getScale().x) / 2 + m_shift * m_object.getScale().x, m_object.getShapeCenter().y);
		m_color_button.setPosition(m_object.getShapeCenter().x - (m_object.getButton()->getSize().x * m_object.getScale().x) / 2 + m_shift * m_object.getScale().x, m_object.getShapeCenter().y);
	}


	sf::Vector2f PercentageBar::getSize() const
	{
		return m_object.getSize();
	}


	////////////////////////////////


	void PercentageBar::setButtonRadius(float radius)
	{
		m_texture_button.setRadius(radius);
		m_color_button.setRadius(radius);

		m_texture_button.setPosition(m_object.getShapeCenter().x - (m_object.getButton()->getSize().x * m_object.getScale().x) / 2 + m_shift * m_object.getScale().x, m_object.getShapeCenter().y);
		m_color_button.setPosition(m_object.getShapeCenter().x - (m_object.getButton()->getSize().x * m_object.getScale().x) / 2 + m_shift * m_object.getScale().x, m_object.getShapeCenter().y);
	}


	float PercentageBar::getButtonRadius() const
	{
		return m_color_button.getRadius();
	}



	////////////////////////////////////////////////////////////////



	void PercentageBar::move(const sf::Vector2f& offset)
	{
		m_object.move(offset);
		m_texture_button.move(offset);
		m_color_button.move(offset);
	}


	void PercentageBar::move(float offset_x, float offset_y)
	{
		m_object.move(offset_x, offset_y);
		m_texture_button.move(offset_x, offset_y);
		m_color_button.move(offset_x, offset_y);
	}



	////////////////////////////////////////////////////////////////



	void PercentageBar::setText(const std::wstring& text)
	{
		// does nothing, not available in this object
	}


	std::wstring PercentageBar::getText() const
	{
		// does nothing, not available in this object

		return std::wstring();
	}



	////////////////////////////////////////////////////////////////



	void PercentageBar::setOrigin(int origin)
	{
		m_object.setOrigin(origin);

		m_texture_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x - (m_object.getButton()->getSize().x * m_object.getScale().x) / 2 + m_shift * m_object.getScale().x, getShapeCenter().y));
		m_color_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x - (m_object.getButton()->getSize().x * m_object.getScale().x) / 2 + m_shift * m_object.getScale().x, getShapeCenter().y));
	}


	int PercentageBar::getOrigin() const
	{
		return m_object.getOrigin();
	}



	////////////////////////////////////////////////////////////////



	void PercentageBar::setRotation(float angle)
	{
		// does nothing, not available in this object
	}


	void PercentageBar::rotate(float angle)
	{
		// does nothing, not available in this object
	}


	float PercentageBar::getRotation() const
	{
		// does nothing, not available in this object

		return 0.0f;
	}



	////////////////////////////////////////////////////////////////



	void PercentageBar::setScale(const sf::Vector2f& factors)
	{
		m_object.setScale(factors);

		this->setPosition(m_object.getPosition());
	}


	void PercentageBar::setScale(float factor_x, float factor_y)
	{
		m_object.setScale(factor_x, factor_y);

		this->setPosition(m_object.getPosition());
	}


	////////////////////////////////


	void PercentageBar::setButtonScale(const sf::Vector2f& factors)
	{
		m_color_button.setScale(factors);
		m_texture_button.setScale(factors);
	}


	void PercentageBar::setButtonScale(float factor_x, float factor_y)
	{
		m_color_button.setScale(factor_x, factor_y);
		m_texture_button.setScale(factor_x, factor_y);
	}


	////////////////////////////////


	void PercentageBar::scale(const sf::Vector2f& factors)
	{
		m_object.scale(factors);

		this->setPosition(m_object.getPosition());
	}


	void PercentageBar::scaleButton(const sf::Vector2f& factors)
	{
		m_color_button.scale(factors);
		m_texture_button.scale(factors);
	}


	////////////////////////////////


	sf::Vector2f PercentageBar::getScale() const
	{
		return m_object.getScale();
	}


	sf::Vector2f PercentageBar::getButtonScale() const
	{
		return m_texture_button.getScale();
	}



	////////////////////////////////////////////////////////////////



	void PercentageBar::setPositionByCenter(const sf::Vector2f& position)
	{
		//m_texture_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x - (m_object.getButton()->getSize().x * m_object.getScale().x) / 2 + m_shift * m_object.getScale().x, getShapeCenter().y));
		//m_color_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x - (m_object.getButton()->getSize().x * m_object.getScale().x) / 2 + m_shift * m_object.getScale().x, getShapeCenter().y));
		m_object.setPositionByCenter(position);

		m_texture_button.setPosition(sf::Vector2f(position.x - (m_object.getButton()->getSize().x * m_object.getScale().x) / 2 + m_shift * m_object.getScale().x, position.y));
		m_color_button.setPosition(sf::Vector2f(position.x - (m_object.getButton()->getSize().x * m_object.getScale().x) / 2 + m_shift * m_object.getScale().x, position.y));
	}


	sf::Vector2f PercentageBar::getShapeCenter() const
	{
		return m_object.getShapeCenter();
	}


	sf::Vector2f PercentageBar::getButtonCenter() const
	{
		return m_texture_button.getShapeCenter();
	}



	////////////////////////////////////////////////////////////////



	void PercentageBar::setTexture(const sf::Texture* texture)
	{
		m_object.setTexture(texture);
	}


	void PercentageBar::setButtonTexture(const sf::Texture* texture)
	{
		m_texture_button.setTexture(texture);
	}


	////////////////////////////////


	void PercentageBar::setTexture(const std::string& filename)
	{
		m_object.setTexture(filename);
	}


	void PercentageBar::setButtonTexture(const std::string& filename)
	{
		m_texture_button.setTexture(filename);
	}


	////////////////////////////////


	const sf::Texture* PercentageBar::getTexture() const
	{
		return m_object.getTexture();
	}


	const sf::Texture* PercentageBar::getButtonTexture() const
	{
		return m_texture_button.getTexture();
	}



	////////////////////////////////////////////////////////////////



	void PercentageBar::setFillColor(const sf::Color& color)
	{
		m_object.setFillColor(color);
	}


	void PercentageBar::setButtonColor(const sf::Color& color)
	{
		m_color_button.setFillColor(color);
	}


	////////////////////////////////


	const sf::Color& PercentageBar::getFillColor() const
	{
		return m_object.getFillColor();
	}


	const sf::Color& PercentageBar::getButtonColor() const
	{
		return m_color_button.getFillColor();
	}



	////////////////////////////////////////////////////////////////



	void PercentageBar::setTextColor(const sf::Color& text_color)
	{
		/// does nothing - not text in this object
	}


	const sf::Color& PercentageBar::getTextColor() const
	{
		/// does nothing - not text in this object

		return sf::Color::Transparent;
	}



	////////////////////////////////////////////////////////////////



	void PercentageBar::setOutlineColor(const sf::Color& outline_color)
	{
		m_object.setOutlineColor(outline_color);
	}


	void PercentageBar::setOutlineButtonColor(const sf::Color& outline_color)
	{
		m_color_button.setOutlineColor(outline_color);
	}


	////////////////////////////////


	const sf::Color& PercentageBar::getOutlineColor() const
	{
		return m_object.getOutlineColor();
	}


	const sf::Color& PercentageBar::getOutlineButtonColor() const
	{
		return m_color_button.getOutlineColor();
	}



	////////////////////////////////////////////////////////////////



	void PercentageBar::setOutlineThickness(float outline_thickness)
	{
		m_object.setOutlineThickness(outline_thickness);
	}


	void PercentageBar::setOutlineButtonThickness(float outline_thickness)
	{
		m_color_button.setOutlineThickness(outline_thickness);
	}


	////////////////////////////////


	float PercentageBar::getOutlineThickness() const
	{
		return m_object.getOutlineThickness();
	}


	float PercentageBar::getOutlineButtonThickness() const
	{
		return m_color_button.getOutlineThickness();
	}





	//-------------------------                                                         -------------------------//
	//+++                                                                                                     +++//
	//==============          R E N D E R   A N D   B E H A V I O U R   F U N C T I O N S          ==============//
	//+++                                                                                                     +++//
	//-------------------------                                                         -------------------------//





	bool PercentageBar::isInvaded(const sf::Vector2f& mousePosition) const
	{
		return m_object.isInvaded(mousePosition);
	}


	bool PercentageBar::isButtonInvaded(const sf::Vector2f& mousePosition) const
	{
		return m_texture_button.isInvaded(mousePosition);
	}


	////////////////////////////////


	bool PercentageBar::isClicked(sf::Mouse::Button button, const sf::Vector2f& mousePosition, sf::Event& event) const
	{
		return m_object.isClicked(button, mousePosition, event);
	}


	bool PercentageBar::isButtonClicked(sf::Mouse::Button button, const sf::Vector2f& mousePosition, sf::Event& event) const
	{
		return m_texture_button.isClicked(button, mousePosition, event);
	}



	////////////////////////////////////////////////////////////////



	bool PercentageBar::isActive() const
	{
		return m_object.isActive();
	}


	void PercentageBar::setActiveStatus(bool status)
	{
		m_color_button.setActiveStatus(status);
		m_texture_button.setActiveStatus(status);
		m_object.setActiveStatus(status);
	}



	////////////////////////////////////////////////////////////////



	Circle* PercentageBar::getColorButton()
	{
		return &m_color_button;
	}


	Circle* PercentageBar::getTextureButton()
	{
		return &m_texture_button;
	}


	CurvedButton* PercentageBar::getObject()
	{
		return &m_object;
	}



	////////////////////////////////////////////////////////////////



	void PercentageBar::setPercent(float percent)
	{
		m_texture_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x - (m_object.getButton()->getSize().x * m_object.getScale().x) / 2 + m_object.getButton()->getSize().x * m_object.getScale().x * (percent / 100), m_object.getShapeCenter().y));
		m_color_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x - (m_object.getButton()->getSize().x * m_object.getScale().x) / 2 + m_object.getButton()->getSize().x * m_object.getScale().x * (percent / 100), m_object.getShapeCenter().y));

		m_shift = m_object.getButton()->getSize().x * m_object.getScale().x * (percent / 100);
	}


	float PercentageBar::getPercent()
	{
		return m_shift * 100 / m_object.getButton()->getSize().x;
	}



	////////////////////////////////////////////////////////////////

	

	void PercentageBar::setHolded(bool holded)
	{
		m_holded = holded;
	}


	bool PercentageBar::isHolded() const
	{
		return m_holded;
	}



	////////////////////////////////////////////////////////////////



	float PercentageBar::getShift() const
	{
		return m_shift;
	}



	////////////////////////////////////////////////////////////////



	void PercentageBar::reverseRenderOrder()
	{
		m_object.getButton()->reverseRenderOrder();
	}


	void PercentageBar::setRenderOrder(bool order)
	{
		m_object.getButton()->setRenderOrder(order);
	}


	bool PercentageBar::getRenderOrder()
	{
		return m_object.getButton()->getRenderOrder();
	}



	////////////////////////////////////////////////////////////////
	


	float PercentageBar::update(const sf::Vector2f& mousePosition, sf::Event& event, sf::Mouse::Button button, sf::View* view)
	{
		if (!m_object.isActive())
			return 0.f;

		if (this->isButtonClicked(button, mousePosition, event))
		{
			m_holded = true;
			m_catchDiff = mousePosition.x - m_texture_button.getShapeCenter().x;
		}
		else if (!this->isButtonClicked(button, mousePosition, event) && this->isClicked(button, mousePosition, event))
		{
			m_holded = true;
			m_catchDiff = 0.f;
		}
		else if (!sf::Mouse::isButtonPressed(button))
			m_holded = false;

		if (m_holded)
		{
			m_color_button.setPosition(mousePosition.x - m_catchDiff, m_object.getShapeCenter().y);
			m_texture_button.setPosition(mousePosition.x - m_catchDiff, m_object.getShapeCenter().y);

			float centbuff = m_texture_button.getShapeCenter().x;

			varGuard(centbuff, m_object.getShapeCenter().x - m_object.getButton()->getSize().x * m_object.getScale().x / 2, m_object.getShapeCenter().x + m_object.getButton()->getSize().x * m_object.getScale().x / 2);

			m_shift = centbuff - (m_object.getShapeCenter().x - m_object.getButton()->getSize().x * m_object.getScale().x / 2);

			if (m_texture_button.getPosition().x < m_object.getShapeCenter().x - m_object.getButton()->getSize().x * m_object.getScale().x / 2)
			{
				m_texture_button.setPosition(m_object.getShapeCenter().x - m_object.getButton()->getSize().x * m_object.getScale().x / 2, m_object.getShapeCenter().y);
				m_color_button.setPosition(m_object.getShapeCenter().x - m_object.getButton()->getSize().x * m_object.getScale().x / 2, m_object.getShapeCenter().y);
			}
			else if (m_texture_button.getPosition().x > m_object.getShapeCenter().x + m_object.getButton()->getSize().x * m_object.getScale().x / 2)
			{
				m_texture_button.setPosition(m_object.getShapeCenter().x + m_object.getButton()->getSize().x * m_object.getScale().x / 2, m_object.getShapeCenter().y);
				m_color_button.setPosition(m_object.getShapeCenter().x + m_object.getButton()->getSize().x * m_object.getScale().x / 2, m_object.getShapeCenter().y);
			}

			return 1.f;
		}
		else return 0.f;
	}



	////////////////////////////////////////////////////////////////



	void PercentageBar::render(sf::RenderWindow* window)
	{
		m_object.render(window);

		if (m_object.getButton()->getRenderOrder())
		{
			m_color_button.render(window);
			m_texture_button.render(window);
		}
		else
		{
			m_texture_button.render(window);
			m_color_button.render(window);
		}
	}



	////////////////////////////////////////////////////////////////



	bool PercentageBar::created() const
	{
		return m_object.created();
	}















	// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
	// \ \ \ \ \ \ \
	//
	//  P  O  I  N  T    
	//
	// / / / / / / /
	// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =









	//-------------------------                                                         -------------------------//
	//+++                                                                                                     +++//
	//============== C O N S T R U C T O R S ,   D E S T R U C T O R S   A N D   O P E R A T O R S ==============//
	//+++                                                                                                     +++//
	//-------------------------                                                         -------------------------//





	PointBar::PointBar()
		: m_pts(0)
		, m_min_pts(0)
		, m_max_pts(0)
	{

	}


	////////////////////////////////


	PointBar::PointBar(
		const sf::Vector2f& size,
		const sf::Vector2f& position,
		const sf::Texture* texture,
		float points,
		float min_points,
		float max_points,
		int origin,
		const sf::Color& object_color,
		const sf::Color& bar_color,
		float object_outline_thickness,
		float bar_outline_thickness,
		const sf::Color& object_outline_color,
		const sf::Color& bar_outline_color,
		bool active)

		: m_pts(points)
		, m_min_pts(min_points)
		, m_max_pts(max_points)
	{
		m_object.create(size, position, origin, texture, L"", 0, MIDDLE_MIDDLE, object_color, sf::Color::Transparent, object_outline_thickness, object_outline_color, 0.f, sf::Text::Regular, sf::Vector2f(0, 0), Arial, active);
		m_bar.create(sf::Vector2f(size.x * ((points - min_points) / (max_points - min_points)), size.y), sf::Vector2f(m_object.getShapeCenter().x - m_object.getSize().x / 2, m_object.getShapeCenter().y), LEFT_MIDDLE, L"", 0, MIDDLE_MIDDLE, bar_color, sf::Color::Transparent, bar_outline_thickness, bar_outline_color, 0.f, sf::Text::Regular, sf::Vector2f(0, 0), Arial, active);
	}



	PointBar::PointBar(
		const sf::Vector2f& size,
		const sf::Vector2f& position,
		const std::string& texture_path,
		float points,
		float min_points,
		float max_points,
		int origin,
		const sf::Color& object_color,
		const sf::Color& bar_color,
		float object_outline_thickness,
		float bar_outline_thickness,
		const sf::Color& object_outline_color,
		const sf::Color& bar_outline_color,
		bool active)

		: m_pts(points)
		, m_min_pts(min_points)
		, m_max_pts(max_points)
	{
		m_object.create(size, position, origin, texture_path, L"", 0, MIDDLE_MIDDLE, object_color, sf::Color::Transparent, object_outline_thickness, object_outline_color, 0, sf::Text::Regular, sf::Vector2f(0, 0), Arial, active);
		m_bar.create(sf::Vector2f(size.x * ((points - min_points) / (max_points - min_points)), size.y), sf::Vector2f(m_object.getShapeCenter().x - m_object.getSize().x / 2, m_object.getShapeCenter().y), LEFT_MIDDLE, L"", 0, MIDDLE_MIDDLE, bar_color, sf::Color::Transparent, bar_outline_thickness, bar_outline_color, 0.f, sf::Text::Regular, sf::Vector2f(0, 0), Arial, active);
	}


	////////////////////////////////


	PointBar::~PointBar()
	{

	}



	////////////////////////////////



	PointBar::PointBar(PointBar& other)
		: m_pts(other.getPointCount())
		, m_min_pts(other.getMinPointCount())
		, m_max_pts(other.getMaxPointCount())
	{
		m_bar = (*other.getBar());
		m_object = (*other.getObject());
	}



	PointBar& PointBar::operator= (PointBar& other)
	{
		m_bar = (*other.getBar());
		m_object = (*other.getObject());

		m_pts = other.getPointCount();
		m_max_pts = other.getMaxPointCount();
		m_min_pts = other.getMinPointCount();

		return *this;
	}



	////////////////////////////////



	void PointBar::create(
		const sf::Vector2f& size,
		const sf::Vector2f& position,
		const sf::Texture* texture,
		float points,
		float min_points,
		float max_points,
		int origin,
		const sf::Color& object_color,
		const sf::Color& bar_color,
		float object_outline_thickness,
		float bar_outline_thickness,
		const sf::Color& object_outline_color,
		const sf::Color& bar_outline_color,
		bool active)
	{
		m_object.create(size, position, origin, texture, L"", 0, MIDDLE_MIDDLE, object_color, sf::Color::Transparent, object_outline_thickness, object_outline_color, 0.f, sf::Text::Regular, sf::Vector2f(0, 0), Arial, active);
		m_bar.create(sf::Vector2f(size.x * ((points - min_points) / (max_points - min_points)), size.y), sf::Vector2f(m_object.getShapeCenter().x - m_object.getSize().x / 2, m_object.getShapeCenter().y), LEFT_MIDDLE, L"", 0, MIDDLE_MIDDLE, bar_color, sf::Color::Transparent, bar_outline_thickness, bar_outline_color, 0.f, sf::Text::Regular, sf::Vector2f(0, 0), Arial, active);

		m_pts = points;
		m_min_pts = min_points;
		m_max_pts = max_points;
	}



	void PointBar::create(
		const sf::Vector2f& size,
		const sf::Vector2f& position,
		const std::string& texture_path,
		float points,
		float min_points,
		float max_points,
		int origin,
		const sf::Color& object_color,
		const sf::Color& bar_color,
		float object_outline_thickness,
		float bar_outline_thickness,
		const sf::Color& object_outline_color,
		const sf::Color& bar_outline_color,
		bool active)
	{
		m_object.create(size, position, origin, texture_path, L"", 0, MIDDLE_MIDDLE, object_color, sf::Color::Transparent, object_outline_thickness, object_outline_color, 0, sf::Text::Regular, sf::Vector2f(0, 0), Arial, active);
		m_bar.create(sf::Vector2f(size.x * ((points - min_points) / (max_points - min_points)), size.y), sf::Vector2f(m_object.getShapeCenter().x - m_object.getSize().x / 2, m_object.getShapeCenter().y), LEFT_MIDDLE, L"", 0, MIDDLE_MIDDLE, bar_color, sf::Color::Transparent, bar_outline_thickness, bar_outline_color, 0.f, sf::Text::Regular, sf::Vector2f(0, 0), Arial, active);

		m_pts = points;
		m_max_pts = max_points;
		m_min_pts = min_points;
	}





	//-------------------------                                                         -------------------------//
	//+++                                                                                                     +++//
	//==============                       P R I V A T E   F U N C T I O N S                       ==============//
	//+++                                                                                                     +++//
	//-------------------------                                                         -------------------------//





	void PointBar::updateBarSize()
	{
		m_bar.setSize(sf::Vector2f(m_object.getSize().x * ((m_pts - m_min_pts) / (m_max_pts - m_min_pts)), m_object.getSize().y));
	}


	void PointBar::updateBarPosition()
	{
		m_bar.setPosition(sf::Vector2f(m_object.getShapeCenter().x - m_object.getSize().x * m_object.getScale().x / 2, m_object.getShapeCenter().y));
	}





	//-------------------------                                                         -------------------------//
	//+++                                                                                                     +++//
	//==============                           M O D    F U N C T I O N S                          ==============//
	//+++                                                                                                     +++//
	//-------------------------                                                         -------------------------//





	void PointBar::setPosition(const sf::Vector2f& position)
	{
		m_object.setPosition(position);
		
		this->updateBarPosition();
	}


	void
		PointBar::setPosition(float x, float y)
	{
		m_object.setPosition(x, y);
		
		this->updateBarPosition();
	}


	sf::Vector2f PointBar::getPosition() const
	{
		return m_object.getPosition();
	}



	////////////////////////////////////////////////////////////////




	void PointBar::setSize(const sf::Vector2f& size)
	{
		m_object.setSize(size);
		
		this->updateBarSize();
		this->updateBarPosition();
	}


	void PointBar::setSize(float size_x, float size_y)
	{
		m_object.setSize(size_x, size_y);

		this->updateBarSize();
		this->updateBarPosition();
	}


	sf::Vector2f PointBar::getSize() const
	{
		return m_object.getSize();
	}


	sf::Vector2f PointBar::getBarSize() const
	{
		return m_bar.getSize();
	}



	////////////////////////////////////////////////////////////////



	void PointBar::move(const sf::Vector2f& offset)
	{
		m_object.move(offset);
		m_bar.move(offset);
	}


	void PointBar::move(float offset_x, float offset_y)
	{
		m_object.move(offset_x, offset_y);
		m_bar.move(offset_x, offset_y);
	}



	////////////////////////////////////////////////////////////////



	void PointBar::setText(const std::wstring& text)
	{
		// Does nothing - not available in PointBar
	}


	std::wstring PointBar::getText() const
	{
		// Does nothing - not available in PointBar

		return std::wstring();
	}



	////////////////////////////////////////////////////////////////



	void PointBar::setOrigin(int origin)
	{
		m_object.setOrigin(origin);

		this->updateBarPosition();
	}


	int PointBar::getOrigin() const
	{
		return m_object.getOrigin();
	}



	////////////////////////////////////////////////////////////////



	void PointBar::setRotation(float angle)
	{
		// Does nothing - not available in PointBar
	}


	void PointBar::rotate(float angle)
	{
		// Does nothing - not available in PointBar
	}


	float PointBar::getRotation() const
	{
		// Does nothing - not available in PointBar

		return 0.0f;
	}



	////////////////////////////////////////////////////////////////



	void PointBar::setScale(const sf::Vector2f& factors)
	{
		m_object.setScale(factors);
		m_bar.setScale(factors);

		this->updateBarPosition();
	}


	void PointBar::setScale(float factor_x, float factor_y)
	{
		m_object.setScale(factor_x, factor_y);
		m_bar.setScale(factor_x, factor_y);

		this->updateBarPosition();
	}


	void PointBar::scale(const sf::Vector2f& factors)
	{
		m_object.scale(factors);
		m_bar.scale(factors);

		this->updateBarPosition();
	}


	sf::Vector2f PointBar::getScale() const
	{
		return m_object.getScale();
	}



	////////////////////////////////////////////////////////////////



	void PointBar::setPositionByCenter(const sf::Vector2f& position)
	{
		m_object.setPositionByCenter(position);

		this->updateBarPosition();
	}


	sf::Vector2f PointBar::getShapeCenter() const
	{
		return m_object.getShapeCenter();
	}



	////////////////////////////////////////////////////////////////



	void PointBar::setTexture(const sf::Texture* texture)
	{
		m_object.setTexture(texture);
	}


	void PointBar::setTexture(const std::string& texture_path)
	{
		m_object.setTexture(texture_path);
	}


	const sf::Texture* PointBar::getTexture() const
	{
		return m_object.getTexture();
	}



	////////////////////////////////////////////////////////////////



	void PointBar::setFillColor(const sf::Color& color)
	{
		m_object.setFillColor(color);
	}


	void PointBar::setBarFillColor(const sf::Color& color)
	{
		m_bar.setFillColor(color);
	}



	const sf::Color& PointBar::getFillColor() const
	{
		return m_object.getFillColor();
	}


	const sf::Color& PointBar::getBarFillColor() const
	{
		return m_bar.getFillColor();
	}



	////////////////////////////////////////////////////////////////



	void PointBar::setTextColor(const sf::Color& text_color)
	{
		///does nothing, no text in this m_object
	}


	const sf::Color& PointBar::getTextColor() const
	{
		///does nothing, no text in this m_object

		return sf::Color::Transparent;
	}



	////////////////////////////////////////////////////////////////



	void PointBar::setOutlineColor(const sf::Color& outline_color)
	{
		m_object.setOutlineColor(outline_color);
	}


	void PointBar::setBarOutlineColor(const sf::Color& outline_color)
	{
		m_bar.setOutlineColor(outline_color);
	}



	const sf::Color& PointBar::getOutlineColor() const
	{
		return m_object.getOutlineColor();
	}


	const sf::Color& PointBar::getBarOutlineColor() const
	{
		return m_bar.getOutlineColor();
	}



	////////////////////////////////////////////////////////////////



	void PointBar::setOutlineThickness(float outline_thickness)
	{
		m_object.setOutlineThickness(outline_thickness);
	}


	void PointBar::setBarOutlineThickness(float outline_thickness)
	{
		m_bar.setOutlineThickness(outline_thickness);
	}



	float PointBar::getOutlineThickness() const
	{
		return m_object.getOutlineThickness();
	}


	float PointBar::getBarOutlineThickness() const
	{
		return m_bar.getOutlineThickness();
	}





	//-------------------------                                                         -------------------------//
	//+++                                                                                                     +++//
	//==============          R E N D E R   A N D   B E H A V I O U R   F U N C T I O N S          ==============//
	//+++                                                                                                     +++//
	//-------------------------                                                         -------------------------//





	bool PointBar::isInvaded(const sf::Vector2f& mousePosition) const
	{
		return m_object.isInvaded(mousePosition);
	}


	bool PointBar::isBarInvaded(const sf::Vector2f& mousePosition) const
	{
		return m_bar.isInvaded(mousePosition);
	}



	////////////////////////////////



	bool PointBar::isClicked(sf::Mouse::Button button, const sf::Vector2f& mousePosition, sf::Event& event) const
	{
		return m_object.isClicked(button, mousePosition, event);
	}


	bool PointBar::isBarClicked(sf::Mouse::Button button, const sf::Vector2f& mousePosition, sf::Event& event) const
	{
		return m_bar.isClicked(button, mousePosition, event);
	}



	////////////////////////////////////////////////////////////////



	bool PointBar::isActive() const
	{
		return m_object.isActive();
	}


	void PointBar::setActiveStatus(bool status)
	{
		m_object.setActiveStatus(status);
		m_bar.setActiveStatus(status);
	}



	////////////////////////////////////////////////////////////////



	Rectangle* PointBar::getBar()
	{
		return &m_bar;
	}


	Button* PointBar::getObject()
	{
		return &m_object;
	}



	////////////////////////////////////////////////////////////////



	void PointBar::addPoint()
	{
		if (m_pts + 1 <= m_max_pts)
			m_pts++;
		else m_pts = m_max_pts;

		this->updateBarSize();
	}


	void PointBar::subtractPoint()
	{
		if (m_pts - 1 >= m_min_pts)
			m_pts--;
		else m_pts = m_min_pts;

		this->updateBarSize();
	}



	////////////////////////////////



	void PointBar::addPoints(float count)
	{
		if (m_pts + count <= m_max_pts)
			m_pts += count;
		else m_pts = m_max_pts;

		this->updateBarSize();
	}


	void PointBar::subtractPoints(float count)
	{
		if (m_pts - count >= m_min_pts)
			m_pts -= count;
		else m_pts = m_min_pts;

		this->updateBarSize();
	}



	////////////////////////////////



	void PointBar::setPointCount(float count)
	{
		m_pts = count;

		varGuard(m_pts, m_min_pts, m_max_pts);

		this->updateBarSize();
	}


	float PointBar::getPointCount() const
	{
		return m_pts;
	}



	////////////////////////////////



	void PointBar::setMinPointCount(float min_count)
	{
		m_min_pts = min_count;

		varGuard(m_pts, m_min_pts, m_max_pts);

		this->updateBarSize();
	}



	float PointBar::getMinPointCount() const
	{
		return m_min_pts;
	}



	////////////////////////////////



	void PointBar::setMaxPointCount(float max_count)
	{
		m_max_pts = max_count;

		varGuard(m_pts, m_min_pts, m_max_pts);

		this->updateBarSize();
	}


	float PointBar::getMaxPointCount() const
	{
		return m_max_pts;
	}



	////////////////////////////////////////////////////////////////



	float PointBar::update(const sf::Vector2f& mousePosition, sf::Event& event, sf::Mouse::Button button, sf::View* view)
	{
		// does nothing

		return 0;
	}



	////////////////////////////////////////////////////////////////



	void PointBar::render(sf::RenderWindow* window)
	{
		m_object.render(window);
		m_bar.render(window);
	}



	////////////////////////////////////////////////////////////////



	bool PointBar::created() const
	{
		return m_object.created();
	}


} // namespace ke