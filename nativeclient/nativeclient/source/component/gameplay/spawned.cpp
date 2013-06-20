#include "component/gameplay/spawned.h"

#include "base/entity.h"
#include "component/gameplay/spawner.h"

#include <cassert>

namespace Natorium
{

Spawned::Spawned()
	: m_spawner(nullptr)
{

}

Spawned::~Spawned()
{

}

void Spawned::OnInit()
{

}

void Spawned::OnTick(const natU64 _dt)
{

}

void Spawned::OnDeInit()
{
}

void Spawned::Clone(Entity* _entity) const
{
	Spawned* component = _entity->AddComponent<Spawned>();
	component->m_spawner = m_spawner;
}

void Spawned::Kill()
{
	assert(m_spawner);
	Spawner* spawner = m_spawner->GetComponent<Spawner>();
	assert(spawner);
	spawner->OnKilled(GetEntity());
}

}