#pragma once

#include "base/natdef.h"
#include "base/entity.h"

#include "component/transform.h"
#include "component/glrender.h"
#include "component/sdlrender.h"
#include "component/sdlinput.h"
#include "component/camera.h"
#include "component/charactercontroller.h"
#include "component/glmanager.h"

namespace Natorium
{

class Player : public Entity
{
public:
	Player()
		: Entity()
	{
		AddComponent<Transform>();
		AddComponent<GLRender>();
		AddComponent<Camera>();
		AddComponent<CharacterController>();

	}




};



}