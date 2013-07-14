#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"


#include "component/gameplay/spawner.h"

#include <glm/glm.hpp>

#include <vector>

namespace Natorium
{

class Bullet;

static natU32 s_BaseWeapon = Hash::Compute("s_BaseWeapon");

class BaseWeapon : public Spawner
{
public:
					BaseWeapon();
	virtual			~BaseWeapon();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_BaseWeapon; }

	virtual void	Clone(Entity* _entity, natU32 _type) const;
	virtual void	WriteData(Serializer& _ser);
	virtual void	ReadData(Serializer& _ser);

	virtual void	ShootAt(glm::vec3 _pos);
	void			OnHit(Contact* _contact);

public:
	natU64			m_rateShot;

protected:
	natU64			m_acc;

	typedef std::vector<Bullet*> bullets_t;
	bullets_t m_bullets;

};




}