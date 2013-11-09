// Generated file : do not edit manually 


#include "component/gameplay/spawner.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void Spawner::Clone(Entity* _entity, ref_t _type) const
{
	Spawner* component;
	ref_t base_type = Spawner::GetType();
	if(_type == 0)
	{
		component = _entity->AddComponent<Spawner>();
	}
	else
	{
		component = static_cast<Spawner*>(_entity->GetComponentByType(_type));
		base_type = _type;
	}

	component->m_max = m_max;
	component->m_prefabType = m_prefabType;
}


void Spawner::WriteData(Serializer& _ser)
{
	_ser << m_max;
	_ser << m_prefabType;
}


void Spawner::ReadData(Serializer& _ser)
{
	_ser >> m_max;
	_ser >> m_prefabType;
}



}
