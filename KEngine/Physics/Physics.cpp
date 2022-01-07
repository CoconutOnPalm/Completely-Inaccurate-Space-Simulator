#include "Physics.hpp"

namespace ke
{

	Physics::Physics()
		: m_object(nullptr)
		, m_speed(0, 0)
		, m_total_force(0, 0)
		, m_gravity(0, 0)
		, m_mass(1)
		, m_friction(0.f)
		, m_max_speed(299'792'458, 299'792'458)
		, m_last_position(0, 0)
		, m_calculated_speed(0, 0)
	{

	}


	////////////////////////////////


	Physics::Physics(GuiObject* object)
		: m_object(object)
		, m_speed(0, 0)
		, m_total_force(0, 0)
		, m_gravity(0, 0)
		, m_mass(1)
		, m_friction(0.f)
		, m_max_speed(299'792'458, 299'792'458)
		, m_calculated_speed(0, 0)
	{
		m_last_position = m_object->getShapeCenter();
	}


	////////////////////////////////


	Physics::Physics(
		GuiObject* object,
		long double mass,
		double friction)

		: m_object(object)
		, m_speed(0, 0)
		, m_total_force(0, 0)
		, m_gravity(0, 0)
		, m_mass(mass)
		, m_friction(friction)
		, m_max_speed(299'792'458, 299'792'458)
		, m_calculated_speed(0, 0)
	{
		m_last_position = m_object->getShapeCenter();

		if (m_mass == 0)
		{
			m_mass = Settings::MinimumAbsoluteMass();
			throw_error("Physics::Physics(...)", "mass cannot be 0", "WARNING");
		}
	}


	////////////////////////////////


	Physics::~Physics()
	{
		
	}



	////////////////////////////////



	void Physics::setTarget(GuiObject* object)
	{
		m_object = object;
		m_last_position = m_object->getShapeCenter();
	}



	////////////////////////////////////////////////////////////////



	void Physics::addForce(const std::string& name, double newtons, float angle)
	{
		float to_rad = angle * TO_RAD; // from degrees to radians

		m_forces[name] = sf::Vector2<double>(newtons * cos(to_rad), -newtons * sin(to_rad));
		m_total_force.x += newtons * cos(to_rad);
		m_total_force.y += -newtons * sin(to_rad);

		// to avoid float computatnion side effects
		//if (abs(m_total_force.x) < Settings::PhysicsAccuracy()) m_total_force.x = 0;
		//if (abs(m_total_force.y) < Settings::PhysicsAccuracy()) m_total_force.y = 0;
	}


	void Physics::addForce(const std::string& name, const sf::Vector2<double>& force)
	{
		m_forces[name] = force;
		m_total_force.x += force.x, 
		m_total_force.y += force.y;

		// to avoid float computatnion side effects
		//if (abs(m_total_force.x) < Settings::PhysicsAccuracy()) m_total_force.x = 0;
		//if (abs(m_total_force.y) < Settings::PhysicsAccuracy()) m_total_force.y = 0;
	}


	////////////////////////////////


	bool Physics::modifyForce(const std::string& name, double newtons, float angle)
	{
		std::map<std::string, sf::Vector2<double>>::iterator itr = m_forces.find(name);

		// if that force exists
		//if (itr != m_forces.end())
		{
			m_total_force -= itr->second;

			itr->second = sf::Vector2<double>(newtons * cos(angle * TO_RAD), -newtons * sin(angle * TO_RAD));

			m_total_force += itr->second;


			// to avoid float computatnion side effects
			//if (abs(m_total_force.x) < Settings::PhysicsAccuracy()) m_total_force.x = 0;
			//if (abs(m_total_force.y) < Settings::PhysicsAccuracy()) m_total_force.y = 0;

			return true;
		}
		//else
		{
			//throw_error("Physics::modifyForce(..)", "force not found", "WARNING");
			/*print_note("adding force form Physics::modifyForce(...)");
			this->addForce(name, newtons, angle);
			return false;*/
		}
	}


	bool Physics::modifyForce(const std::string& name, const sf::Vector2<double>& force)
	{
		std::map<std::string, sf::Vector2<double>>::iterator itr = m_forces.find(name);

		// if that force exists
		//if (itr != m_forces.end())
		{
			m_total_force -= (itr->second);
			m_total_force += force;

			itr->second = force;

			// to avoid float computatnion side effects
			//if (abs(m_total_force.x) < Settings::PhysicsAccuracy()) m_total_force.x = 0;
			//if (abs(m_total_force.y) < Settings::PhysicsAccuracy()) m_total_force.y = 0;

			return true;
		}
		//else
		{
			//	//throw_error("Physics::modifyForce(..)", "force not found", "WARNING");
			//	print_note("adding force form Physics::modifyForce(...)");
			//	this->addForce(name, force);
			//	return false;
			//
		}
	}


	////////////////////////////////


	bool Physics::removeForce(const std::string& name)
	{
		std::map<std::string, sf::Vector2<double>>::iterator itr = m_forces.find(name);

		// if that force exists
		if (itr != m_forces.end())
		{
			m_total_force -= itr->second;

			m_forces.erase(itr);

			return true;
		}
		else
		{
			throw_error("Physics::removeForce(..)", "force not found", "WARNING");
			return false;
		}
	}


	////////////////////////////////


	void Physics::clearForces()
	{
		m_total_force.x = 0;
		m_total_force.y = 0;

		m_forces.clear();
	}


	////////////////////////////////


	sf::Vector2<double> Physics::getForce(const std::string& name)
	{
		std::map<std::string, sf::Vector2<double>>::iterator itr = m_forces.find(name);

		if (itr != m_forces.end())
			return itr->second;
		else
			throw_error("Physics::getForce(..)", "force not found", "WARNING");
		return { 0, 0 };
	}


	////////////////////////////////


	const std::map<std::string, sf::Vector2<double>>* Physics::getForceList() const
	{
		return &m_forces;
	}


	////////////////////////////////


	sf::Vector2<double> Physics::getTotalForce() const
	{
		return m_total_force;
	}



	////////////////////////////////////////////////////////////////



	void Physics::addMomentaryForce(double newtons, float angle)
	{
		m_speed.x += newtons * cos(angle * TO_RAD);
		m_speed.y += -newtons * sin(angle * TO_RAD);
	}


	void Physics::addMomentaryForce(const sf::Vector2<double>& newtons)
	{
		m_speed += newtons;
	}



	////////////////////////////////////////////////////////////////



	bool Physics::findForce(const std::string& name) const
	{
		auto itr = m_forces.find(name);
		return itr != m_forces.end();
	}



	////////////////////////////////////////////////////////////////



	void Physics::setGravity(double force, float angle)
	{
		m_gravity = sf::Vector2<double>(force * cos(DTR(angle)), -force * sin(DTR(angle)));
	}


	sf::Vector2<double> Physics::getGravityValue() const
	{
		return m_gravity;
	}


	void Physics::removeGravity()
	{
		m_gravity = { 0, 0 };
	}



	////////////////////////////////////////////////////////////////



	void Physics::setSpeed(double px_per_frame, float angle)
	{
		m_speed.x = px_per_frame * cos(angle * TO_RAD);
		m_speed.y = -px_per_frame * sin(angle * TO_RAD);
	}


	void Physics::setSpeed(const sf::Vector2<double>& px_per_frame)
	{
		m_speed = px_per_frame;
	}


	sf::Vector2<double> Physics::getSpeed() const
	{
		return m_speed;
	}


	////////////////////////////////


	void Physics::stopObject()
	{
		m_speed = { 0, 0 };
	}



	////////////////////////////////////////////////////////////////



	void Physics::setMaxSpeed(sf::Vector2<double> px_per_frame)
	{
		m_max_speed = px_per_frame;
	}


	sf::Vector2<double> Physics::getMaxSpeed() const
	{
		return m_max_speed;
	}



	////////////////////////////////////////////////////////////////



	sf::Vector2f Physics::calculateSpeed(const float scale, const float dt) // use once in frame
	{
		sf::Vector2f temp((m_last_position.x - m_object->getShapeCenter().x), (m_last_position.y - m_object->getShapeCenter().y));
		m_last_position = m_object->getShapeCenter();
		m_calculated_speed = -temp;
		return -temp;
	}


	sf::Vector2f Physics::getCalculatedSpeed() const
	{
		return m_calculated_speed;
	}



	////////////////////////////////////////////////////////////////



	void Physics::setMass(long double mass)
	{
		m_mass = mass;

		if (m_mass == 0)
		{
			m_mass = Settings::MinimumAbsoluteMass();
			throw_error("Physics::Physics(...)", "m_mass cannot be 0 -> m_mass = 0.000001", "WARNING");
		}
	}


	long double Physics::getMass() const
	{
		return m_mass;
	}



	////////////////////////////////////////////////////////////////



	void Physics::setFriction(float friction)
	{
		m_friction = friction;
	}


	float Physics::getFriction() const
	{
		return m_friction;
	}



	////////////////////////////////////////////////////////////////



	void Physics::update(const double dt)
	{
		sf::Vector2<double> acceleration(m_total_force.x / m_mass + m_gravity.x, m_total_force.y / m_mass + m_gravity.y);

		if (m_max_speed.x < 299'792'458 || m_max_speed.y < 299'792'458)
		{
				m_speed += acceleration * dt;

				if (m_speed.x > 0 && m_speed.x - m_friction * dt > 0)
					m_speed.x -= m_friction * dt;
				else if (m_speed.x < 0 && m_speed.x + m_friction * dt < 0)
					m_speed.x += m_friction * dt;
				else
					m_speed.x = 0;

				if (m_speed.y > 0 && m_speed.y - m_friction * dt > 0)
					m_speed.y -= m_friction * dt;
				else if (m_speed.y < 0 && m_speed.y + m_friction * dt < 0)
					m_speed.y += m_friction * dt;
				else
					m_speed.y = 0;

				if (fabs(m_speed.x) < Settings::PhysicsAccuracy()) m_speed.x = Settings::PhysicsAccuracy();
				if (fabs(m_speed.y) < Settings::PhysicsAccuracy()) m_speed.y = Settings::PhysicsAccuracy();

				varGuard(m_speed.x, -m_max_speed.x, m_max_speed.x);
				varGuard(m_speed.y, -m_max_speed.y, m_max_speed.y);

				m_object->move(sf::Vector2f(m_speed * dt));
		}
		else
		{
			m_speed += acceleration * dt;

			if (m_speed.x > 0 && m_speed.x - m_friction * dt > 0)
				m_speed.x -= m_friction * dt;
			else if (m_speed.x < 0 && m_speed.x + m_friction * dt < 0)
				m_speed.x += m_friction * dt;
			else
				m_speed.x = 0;

			if (m_speed.y > 0 && m_speed.y - m_friction * dt > 0)
				m_speed.y -= m_friction * dt;
			else if (m_speed.y < 0 && m_speed.y + m_friction * dt < 0)
				m_speed.y += m_friction * dt;
			else
				m_speed.y = 0;


			if (fabs(m_speed.x * dt) < Settings::PhysicsAccuracy()) m_speed.x = Settings::PhysicsAccuracy();
			if (fabs(m_speed.y * dt) < Settings::PhysicsAccuracy()) m_speed.y = Settings::PhysicsAccuracy();


			m_object->move(sf::Vector2f(m_speed * dt));
		}
	}





	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





	bool areColliding_RectangleRectangle(GuiObject* object1, GuiObject* object2)
	{
		if (!object1->isActive() || !object2->isActive())
			return false;

		return
			((fabs(object1->getShapeCenter().x - object2->getShapeCenter().x) <= object1->getSize().x * object1->getScale().x * 0.5f + object2->getSize().x * object2->getScale().x * 0.5f &&
				fabs(object1->getShapeCenter().y - object2->getShapeCenter().y) <= object1->getSize().y * object1->getScale().y * 0.5f + object2->getSize().y * object2->getScale().y * 0.5f));
	}


	////////////////////////////////


	bool areColliding_CircleCircle(GuiObject* object1, GuiObject* object2)
	{
		if (!object1->isActive() || !object2->isActive())
			return false;
		return
			((object1->getSize().x * object1->getScale().x * 0.5f + object2->getSize().x * object2->getScale().x * 0.5f) * (object1->getSize().x * object1->getScale().x * 0.5f + object2->getSize().x * object2->getScale().x * 0.5f) >=
				(object2->getShapeCenter().x - object1->getShapeCenter().x) * (object2->getShapeCenter().x - object1->getShapeCenter().x) +
				(object2->getShapeCenter().y - object1->getShapeCenter().y) * (object2->getShapeCenter().y - object1->getShapeCenter().y));
		 // radius^2 >= (centre2 - centre1)^2
	}


	////////////////////////////////


	bool areColliding_RectangleCircle(GuiObject* rectangle, GuiObject* circle)
	{
		if (!rectangle->isActive() || !circle->isActive())
			return false;

		float rx = rectangle->getShapeCenter().x - rectangle->getSize().x * rectangle->getScale().x / 2;
		float ry = rectangle->getShapeCenter().y - rectangle->getSize().y * rectangle->getScale().y / 2;

		// temporary variables to set edges for testing
		float vtestX = circle->getShapeCenter().x;
		float vtestY = circle->getShapeCenter().y;

		// which edge is closest?
		if (circle->getShapeCenter().x < rx)
			vtestX = rx;      // test left edge
		else if (circle->getShapeCenter().x > rx + rectangle->getSize().x * rectangle->getScale().x)
			vtestX = rx + rectangle->getSize().x * rectangle->getScale().x;   // right edge
		if (circle->getShapeCenter().y < ry)
			vtestY = ry;      // top edge
		else if (circle->getShapeCenter().y > ry + rectangle->getSize().y * rectangle->getScale().x)
			vtestY = ry + rectangle->getSize().y * rectangle->getScale().y;   // bottom edge

		// get distance from closest edges
		//float distX = circle->getShapeCenter().x - vtestX;
		//float distY = circle->getShapeCenter().y - vtestY;
		float distance = sqrt(circle->getShapeCenter().x - vtestX * circle->getShapeCenter().x - vtestX + circle->getShapeCenter().y - vtestY * circle->getShapeCenter().y - vtestY);

		// if the distance is less than the radius, collision!
		return (distance <= circle->getSize().x * circle->getScale().x * 0.5f);
	}



	////////////////////////////////////////////////////////////////



	bool BounceFromView(int wall, GuiObject* object, sf::View* view, float energy_loss_prc)
	{
		if (!object->isActive())
			return false;

		//float width_half = object->getSize().x * object->getScale().x * 0.5f;
		//float height_half = object->getSize().y * object->getScale().y * 0.5f;

		switch (wall)
		{
		case RIGHT:
		{
			if (object->getShapeCenter().x + object->getSize().x * object->getScale().x * 0.5f > view->getCenter().x + view->getSize().x / 2)
			{
				object->setPositionByCenter(sf::Vector2f(view->getCenter().x + view->getSize().x / 2 - object->getSize().x * object->getScale().x * 0.5f, object->getShapeCenter().y));
				object->physics()->setSpeed(sf::Vector2<double>(-object->physics()->getSpeed().x * ((100 - energy_loss_prc) / 100), object->physics()->getSpeed().y));
				return true;
			}
		}
		break;

		case TOP:
		{
			if (object->getShapeCenter().y - object->getSize().y * object->getScale().y * 0.5f < view->getCenter().y - view->getSize().y / 2)
			{
				object->setPositionByCenter(sf::Vector2f(object->getShapeCenter().x, view->getCenter().y - view->getSize().y / 2 + object->getSize().y * object->getScale().y * 0.5f));
				object->physics()->setSpeed(sf::Vector2<double>(object->physics()->getSpeed().x, -object->physics()->getSpeed().y * ((100 - energy_loss_prc) / 100)));
				return true;
			}
		}
		break;

		case LEFT:
		{
			if (object->getShapeCenter().x - object->getSize().x * object->getScale().x * 0.5f < view->getCenter().x - view->getSize().x / 2)
			{
				object->setPositionByCenter(sf::Vector2f(view->getCenter().x - view->getSize().x / 2 + object->getSize().x * object->getScale().x * 0.5f, object->getShapeCenter().y));
				object->physics()->setSpeed(sf::Vector2<double>(-object->physics()->getSpeed().x * ((100 - energy_loss_prc) / 100), object->physics()->getSpeed().y));
				return true;
			}
		}
		break;

		case BOTTOM:
		{
			if (object->getShapeCenter().y + object->getSize().y * object->getScale().y * 0.5f > view->getCenter().y + view->getSize().y / 2)
			{
				object->setPositionByCenter(sf::Vector2f(object->getShapeCenter().x, view->getCenter().y + view->getSize().y / 2 - object->getSize().y * object->getScale().y * 0.5f));
				object->physics()->setSpeed(sf::Vector2<double>(object->physics()->getSpeed().x, -object->physics()->getSpeed().y * ((100 - energy_loss_prc) / 100)));
				return true;
			}
		}
		break;

		default:
		{
			throw_error("ke::BounceFromView(...)", "wall is incorrect", "ERROR");
			return false;
		}
		}

		return false;
	}



	////////////////////////////////////////////////////////////////



	bool BounceFromObject(GuiObject* movable_object, GuiObject* stable_object, float collision_mistake_tollerance, const float dt, float energy_loss_prc, float friction)
	{
		if (!areColliding_RectangleRectangle(movable_object, stable_object))
			return false;

		float m_width_half = movable_object->getSize().x * movable_object->getScale().x * 0.5;
		float m_height_half = movable_object->getSize().y * movable_object->getScale().y * 0.5;

		float s_width_half = stable_object->getSize().x * stable_object->getScale().x * 0.5;
		float s_height_half = stable_object->getSize().y * stable_object->getScale().y * 0.5;

		float dist[] = { (fabs(stable_object->getShapeCenter().y - s_height_half - (movable_object->getShapeCenter().y + m_height_half))),
						 (fabs(stable_object->getShapeCenter().y + s_height_half - (movable_object->getShapeCenter().y - m_height_half))),
						 (fabs(stable_object->getShapeCenter().x + s_width_half - (movable_object->getShapeCenter().x - m_width_half))),
						 (fabs(stable_object->getShapeCenter().x - s_width_half - (movable_object->getShapeCenter().x + m_width_half))) };

		float closest_one = *std::min_element(dist, dist + 4);

		int which_wall = 4;

		for (int i = 0; i < 4; i++)
		{
			if (closest_one == dist[i])
			{
				which_wall = i;
				break;
			}
		}

		//if (closest_one > collision_mistake_tollerance && closest_one <= 1.0f)
		  //  return false;

		switch (which_wall)
		{
		case 0: // BOTTOM
		{
			if (closest_one <= collision_mistake_tollerance)
			{
				if (movable_object->physics()->getSpeed().x > 0 && movable_object->physics()->getSpeed().x - friction * dt > 0)
					movable_object->physics()->setSpeed(sf::Vector2<double>(movable_object->physics()->getSpeed().x - friction * dt, movable_object->physics()->getSpeed().y));
				else if (movable_object->physics()->getSpeed().x < 0 && movable_object->physics()->getSpeed().x + friction * dt < 0)
					movable_object->physics()->setSpeed(sf::Vector2<double>(movable_object->physics()->getSpeed().x + friction * dt, movable_object->physics()->getSpeed().y));
				else movable_object->physics()->setSpeed(sf::Vector2<double>(0, movable_object->physics()->getSpeed().y));

				movable_object->setPositionByCenter(sf::Vector2f(movable_object->getShapeCenter().x, stable_object->getShapeCenter().y - s_height_half - m_height_half));
				movable_object->physics()->setSpeed(sf::Vector2<double>(movable_object->physics()->getSpeed().x, -movable_object->physics()->getSpeed().y * ((100 - energy_loss_prc) * 0.01f)));

				return true;
			}
		}
		break;
		case 1: // TOP
		{
			if (closest_one <= collision_mistake_tollerance)
			{
				if (movable_object->physics()->getSpeed().x > 0 && movable_object->physics()->getSpeed().x - friction * dt > 0)
					movable_object->physics()->setSpeed(sf::Vector2<double>(movable_object->physics()->getSpeed().x - friction * dt, movable_object->physics()->getSpeed().y));
				else if (movable_object->physics()->getSpeed().x < 0 && movable_object->physics()->getSpeed().x + friction * dt < 0)
					movable_object->physics()->setSpeed(sf::Vector2<double>(movable_object->physics()->getSpeed().x + friction * dt, movable_object->physics()->getSpeed().y));
				else movable_object->physics()->setSpeed(sf::Vector2<double>(0, movable_object->physics()->getSpeed().y));

				movable_object->setPositionByCenter(sf::Vector2f(movable_object->getShapeCenter().x, stable_object->getShapeCenter().y + s_height_half + m_height_half));
				movable_object->physics()->setSpeed(sf::Vector2<double>(movable_object->physics()->getSpeed().x, -movable_object->physics()->getSpeed().y * ((100 - energy_loss_prc) * 0.01f)));

				return true;
			}
		}
		break;

		case 2: // LEFT
		{
			if (closest_one <= collision_mistake_tollerance)
			{
				if (movable_object->physics()->getSpeed().y > 0 && movable_object->physics()->getSpeed().y - friction * dt > 0)
					movable_object->physics()->setSpeed(sf::Vector2<double>(movable_object->physics()->getSpeed().x, movable_object->physics()->getSpeed().y - friction * dt));
				else if (movable_object->physics()->getSpeed().y < 0 && movable_object->physics()->getSpeed().y + friction * dt < 0)
					movable_object->physics()->setSpeed(sf::Vector2<double>(movable_object->physics()->getSpeed().x, movable_object->physics()->getSpeed().y + friction * dt));
				else movable_object->physics()->setSpeed(sf::Vector2<double>(movable_object->physics()->getSpeed().x, 0));

				movable_object->setPositionByCenter(sf::Vector2f(stable_object->getShapeCenter().x + s_width_half + m_width_half, movable_object->getShapeCenter().y));
				movable_object->physics()->setSpeed(sf::Vector2<double>(-movable_object->physics()->getSpeed().x * ((100 - energy_loss_prc) * 0.01f), movable_object->physics()->getSpeed().y));

				return true;
			}
		}
		break;

		case 3: // RIGHT
		{
			if (closest_one <= collision_mistake_tollerance)
			{
				if (movable_object->physics()->getSpeed().y > 0 && movable_object->physics()->getSpeed().y - friction * dt > 0)
					movable_object->physics()->setSpeed(sf::Vector2<double>(movable_object->physics()->getSpeed().x, movable_object->physics()->getSpeed().y - friction * dt));
				else if (movable_object->physics()->getSpeed().y < 0 && movable_object->physics()->getSpeed().y + friction * dt < 0)
					movable_object->physics()->setSpeed(sf::Vector2<double>(movable_object->physics()->getSpeed().x, movable_object->physics()->getSpeed().y + friction * dt));
				else movable_object->physics()->setSpeed(sf::Vector2<double>(movable_object->physics()->getSpeed().x, 0));

				movable_object->setPositionByCenter(sf::Vector2f(stable_object->getShapeCenter().x - s_width_half - m_width_half, movable_object->getShapeCenter().y));
				movable_object->physics()->setSpeed(sf::Vector2<double>(-movable_object->physics()->getSpeed().x * ((100 - energy_loss_prc) * 0.01f), movable_object->physics()->getSpeed().y));

				return true;
			}
		}
		break;

		default:
			return false;
			break;
		}

		return true;
	}



	////////////////////////////////////////////////////////////////



	bool RectangleCollision(GuiObject* rectangle1, GuiObject* rectangle2, const float dt, float energy_loss_prc, float friction)
	{
		if (!areColliding_RectangleRectangle(rectangle1, rectangle2))
			return false;

		float m_width_half = rectangle1->getSize().x * rectangle1->getScale().x * 0.5;
		float m_height_half = rectangle1->getSize().y * rectangle1->getScale().y * 0.5;

		float s_width_half = rectangle2->getSize().x * rectangle2->getScale().x * 0.5;
		float s_height_half = rectangle2->getSize().y * rectangle2->getScale().y * 0.5;

		float dist[] = { (fabs(rectangle2->getShapeCenter().y - s_height_half - (rectangle1->getShapeCenter().y + m_height_half))),
						 (fabs(rectangle2->getShapeCenter().y + s_height_half - (rectangle1->getShapeCenter().y - m_height_half))),
						 (fabs(rectangle2->getShapeCenter().x + s_width_half - (rectangle1->getShapeCenter().x - m_width_half))),
						 (fabs(rectangle2->getShapeCenter().x - s_width_half - (rectangle1->getShapeCenter().x + m_width_half))) };

		float closest_one = *std::min_element(dist, dist + 4);

		int which_wall = 4;

		for (int i = 0; i < 4; i++)
		{
			if (closest_one == dist[i])
			{
				which_wall = i;
				break;
			}
		}


		// if you wanted more readable equasions
		//long double m1 = rectangle1->physics()->getMass();
		//long double m2 = rectangle2->physics()->getMass();
		
		//sf::Vector2f v1 = rectangle1->physics()->getSpeed();
		//sf::Vector2f v2 = rectangle2->physics()->getSpeed();


		switch (which_wall)
		{
		case 0: // BOTTOM
		{
			if (rectangle1->physics()->getSpeed().x > 0 && rectangle1->physics()->getSpeed().x - friction * dt > 0)
				rectangle1->physics()->setSpeed(sf::Vector2<double>(rectangle1->physics()->getSpeed().x - friction * dt, rectangle1->physics()->getSpeed().y));
			else if (rectangle1->physics()->getSpeed().x < 0 && rectangle1->physics()->getSpeed().x + friction * dt < 0)
				rectangle1->physics()->setSpeed(sf::Vector2<double>(rectangle1->physics()->getSpeed().x + friction * dt, rectangle1->physics()->getSpeed().y));
			else rectangle1->physics()->setSpeed(sf::Vector2<double>(0, rectangle1->physics()->getSpeed().y));

			rectangle1->setPositionByCenter(sf::Vector2f(rectangle1->getShapeCenter().x, rectangle2->getShapeCenter().y - (rectangle1->getSize().y * rectangle1->getScale().y + rectangle2->getSize().y * rectangle2->getScale().y) * 0.5f));
			rectangle1->physics()->setSpeed(sf::Vector2<double>(rectangle1->physics()->getSpeed().x, ((rectangle1->physics()->getMass() - rectangle2->physics()->getMass()) / (rectangle1->physics()->getMass() + rectangle2->physics()->getMass()) * rectangle1->physics()->getSpeed().y + (2 * rectangle2->physics()->getMass()) / (rectangle1->physics()->getMass() + rectangle2->physics()->getMass()) * rectangle2->physics()->getSpeed().y) * ((100 - energy_loss_prc) * 0.01)));
			rectangle2->physics()->setSpeed(sf::Vector2<double>(rectangle2->physics()->getSpeed().x, ((2 * rectangle1->physics()->getMass()) / (rectangle1->physics()->getMass() + rectangle2->physics()->getMass()) * rectangle1->physics()->getSpeed().y + (rectangle2->physics()->getMass() - rectangle1->physics()->getMass()) / (rectangle1->physics()->getMass() + rectangle2->physics()->getMass()) * rectangle2->physics()->getSpeed().y) * ((100 - energy_loss_prc) * 0.01)));
		}
		break;
		case 1: // TOP
		{
			if (rectangle1->physics()->getSpeed().x > 0 && rectangle1->physics()->getSpeed().x - friction * dt > 0)
				rectangle1->physics()->setSpeed(sf::Vector2<double>(rectangle1->physics()->getSpeed().x - friction * dt, rectangle1->physics()->getSpeed().y));
			else if (rectangle1->physics()->getSpeed().x < 0 && rectangle1->physics()->getSpeed().x + friction * dt < 0)
				rectangle1->physics()->setSpeed(sf::Vector2<double>(rectangle1->physics()->getSpeed().x + friction * dt, rectangle1->physics()->getSpeed().y));
			else rectangle1->physics()->setSpeed(sf::Vector2<double>(0, rectangle1->physics()->getSpeed().y));

			rectangle2->setPositionByCenter(sf::Vector2f(rectangle2->getShapeCenter().x, rectangle1->getShapeCenter().y - (rectangle1->getSize().y * rectangle1->getScale().y + rectangle2->getSize().y * rectangle2->getScale().y) * 0.5f));
			rectangle1->physics()->setSpeed(sf::Vector2<double>(rectangle1->physics()->getSpeed().x, ((rectangle1->physics()->getMass() - rectangle2->physics()->getMass()) / (rectangle1->physics()->getMass() + rectangle2->physics()->getMass()) * rectangle1->physics()->getSpeed().y + (2 * rectangle2->physics()->getMass()) / (rectangle1->physics()->getMass() + rectangle2->physics()->getMass()) * rectangle2->physics()->getSpeed().y) * ((100 - energy_loss_prc) * 0.01)));
			rectangle2->physics()->setSpeed(sf::Vector2<double>(rectangle2->physics()->getSpeed().x, ((2 * rectangle1->physics()->getMass()) / (rectangle1->physics()->getMass() + rectangle2->physics()->getMass()) * rectangle1->physics()->getSpeed().y + (rectangle2->physics()->getMass() - rectangle1->physics()->getMass()) / (rectangle1->physics()->getMass() + rectangle2->physics()->getMass()) * rectangle2->physics()->getSpeed().y) * ((100 - energy_loss_prc) * 0.01)));
		}
		break;

		case 2: // LEFT
		{
			if (rectangle1->physics()->getSpeed().x > 0 && rectangle1->physics()->getSpeed().x - friction * dt > 0)
				rectangle1->physics()->setSpeed(sf::Vector2<double>(rectangle1->physics()->getSpeed().x - friction * dt, rectangle1->physics()->getSpeed().y));
			else if (rectangle1->physics()->getSpeed().x < 0 && rectangle1->physics()->getSpeed().x + friction * dt < 0)
				rectangle1->physics()->setSpeed(sf::Vector2<double>(rectangle1->physics()->getSpeed().x + friction * dt, rectangle1->physics()->getSpeed().y));
			else rectangle1->physics()->setSpeed(sf::Vector2<double>(0, rectangle1->physics()->getSpeed().y));

			rectangle2->setPositionByCenter(sf::Vector2f(rectangle1->getShapeCenter().x - (rectangle1->getSize().x * rectangle1->getScale().x + rectangle2->getSize().x * rectangle2->getScale().x) * 0.5f, rectangle2->getShapeCenter().y));
			rectangle1->physics()->setSpeed(sf::Vector2<double>(((rectangle1->physics()->getMass() - rectangle2->physics()->getMass()) / (rectangle1->physics()->getMass() + rectangle2->physics()->getMass()) * rectangle1->physics()->getSpeed().x + (2 * rectangle2->physics()->getMass()) / (rectangle1->physics()->getMass() + rectangle2->physics()->getMass()) * rectangle2->physics()->getSpeed().x) * ((100 - energy_loss_prc) * 0.01), rectangle2->physics()->getSpeed().y));
			rectangle2->physics()->setSpeed(sf::Vector2<double>(((2 * rectangle1->physics()->getMass()) / (rectangle1->physics()->getMass() + rectangle2->physics()->getMass()) * rectangle1->physics()->getSpeed().x + (rectangle2->physics()->getMass() - rectangle1->physics()->getMass()) / (rectangle1->physics()->getMass() + rectangle2->physics()->getMass()) * rectangle2->physics()->getSpeed().x) * ((100 - energy_loss_prc) * 0.01), rectangle2->physics()->getSpeed().y));
		}
		break;

		case 3: // RIGHT
		{
			if (rectangle1->physics()->getSpeed().y > 0 && rectangle1->physics()->getSpeed().y - friction * dt > 0)
				rectangle1->physics()->setSpeed(sf::Vector2<double>(rectangle1->physics()->getSpeed().x, rectangle1->physics()->getSpeed().y - friction * dt));
			else if (rectangle1->physics()->getSpeed().y < 0 && rectangle1->physics()->getSpeed().y + friction * dt < 0)
				rectangle1->physics()->setSpeed(sf::Vector2<double>(rectangle1->physics()->getSpeed().x, rectangle1->physics()->getSpeed().y + friction * dt));
			else rectangle1->physics()->setSpeed(sf::Vector2<double>(rectangle1->physics()->getSpeed().x, 0));

			rectangle2->setPositionByCenter(sf::Vector2f(rectangle1->getShapeCenter().x + (rectangle1->getSize().x * rectangle1->getScale().x + rectangle2->getSize().x * rectangle2->getScale().x) * 0.5f, rectangle2->getShapeCenter().y));
			rectangle1->physics()->setSpeed(sf::Vector2<double>(((rectangle1->physics()->getMass() - rectangle2->physics()->getMass()) / (rectangle1->physics()->getMass() + rectangle2->physics()->getMass()) * rectangle1->physics()->getSpeed().x + (2 * rectangle2->physics()->getMass()) / (rectangle1->physics()->getMass() + rectangle2->physics()->getMass()) * rectangle2->physics()->getSpeed().x) * ((100 - energy_loss_prc) * 0.01), rectangle2->physics()->getSpeed().y));
			rectangle2->physics()->setSpeed(sf::Vector2<double>(((2 * rectangle1->physics()->getMass()) / (rectangle1->physics()->getMass() + rectangle2->physics()->getMass()) * rectangle1->physics()->getSpeed().x + (rectangle2->physics()->getMass() - rectangle1->physics()->getMass()) / (rectangle1->physics()->getMass() + rectangle2->physics()->getMass()) * rectangle2->physics()->getSpeed().x) * ((100 - energy_loss_prc) * 0.01), rectangle2->physics()->getSpeed().y));
		}
		break;

		default:
			return false;
			break;
		}
	}

	sf::Vector2f getCircleCollisionPoint(GuiObject* circle1, GuiObject* circle2, const float dt)
	{
		float radius_1 = circle1->getSize().x * 0.5;
		float radius_2 = circle2->getSize().x * 0.5;

		return sf::Vector2f(
			(circle1->getShapeCenter().x * radius_2 + circle2->getShapeCenter().x * radius_1) / (radius_1 + radius_2),
			(circle1->getShapeCenter().y * radius_2 + circle2->getShapeCenter().y * radius_1) / (radius_1 + radius_2));
	}

	bool CircleCollision(GuiObject* circle1, GuiObject* circle2, const float dt, float energy_loss_prc, float friction)
	{
		// I'm too dumb to figure it out myself, here's my 'inspiration':
		// https://gamedevelopment.tutsplus.com/tutorials/when-worlds-collide-simulating-circle-circle-collisions--gamedev-769

		//if (areColliding_CircleCircle(circle1, circle2))
		{
			/*sf::Vector2<double> new_speed_1(
				circle1->physics()->getSpeed().x * (circle1->physics()->getMass() - circle2->physics()->getMass()) + (2 * circle2->physics()->getMass() * circle2->physics()->getSpeed().x) / (circle1->physics()->getMass() + circle2->physics()->getMass()),
				circle1->physics()->getSpeed().y * (circle1->physics()->getMass() - circle2->physics()->getMass()) - (2 * circle2->physics()->getMass() * circle2->physics()->getSpeed().y) / (circle1->physics()->getMass() + circle2->physics()->getMass()));

			sf::Vector2<double> new_speed_2(
				circle2->physics()->getSpeed().x * (circle2->physics()->getMass() - circle1->physics()->getMass()) + (2 * circle1->physics()->getMass() * circle1->physics()->getSpeed().x) / (circle1->physics()->getMass() + circle2->physics()->getMass()),
				circle2->physics()->getSpeed().y * (circle2->physics()->getMass() - circle1->physics()->getMass()) - (2 * circle1->physics()->getMass() * circle1->physics()->getSpeed().y) / (circle1->physics()->getMass() + circle2->physics()->getMass()));

			circle1->physics()->setSpeed(circle1->physics()->getSpeed() + new_speed_1);
			circle2->physics()->setSpeed(circle2->physics()->getSpeed() + new_speed_2);

			return true;*/


		}

		return false;
	}

} // namespace ke