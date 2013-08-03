// Generated file : do not edit manually 


#include "component/spriteranimator.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void SpriterAnimator::Clone(Entity* _entity, natU32 _type) const
{
	SpriterAnimator* component;
	natU32 base_type = SpriterAnimator::GetType();
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
}


void SpriterAnimator::WriteData(Serializer& _ser)
{
	_ser << m_animatorRef;
}


void SpriterAnimator::ReadData(Serializer& _ser)
{
	_ser >> m_animatorRef;
}



}
