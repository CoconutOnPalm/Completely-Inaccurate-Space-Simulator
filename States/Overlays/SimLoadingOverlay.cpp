#include "SimLoadingOverlay.hpp"

SimLoadingOverlay::SimLoadingOverlay(const sf::Vector2f& winsize, SaveController* save_controller, bool* simulation_running, sf::RenderWindow* window)
	: m_quitCode(OverlayQuitCode::NOT_QUITTING)
	, m_saveController(save_controller)
	, m_winsize(winsize)
	, m_window(window)
{
	*simulation_running = false;

	m_background.create(
		sf::Vector2f(winsize.x * 0.75, winsize.y), winsize / 2.f, ke::Origin::MIDDLE_MIDDLE, nullptr, L"",
		winsize.x / 56.f, ke::Origin::MIDDLE_MIDDLE, sf::Color::Black);

	m_buttons_background.create(sf::Vector2f(winsize.x * 0.75, winsize.y / 9), sf::Vector2f(winsize.x / 2, 0), ke::Origin::MIDDLE_TOP, nullptr, std::wstring(), 0, ke::Origin::MIDDLE_MIDDLE, sf::Color(8, 8, 8, 255));

	m_search_button.create(sf::Vector2f(winsize.x * 0.38, winsize.y / 15), sf::Vector2f(winsize.x / 8 + winsize.x / 64, winsize.y / 18), ke::Origin::LEFT_MIDDLE, nullptr,
		L"Search...", ke::TextScope::ASCII_Everything, 50, 1, winsize.y / 32, ke::Origin::LEFT_MIDDLE, sf::Color(32, 32, 32, 255),
		sf::Color::White, sf::Color(92, 92, 92, 255), 0, sf::Color::Transparent, {}, sf::Vector2f(winsize.x * 0.0125, 0));

	m_slider.create(sf::Vector2f(winsize.x / 128, winsize.y - winsize.y / 9), sf::Vector2f(m_background.getShapeCenter().x + m_background.getSize().x * 0.5, winsize.y),
		winsize.y, ke::Origin::RIGHT_BOTTOM, nullptr, nullptr, sf::Color(64, 64, 64, 255), sf::Color((32, 32, 32, 32)));

	m_load.create(sf::Vector2f(winsize.x * 0.1, winsize.y / 18), sf::Vector2f(m_background.getPosition().x + m_background.getSize().x * 0.5 - winsize.x / 64, m_search_button.getPosition().y), ke::Origin::RIGHT_MIDDLE,
		nullptr, L"LOAD", winsize.y / 48, ke::Origin::MIDDLE_MIDDLE, sf::Color(16, 16, 16, 255), sf::Color(64, 255, 64, 128));

	m_cancel.create(sf::Vector2f(winsize.x * 0.1, winsize.y / 18), sf::Vector2f(m_background.getPosition().x + m_background.getSize().x * 0.5 - winsize.x / 32 - m_load.getSize().x, m_search_button.getPosition().y), ke::Origin::RIGHT_MIDDLE,
		nullptr, L"CANCEL", winsize.y / 48, ke::Origin::MIDDLE_MIDDLE, sf::Color(16, 16, 16, 255), sf::Color(255, 64, 64, 128));


	//m_saved_simulations.emplace_back(std::make_unique<SaveBlock>("stress_test01", winsize));
	//m_saved_simulations.back()->setPosition(sf::Vector2f(winsize.x * 0.5 - winsize.x * 0.375, winsize.y / 4));

	m_view.setSize(winsize);
	m_view.setCenter(winsize.x * 0.5, winsize.y * 0.5);


	m_simulations_names.reserve(save_controller->m_savedSimulations.size());
	m_BlockColors.reserve(save_controller->m_savedSimulations.size());

	for (auto& itr : save_controller->m_savedSimulations)
	{
		m_simulations_names.push_back(itr.first);
		m_BlockColors.push_back(ke::Colorf());
	}

	std::sort(m_simulations_names.begin(), m_simulations_names.end());

	float some_space = winsize.y / 48;
	sf::Vector2f block_position(winsize.x * 0.5 - winsize.x * 0.375, winsize.y / 9 + some_space);

	for (auto& itr : m_simulations_names)
	{
		m_saved_simulations.emplace_back(std::make_unique<SaveBlock>(itr, winsize));
		m_saved_simulations.back()->setPosition(block_position);
		block_position.y += winsize.y / 6 + some_space; // size of 1 block and some space
	}

	float fheigh = block_position.y;

	if (fheigh < winsize.y)
		fheigh = winsize.y;


	m_view_barrier.setView(&m_view);
	m_slider.setFieldHeight(fheigh);
	m_view_barrier.setBorders(sf::Vector2f(0, 0), sf::Vector2f(winsize.x, m_slider.getFieldHeight()));

	m_selected_simulation = m_saved_simulations.end();
}

SimLoadingOverlay::~SimLoadingOverlay()
{

}

void SimLoadingOverlay::updateEvents(const MousePosition& mousePosition, float dt)
{
	m_search_button.updateCursor();
	m_slider.updateSliderPosition(&m_view);
	m_view_barrier.update(mousePosition.byWindow, sf::Mouse::Right);
}

void SimLoadingOverlay::updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event, std::vector<std::unique_ptr<SpaceObject>>* objects, const sf::Vector2f& viewsize, std::vector<std::unique_ptr<SpaceObject>>::iterator& selected_object, long double space_scale)
{
	if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left && !m_background.isInvaded(mousePosition.byWindow))
	{
		m_quitCode = OverlayQuitCode::CLOSING_OVRL;
		return;
	}
	if (m_cancel.isClicked(sf::Mouse::Left, mousePosition.byWindow, event) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
	{
		State::sfx.play("click");

		m_quitCode = OverlayQuitCode::CLOSING_OVRL;
		return;
	}
	if (m_load.isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
	{
		if (m_selected_simulation != m_saved_simulations.end())
		{
			State::sfx.play("click");

			//m_window->setActive(false);
			//LoadingBarOverlay loadingBarOvrl(m_window);
			//std::thread lbthread(&LoadingBarOverlay::run, loadingBarOvrl);
			m_saveController->Load((*m_selected_simulation)->name(), objects, viewsize, m_winsize, selected_object, space_scale);
			//lbthread.join();
			//m_window->setActive(true);

			//m_saveController->Load((*m_selected_simulation)->name(), objects, viewsize, m_winsize, selected_object, space_scale);
			m_quitCode = OverlayQuitCode::CLOSING_OVRL;
			return;
		}
		else
		{
			State::sfx.play("error");
		}
	}


	m_slider.update(mousePosition.byWindow, event, sf::Mouse::Left, &m_view);
	m_view_barrier.updateClick(mousePosition.byWindow, sf::Mouse::Right, event);


	if (m_search_button.update(mousePosition.byWindow, event, sf::Mouse::Left, nullptr))
	{
		if (m_search_button.getText().empty())
		{
			float some_space = m_winsize.y / 48;
			sf::Vector2f block_position(m_winsize.x * 0.5 - m_winsize.x * 0.375, m_winsize.y / 9 + some_space);
			for (auto& itr : m_saved_simulations)
			{
				itr->setPosition(block_position);
				block_position.y += m_winsize.y / 6 + some_space; // size of 1 block and some space
			}

			float fheigh = block_position.y;

			if (fheigh < m_winsize.y)
				fheigh = m_winsize.y;

			m_slider.setFieldHeight(fheigh);
			m_view_barrier.setBorders(sf::Vector2f(0, 0), sf::Vector2f(m_winsize.x, m_slider.getFieldHeight()));
		}
		else
		{
			std::string searched_name(ke::fixed::wtos(m_search_button.getText())); // text in search button but lowercase

			std::transform(searched_name.begin(), searched_name.end(), searched_name.begin(),
				[](unsigned char c) { return std::tolower(c); });

			std::vector<SaveBlock*> matching;

			for (auto& itr : m_saved_simulations)
				if (itr->name().compare(0, searched_name.size(), searched_name) == 0)
					matching.push_back(itr.get());

			for (auto& itr : m_saved_simulations) // place not matching ones somewhere else
				itr->setPosition(sf::Vector2f(-1000, -1000));

			float some_space = m_winsize.y / 48;
			sf::Vector2f block_position(m_winsize.x * 0.5 - m_winsize.x * 0.375, m_winsize.y / 9 + some_space);
			for (auto& itr : matching)
			{
				itr->setPosition(block_position);
				block_position.y += m_winsize.y / 6 + some_space; // size of 1 block and some space
			}

			float fheigh = block_position.y;

			if (fheigh < m_winsize.y)
				fheigh = m_winsize.y;

			m_slider.setFieldHeight(fheigh);
			m_view_barrier.setBorders(sf::Vector2f(0, 0), sf::Vector2f(m_winsize.x, m_slider.getFieldHeight()));
		}
	}


	if (event.type == sf::Event::MouseWheelScrolled)
	{
		if (event.mouseWheelScroll.delta > 0)
		{
			//m_next_vpos -= m_window->getSize().y / 3600;
			//ke::varGuard(m_next_vpos, m_window->getSize().y / 2, m_window->getSize().y / 2);
			m_view.move(0, -static_cast<float>(m_winsize.y) / 18);

			if (m_view.getCenter().y < m_winsize.y * 0.5)
				m_view.setCenter(m_winsize * 0.5f);
		}
		else if (event.mouseWheelScroll.delta < 0)
		{
			//m_next_vpos += m_window->getSize().y / 3600;
			//ke::varGuard(m_next_vpos, m_slider.getFieldHeight() - m_window->getSize().y / 2, m_slider.getFieldHeight() - m_window->getSize().y / 2);
			m_view.move(0, m_winsize.y / 18);

			if (m_view.getCenter().y > m_slider.getFieldHeight() - m_winsize.y * 0.5)
				m_view.setCenter(sf::Vector2f(m_winsize.x * 0.5f, m_slider.getFieldHeight() - m_winsize.y * 0.5));
		}


		//m_on_screen.clear();

		//for (auto itr = m_objects.begin(); itr != m_objects.end(); ++itr)
		//{
		//	if ((*itr)->Icon().icon.isActive())
		//		if (ke::ionRange((*itr)->Icon().icon.getPosition().y, -1.5 * (*itr)->Icon().icon.getSize().y, m_window->getSize().y + 1.5 * (*itr)->Icon().icon.getSize().y))
		//			m_on_screen.push_back(itr);
		//}
	}


	m_on_screen.clear();

	for (auto itr = m_saved_simulations.begin(); itr != m_saved_simulations.end(); ++itr)
		if (!ke::isOutsideTheView((*itr)->getHitbox(), &m_view, sf::Vector2f(20, 20)))
			m_on_screen.push_back(itr);


	for (auto& itr : m_on_screen)
	{
		if ((*itr)->getHitbox()->isClicked(sf::Mouse::Left, mPosView, event))
		{

			if (m_selected_simulation != itr)
			{
				if (m_selected_simulation != m_saved_simulations.end())
					(*m_selected_simulation)->getHitbox()->setOutlineColor(sf::Color::Transparent);

				m_selected_simulation = itr;
				(*m_selected_simulation)->getHitbox()->setOutlineColor(sf::Color(32, 32, 255, 128));
			}
			else
			{
				(*m_selected_simulation)->getHitbox()->setOutlineColor(sf::Color::Transparent);
				m_selected_simulation = m_saved_simulations.end();
			}
		}
	}
}

void SimLoadingOverlay::updateColors(const sf::Vector2f& mousePosition, const float dt)
{
	auto GUI_color_itr = m_colors.begin();

	ke::SmoothColorChange(m_slider.getSlider(), m_slider.getSlider()->isInvaded(mousePosition) || m_slider.isHolded(), sf::Color(96, 96, 96, 255), sf::Color(64, 64, 64, 255), *GUI_color_itr, 256, dt); ++GUI_color_itr;
	ke::SmoothColorChange(m_slider.getSliderTrack(), m_slider.getSliderTrack()->isInvaded(mousePosition) || m_slider.isHolded(), sf::Color(64, 64, 64, 64), sf::Color(32, 32, 32, 32), *GUI_color_itr, 256, dt); ++GUI_color_itr;

	ke::SmoothColorChange(&m_load, m_load.isInvaded(mousePosition), sf::Color(24, 24, 24, 255), sf::Color(16, 16, 16, 255), *GUI_color_itr, 512, dt); ++GUI_color_itr;
	ke::SmoothTextColorChange(&m_load, m_load.isInvaded(mousePosition), sf::Color(64, 255, 64, 255), sf::Color(64, 255, 64, 128), *GUI_color_itr, 1024, dt); ++GUI_color_itr;
	ke::SmoothColorChange(&m_cancel, m_cancel.isInvaded(mousePosition), sf::Color(24, 24, 24, 255), sf::Color(16, 16, 16, 255), *GUI_color_itr, 512, dt); ++GUI_color_itr;
	ke::SmoothTextColorChange(&m_cancel, m_cancel.isInvaded(mousePosition), sf::Color(255, 64, 64, 255), sf::Color(255, 24, 24, 128), *GUI_color_itr, 1024, dt); ++GUI_color_itr;


	ke::SmoothColorChange(&m_search_button, m_search_button.isInvaded(mousePosition) || m_search_button.getEPS(), sf::Color(40, 40, 40, 255), sf::Color(32, 32, 32, 255), *GUI_color_itr, 128, dt); ++GUI_color_itr;


	auto color_itr = m_BlockColors.begin();

	for (auto& itr : m_on_screen)
	{
		ke::SmoothColorChange(itr->get()->getHitbox(), itr->get()->getHitbox()->isInvaded(mPosView), sf::Color(32, 32, 32, 128), sf::Color(32, 32, 32, 32), *color_itr, 256, dt);
		++color_itr;
	}
}

OverlayQuitCode SimLoadingOverlay::quitStatus() const
{
	return m_quitCode;
}

void SimLoadingOverlay::render(sf::RenderWindow* window)
{
	window->setView(window->getDefaultView());

	m_background.render(window);

	window->setView(m_view);

	mPosView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

	for (auto& itr : m_on_screen)
		(*itr)->render(window);

	window->setView(window->getDefaultView());

	m_buttons_background.render(window);
	m_search_button.render(window);
	m_slider.render(window);

	m_cancel.render(window);
	m_load.render(window);
}










////////////////////////////////////////////////////////////////





SaveBlock::SaveBlock(std::string name, const sf::Vector2f& winsize)
{
	s_winsize = winsize;

	m_name = name;

	m_background.create(sf::Vector2f(winsize.x * 0.75 - winsize.x / 128, winsize.y / 6), sf::Vector2f(-1000, -1000), ke::Origin::LEFT_TOP, nullptr, std::wstring(), 0, 0, sf::Color(32, 32, 32, 32));
	m_icon.create(sf::Vector2f(winsize.y / 8, winsize.y / 8), sf::Vector2f(m_background.getPosition().x + s_winsize.y / 48, m_background.getPosition().y + s_winsize.y / 48), ke::Origin::LEFT_TOP, "Data/Simulations/SimulationIcons/" + name + ".jpg");
	m_name_block.create(sf::Vector2f(winsize.x * 0.5, winsize.y / 10), sf::Vector2f(m_background.getPosition().x + winsize.y / 9, m_background.getPosition().y + winsize.y / 180), ke::Origin::LEFT_MIDDLE, nullptr, ke::fixed::stow(name), winsize.y / 32, ke::Origin::LEFT_MIDDLE);

	m_background.setOutlineThickness(winsize.y / 360);
}


sf::Vector2f SaveBlock::s_winsize;


SaveBlock::~SaveBlock()
{

}

void SaveBlock::setPosition(const sf::Vector2f& position)
{
	m_background.setPosition(position);
	m_icon.setPosition(sf::Vector2f(m_background.getPosition().x + s_winsize.y / 48, m_background.getPosition().y + s_winsize.y / 48));
	m_name_block.setPosition(sf::Vector2f(m_background.getPosition().x + s_winsize.y / 5, m_background.getPosition().y + m_background.getSize().y / 2));
}

sf::Vector2f SaveBlock::getPosition() const
{
	return m_background.getPosition();
}


void SaveBlock::assign(const sf::Vector2f& winsize)
{
	s_winsize = winsize;
}



void SaveBlock::updateEvents(const MousePosition& mousePosition, float dt)
{

}

void SaveBlock::updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event)
{

}

void SaveBlock::updateColors(const sf::Vector2f& mousePosition, const float dt)
{

}

std::string& SaveBlock::name()
{
	return m_name;
}

void SaveBlock::resetSize(const sf::Vector2f& winsize)
{
	m_background.setSize(sf::Vector2f(winsize.x * 0.75 - winsize.x / 128, winsize.y / 6));
	m_icon.setSize(sf::Vector2f(winsize.y / 8, winsize.y / 8));
	m_icon.setTexture(m_icon.getTexturePath());
	m_name_block.setSize(sf::Vector2f(winsize.x * 0.5, winsize.y / 10));
	m_name_block.setCharacterSize(winsize.y / 32);

	m_background.setOutlineThickness(winsize.y / 360);
}

void SaveBlock::render(sf::RenderWindow* window)
{
	m_background.render(window);
	m_icon.render(window);
	m_name_block.render(window);
}


ke::Button* SaveBlock::getHitbox()
{
	return &m_background;
}
