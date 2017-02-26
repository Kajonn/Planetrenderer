#include "heightmap.h"


heightmap::heightmap(void)
{

}


heightmap::~heightmap(void)
{
}


void heightmap::init(const std::vector<float> &heights_, int sizex_, int sizey_, float pointDist_) {
	//Copy the height map
	m_heights = heights_;
	//Set the distance between points in the map
	m_pointDist = pointDist_;
	m_xSize = sizex_;
	m_ySize = sizey_;
}


	//Get height by linear interpolation
float heightmap::getHeight(const glm::vec2 &pos_) {
	float xindf = pos_[0] / ((float)m_pointDist);
	float yindf = pos_[1] / ((float)m_pointDist);
	
	int xind = (int)xindf;
	int yind = (int)yindf;
	float xdif = xindf-xind;
	float ydif = yindf-yind;

	float xylow = getHeight(xind,yind);
	float xhigh = getHeight(xind+1,yind);
	float yhigh = getHeight(xind,yind+1);
	float xyhigh = getHeight(xind+1,yind+1);

	return ( (xyhigh * (xdif*ydif) ) + 
			 (yhigh * ((1.0f-xdif)*ydif)) +
			 (xylow * ((1.0f-xdif)*(1.0f-ydif))) +
			 (xhigh * (xdif*(1.0f-ydif))) );

}
