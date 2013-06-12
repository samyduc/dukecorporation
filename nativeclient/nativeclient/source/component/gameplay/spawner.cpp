#include "component/gameplay/spawner.h"

#include "base/entity.h"
#include "base/component.h"
#include "base/kernel.h"
#include "component/transform.h"

#include "base/timeplatform.h"


#include "entity/civilian.h"

namespace Natorium
{

Spawner::Spawner()
	: m_max(40)
	, m_interval(1000)
{
}

Spawner::~Spawner()
{
}

void Spawner::OnInit()
{
	m_currentInterval = Time::GetMsTime();
}

void Spawner::OnTick(const natU64 _dt)
{
	if(m_currentInterval + m_interval < Time::GetMsTime())
	{
		m_currentInterval = Time::GetMsTime();

		if(m_entities.size() < m_max)
		{
			Spawn();
		}
	}
}

void Spawner::OnDeInit()
{

}

void Spawner::Spawn()
{
	Entity* entity = new Civilian();
	Transform* transform = entity->GetComponent<Transform>();
	transform->m_pos = GetEntity()->GetComponent<Transform>()->GetPos();

	GetEntity()->GetKernel()->AddEntity(Layer::Layer_2, entity);

	m_entities.push_back(entity);
}



}