#pragma once

#include "base/natdef.h"
#include "base/entity.h"

#include "component/transform.h"
#include "component/sdlrender.h"

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
	}




};



}