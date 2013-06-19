#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#include "component/gameplay/spawned.h"

#include <glm/glm.hpp>

#include <list>

namespace Natorium
{

static natU32 s_Spawner = Hash::Compute("s_Spawner");

class Spawner : public Component
{
public:

	friend class	Spawned;

					Spawner();
	virtual			~Spawner();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	virtual void	Clone(Entity* _entity) const;

	static natU32	GetType() { return s_Spawner; }

public:
	natU32			m_max;
	Entity*			m_refEntity;

protected:
	Entity*			Spawn();

	virtual void	OnKilled(Entity* _entity);

protected:
	typedef	std::list<Entity*> entities_spawner_t;
	entities_spawner_t	m_active_entities;
	entities_spawner_t	m_pool_entities;
	entities_spawner_t	m_kill_entities;
};




}