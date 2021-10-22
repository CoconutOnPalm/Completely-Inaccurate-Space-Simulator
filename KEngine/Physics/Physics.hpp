#pragma once

#include "../Objects/ObjectParent.hpp"
#include <map>
#include <cmath>

namespace ke
{

	class GuiObject; // pre-declared class



	////////////////////////////////////////////////////////////////



	/// <summary>
	/// Kengine Physics is a GuiObject component that can apply simple physics for it
	/// </summary>
	class Physics
	{
	public:

		
		/// <summary>
		/// Default Physics constructor
		/// </summary>
		Physics();


		////////////////////////////////


		/// <summary>
		/// Physics constructor
		/// </summary>
		/// <param name="object">GuiObject: Rectanlge, Circle, Button or Triangle</param>
		Physics(GuiObject* object);


		////////////////////////////////


		/// <summary>
		/// Physics constructor
		/// </summary>
		/// <param name="object">GuiObject: Rectanlge, Circle, Button or Triangle</param>
		/// <param name="mass">object mass</param>
		/// <param name="fricton">object friction (friction every frame))</param>
		Physics(
			GuiObject* object,
			long double mass,
			double fricton);


		////////////////////////////////


		/// <summary>
		/// Physics destructor
		/// </summary>
		~Physics();



		////////////////////////////////



		/// <summary>
		/// Sets object and adds physics to it
		/// </summary>
		/// <param name="object">GuiObject: Rectanlge, Circle, Button or Triangle</param>
		void setTarget(GuiObject* object);



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// Adds force to the object
		/// </summary>
		/// <param name="name">force name</param>
		/// <param name="newtons">force in 'newtons'</param>
		/// <param name="angle">force angle in degrees</param>
		void addForce(const std::string& name, double newtons, float angle);


		/// <summary>
		/// Adds force vector to the object
		/// </summary>
		/// <param name="name">force name</param>
		/// <param name="force">force in SFML Vector2</param>
		void addForce(const std::string& name, const sf::Vector2<double>& force);


		////////////////////////////////


		/// <summary>
		/// Modifies existing force
		/// </summary>
		/// <param name="name">force name</param>
		/// <param name="newtons">new force value in 'newtons'</param>
		/// <param name="angle">new force angle in degrees</param>
		/// <returns>force found - true</returns>
		bool modifyForce(const std::string& name, double newtons, float angle);


		/// <summary>
		/// Modifies existing force
		/// </summary>
		/// <param name="name">force name</param>
		/// <param name="force">new force value in SFML Vector2</param>
		/// <returns>force found - true</returns>
		bool modifyForce(const std::string& name, const sf::Vector2<double>& force);


		////////////////////////////////


		/// <summary>
		/// Removes force from object
		/// </summary>
		/// <param name="name">force name</param>
		/// <returns>if found and removed - true</returns>
		bool removeForce(const std::string& name);


		/// <summary>
		/// Removes all forces from the object
		/// </summary>
		void clearForces();


		////////////////////////////////


		/// <summary>
		/// returns force value in SFML Vector2
		/// </summary>
		/// <param name="name">force name</param>
		/// <returns>force value</returns>
		sf::Vector2<double> getForce(const std::string& name);


		////////////////////////////////


		/// <summary>
		/// returns force list
		/// </summary>
		/// <returns>force map[name, value]</returns>
		const std::map<std::string, sf::Vector2<double>>* getForceList() const;


		////////////////////////////////


		/// <summary>
		/// returns sum of all the forces
		/// </summary>
		/// <returns>all forces sum in SFML Vector2</returns>
		sf::Vector2<double> getTotalForce() const;



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// Adds force for one frame
		/// </summary>
		/// <param name="newtons">force in 'newtons'</param>
		/// <param name="angle">angle in degrees</param>
		void addMomentaryForce(double newtons, float angle);


		/// <summary>
		/// Adds force for one frame
		/// </summary>
		/// <param name="force">force value in SFML Vector2</param>
		void addMomentaryForce(const sf::Vector2<double>& force);


		////////////////////////////////


		/// <summary>
		/// checks if given force exists
		/// </summary>
		/// <param name="name">force name</param>
		/// <returns>exists - true</returns>
		bool findForce(const std::string& name) const;



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// Adds gravity to the object
		/// </summary>
		/// <param name="force">gravity force</param>
		/// <param name="angle">angle in degrees</param>
		void setGravity(double force, float angle = 270);


		/// <summary>
		/// Returns gravity value
		/// </summary>
		/// <returns>gravity value in SFML Vector2</returns>
		sf::Vector2<double> getGravityValue() const;


		/// <summary>
		/// Removes gravity from the object
		/// </summary>
		void removeGravity();



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// Sets object velocity
		/// </summary>
		/// <param name="px_per_frame">velocity</param>
		/// <param name="angle">angle in degrees</param>
		void setSpeed(double px_per_frame, float angle);


		/// <summary>
		/// Sets object velocity
		/// </summary>
		/// <param name="px_per_frame">velocity</param>
		void setSpeed(const sf::Vector2<double>& px_per_frame);


		/// <summary>
		/// Returns object velocity
		/// </summary>
		/// <returns>object velocity</returns>
		sf::Vector2<double> getSpeed() const;


		////////////////////////////////


		/// <summary>
		/// Stops object
		/// </summary>
		void stopObject();



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// Sets maximum object speed
		/// </summary>
		/// <param name="px_per_frame">velocity</param>
		void setMaxSpeed(sf::Vector2<double> px_per_frame);


		/// <summary>
		/// Returns object max speed
		/// </summary>
		/// <returns>max velcity</returns>
		sf::Vector2<double> getMaxSpeed() const;



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// Calculates object speed by its position on screen, use once in frame
		/// </summary>
		/// <param name="scale">movement scale</param>
		/// <param name="dt">delta time</param>
		/// <returns>calculated speed</returns>
		sf::Vector2f calculateSpeed(const float scale, const float dt);


		/// <summary>
		/// Returns latest calculated speed
		/// </summary>
		/// <returns>calculated speed</returns>
		sf::Vector2f getCalculatedSpeed() const;



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// Sets object mass
		/// </summary>
		/// <param name="mass"></param>
		void setMass(long double mass);


		/// <summary>
		/// Returns object mass
		/// </summary>
		/// <returns>object mass</returns>
		long double getMass() const;



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// Sets object friction
		/// </summary>
		/// <param name="fricton">-v per frame</param>
		void setFriction(float fricton);


		/// <summary>
		/// returns friction
		/// </summary>
		/// <returns>friction</returns>
		float getFriction() const;



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// updates physics
		/// </summary>
		/// <param name="dt">delta time</param>
		void update(const double dt);





	private:



		GuiObject* m_object;

		std::map<std::string, sf::Vector2<double>> m_forces;

		sf::Vector2<double>	m_speed;			// speed / velocity
		sf::Vector2<double>	m_total_force;		// sum of all forces
		sf::Vector2<double>	m_gravity;			// gravity
		long double			m_mass;				// mass
		double				m_friction;			// friction per frame
											
		sf::Vector2<double>	m_max_speed;		// maximum speed
											
		sf::Vector2f		m_last_position;	// last calculated position
		sf::Vector2f		m_calculated_speed;	// calculated speed
	};





	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





	/// <summary>
	/// checks if two rectangles are colliding
	/// </summary>
	/// <param name="object1">rectangle 1</param>
	/// <param name="object2">rectangle 2</param>
	/// <returns>if collidong - true</returns>
	bool areColliding_RectangleRectangle(GuiObject* object1, GuiObject* object2);



	/// <summary>
	/// checks if two circles are colliding
	/// </summary>
	/// <param name="object1">circle 1</param>
	/// <param name="object2">circle 2</param>
	/// <returns>if colligin - true</returns>
	bool areColliding_CircleCircle(GuiObject* object1, GuiObject* object2);


	/// <summary>
	/// checks if rectangle and circle are colliding
	/// </summary>
	/// <param name="rectangle">rectangular object</param>
	/// <param name="circle">circular object</param>
	/// <returns>if colliding - true</returns>
	bool areColliding_RectangleCircle(GuiObject* rectangle, GuiObject* circle);



	////////////////////////////////////////////////////////////////



	/// <summary>
	/// Enum used for specifying wall you want to collide with
	/// </summary>
	enum Walls { RIGHT, TOP, LEFT, BOTTOM };


	/// <summary>
	/// Makes object bouce from view
	/// </summary>
	/// <param name="wall">which wall you want to collide with</param>
	/// <param name="object">affected object</param>
	/// <param name="view">SFML view</param>
	/// <param name="energy_loss_prc">energy lost on collision</param>
	/// <returns>if colliding with view - true</returns>
	bool BounceFromView(int wall, GuiObject* object, sf::View* view, float energy_loss_prc = 0);


	////////////////////////////////


	/// <summary>
	/// Makes object bouce from stable object
	/// </summary>
	/// <param name="movable_object">moving object</param>
	/// <param name="stable_object">stable object</param>
	/// <param name="collision_mistake_tollerance">tollerance of collision (to avoid tunneling)</param>
	/// <param name="dt">delta time</param>
	/// <param name="energy_loss_prc">energy lost on collision</param>
	/// <param name="friction"></param>
	/// <returns>if colliding - ture</returns>
	bool BounceFromObject(GuiObject* movable_object, GuiObject* stable_object, float collision_mistake_tollerance, const float dt, float energy_loss_prc = 0.f, float friction = 0.f);


	////////////////////////////////


	/// <summary>
	/// Makes two rectangles colliding with each other
	/// </summary>
	/// <param name="rectangle1"></param>
	/// <param name="rectangle2"></param>
	/// <param name="dt">delta time</param>
	/// <param name="energy_loss_prc">energy lost on collision, recommended to set more than ~30</param>
	/// <param name="friction"></param>
	/// <returns>if colliding - true</returns>
	bool RectangleCollision(GuiObject* rectangle1, GuiObject* rectangle2, const float dt, float energy_loss_prc = 0.f, float friction = 0.f);

} // namespace ke