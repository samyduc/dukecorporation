#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#include <glm/glm.hpp>

namespace Natorium
{


static natU32 s_Transform = Hash::Compute("s_Transform");

static const natF32 s_PI = 3.14159265358979f; 

class Transform : public Component
{
public:
					Transform();
	virtual			~Transform();

	virtual void	OnInit();
	virtual void	OnTick(natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_Transform; }

public:

	glm::vec3		m_pos;
	glm::vec3		m_rad;
	glm::vec3		m_scale;

public:

	glm::vec3		GetDeg() { return glm::degrees(m_rad); }




protected:
	natF32			RadToDeg(natF32 _rad);

};




}