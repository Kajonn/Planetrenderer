#include "Planet.h"
#include "commonenums.hpp"
#include "gtx\noise.hpp"

using namespace basegame;

Planet::Planet(void) :
	m_heightmap(),
	m_radius(0)
{
}

Planet::~Planet(void)
{
}

void Planet::generate(float minRadius_, float maxSurfaceHeight_, int heightsamples_) {
	m_radius = minRadius_;
	std::vector<float> vec(heightsamples_*heightsamples_);
	std::srand(10);
	for (size_t i = 0; i < vec.size(); i++)
	{
		vec[i] = ((float)glm::simplex(glm::vec3()) / (float)RAND_MAX)*maxSurfaceHeight_;
	}
	//float diff = 4.0f*PI2_APROX*minRadius_*minRadius_/(float)(vec.size());// TODO calculate distance between samples
	m_heightmap.init(vec, heightsamples_, heightsamples_, PI_APROX*2.0f/(float)heightsamples_);
	
}

float Planet::generateHeight(const glm::vec3 &vec_, int octaves, float lacunarity, float gain)
{
    float amplitude = 1.0;
    float frequency = 1.0;
    float sum = 0.0;
    for(int i = 0; i < octaves; ++i)
    {
		sum += amplitude * glm::perlin(vec_*frequency);
        amplitude *= gain;
        frequency *= lacunarity;
    }
    return sum;
}

std::shared_ptr<Mesh> Planet::getMesh(float res) {
	std::shared_ptr<Mesh> mesh(new Mesh());
	
	
	//resolution is distance between the samples taken
	//
	float circumference = 2*PI_APROX*m_radius;
	float halfcirc = circumference*0.5f;
	int radialSteps = (int)(circumference/res); //Around the equator. 0 to pi*2
	int azimutSteps = (int)(halfcirc/res); //From north to south. 0 tp pi	 

	float radialStepSize = 2*PI_APROX/radialSteps; // to get correct size
	float azimutStepSize = PI_APROX/azimutSteps;

	std::vector<glm::vec3> verts;
	std::vector<glm::vec3> normals;
	std::vector<int> indices;
	//verts.reserve(radialSteps*azimutSteps);
	//get vertices
	int ind = 0;
	for (int j = 1; j < azimutSteps-1; j++)
	{
		for (int i = 0; i < radialSteps; i++)
		{						
			float rad = i*radialStepSize;
			float azim = j*azimutStepSize;
			float r = m_radius + generateHeight(sphericalToCartesian(1.0f, rad, azim), 8, 1.4f, 0.75f);
			
			verts.push_back(sphericalToCartesian(r, rad, azim));			
			if(j>1 && j<azimutSteps-1) { //Handle the polar caps seperatly 
				
				indices.push_back( ind );
				indices.push_back( i + (radialSteps*(j-2)) );

				if(i==0) 
					indices.push_back( radialSteps-1 + (radialSteps*(j-2)) );
				else 
					indices.push_back( (i-1) + (radialSteps*(j-2)) );

				indices.push_back( ind );
				indices.push_back( (i+1)%radialSteps + (radialSteps*(j-1)) );
				indices.push_back( i + (radialSteps*(j-2)) );
			}
			ind++;
		}
	}

	verts.push_back(sphericalToCartesian(m_radius + m_heightmap.getHeight(glm::vec2(0, 0)), 0, 0));
	verts.push_back(sphericalToCartesian(m_radius + m_heightmap.getHeight(glm::vec2(PI_APROX*2.0f, PI_APROX)), 0, PI_APROX));
	
	for (int i = 0; i < radialSteps; i++) {
		indices.push_back( verts.size()-2 );
		indices.push_back( i + radialSteps);
		indices.push_back( (i+1)%radialSteps + radialSteps);
	}
	for (int i = 0; i < radialSteps; i++) {
		indices.push_back( i + radialSteps*(azimutSteps-3));
		indices.push_back( verts.size()-1 );
		indices.push_back( (i+1)%radialSteps + radialSteps*(azimutSteps-3));
	}
	
	for (int j = 1; j < azimutSteps-1; j++)
	{
		for (int i = 0; i < radialSteps; i++)
		{	
			if(j>1 && j<azimutSteps-1) { //Handle the polar caps seperatly 
				glm::vec3 v0 = verts[ i + (radialSteps*(j-1)) ];
				glm::vec3 v1 = verts[ i + (radialSteps*(j-2)) ];
				glm::vec3 v2 = verts[ (i+1)%radialSteps + (radialSteps*(j-2)) ];
				glm::vec3 v3;
				if(i==0) 
					v3 = verts[ radialSteps-1 + (radialSteps*(j-2)) ];
				else 
					v3 = verts[ (i-1)%radialSteps + (radialSteps*(j-2)) ];

				glm::vec3 v4 = verts[ (i)%radialSteps + (radialSteps*(j)) ];

				normals.push_back( glm::normalize( glm::cross(v1-v0,v2-v0) + glm::cross(v0-v2,v0-v3) ));
			} else {
				normals.push_back(glm::vec3());
			}
		}
	}

	mesh->beginNewMesh(verts.size(), indices.size(), glm::vec4(0,0.2f,0.8f,1.0f));
	for (unsigned int i = 0; i < verts.size(); i++)
	{
		mesh->addVertex(verts[i].x,verts[i].y,verts[i].z,normals[i].x,normals[i].y,normals[i].z);
	}

	for (unsigned int i = 0; i < indices.size(); i++) {
		mesh->addIndex(indices[i]);
	}


	return mesh;
}



glm::vec3 Planet::getCenterPos() {
	return glm::vec3();
}

glm::vec3 Planet::getSurfacePos(const glm::vec3 &pos_) {
	//TODO move position to the surface
	return pos_;
}