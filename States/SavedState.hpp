#pragma once

#include "State.hpp"
#include "OpeningState.hpp"
#include "Overlays/SimLoadingOverlay.hpp"



class SavedState :
    public State
{
public:

    SavedState(sf::RenderWindow* sf_window, sf::View* sf_view);
    ~SavedState();

    void InitState();

    void reloadState();

    void updateEvents(const MousePosition& mousePosition, float dt);
    void updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event);


    void renderBackground();
    void renderByView();
    void renderByWindow();

private:

    STATE m_next_state;

    SaveController m_saveController;

    ke::Rectangle m_stateMask;
    ke::Colorf m_sm_color; // state mask color

    sf::Clock m_outro_clock;
    float m_outro_time;

    ke::Rectangle m_back_button;

    ke::Button m_background;
    ke::Button m_buttons_background;

    ke::Button m_load;
    ke::Button m_delete;

    std::vector<std::unique_ptr<SaveBlock>> m_saved_simulations;
    std::vector<std::unique_ptr<SaveBlock>>::iterator m_selected_simulation;
    std::vector<std::string> m_simulations_names;

    std::list<std::vector<std::unique_ptr<SaveBlock>>::iterator> m_on_screen;

    ke::InputButton m_search_button;
    ke::Slider m_slider;

    ke::HoldView m_view_barrier;

    std::array<ke::Colorf, 12> m_colors;

    std::vector<ke::Colorf> m_BlockColors;

};

