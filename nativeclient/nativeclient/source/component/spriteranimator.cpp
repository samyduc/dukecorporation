#include "component/spriteranimator.h"


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

SpriterAnimator::SpriterAnimator()
	: m_animatorRef(0)
	, m_defaultAction(0)
	, m_sprite(nullptr)
	, m_currentAnimation(nullptr)
{

}

SpriterAnimator::~SpriterAnimator()
{

}

void SpriterAnimator::OnInit()
{
	SpriterManager* spritermanager = GetEntity()->GetKernel()->GetLayer(Layer::Layer_0)->GetRootEntity()->GetComponent<SpriterManager>();
	assert(spritermanager);

	m_sprite = spritermanager->Get(m_animatorRef);
	assert(m_sprite);

	if(m_defaultAction)
	{
		Play(m_defaultAction);
	}
}

void SpriterAnimator::OnTick(const natU64 _dt)
{
	m_time += _dt;

	for(size_t i = 0; i < m_currentAnimation->m_timelines.size(); ++i)
	{

	}
}

void SpriterAnimator::OnDeInit()
{

}

void SpriterAnimator::Play(const natChar* _name)
{
	ref_t hash = Hash::Compute(_name);
}

void SpriterAnimator::Play(ref_t _hash)
{
	assert(m_sprite);

	const animationMap_t::const_iterator it = m_sprite->m_animations.find(_hash);

	if(it != m_sprite->m_animations.end())
	{
		m_currentAnimation = &(*it).second;
		InitAnimation();
	}
	else
	{
		// missing animation
		assert(false);
	}
}

void SpriterAnimator::InitAnimation()
{
	assert(m_sprite);
	assert(m_currentAnimation);

	m_time = 0;

	if(m_managedEntities.size() < m_currentAnimation->m_timelines.size())
	{
		entities_t entities_to_add;
		// create missing entities
		for(size_t i = m_managedEntities.size(); i < m_currentAnimation->m_timelines.size(); ++i)
		{
			Entity* entity = new Entity();
			entities_to_add.push_back(entity);
		}
		
		// entity settings
		size_t original_size = m_managedEntities.size();
		for(size_t i = 0; i < m_currentAnimation->m_timelines.size(); ++i)
		{
			const timeline_sprite_t& timeline = m_currentAnimation->m_timelines[i];
			Entity* entity;
			natBool is_new = false;

			if(i < original_size)
			{
				entity = m_managedEntities[i];
			}
			else
			{
				entity = entities_to_add[i - original_size];
				is_new = true;
			}

			SetupEntity(entity, timeline);

			if(is_new)
			{
				GetEntity()->GetKernel()->AddEntity(GetEntity()->GetLayer()->GetEnumLayer(), entity, GetEntity());
				m_managedEntities.push_back(entity);
			}
			else
			{
				entity->Reset();
			}
		}

		// if more entity than necessary, deactivate the rest
		for(size_t i = m_currentAnimation->m_timelines.size(); i < m_managedEntities.size(); ++i)
		{
			Entity* entity = m_managedEntities[i];
			entity->SetEnabled(false);
		}
	}
}

ref_t s_MonoTexture = Hash::Compute("monotexture");

void SpriterAnimator::SetupEntity(Entity* _entity, const timeline_sprite_t& _timeline)
{
	GLRender* glrender = _entity->AddComponent<GLRender>();
	glrender->m_shapeType = s_SquareShape;
	glrender->m_type = s_MonoTexture;

	Transform* transform = _entity->AddComponent<Transform>();
	transform->m_pos = _timeline.m_keys[0].m_position;
	transform->m_scale = _timeline.m_keys[0].m_scale;
	transform->m_rad.z = glm::radians(_timeline.m_keys[0].m_rotation);

	SquareShape* squareshape = _entity->AddComponent<SquareShape>();
	squareshape->m_color = glm::vec4(1.f, 1.f, 1.f, _timeline.m_keys[0].m_alpha);
	squareshape->m_size = _timeline.m_keys[0].m_ressource.m_size;
	squareshape->m_textureRef = _timeline.m_keys[0].m_ressource.m_ref;
	squareshape->m_repeat = 1.f;
}





}