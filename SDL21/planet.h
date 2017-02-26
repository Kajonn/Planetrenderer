#pragma once

#include "heightmap.h"
#include "mesh.hpp"

namespace basegame {

class Planet
{
public:
	Planet(void);
	~Planet(void);

	void Planet::generate(float minRadius_, float maxSurfaceHeight_, int heightsamples_);

	//Get the mesh of the Planet
	//given a specific resolution(triangle size)
	std::shared_ptr<Mesh> getMesh(float res);

	//Get center of planet
	glm::vec3 getCenterPos();

	//Get position on surface
	glm::vec3 getSurfacePos(const glm::vec3 &pos_);

private:

	inline glm::vec3 sphericalToCartesian(float radius_, float phi_, float theta_);

	float generateHeight(const glm::vec3 &vec_, int octaves = 8, float lacunarity = 2.0, float gain = 0.5);

	//Height map for the surface
	heightmap m_heightmap;
	//Size at sea level
	float m_radius;

};

inline glm::vec3 Planet::sphericalToCartesian(float radius_, float phi_, float theta_) {
	return glm::vec3( radius_ * glm::cos(phi_) * glm::sin(theta_),
					  radius_ * glm::sin(phi_) * glm::sin(theta_),
					  radius_ * glm::cos(theta_) );
}

}
