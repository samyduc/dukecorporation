#pragma once

#include "base/natdef.h"
#include "base/entity.h"

#include "component/sdlmanager.h"
#include "component/scenemanager.h"

namespace Natorium
{

class Root : public Entity
{
public:
	Root()
		: Entity()
	{
		//AddComponent<SDLManager>();
		//AddComponent<SceneManager>();
	}




};



}