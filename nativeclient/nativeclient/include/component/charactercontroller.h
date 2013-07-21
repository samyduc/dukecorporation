#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"


#include <glm/glm.hpp>

namespace Natorium
{

class BaseWeapon;

static natU32 s_CharacterController = Hash::Compute("CharacterController");


class CharacterController : public Component
{
public:
					CharacterController();
	virtual			~CharacterController();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_CharacterController; }

	virtual void	Clone(Entity* _entity, natU32 _type) const;
	void			WriteData(Serializer& _ser);
	void			ReadData(Serializer& _ser);

	virtual void	LookAtScreen(glm::vec3& _look);

private:
	BaseWeapon*		m_currentWeapon;

};




}