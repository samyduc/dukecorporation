// Generated file : do not edit manually 


#include "component/spriteranimatorslave.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void SpriterAnimatorSlave::Clone(Entity* _entity, natU32 _type) const
{
	SpriterAnimatorSlave* component;
	natU32 base_type = SpriterAnimatorSlave::GetType();
	if(_type == 0)
	{
		component = _entity->AddComponent<SpriterAnimatorSlave>();
	}
	else
	{
		component = static_cast<SpriterAnimatorSlave*>(_entity->GetComponentByType(_type));
		base_type = _type;
	}

}


void SpriterAnimatorSlave::WriteData(Serializer& _ser)
{
}


void SpriterAnimatorSlave::ReadData(Serializer& _ser)
{
}



}
