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
#include "component/textshape.h"
#include "component/rigidbody.h"

#include "component/gameplay/lifecontroller.h"
#include "component/gameplay/baseweapon.h"
#include "component/gameplay/shotgunweapon.h"

namespace Natorium
{

class Player : public Entity
{
public:
	Player()
		: Entity()
	{
		AddComponent<Transform>();
		SquareShape* shape = AddComponent<SquareShape>();
		AddComponent<CharacterController>();
		AddComponent<LifeController>();
		AddComponent<BaseWeapon>();
		AddComponent<ShotgunWeapon>();
		RigidBody* rigidbody = AddComponent<RigidBody>();
		AddComponent<Camera>();
		GLRender* render = AddComponent<GLRender>();
		render->m_type = Hash::Compute("monotexture");
		render->m_shapeType = Hash::Compute("SquareShape");
		rigidbody->m_shapeType = Hash::Compute("SquareShape");
	}




};



}