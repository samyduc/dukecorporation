#pragma once

#include "base/natdef.h"
#include "base/entity.h"

#include "component/sdlmanager.h"

namespace Natorium
{

class Root : public Entity
{
public:
	Root()
		: Entity()
	{
		AddComponent<SDLManager>();
	}




};



}