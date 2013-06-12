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
#include "component/squareshape.h"
#include "component/gameplay/spawner.h"



namespace Natorium
{

class SpawnerCivilian : public Entity
{
public:
	SpawnerCivilian()
		: Entity()
	{
		AddComponent<Transform>();
		Spawner* spawner = AddComponent<Spawner>();
	}




};



}