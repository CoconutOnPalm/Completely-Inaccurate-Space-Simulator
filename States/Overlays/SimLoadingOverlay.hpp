#pragma once

#include "States/State.hpp"
#include "States/Modules/SaveController.hpp"


class SaveBlock;


class SimLoadingOverlay
{
public: 

	SimLoadingOverlay(const sf::Vector2f& winsize, SaveController* save_controller, bool* simulation_running);
	~SimLoadingOverlay();


	void updateEvents(const MousePosition& mousePosition, float dt);
	void updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event, std::vector<std::unique_ptr<SpaceObject>>* objects, const sf::Vector2f& viewsize, std::vector<std::unique_ptr<SpaceObject>>::iterator& selected_object, long double space_scale);

	void updateColors(const sf::Vector2f& mousePosition, const float dt);

	OverlayQuitCode quitStatus() const;

	void render(sf::RenderWindow* window);

private:

	sf::Vector2f m_winsize;

	SaveController* m_saveController;
	OverlayQuitCode m_quitCode;

	ke::Button m_background;
	ke::Button m_buttons_background;

	ke::Button m_load;
	ke::Button m_cancel;

	std::vector<std::unique_ptr<SaveBlock>> m_saved_simulations;
	std::vector<std::unique_ptr<SaveBlock>>::iterator m_selected_simulation;
	std::vector<std::string> m_simulations_names;

	std::list<std::vector<std::unique_ptr<SaveBlock>>::iterator> m_on_screen;

	ke::InputButton m_search_button;
	ke::Slider m_slider;

	sf::Vector2f mPosView;
	ke::HoldView m_view_barrier;

	sf::View m_view;

	std::array<ke::Colorf, 10> m_colors;

	std::vector<ke::Colorf> m_BlockColors;
};



////////////////////////////////////////////////////////////////



class SaveBlock
{
public:

	SaveBlock(std::string name, const sf::Vector2f& winsize);
	~SaveBlock();

	void setPosition(const sf::Vector2f& position);
	void resetSize(const sf::Vector2f& winsize);
	static void assign(const sf::Vector2f& winsize);

	void updateEvents(const MousePosition& mousePosition, float dt);
	void updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event);

	void updateColors(const sf::Vector2f& mousePosition, const float dt);

	std::string& name();

	ke::Button* getHitbox();

	void render(sf::RenderWindow* window);

private:

	static sf::Vector2f s_winsize;

	std::string m_name;

	ke::Button m_background;
	ke::Button m_icon;
	ke::Button m_name_block;
};