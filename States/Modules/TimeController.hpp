#pragma once


#include "States/State.hpp"

#include "Space Objects/Planet.hpp"
#include "Space Objects/Star.hpp"
#include "Space Objects/CenterOfMass.hpp"
#include "Space Objects/ObjectIcon.hpp"
#include "Equasions/Equasions.hpp"
#include "Equasions/Constants.hpp"


class TimeController
{
public:

	TimeController();
	virtual ~TimeController();

	void assign(std::vector<std::unique_ptr<ke::Button>>* time_menagers);

	void resume(bool &running_status, sf::Texture* play_texture = nullptr);
	void stop(bool &running_status, sf::Texture* pause_texture = nullptr);

	void speedUp(float &sim_speed, float mult_Time_by);
	void slowDown(float &sim_speed, float div_Time_by);


private:

	std::vector<std::unique_ptr<ke::Button>>* m_time_menagers;

};