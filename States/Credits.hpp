#pragma once


#include "State.hpp"
#include "MainMenu.hpp"


class Credits
    : public State
{
public:

    Credits(sf::RenderWindow* sf_window, sf::View* sf_view);
    virtual ~Credits();

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
    ke::Rectangle m_backgroundMask;
    ke::Rectangle m_stateMask;
    ke::Colorf m_sm_color; // state mask color


    std::vector<std::unique_ptr<ke::Button>> m_credits;


    STATE m_next_state;

    sf::Clock m_outro_clock;
    float m_outro_time;

    ke::Playlist m_credits_music;

    float m_starViewSize;
    float m_viewposY;
};

