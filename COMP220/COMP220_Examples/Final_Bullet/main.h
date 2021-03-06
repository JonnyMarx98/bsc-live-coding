#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>

#include "vertex.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"

#include "GameObject.h"
//#include "Camera.h"
#include "Raycast.h"


using namespace glm;