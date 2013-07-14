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

void Spawned::Kill()
{
	assert(m_spawner);
	m_spawner->OnKilled(GetEntity());
}

}