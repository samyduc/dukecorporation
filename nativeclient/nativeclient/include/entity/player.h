#pragma once

#include "base/natdef.h"
#include "base/entity.h"

#include "component/transform.h"
#include "component/sdlrender.h"
#include "component/sdlinput.h"
#include "component/charactercontroller.h"

namespace Natorium
{

class Player : public Entity
{
public:
	Player()
		: Entity()
	{
		AddComponent<Transform>();
		AddComponent<SDLRender>();
		AddComponent<SDLInput>();
		AddComponent<CharacterController>();

		SDLInput* input = GetComponent<SDLInput>();
	}




};



}