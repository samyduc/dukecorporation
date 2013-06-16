#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#include <list>
#include <cassert>

namespace Natorium
{

static natU32 s_PlayersManager = Hash::Compute("s_PlayersManager");

class PlayersManager : public Component
{
public:
					PlayersManager();
	virtual			~PlayersManager();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_PlayersManager; }

	void			AddPlayer(Entity* _entity);

	Entity*			GetLocalPlayer() { assert(m_players.size() != 0); return m_players.front(); }

public:


private:
	typedef std::list<Entity*> players_t;
	players_t		m_players;

};




}