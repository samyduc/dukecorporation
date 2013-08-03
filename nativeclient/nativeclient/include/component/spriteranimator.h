#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#include <glm/glm.hpp>

namespace Natorium
{

struct scml_sprite_t;

static natU32 s_SpriterAnimator = Hash::Compute("SpriterAnimator");

class SpriterAnimator : public Component
{
public:
					SpriterAnimator();
	virtual			~SpriterAnimator();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_SpriterAnimator; }

	virtual void	Clone(Entity* _entity, natU32 _type) const;
	void			WriteData(Serializer& _ser);
	void			ReadData(Serializer& _ser);

public:
	ref_t			m_animatorRef;

public:


protected:
	scml_sprite_t*	m_sprite;

};




}