// Generated file : do not edit manually 


#include "component/gameplay/spawner.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void Spawner::Clone(Entity* _entity, natU32 _type) const
{
	Spawner* component;
	if(_type == 0)
	{
		component = _entity->AddComponent<Spawner>();
	}
	else
	{
		component = static_cast<Spawner*>(_entity->GetComponentByType(_type));
	}

	component->m_max = m_max;
	component->m_refEntity = m_refEntity;
}


void Spawner::WriteData(Serializer& _ser)
{
	_ser << m_max;
	_ser << reinterpret_cast<void**>(&m_refEntity);
}


void Spawner::ReadData(Serializer& _ser)
{
	_ser >> m_max;
	_ser >> reinterpret_cast<void**>(&m_refEntity);
}



}
