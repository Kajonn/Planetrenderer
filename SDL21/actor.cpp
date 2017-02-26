#include "actor.h"
#include "planet.h"
#include "glmutil.h"

using namespace basegame;

Actor::Actor(void)
{
}


Actor::~Actor(void)
{
}

void Actor::setPlanet(Planet *planet_) {
	m_currentPlanet = planet_;
}

void Actor::setPosition(const glm::vec3 &position_) {
	m_position = position_;
	//should limit to planet surface
}

void Actor::moveForward(float dist_) {
	//move position according to the orientation
	//also keep direction
	m_position += dist_ * m_forward;
}

void Actor::rotate(float yaw_, float pitch_) {
	//change yaw and pitch. These rotations are applied to forward and up

	//Yaw allways changes forward vector
	//store yaw_ value
	//set new forward by rotating around up
	//glm::quat yawrot = glm::angleAxis(yaw_, m_up);
	m_yaw += yaw_;
	m_forward = glm::angleAxis(m_yaw, m_up) * m_forward;
	
	//pitch does not change up 
	//store pitch value, may be used for camera
	m_pitch += pitch_;
}

void Actor::setPlanetNoClip(bool flag_) {
	m_planetNoClip = flag_;
}

void Actor::setMoveToPlanet(bool flag_) {
	m_moveToPlanet = flag_;
}

void Actor::update(long time_) {
	if(m_currentPlanet) {
		if(m_moveToPlanet) {
			glm::vec3 dist = m_position - m_currentPlanet->getCenterPos();
			glm::normalize(dist);

			m_position += dist*0.1f; ///XXX use update time etc
			
			glm::quat rot = RotationBetweenVectors(m_up, -dist);

			m_forward = rot * m_forward;
			m_up = rot * m_up;
		}

		if(!m_planetNoClip) {
			m_position = m_currentPlanet->getSurfacePos(m_position);
		}
	}
}

