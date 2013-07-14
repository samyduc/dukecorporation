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
	if(_type == 0)
	{
		component = _entity->AddComponent<Spawned>();
	}
	else
	{
		component = static_cast<Spawned*>(_entity->GetComponentByType(_type));
	}

	component->m_spawner = m_spawner;
}


void Spawned::WriteData(Serializer& _ser)
{
	_ser << reinterpret_cast<void**>(&m_spawner);
}


void Spawned::ReadData(Serializer& _ser)
{
	_ser >> reinterpret_cast<void**>(&m_spawner);
}



}
