#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#include <glm/glm.hpp>

#include <list>

namespace Natorium
{

static natU32 s_Spawner = Hash::Compute("s_Spawner");

class Spawner : public Component
{
public:

	friend class AiController;

					Spawner();
	virtual			~Spawner();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	virtual void	Clone(Entity* _entity) const;

	static natU32	GetType() { return s_Spawner; }

public:
	natU32			m_max;
	natU64			m_interval;

	Entity*			m_refEntity;

protected:
	void			Spawn();

	virtual void	OnKilled(Entity* _entity);

private:
	natU64			m_currentInterval;
	size_t			m_cursor;

	typedef	std::list<Entity*> entities_spawner_t;
	entities_spawner_t	m_active_entities;
	entities_spawner_t	m_pool_entities;
	entities_spawner_t	m_kill_entities;
};




}