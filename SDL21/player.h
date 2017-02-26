#pragma once
#include "actor.h"
#include "camera.h"

namespace basegame {

class Player :
	public Actor
{
public:
	Player(void);
	~Player(void);

private:

	CameraPtr m_camera;
	
};

}