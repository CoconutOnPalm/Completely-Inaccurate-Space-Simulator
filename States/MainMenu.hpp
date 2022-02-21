#pragma once

#include "State.hpp"
#include "SettingsState.hpp"
#include "OpeningState.hpp"


class MainMenu :
    public State
{
public:

    MainMenu(sf::RenderWindow* sf_window, sf::View* sf_view, bool with_animation);
    virtual ~MainMenu();

    void InitState();

    void reloadState();


    void updateEvents(const MousePosition& mousePosition, float dt);
    void updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event);


    void renderBackground();
    void renderByView();
    void renderByWindow();


    StateQuitCode Quit();


private:

    ke::Rectangle m_stateBackground;
    ke::Rectangle m_menu_logo;
    ke::Rectangle m_backgroundMask;
    ke::Rectangle m_stateMask;
    ke::Colorf m_sm_color; // state mask color

    ke::Circle m_start_button;
    ke::Circle m_settings_button;
    ke::Circle m_quitButton;

    sf::CircleShape m_orbit_1;
    sf::CircleShape m_orbit_2;
    
    size_t m_current_point_1;
    size_t m_current_point_2;

    std::array<sf::VertexArray, 1000> m_hyperspace_jump;

    ke::SoundEffects m_sfx;

    std::array<ke::Colorf, 4> m_colors;

    sf::Shader m_star_shader;


    //ke::Rectangle m_start_button;
    //ke::Rectangle m_savedsim_button;
    //ke::Rectangle m_settings_button;
    //ke::Rectangle m_quit_button;

    //std::vector<std::unique_ptr<ke::Rectangle>> m_buttons;

    //std::vector<ke::Colorf> m_floatcolors;

    STATE m_next_state;

    bool m_animation_finished;
    bool m_quitting_app;

    sf::Clock m_outro_clock;
    float m_outro_time;

    const unsigned int point_count_multiplier = 1;
};