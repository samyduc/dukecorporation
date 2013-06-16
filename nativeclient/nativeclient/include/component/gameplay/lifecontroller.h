#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

namespace Natorium
{

static natU32 s_LifeController = Hash::Compute("s_LifeController");

class LifeController : public Component
{
public:
					LifeController();
	virtual			~LifeController();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_LifeController; }

	void			Clone(Entity* _entity) const;

	natBool			IsAlive() { return m_currentLife > 0; }
	virtual	void	TakeDamage(natS32 _damage);

public:
	natS32			m_life;

private:
	natS32			m_currentLife;
};




}