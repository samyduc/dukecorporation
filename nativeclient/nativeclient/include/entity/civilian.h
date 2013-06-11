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

#include "component/gameplay/civilianai.h"

#include <glm/glm.hpp>

namespace Natorium
{

class Civilian : public Entity
{
public:
	Civilian()
		: Entity()
	{
		AddComponent<Transform>();
		AddComponent<GLRender>();
		AddComponent<Camera>();
		SquareShape *shape = AddComponent<SquareShape>();
		AddComponent<Camera>();
		AddComponent<CharacterController>();
		AddComponent<CivilianAI>();

		shape->SetColor(glm::vec4(0.f, 0.f, 1.f, 1.f));
	}




};



}