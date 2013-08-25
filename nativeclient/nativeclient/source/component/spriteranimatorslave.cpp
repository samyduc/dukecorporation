#include "component/spriteranimatorslave.h"


#include "base/entity.h"
#include "base/kernel.h"
#include "base/layer.h"
#include "base/component.h"
#include "base/hash.h"

#include "component/glrender.h"
#include "component/squareshape.h"
#include "component/transform.h"

#include "component/spritermanager.h"
#include "component/texturemanager.h"



namespace Natorium
{

SpriterAnimatorSlave::SpriterAnimatorSlave()
	: m_keyIndex(0)
	, m_timeline(nullptr)
	, m_animation(nullptr)
{

}

SpriterAnimatorSlave::~SpriterAnimatorSlave()
{

}

void SpriterAnimatorSlave::OnInit()
{
	assert(m_animation);
	assert(m_timeline);

	// init transform
	Transform* transform = GetEntity()->GetComponent<Transform>();
	transform->m_pos = m_timeline->m_keys[0].m_position;
	transform->m_scale = m_timeline->m_keys[0].m_scale;
	transform->m_rot = m_timeline->m_keys[0].m_rotation;

	// hackish
	Interpolate(m_timeline->m_keys[0], m_timeline->m_keys[0], 0.f);

	m_isPlay = m_timeline->m_keys.size() > 1;
}

void SpriterAnimatorSlave::OnTick(const natU64 _dt)
{
	assert(m_animation);
	assert(m_timeline);

	if(m_timeline->m_keys.size() > 1)
	{

		m_time += _dt;

		if(m_time > m_animation->m_duration)
		{
			m_time -= m_animation->m_duration;
			m_keyIndex = 0;
			ComputeNextKey();
		}

		// while to avoid freeze
		while((m_keyIndex != m_timeline->m_keys.size() -1) && m_timeline->m_keys[m_keyIndexNext].m_time < m_time)
		{
			++m_keyIndex;
			ComputeNextKey();
		}

		const struct timeline_sprite_t& timeline = *m_timeline;
		const struct key_sprite_t& key = timeline.m_keys[m_keyIndex];
		const struct key_sprite_t& nextKey = timeline.m_keys[m_keyIndexNext];

		natF32 t = ComputeLerpTime(key, nextKey);
		Interpolate(key, nextKey, t);
		Animate(key);
	}
}

void SpriterAnimatorSlave::OnDeInit()
{
	m_isPlay = false;
}

void SpriterAnimatorSlave::ComputeNextKey()
{
	assert(m_animation);
	assert(m_timeline);

	m_keyIndexNext = m_keyIndex + 1;
	if(m_keyIndexNext >= m_timeline->m_keys.size())
	{
		m_keyIndexNext = 0;
	}
}

natF32 SpriterAnimatorSlave::ComputeLerpTime(const struct key_sprite_t& _a,  const struct key_sprite_t& _b) const
{
	natU64 next_time = _b.m_time;

	if(next_time < _a.m_time)
	{
		next_time = m_animation->m_duration + _b.m_time;
	}

	return (m_time - _a.m_time) / natF32(next_time - _a.m_time);
}

natF32 SpriterAnimatorSlave::Lerp(natF32 _a, natF32 _b, natF32 _t) const
{
	assert(_t >= 0);
	assert(_t <= 1);

	return ((_b-_a)*_t) + _a;
}

// http://www.brashmonkeygames.com/spriter/ScmlDocs/ScmlReference.html
glm::vec3 SpriterAnimatorSlave::Lerp(const glm::vec3& _a, const glm::vec3& _b, natF32 _t) const
{
	assert(_t >= 0);
	assert(_t <= 1);

	return ((_b-_a)*_t) + _a;
}

void SpriterAnimatorSlave::Interpolate(const struct key_sprite_t& _a,  const struct key_sprite_t& _b, natF32 _t)
{
	Transform *transform = GetEntity()->GetComponent<Transform>();
	SquareShape *squareshape = GetEntity()->GetComponent<SquareShape>();

	transform->m_pos = Lerp(_a.m_position, _b.m_position, _t);
	transform->m_rot = glm::slerp(_a.m_rotation, _b.m_rotation, _t);
	transform->m_scale = Lerp(_a.m_scale, _b.m_scale, _t);

	squareshape->SetAlpha(Lerp(_a.m_alpha, _b.m_alpha, _t));

	// TODO : found a way to do rotation around a pivot
	glm::vec3 pivot = Lerp(_a.m_pivot, _b.m_pivot, _t);
	glm::vec3 euler = glm::eulerAngles(transform->m_rot);

	CorrectPos(transform->m_pos, pivot, euler, _a);
	CorrectRot(transform->m_rot, euler);

	// change z ordering
	//transform->m_pos.z = _a.m_z_index;
}

void SpriterAnimatorSlave::CorrectPos(glm::vec3& _pos, glm::vec3& _pivot, glm::vec3& _euler, const struct key_sprite_t& _a)
{
	_pivot.x = (_pivot.x - 0.5f)*_a.m_ressource.m_size.x;
	_pivot.y = (_pivot.y - 0.5f)*_a.m_ressource.m_size.y;

	natF32 s = glm::sin(_euler.z);
	natF32 c = glm::cos(_euler.z);
	_pos.x -= (_pivot.x * c) - (_pivot.y * s);
	_pos.y -= (_pivot.x * s) + (_pivot.y * c);

	// correct transform
	_pos.y *= -1.f;
}

void SpriterAnimatorSlave::CorrectRot(glm::quat& _rot, glm::vec3& _euler)
{
	// correct orientation for your repere
	_rot = glm::quat(glm::vec3(0.0f, 0.0f, 2.0f*s_PI - _euler.z));
}

void SpriterAnimatorSlave::Animate(const struct key_sprite_t& _a)
{
	SquareShape *squareshape = GetEntity()->GetComponent<SquareShape>();

	if(squareshape->m_textureRef != _a.m_ressource.m_ref)
	{
		squareshape->m_textureRef = _a.m_ressource.m_ref;
		squareshape->m_size = _a.m_ressource.m_size;

		squareshape->Reset();
	}
}

void SpriterAnimatorSlave::Play(const struct animation_sprite_t* _animation, const struct timeline_sprite_t* _timeline)
{
	m_animation = _animation;
	m_timeline = _timeline;

	InitAnimation();
}

void SpriterAnimatorSlave::InitAnimation()
{
	assert(m_animation);
	assert(m_timeline);

	m_time = 0;
	m_keyIndex = 0;
	ComputeNextKey();
}






}