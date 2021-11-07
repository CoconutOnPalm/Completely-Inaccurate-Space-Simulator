#pragma once

#include "State.hpp"


class WindowGui :
    public State
{

public:

    WindowGui(sf::RenderWindow* sf_window, sf::View* sf_view);
    virtual ~WindowGui();

    void InitState();

    void reloadState();


    void updateEvents(const MousePosition& mousePosition, float dt);
    void updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event);


    void renderBackground();
    void renderByView();
    void renderByWindow();


    StateQuitCode Quit();

private:

    //ke::Rectangle m_stateMask;

    ke::Button m_close;
    ke::Button m_maximize;
    ke::Button m_minimize;
               
    ke::Colorf m_closecolor;
    ke::Colorf m_maximcolor;
    ke::Colorf m_minmimcolor;

    bool m_windowStatus; // 0 - none. 1 - fullscreen

    bool m_windowHolded;
    sf::Vector2f m_windowCatchDiff;

    ke::Rectangle m_mousePosVis;
};

