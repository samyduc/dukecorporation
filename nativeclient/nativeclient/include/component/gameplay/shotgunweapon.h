#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#include "component/gameplay/baseweapon.h"

#include <glm/glm.hpp>


namespace Natorium
{

class Bullet;

static natU32 s_ShotgunWeapon = Hash::Compute("ShotgunWeapon");

class ShotgunWeapon : public BaseWeapon
{
public:
					ShotgunWeapon();
	virtual			~ShotgunWeapon();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_ShotgunWeapon; }

	virtual void	Clone(Entity* _entity, natU32 _type) const;
	void			WriteData(Serializer& _ser);
	void			ReadData(Serializer& _ser);

	virtual void	ShootAt(glm::vec3 _pos);

public:
	natF32			m_radius;
	natU64			m_bullets;

protected:




};




}