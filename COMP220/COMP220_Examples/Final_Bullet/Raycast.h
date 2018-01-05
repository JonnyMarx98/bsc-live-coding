#pragma once
#include "Camera.h"
#include <btBulletDynamicsCommon.h>

class Raycast
{
public:
	Raycast();
	~Raycast();

	// Sets ray position and checks for hit
	void update(Camera* camera, btDynamicsWorld* dynamicsWorld);
	void destroy();

private:
	// The ray start and end positions
	glm::vec4 rayStart;
	glm::vec4 rayEnd;
};