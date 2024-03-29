#pragma once


#include "State.hpp"
#include "MainMenu.hpp"

#include "Space Objects/Planet.hpp"
#include "Space Objects/Star.hpp"
#include "Space Objects/CenterOfMass.hpp"
#include "Space Objects/ObjectIcon.hpp"

#include "Modules/VisibleDataController.hpp"
#include "Modules/TimeController.hpp"
#include "Modules/ObjectController.hpp"
#include "Modules/ObjectSelectionPanel.hpp"
#include "Modules/StateControlPanel.hpp"
#include "Modules/Collider.hpp"
#include "Modules/SaveController.hpp"

#include "Overlays/ObjectLibraryOverlay.hpp"
#include "Overlays/SimParamsOverlay.hpp"
#include "Overlays/SettingsOverlay.hpp"
#include "Overlays/SimSavingOverlay.hpp"
#include "Overlays/SimLoadingOverlay.hpp"
#include "Overlays/WarningOverlay.hpp"
#include "Overlays/HelpOverlay.hpp"
#include "Overlays/EquasionSelectionOverlay.hpp"

//#include "Overlays/QuitOverlay.hpp"

class StateControlPanel;




class SimulationState :
    public State
{
public:

    SimulationState(sf::RenderWindow* sf_window, sf::View* sf_view, const std::string& simulation_name);
    virtual ~SimulationState();

    void InitState();
    void InitSpaceObjects();
    void InitBackground();
    void InitTopGUI();
    void InitObjDataGUI();
    void InitTimeGUI();

    void reloadState();


    void updateEvents(const MousePosition& mousePosition, float dt);
    //void updateBackgrounds(const MousePosition& mousePosition, float dt);
    //void updateTopGuiEvents(const MousePosition& mousePosition, float dt);
    //void updateObjDataEvents(const MousePosition& mousePosition, float dt);
    //void updateTimeGUiEvents(const MousePosition& mousePosition, float dt);

    void updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event);
    //void updateSpaceObjectPollEvents(const MousePosition& mousePosition, float dt, sf::Event& event);
    //void updateTopPollEvents(const MousePosition& mousePosition, float dt, sf::Event& event);
    //void updateODataPollEvents(const MousePosition& mousePosition, float dt, sf::Event& event);
    //void updateTimePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event);


    void renderBackground();
    void renderByView();
    void renderByWindow();

private:

    std::string m_simulation_name;

    STATE m_next_state;

    sf::Clock m_outro_clock;
    float m_outro_time;

    ke::HoldView m_view_holding;

    // simulation behaiour

    float m_deltaTime;

    bool m_running;
    unsigned int m_time_scale;
    float m_simulation_speed;

    long double m_space_scale;
    long double m_star_scale;
    long double m_planet_scale;
    float m_shader_scale;
    float m_brightness_scale;
    

    bool m_text_entered;
    bool m_object_buffer_ready; // variable that checks if object added from ObjectLibraryOverlay is loaded

    bool m_center_view_to_center_of_mass;


    std::list<SpaceObject*> m_onScreen; // currently visible objects


    // MODULES

    VisibleDataController m_VDController;
    TimeController m_TimeController;
    ObjectController m_ObjController;
    ObjectSelectionPanel m_objIconPanel;
    StateControlPanel m_StateControlPanel;
    Collider m_collider;
    SaveController m_saveController;


    // EXTERNAL WINDOWS

    DetailedDataWindow detailedDataWindow; // don't touch anything related to that (please)


    // state holders & overlays

    std::unique_ptr<QuitOverlay> m_quitOverlay;
    std::unique_ptr<SimSavingOverlay> m_simSavingOverlay;
    std::unique_ptr<SimLoadingOverlay> m_simLoadingOverlay;
    std::unique_ptr<WarningOverlay> m_new_simulation_warning;
    std::unique_ptr<HelpOverlay> m_helpOverlay;
    std::unique_ptr<EquasionSelectionOverlay> m_equasionSelectionOverlay;
    ObjectLibraryOverlay m_ObjectLibraryOverlay;
    SimParamsOverlay m_SimParamsOverlay;
    SettingsOverlay m_SettingsOverlay;
    //LoadingBarOverlay m_ladingBarOverlay;




    // EXTERNAL CLASSES


    // simulation objects

    std::vector<std::unique_ptr<SpaceObject>> m_objects;
    std::vector<std::unique_ptr<SpaceObject>>::iterator m_selected_object;

    ObjectBuffer m_objectBuffer;

    // background and masks

    ke::Button m_stateBackground;
    ke::Rectangle m_backgroundMask;
    ke::Rectangle m_stateMask;
    ke::Colorf m_sm_color; // state mask color

    ke::Rectangle m_overlayMask;
    ke::Colorf m_om_color; // overlay mask color

    ke::Rectangle m_shaderMask;

    std::vector<std::unique_ptr<ke::Rectangle>> m_backgrounds;
    std::array<ke::Colorf, 12> m_backgrounds_colors;


    // top GUI

    std::vector<std::unique_ptr<ke::Button>> m_project_menagers;
    std::vector<std::unique_ptr<ke::Button>> m_state_controllers;
    std::vector<std::unique_ptr<ke::Button>> m_tools;

    std::vector<std::unique_ptr<ke::Button>> m_iconUI; // object icons gui
    std::vector<std::unique_ptr<ObjectIcon>> m_object_icons;
    std::vector<std::unique_ptr<ObjectIcon>>::iterator m_icon_inv_iterator;
    std::vector<std::unique_ptr<ObjectIcon>>::iterator m_icon_iterator;

    ke::Circle m_placed_object; // space object that is currenly beeing placed by user

    ke::Button m_equasionSelector;

    // Obj data GUI

    ke::InputButton m_object_name;

    std::vector<std::unique_ptr<ke::Button>> m_symbols;
    std::unordered_map<std::string, std::unique_ptr<ke::InputButton>> m_values;
    std::vector<std::unique_ptr<ke::Button>> m_units;

    std::vector<std::unique_ptr<ke::Button>> m_modifiers;


    // time GUI

    std::vector<std::unique_ptr<ke::Button>> m_time_menagers;
    sf::Texture m_play_texture;
    sf::Texture m_pause_texture;

    std::array<ke::Colorf, 12> m_timeGuiColors;
    std::array<ke::Colorf, 12> m_otherTopPanelColors;
                                     
    // object GUI

    ke::Circle m_orbit_preview;
    ke::Rectangle m_distance_preview;

    // threads

    std::vector<std::future<void>> m_filteringThreads; // don't use it
    std::future<void> m_DetailedDataWindwThread;
};