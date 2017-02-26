#pragma once

#include <vector>
#include "glm.hpp"

class heightmap
{
public:
	heightmap(void);
	~heightmap(void);

	void init(const std::vector<float> &heights_, int sizex_, int sizey_, float diff_); 

	//Get height by interpolation
	float getHeight(const glm::vec2 &pos_);

private:
	//Hold height map data
	std::vector<float> m_heights;
	//Distance between points
	float m_pointDist;

	int m_xSize;

	int m_ySize;

	inline float getHeight(int x, int y);
};

inline float heightmap::getHeight(int x, int y) {	
	int xind = x%m_xSize;
	int yind = y%m_ySize;
	return m_heights[xind + m_xSize*yind];
}

