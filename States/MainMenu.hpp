#pragma once

#include "State.hpp"
#include "SettingsState.hpp"
#include "OpeningState.hpp"


class MainMenu :
    public State
{
public:

    MainMenu(sf::RenderWindow* sf_window, sf::View* sf_view);
    virtual ~MainMenu();

    void InitState();

    void reloadState();


    void updateEvents(const MousePosition& mousePosition, float dt);
    void updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event);


    void renderBackground();
    void renderByView();
    void renderByWindow();


    int Quit();


private:

    ke::Rectangle m_stateBackground;
    ke::Rectangle m_backgroundMask;
    ke::Rectangle m_stateMask;
    ke::Colorf m_sm_color; // state mask color

    ke::Rectangle m_start_button;
    ke::Rectangle m_savedsim_button;
    ke::Rectangle m_settings_button;
    ke::Rectangle m_quit_button;

    std::vector<std::unique_ptr<ke::Rectangle>> m_buttons;

    std::vector<ke::Colorf> m_floatcolors;

    int m_next_state;

    sf::Clock m_outro_clock;
    float m_outro_time;
};