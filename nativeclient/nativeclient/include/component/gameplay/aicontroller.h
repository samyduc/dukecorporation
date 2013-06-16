#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#include "component/gameplay/lifecontroller.h"
#include "component/gameplay/spawner.h"
#include "component/playersmanager.h"



#include <glm/glm.hpp>

namespace Natorium
{

static natU32 s_AiController = Hash::Compute("s_AiController");

class AiController : public Component
{
public:
					AiController();
	virtual			~AiController();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_AiController; }

	void			Clone(Entity* _entity) const;

	virtual void	OnKilled();

public:
	Spawner*		m_spawner;

private:
	natF32			m_t;
	natF32			m_radius;
	glm::vec3		m_center;
	natF32			m_speed;

	natBool			m_killedCall;

	PlayersManager*	m_playersManager;
	LifeController*	m_lifeController;
	
};




}