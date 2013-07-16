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
#include "component/gameplay/baseweapon.h"
#include "component/gameplay/shotgunweapon.h"

namespace Natorium
{

class Floor : public Entity
{
public:
	Floor()
		: Entity()
	{
		Transform* transform = AddComponent<Transform>();
		SquareShape *shape = AddComponent<SquareShape>();
		GLRender* render = AddComponent<GLRender>();
		render->m_type = Hash::Compute("monotexture");

		glm::vec2 size(50000.f, 50000.f);
		shape->m_size = size;
		shape->m_repeat = 50000.f / 1024.f;

		render->m_shapeType = Hash::Compute("s_SquareShape");
		transform->m_pos = glm::vec3(-1000.f, -1000.f, -1.f);
	}




};



}