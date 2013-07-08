#pragma once

#include "base/natdef.h"
#include "base/entity.h"

#include "component/transform.h"
#include "component/glrender.h"
#include "component/ui.h"
#include "component/textshape.h"

#include "component/ui/fpscounter.h"

namespace Natorium
{

class FPS : public Entity
{
public:
	FPS()
		: Entity()
	{
		AddComponent<Transform>();
		AddComponent<TextShape>();
		AddComponent<FPSCounter>();
		//AddComponent<UI>();
		GLRender* render = AddComponent<GLRender>();
		render->m_type = Hash::Compute("monotexture");
	}




};



}