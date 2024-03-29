// Generated file : do not edit manually 


#include "component/spriteranimator.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void SpriterAnimator::Clone(Entity* _entity, ref_t _type) const
{
	SpriterAnimator* component;
	ref_t base_type = SpriterAnimator::GetType();
	if(_type == 0)
	{
		component = _entity->AddComponent<SpriterAnimator>();
	}
	else
	{
		component = static_cast<SpriterAnimator*>(_entity->GetComponentByType(_type));
		base_type = _type;
	}

	component->m_animatorRef = m_animatorRef;
	component->m_defaultAction = m_defaultAction;
}


void SpriterAnimator::WriteData(Serializer& _ser)
{
	_ser << m_animatorRef;
	_ser << m_defaultAction;
}


void SpriterAnimator::ReadData(Serializer& _ser)
{
	_ser >> m_animatorRef;
	_ser >> m_defaultAction;
}



}
