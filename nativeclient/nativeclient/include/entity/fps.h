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
		TextShape* textShape = AddComponent<TextShape>();
		AddComponent<FPSCounter>();
		UI* ui = AddComponent<UI>();
		ui->m_pos = glm::vec2(0.940f, 0.01f);
		GLRender* render = AddComponent<GLRender>();
		render->m_type = Hash::Compute("monotexture");
		render->m_shapeType = Hash::Compute("TextShape");
	}




};



}