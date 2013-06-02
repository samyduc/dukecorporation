#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#include <glm/glm.hpp>

namespace Natorium
{

static natU32 s_CharacterController = Hash::Compute("s_CharacterController");

class CharacterController : public Component
{
public:
					CharacterController();
	virtual			~CharacterController();

	virtual void	OnInit();
	virtual void	OnTick(natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_CharacterController; }

	virtual void	LookAtScreen(glm::vec2& _look);
	virtual void	LookAtWorld(natF32 _x, natF32 _y, natF32 _z);

private:

};




}