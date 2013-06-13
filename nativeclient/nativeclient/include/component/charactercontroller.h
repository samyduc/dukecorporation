#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"


#include <glm/glm.hpp>

namespace Natorium
{

static natU32 s_CharacterController = Hash::Compute("s_CharacterController");


class IWeapon;

class CharacterController : public Component
{
public:
					CharacterController();
	virtual			~CharacterController();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_CharacterController; }

	virtual void	LookAtScreen(glm::vec3& _look);

private:
	IWeapon*		m_currentWeapon;

};




}