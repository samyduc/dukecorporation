#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#include <glm/glm.hpp>

#include <vector>

namespace Natorium
{

class Entity;
struct scml_sprite_t;
struct timeline_sprite_t;
struct key_sprite_t;

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

	void			Play(const natChar* _name);
	void			Play(ref_t _hash);

	const struct scml_sprite_t* GetSpriteSource() { return m_sprite; }

public:
	ref_t			m_animatorRef;
	ref_t			m_defaultAction;

public:

protected:
	void			InitAnimation();
	void			SetupEntity(Entity* _entity, const struct timeline_sprite_t& _timeline);

protected:
	const struct scml_sprite_t*			m_sprite;
	natU64								m_time;

	const struct animation_sprite_t*	m_currentAnimation;

	typedef std::vector<Entity*> entities_t;
	entities_t							m_managedEntities;

};




}