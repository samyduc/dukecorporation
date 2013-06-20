#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#include "component/gameplay/spawner.h"

#include <glm/glm.hpp>

namespace Natorium
{

//static natU32 s_TimeSpawner = Hash::Compute("s_TimeSpawner");
extern natU32 s_Spawner;

class TimeSpawner : public Spawner
{
public:
	friend class AiController;

					TimeSpawner();
	virtual			~TimeSpawner();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);

	virtual void	Clone(Entity* _entity) const;

	static natU32	GetType() { return s_Spawner; }

public:
	natU64			m_interval;

private:
	natU64			m_currentInterval;

};




}