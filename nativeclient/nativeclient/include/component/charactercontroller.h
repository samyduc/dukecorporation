#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"


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

private:

};




}