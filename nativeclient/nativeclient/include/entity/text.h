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
#include "component/textshape.h"

#include "component/fontmanager.h"


#include <glm/glm.hpp>

namespace Natorium
{

class Text : public Entity
{
public:
	Text()
		: Entity()
	{
		AddComponent<Transform>();
		AddComponent<GLRender>();
		AddComponent<TextShape>();
	}




};



}