#include "component/gameplay/timespawner.h"

#include "base/entity.h"
#include "base/component.h"
#include "base/kernel.h"
#include "component/transform.h"

#include "base/timeplatform.h"


#include "entity/civilian.h"

#include <cassert>

namespace Natorium
{


TimeSpawner::TimeSpawner()
	: m_interval(1000)
{
}

TimeSpawner::~TimeSpawner()
{
}

void TimeSpawner::OnInit()
{
	Spawner::OnInit();

	m_currentInterval = Time::GetMsTime();;
}

void TimeSpawner::OnTick(const natU64 _dt)
{
	Spawner::OnTick(_dt);

	if(m_currentInterval + m_interval < Time::GetMsTime())
	{
		m_currentInterval = Time::GetMsTime();

		if(m_pool_entities.size() > 0)
		{
			Spawn();
		}
	}
}

void TimeSpawner::Clone(Entity* _entity) const 
{
	TimeSpawner* component = _entity->AddComponent<TimeSpawner>();
	component->m_max = m_max;
	component->m_refEntity = m_refEntity;
}



}