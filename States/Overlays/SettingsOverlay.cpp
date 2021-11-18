//#include "SimParamsOverlay.hpp"
//
//SimParamsOverlay::SimParamsOverlay()
//	: m_active(false)
//	, m_quitCode(OverlayQuitCode::NOT_QUITTING)
//{
//
//}
//
//SimParamsOverlay::~SimParamsOverlay()
//{
//
//}
//
//void SimParamsOverlay::assign(sf::RenderWindow* window)
//{
//	m_window = window;
//}
//
//void SimParamsOverlay::initUI()
//{
//	
//}
//
//
//void SimParamsOverlay::updateEvents(const MousePosition& mousePosition, float dt)
//{
//	
//}
//
//void SimParamsOverlay::updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event)
//{
//	
//}
//
//void SimParamsOverlay::updateColors(const sf::Vector2f& mousePosition, const float dt)
//{
//	
//}
//
//OverlayQuitCode SimParamsOverlay::quitStatus() const
//{
//	return m_quitCode;
//}
//
//void SimParamsOverlay::resetQuitStatus()
//{
//	m_quitCode = OverlayQuitCode::NOT_QUITTING;
//}
//
//void SimParamsOverlay::render()
//{
//	if (!m_active)
//		return;
//
//	m_background.render(m_window);
//}
//
//bool SimParamsOverlay::active() const
//{
//	return m_active;
//}
//
//void SimParamsOverlay::activate()
//{
//	m_quitCode = OverlayQuitCode::NOT_QUITTING;
//
//	m_active = true;
//}
//
//void SimParamsOverlay::deactivate()
//{
//	m_active = false;
//}
//
//
//void SimParamsOverlay::saveSettings()
//{
//
//}