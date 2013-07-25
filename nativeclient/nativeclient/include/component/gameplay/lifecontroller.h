#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

namespace Natorium
{

static natU32 s_LifeController = Hash::Compute("LifeController");

class LifeController : public Component
{
public:
					LifeController();
	virtual			~LifeController();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_LifeController; }

	virtual void	Clone(Entity* _entity, natU32 _type) const;
	void			WriteData(Serializer& _ser);
	void			ReadData(Serializer& _ser);

	natBool			IsAlive() { return m_currentLife > 0; }
	virtual	void	TakeDamage(natS32 _damage);

public:
	natS32			m_life;
	ref_t			m_smallDamageTexture;
	ref_t			m_BigDamageTexture;

private:
	natS32			m_currentLife;
};




}