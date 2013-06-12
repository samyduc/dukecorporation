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
					Spawner();
	virtual			~Spawner();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_Spawner; }

public:
	natU32			m_max;
	natU64			m_interval;

protected:
	void			Spawn();

private:
	natU64			m_currentInterval;
	size_t			m_cursor;

	typedef	std::list<Entity*> spawned_entities;
	spawned_entities	m_entities;

};




}