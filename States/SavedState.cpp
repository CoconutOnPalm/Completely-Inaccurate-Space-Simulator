#include "SavedState.hpp"

SavedState::SavedState(sf::RenderWindow* sf_window, sf::View* sf_view)
	: State(sf_window, sf_view, STATE::SIM_OPENING)
	, m_sm_color(sf::Color::Black)
	, m_next_state(STATE::NONE)
	, m_outro_time(0)
{
	view->setCenter(winSize / 2.f);
}

SavedState::~SavedState()
{

}

void SavedState::InitState()
{
	m_stateMask.create(winSize, { 0, 0 }, ke::Origin::LEFT_TOP, {}, {}, {}, sf::Color::Black);

	sf::Vector2f winsize(window->getSize());

	view->setSize(winsize);
	view->setCenter(winsize.x * 0.5, winsize.y * 0.5);

	sf::Texture backb_texture;
	backb_texture.loadFromFile("Textures/StateTextures/back_arrow.png");
	backb_texture.setSmooth(true);
	m_back_button.create({ winSize.y / 8, winSize.y / 8 }, { 0, 0 }, ke::Origin::LEFT_TOP, &backb_texture);
	m_back_button.setFillColor(sf::Color(255, 255, 255, 128));


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

	m_delete.create(sf::Vector2f(winsize.x * 0.1, winsize.y / 18), sf::Vector2f(m_background.getPosition().x + m_background.getSize().x * 0.5 - winsize.x / 32 - m_load.getSize().x, m_search_button.getPosition().y), ke::Origin::RIGHT_MIDDLE,
		nullptr, L"DELETE", winsize.y / 48, ke::Origin::MIDDLE_MIDDLE, sf::Color(16, 16, 16, 255), sf::Color(255, 64, 64, 128));


	m_simulations_names.reserve(m_saveController.m_savedSimulations.size());
	m_BlockColors.reserve(m_saveController.m_savedSimulations.size());

	for (auto& itr : m_saveController.m_savedSimulations)
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


	m_view_barrier.setView(view);
	m_slider.setFieldHeight(fheigh);
	m_view_barrier.setBorders(sf::Vector2f(0, 0), sf::Vector2f(winsize.x, m_slider.getFieldHeight()));

	m_selected_simulation = m_saved_simulations.end();
}

void SavedState::reloadState()
{
	sf::Vector2f winsize(window->getSize());
	SaveBlock::assign(winsize);

	m_stateMask.setScale(winsize);
	m_stateMask.setPosition(0, 0);

	view->setSize(winsize);
	view->setCenter(winsize.x * 0.5, winsize.y * 0.5);

	sf::Texture backb_texture;
	backb_texture.loadFromFile("Textures/StateTextures/back_arrow.png");
	backb_texture.setSmooth(true);
	m_back_button.create({ winSize.y / 8, winSize.y / 8 }, { 0, 0 }, ke::Origin::LEFT_TOP, &backb_texture);
	m_back_button.setFillColor(sf::Color(255, 255, 255, 128));

	m_background.setSize(sf::Vector2f(winsize.x * 0.75, winsize.y / 9));
	m_background.setPosition(sf::Vector2f(winsize.x / 2, 0));

	m_buttons_background.setSize(sf::Vector2f(winsize.x * 0.75, winsize.y / 9));
	m_buttons_background.setPosition(sf::Vector2f(winsize.x / 2, 0));


	m_search_button.setSize(sf::Vector2f(winsize.x * 0.38, winsize.y / 15));
	m_search_button.setPosition(sf::Vector2f(winsize.x / 8 + winsize.x / 64, winsize.y / 18));
	m_search_button.setCharacterSize(winsize.y / 32);

	m_load.setSize(sf::Vector2f(winsize.x * 0.1, winsize.y / 18));
	m_load.setPosition(sf::Vector2f(m_background.getPosition().x + m_background.getSize().x * 0.5 - winsize.x / 64, m_search_button.getPosition().y));
	m_load.setCharacterSize(winsize.y / 48);

	m_delete.setSize(sf::Vector2f(winsize.x * 0.1, winsize.y / 18));
	m_delete.setPosition(sf::Vector2f(m_background.getPosition().x + m_background.getSize().x * 0.5 - winsize.x / 32 - m_load.getSize().x, m_search_button.getPosition().y));
	m_delete.setCharacterSize(winsize.y / 48);

	m_slider.setSize(sf::Vector2f(winsize.x / 128, winsize.y - winsize.y / 9));
	m_slider.setPosition(sf::Vector2f(m_background.getShapeCenter().x + m_background.getSize().x * 0.5, winsize.y));

	for (auto& itr : m_saved_simulations)
		itr->resetSize(winsize);

	float some_space = winsize.y / 48;
	sf::Vector2f block_position(winsize.x * 0.5 - winsize.x * 0.375, winsize.y / 9 + some_space);

	for (auto& itr : m_saved_simulations)
	{
		itr->setPosition(block_position);
		block_position.y += winsize.y / 6 + some_space; // size of 1 block and some space
	}

	float fheigh = block_position.y;

	if (fheigh < winsize.y)
		fheigh = winsize.y;


	m_slider.setFieldHeight(fheigh);
	m_view_barrier.setBorders(sf::Vector2f(0, 0), sf::Vector2f(winsize.x, m_slider.getFieldHeight()));
}

void SavedState::updateEvents(const MousePosition& mousePosition, float dt)
{
	if (p_quitCode == StateQuitCode::STATE_QUIT)
	{
		ke::SmoothColorChange(&m_stateMask, true, sf::Color::Black, sf::Color::Transparent, m_sm_color, 512, dt);

		if (m_sm_color == ke::Colorf(sf::Color::Black))
		{
			switch (m_next_state)
			{
			case STATE::SIM_OPENING:
				states->back() = std::make_unique<OpeningState>(window, view);
				break;
			case STATE::SIMULATION:
				states->back() = std::make_unique<SimulationState>(window, view, m_selected_simulation->get()->name());
				break;
			default:
				ke::throw_error("OpeningState::updateEvents() -> state quitting", "State not found", "ERROR");
				break;
			}

			states->back()->InitState();
			return;
		}


		m_outro_time = m_outro_clock.getElapsedTime().asMilliseconds();

		if (m_outro_time > 10000) // safety guard
		{
			switch (m_next_state)
			{
			case STATE::SIM_OPENING:
				states->back() = std::make_unique<OpeningState>(window, view);
				break;
			case STATE::SIMULATION:
				states->back() = std::make_unique<SimulationState>(window, view, m_selected_simulation->get()->name());
				break;
			default:
				ke::throw_error("OpeningState::updateEvents() -> state quitting", "State not found", "ERROR");
				break;
			}

			states->back()->InitState();
			return;
		}
	}
	else
	{
		m_outro_clock.restart();
		ke::SmoothColorChange(&m_stateMask, true, sf::Color::Transparent, sf::Color::Black, m_sm_color, 256, dt);
	}


	m_search_button.updateCursor();
	m_slider.updateSliderPosition(view);
	m_view_barrier.update(mousePosition.byWindow, sf::Mouse::Right);




	// color update



	auto GUI_color_itr = m_colors.begin();

	ke::SmoothColorChange(&m_back_button, m_back_button.isInvaded(mousePosition.byWindow), sf::Color::White, sf::Color(255, 255, 255, 128), *GUI_color_itr, 255, dt);

	ke::SmoothColorChange(m_slider.getSlider(), m_slider.getSlider()->isInvaded(mousePosition.byWindow) || m_slider.isHolded(), sf::Color(96, 96, 96, 255), sf::Color(64, 64, 64, 255), *GUI_color_itr, 256, dt); ++GUI_color_itr;
	ke::SmoothColorChange(m_slider.getSliderTrack(), m_slider.getSliderTrack()->isInvaded(mousePosition.byWindow) || m_slider.isHolded(), sf::Color(64, 64, 64, 64), sf::Color(32, 32, 32, 32), *GUI_color_itr, 256, dt); ++GUI_color_itr;

	ke::SmoothColorChange(&m_load, m_load.isInvaded(mousePosition.byWindow), sf::Color(24, 24, 24, 255), sf::Color(16, 16, 16, 255), *GUI_color_itr, 512, dt); ++GUI_color_itr;
	ke::SmoothTextColorChange(&m_load, m_load.isInvaded(mousePosition.byWindow), sf::Color(64, 255, 64, 255), sf::Color(64, 255, 64, 128), *GUI_color_itr, 1024, dt); ++GUI_color_itr;
	ke::SmoothColorChange(&m_delete, m_delete.isInvaded(mousePosition.byWindow), sf::Color(24, 24, 24, 255), sf::Color(16, 16, 16, 255), *GUI_color_itr, 512, dt); ++GUI_color_itr;
	ke::SmoothTextColorChange(&m_delete, m_delete.isInvaded(mousePosition.byWindow), sf::Color(255, 64, 64, 255), sf::Color(255, 24, 24, 128), *GUI_color_itr, 1024, dt); ++GUI_color_itr;


	ke::SmoothColorChange(&m_search_button, m_search_button.isInvaded(mousePosition.byWindow) || m_search_button.getEPS(), sf::Color(40, 40, 40, 255), sf::Color(32, 32, 32, 255), *GUI_color_itr, 128, dt); ++GUI_color_itr;


	auto color_itr = m_BlockColors.begin();

	for (auto& itr : m_on_screen)
	{
		ke::SmoothColorChange(itr->get()->getHitbox(), itr->get()->getHitbox()->isInvaded(mousePosition.byView), sf::Color(32, 32, 32, 128), sf::Color(32, 32, 32, 32), *color_itr, 256, dt);
		++color_itr;
	}
}

void SavedState::updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		p_quitCode = StateQuitCode::STATE_QUIT;
		m_next_state = STATE::SIM_OPENING;
	}
	else if (m_back_button.isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
	{
		p_quitCode = StateQuitCode::STATE_QUIT;
		m_next_state = STATE::SIM_OPENING;
	}
	else if (m_load.isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
	{
		if (m_selected_simulation != m_saved_simulations.end())
		{
			p_quitCode = StateQuitCode::STATE_QUIT;
			m_next_state = STATE::SIMULATION;
		}
	}
	else if (m_delete.isClicked(sf::Mouse::Left, mousePosition.byWindow, event))
	{
		if (m_selected_simulation != m_saved_simulations.end())
		{
			m_saveController.m_savedSimulations.erase(m_selected_simulation->get()->name());
			m_saved_simulations.erase(m_selected_simulation);
			m_selected_simulation = m_saved_simulations.end();


			m_simulations_names.clear();

			for (auto& itr : m_saveController.m_savedSimulations)
			{
				m_simulations_names.push_back(itr.first);
			}

			std::sort(m_simulations_names.begin(), m_simulations_names.end());

			float some_space = window->getSize().y / 48;
			sf::Vector2f block_position(window->getSize().x * 0.5 - window->getSize().x * 0.375, window->getSize().y / 9 + some_space);

			for (auto& itr : m_saved_simulations)
			{
				itr->setPosition(block_position);
				block_position.y += window->getSize().y / 6 + some_space; // size of 1 block and some space
			}

			float fheigh = block_position.y;

			if (fheigh < window->getSize().y)
				fheigh = window->getSize().y;

			m_slider.setFieldHeight(fheigh);
			m_view_barrier.setBorders(sf::Vector2f(0, 0), sf::Vector2f(window->getSize().x, m_slider.getFieldHeight()));
		}
	}



	m_slider.update(mousePosition.byWindow, event, sf::Mouse::Left, view);
	m_view_barrier.updateClick(mousePosition.byWindow, sf::Mouse::Right, event);


	if (m_search_button.update(mousePosition.byWindow, event, sf::Mouse::Left, nullptr))
	{
		if (m_search_button.getText().empty())
		{
			float some_space = window->getSize().y / 48;
			sf::Vector2f block_position(window->getSize().x * 0.5 - window->getSize().x * 0.375, window->getSize().y / 9 + some_space);
			for (auto& itr : m_saved_simulations)
			{
				itr->setPosition(block_position);
				block_position.y += window->getSize().y / 6 + some_space; // size of 1 block and some space
			}

			float fheigh = block_position.y;

			if (fheigh < window->getSize().y)
				fheigh = window->getSize().y;

			m_slider.setFieldHeight(fheigh);
			m_view_barrier.setBorders(sf::Vector2f(0, 0), sf::Vector2f(window->getSize().x, m_slider.getFieldHeight()));
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

			float some_space = window->getSize().y / 48;
			sf::Vector2f block_position(window->getSize().x * 0.5 - window->getSize().x * 0.375, window->getSize().y / 9 + some_space);
			for (auto& itr : matching)
			{
				itr->setPosition(block_position);
				block_position.y += window->getSize().y / 6 + some_space; // size of 1 block and some space
			}

			float fheigh = block_position.y;

			if (fheigh < window->getSize().y)
				fheigh = window->getSize().y;

			m_slider.setFieldHeight(fheigh);
			m_view_barrier.setBorders(sf::Vector2f(0, 0), sf::Vector2f(window->getSize().x, m_slider.getFieldHeight()));
		}
	}


	if (event.type == sf::Event::MouseWheelScrolled)
	{
		if (event.mouseWheelScroll.delta > 0)
		{
			//m_next_vpos -= m_window->getSize().y / 3600;
			//ke::varGuard(m_next_vpos, m_window->getSize().y / 2, m_window->getSize().y / 2);
			view->move(0, -static_cast<float>(window->getSize().y) / 18);

			if (view->getCenter().y < window->getSize().y * 0.5)
				view->setCenter(sf::Vector2f(window->getSize()) * 0.5f);
		}
		else if (event.mouseWheelScroll.delta < 0)
		{
			//m_next_vpos += m_window->getSize().y / 3600;
			//ke::varGuard(m_next_vpos, m_slider.getFieldHeight() - m_window->getSize().y / 2, m_slider.getFieldHeight() - m_window->getSize().y / 2);
			view->move(0, window->getSize().y / 18);

			if (view->getCenter().y > m_slider.getFieldHeight() - window->getSize().y * 0.5)
				view->setCenter(sf::Vector2f(window->getSize().x * 0.5f, m_slider.getFieldHeight() - window->getSize().y * 0.5));
		}
	}


	m_on_screen.clear();

	for (auto itr = m_saved_simulations.begin(); itr != m_saved_simulations.end(); ++itr)
		if (!ke::isOutsideTheView((*itr)->getHitbox(), view, sf::Vector2f(20, 20)))
			m_on_screen.push_back(itr);


	if (mousePosition.byWindow.y > m_buttons_background.getSize().y)
	{
		for (auto& itr : m_on_screen)
		{
			if ((*itr)->getHitbox()->isClicked(sf::Mouse::Left, mousePosition.byView, event))
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
}

void SavedState::renderBackground()
{

}

void SavedState::renderByView()
{
	for (auto& itr : m_on_screen)
		(*itr)->render(window);
}

void SavedState::renderByWindow()
{
	m_back_button.render(window);

	m_buttons_background.render(window);
	m_search_button.render(window);
	m_slider.render(window);

	m_delete.render(window);
	m_load.render(window);

	m_stateMask.render(window);
}