#include "component/playersmanager.h"

#include "base/entity.h"
#include "base/kernel.h"

#include <cassert>

namespace Natorium
{

PlayersManager::PlayersManager()
{
}

PlayersManager::~PlayersManager()
{
}

void PlayersManager::OnInit()
{
	//assert(m_players.size() == 0);
}

void PlayersManager::OnTick(const natU64 _dt)
{
}

void PlayersManager::OnDeInit()
{

	m_players.clear();
}

void PlayersManager::AddPlayer(Entity* _entity)
{
	assert(_entity);
	m_players.push_back(_entity);
}


}