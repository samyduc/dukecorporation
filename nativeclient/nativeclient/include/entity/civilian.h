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
#include "component/rigidbody.h"

#include "component/gameplay/lifecontroller.h"
#include "component/gameplay/aicontroller.h"


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
		//AddComponent<CharacterController>();
		AddComponent<AiController>();
		AddComponent<LifeController>();
		AddComponent<RigidBody>();

		glm::vec4 color(0.f, 0.f, 1.f, 1.f);
		shape->SetColor(color);
	}




};



}