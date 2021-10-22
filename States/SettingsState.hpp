#pragma once

#include "State.hpp"
#include "MainMenu.hpp"


class SettingsState :
    public State
{
public:

    SettingsState(sf::RenderWindow* sf_window, sf::View* sf_view);
    virtual ~SettingsState();

    void InitState();

    void InitGenSettGUI();
    void InitWindowSettings();
    void InitAudioSettings();
    void InitSimulationSettings();
    void InitKeybindsSettings();


    void reloadState();

    void reloadGenSettGUI();
    void reloadWindowSettings();
    void reloadAudioSettings();
    void reloadSimulationSettings();
    void reloadKeybindsSettings();
    void reloadCharacterSize();


    void updateEvents(const MousePosition& mousePosition, float dt);
    void updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event);


    void genSettColorUpdate(const MousePosition& mousePosition, const float dt);
    void winSettColorUpdate(const MousePosition& mousePosition, const float dt);
    void audSettColorUpdate(const MousePosition& mousePosition, const float dt);

    void renderBackground();
    void renderByView();
    void renderByWindow();


    int Quit();

private:

    // Backgrounds and state masks 

    ke::Rectangle m_stateBackground;
    ke::Rectangle m_backgroundMask;
    ke::Rectangle m_stateMask;
    ke::Colorf m_sm_color; // state mask color


    // State behaviour

    int m_next_state;

    sf::Clock m_outro_clock;
    float m_outro_time;

    bool m_view_scrolling;
    float m_view_last_pos;
    float m_view_next_pos;


    // Settings GUI ////////////////////////

    std::vector<std::unique_ptr<ke::Rectangle>> m_settings_types;
    std::vector<std::unique_ptr<ke::Rectangle>>::iterator m_selected_type_itr;
    int m_selected_type_id;
    int m_last_sel_type_id;
    bool m_view_moving;

    std::array<float, 4> m_view_yPositions; // view positions on overlaps


    ke::Rectangle m_separation_bar;
    ke::Rectangle m_back_button;


    ke::Slider m_slider;


    ke::Rectangle m_apply_button;
    ke::Rectangle m_restore_def_buttoon;


    // Window settings ////////////////////////

    ke::PointBar m_maxMenuFPS_bar;
    ke::PointBar m_maxSimFPS_bar;

    std::vector<std::unique_ptr<ke::Rectangle>> m_WS_accessories; // for window settings


    ke::Rectangle m_vSyncOn;
    ke::Rectangle m_vSyncOff;
    bool m_vSyncStatus;


    ke::PercentageBar m_bright_lvl;


    ke::DropdownList m_windowSize_drl;

    bool m_window_size_changed;
    int m_start_window_size;
    int m_current_window_size;


    // Audio Settings ////////////////////////
                        
    ke::PercentageBar m_SFX_volume;
    ke::PercentageBar m_music_volume;

    std::vector<std::unique_ptr<ke::Rectangle>> m_AS_accessories; // for audio settings

    ke::SoundEffects m_test_effects;
    ke::Playlist m_test_music;


    // Colors ////////////////////////

    std::array<ke::Colorf, 5> m_st_fcolors; // settings_types_colors
    ke::Colorf m_slider_colorf; // Slider color
    std::array<ke::Colorf, 4> m_settings_manip_colors; // apply button and restore def button colors
    std::array<ke::Colorf, 26> m_windowSettings_colors; // window settings colors
    std::array<ke::Colorf, 8> m_audio_colors;
};