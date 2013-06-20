#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#include <glm/glm.hpp>


namespace Natorium
{

class Bullet;

static natU32 s_BulletController = Hash::Compute("s_BulletController");

class BulletController : public Component
{
public:
					BulletController();
	virtual			~BulletController();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_BulletController; }

	virtual void	Clone(Entity* _entity) const;

	void			OnEnterCollide(Contact* _contact);

public:
	natS32			m_damage;
	natU64			m_lifetime;

protected:
	natU64			m_time;


};




}