#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>



namespace Natorium
{

class Entity;
struct scml_sprite_t;
struct timeline_sprite_t;
struct key_sprite_t;

static natU32 s_SpriterAnimatorSlave = Hash::Compute("SpriterAnimatorSlave");

class SpriterAnimatorSlave : public Component
{
public:

	friend class SpriterAnimator;

					SpriterAnimatorSlave();
	virtual			~SpriterAnimatorSlave();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_SpriterAnimatorSlave; }

	virtual void	Clone(Entity* _entity, natU32 _type) const;
	void			WriteData(Serializer& _ser);
	void			ReadData(Serializer& _ser);

	void			Play(const struct animation_sprite_t* _animation, const struct timeline_sprite_t* _timeline);


public:

protected:
	void			InitAnimation();

	void			ComputeNextKey();

	natF32			ComputeLerpTime(const struct key_sprite_t& _a,  const struct key_sprite_t& _b) const;
	natF32			Lerp(natF32 _a, natF32 _b, natF32 _t) const;
	glm::vec3		Lerp(const glm::vec3& _a, const glm::vec3& _b, natF32 _t) const;

	void			Interpolate(const struct key_sprite_t& _a,  const struct key_sprite_t& _b, natF32 _t);
	void			CorrectPos(glm::vec3& _pos, glm::vec3& _pivot, glm::vec3& _euler, const struct key_sprite_t& _a);
	void			CorrectRot(glm::quat& _rot, glm::vec3& _euler);
	void			Animate(const struct key_sprite_t& _a);

protected:
	const struct timeline_sprite_t*		m_timeline;
	const struct animation_sprite_t*	m_animation;
	natU64								m_time;
	size_t								m_keyIndex;
	size_t								m_keyIndexNext;
	natBool								m_isPlay;

};




}