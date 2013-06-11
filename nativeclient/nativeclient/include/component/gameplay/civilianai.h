#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#include <glm/glm.hpp>

namespace Natorium
{

static natU32 s_CivilianAI = Hash::Compute("s_CivilianAI");

class CivilianAI : public Component
{
public:
					CivilianAI();
	virtual			~CivilianAI();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_CivilianAI; }

public:


private:
	natF32		m_t;
	natF32		m_radius;
	glm::vec3	m_center;

};




}