#pragma once

#include "State.hpp"
#include "MainMenu.hpp"
#include "SimulationState.hpp"
#include "SavedState.hpp"

class OpeningState :
    public State
{
public:

    OpeningState(sf::RenderWindow* sf_window, sf::View* sf_view);
    ~OpeningState();

    void InitState();

    void reloadState();


    void updateEvents(const MousePosition& mousePosition, float dt);
    void updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event);


    void renderBackground();
    void renderByView();
    void renderByWindow();


private:

    ke::Rectangle m_stateBackground;
    ke::Rectangle m_backgroundMask;
    ke::Rectangle m_stateMask;
    ke::Colorf m_sm_color; // state mask color

    ke::Rectangle m_back_button;

    ke::Button m_load_latest;
    ke::Button m_create_new;
    ke::Button m_load_saved;

    std::array<ke::Colorf, 7> m_button_colors;

    std::string m_simulation_name;

    STATE m_next_state;

    sf::Clock m_outro_clock;
    float m_outro_time;
};

