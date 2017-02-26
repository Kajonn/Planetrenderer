#pragma once
#include "commonenums.hpp"
#include <memory>
#include "glm.hpp"
#include "gtx\quaternion.hpp"

namespace basegame {
	class Planet;
//represent something which moves on a planet.
class Actor
{
public:
	Actor(void);
	virtual ~Actor(void);
	//Sets the planet which this actors movement will use
	void setPlanet(Planet *planet_);

	//Updates position, but respects the limits of the planet
	void setPosition(const glm::vec3 &position_);

	//Move in the forward direction (local z)
	void moveForward(float dist_);

	//Rotate the actor
	void rotate(float yaw_, float pitch_);

	//When true, will limit motions to planet surface
	void setPlanetNoClip(bool flag_);

	//When true, will update position regarding to the planets "gravity", and keep the 
	//actor at the planet
	void setMoveToPlanet(bool flag_);

	//Update actor using the ms update
	void update(long time_);

private:
	//Current planet
	Planet * m_currentPlanet;
	//Current position
	glm::vec3 m_position;
	//Forward direction, for movement
	glm::vec3 m_forward;
	//Up direction
	glm::vec3 m_up;

	//
	float m_yaw;
	//
	float m_pitch;

	bool m_planetNoClip;

	bool m_moveToPlanet;

};

}