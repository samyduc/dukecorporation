#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"


namespace Natorium
{

class Spawner;

static natU32 s_Spawned = Hash::Compute("s_Spawned");

class Spawned : public Component
{
public:
					Spawned();
	virtual			~Spawned();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	virtual void	Clone(Entity* _entity) const;

	static natU32	GetType() { return s_Spawned; }

	void			Kill();
	Entity*			GetSpawner() { return m_spawner; }

public:
	Entity*			m_spawner;


};








}