#pragma once

#include "KEngine/Algorithms/FileStream.hpp"

#include "States/State.hpp"

#include "States/Overlays/ObjectLibraryOverlay.hpp"

#include "Space Objects/Planet.hpp"
#include "Space Objects/Star.hpp"
#include "Space Objects/CenterOfMass.hpp"
#include "Space Objects/ObjectIcon.hpp"
#include "Space Objects/ObjectBuffer.hpp"
#include "Space Objects/ObjectBuffer.hpp"
#include "Equasions/Equasions.hpp"
#include "Equasions/Constants.hpp"

#include "States/Global/FileStorage.hpp"

#define iconUIvector std::vector<std::unique_ptr<ke::Button>>
#define iconvector std::vector<std::unique_ptr<ObjectIcon>>
#define filestorage FileStorage::Get()


class ObjectSelectionPanel
{
public:

	ObjectSelectionPanel();
	~ObjectSelectionPanel();

	void assign(iconUIvector* UI, iconvector* icons, ObjectLibraryOverlay* objectLibraryOverlay);

	void loadFromFile();
	void saveToFile();

	void loadStaticIcons(const std::string& layout_name);
	void setDefaultLayout();

	void pushIcon(const ObjectBuffer& buffer);

	void updatePollEvents(const sf::Vector2f& mousePosition, float dt, sf::Event& event);

	void updateColors(const sf::Vector2f& mousePosition, const float dt);

private:

	iconUIvector* m_iconUI;
	iconvector* m_object_icons;
	
	std::string m_layout_name; // bottom icons "layout"

	std::array<ke::Colorf, 33> m_icon_colors;

	iconvector::iterator fbegin;
	iconvector::iterator fend;
	iconvector::iterator sbegin;
	iconvector::iterator send;

	std::map<std::string, std::string>::iterator selected_layout;

	ObjectLibraryOverlay* m_objectLibraryOverlay;
};

