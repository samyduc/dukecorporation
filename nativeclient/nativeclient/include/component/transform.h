#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

namespace Natorium
{


static natU32 s_Transform = Hash::Compute("s_Transform");

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

	natF32			m_pos_x;
	natF32			m_pos_y;
	natF32			m_pos_z;

	natF32			m_rad_x;
	natF32			m_rad_y;
	natF32			m_rad_z;
};




}