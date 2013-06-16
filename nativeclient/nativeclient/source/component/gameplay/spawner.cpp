#include "component/gameplay/spawner.h"

#include "base/entity.h"
#include "base/component.h"
#include "base/kernel.h"
#include "component/transform.h"

#include "base/timeplatform.h"


#include "entity/civilian.h"

#include <cassert>

namespace Natorium
{

Spawner::Spawner()
	: m_max(40)
	, m_interval(1000)
	, m_refEntity(nullptr)
{
}

Spawner::~Spawner()
{
}

void Spawner::OnInit()
{
	assert(m_refEntity);
	m_currentInterval = Time::GetMsTime();

	// spawn a pool of entities
	for(size_t i = 0; i < m_max; ++i)
	{
		Entity* entity = m_refEntity->Clone();
		GetEntity()->GetKernel()->AddEntity(Layer::Layer_2, entity);
		entity->SetEnabled(false);

		m_pool_entities.push_back(entity);
	}
}

void Spawner::OnTick(const natU64 _dt)
{
	if(m_currentInterval + m_interval < Time::GetMsTime())
	{
		m_currentInterval = Time::GetMsTime();

		if(m_pool_entities.size() > 0)
		{
			Spawn();
		}
	}

	for(entities_spawner_t::iterator it = m_kill_entities.begin(); it != m_kill_entities.end(); ++it)
	{
		Entity* entity = (*it);
		AiController* ai_controller = entity->GetComponent<AiController>();
		ai_controller->OnKilled();
		entity->SetEnabled(false);
		m_pool_entities.push_back(entity);

	}
	m_kill_entities.clear();
}

void Spawner::Clone(Entity* _entity) const
{
	Spawner* component = _entity->AddComponent<Spawner>();
	component->m_max = m_max;
	component->m_interval = m_interval;
	component->m_refEntity = m_refEntity;
}

void Spawner::OnDeInit()
{

}

void Spawner::Spawn()
{
	Entity* entity = m_pool_entities.back();
	m_pool_entities.pop_back();

	Transform* transform = entity->GetComponent<Transform>();
	transform->m_pos = GetEntity()->GetComponent<Transform>()->GetPos();

	AiController* ai_controller = entity->GetComponent<AiController>();
	assert(ai_controller);
	ai_controller->m_spawner = this;

	entity->Reset();
	entity->SetEnabled(true);
	m_active_entities.push_back(entity);
}

void Spawner::OnKilled(Entity* _entity)
{
	for(entities_spawner_t::iterator it = m_active_entities.begin(); it != m_active_entities.end(); ++it)
	{
		Entity* cmp = (*it);
		if(cmp->GetId() == _entity->GetId())
		{
			m_active_entities.erase(it);
			m_kill_entities.push_back(_entity);
			break;
		}
	}
}



}