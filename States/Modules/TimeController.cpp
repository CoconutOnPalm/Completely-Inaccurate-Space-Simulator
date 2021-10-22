#include "TimeController.hpp"

TimeController::TimeController() : m_time_menagers(nullptr) {}

TimeController::~TimeController() {}


void TimeController::assign(std::vector<std::unique_ptr<ke::Button>>* time_menagers)
{
	m_time_menagers = time_menagers;
}


void TimeController::resume(bool &running_status, sf::Texture* play_texture)
{
	running_status = true;
	m_time_menagers->at(1)->setTexture(play_texture);
}

void TimeController::stop(bool &running_status, sf::Texture* pause_texture)
{
	running_status = false;
	m_time_menagers->at(1)->setTexture(pause_texture);
}

void TimeController::speedUp(float& sim_speed, float mult_Time_by)
{
	sim_speed *= mult_Time_by;
	ke::varGuard(sim_speed, 0.125f, 8192.f);

	std::wstringstream wstream;

	if (sim_speed >= 1)
		wstream << std::setprecision(0) << std::fixed << sim_speed;
	else
		wstream << std::setprecision(3) << sim_speed;

	m_time_menagers->at(3)->setText(L"Time: \u00D7" + wstream.str());
}

void TimeController::slowDown(float& sim_speed, float div_Time_by)
{
	sim_speed /= div_Time_by;
	ke::varGuard(sim_speed, 0.125f, 8192.f);

	std::wstringstream wstream;

	if (sim_speed >= 1)
		wstream << std::setprecision(0) << std::fixed << sim_speed;
	else
		wstream << std::setprecision(3) << sim_speed;

	m_time_menagers->at(3)->setText(L"Time: \u00D7" + wstream.str());
}
