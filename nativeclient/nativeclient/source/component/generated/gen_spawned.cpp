// Generated file : do not edit manually 


#include "component/gameplay/spawned.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void Spawned::Clone(Entity* _entity, natU32 _type) const
{
	Spawned* component;
	natU32 base_type = Spawned::GetType();
	if(_type == 0)
	{
		component = _entity->AddComponent<Spawned>();
	}
	else
	{
		component = static_cast<Spawned*>(_entity->GetComponentByType(_type));
		base_type = _type;
	}

}


void Spawned::WriteData(Serializer& _ser)
{
}


void Spawned::ReadData(Serializer& _ser)
{
}



}
