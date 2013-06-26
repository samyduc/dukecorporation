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

#include "component/gameplay/aicontroller.h"
#include "component/gameplay/bulletcontroller.h"

#include <glm/glm.hpp>

namespace Natorium
{

class Bullet : public Entity
{
public:
	Bullet()
		: Entity()
	{
		AddComponent<Transform>();
		AddComponent<GLRender>();
		SquareShape *shape = AddComponent<SquareShape>();
		AddComponent<BulletController>();
		RigidBody* rigidbody = AddComponent<RigidBody>();

		glm::vec2 size(5.f, 5.f);
		glm::vec4 color(102.f, 0.f, 51.f, 1.f);
		shape->SetSize(size);
		shape->SetColor(color);

		rigidbody->m_density = 3.f;
	}




};



}