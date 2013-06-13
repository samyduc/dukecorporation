#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#include <glm/glm.hpp>

namespace Natorium
{


class IWeapon
{

public:


	virtual void ShootAt(glm::vec3 _pos) = 0;





private:




};


}