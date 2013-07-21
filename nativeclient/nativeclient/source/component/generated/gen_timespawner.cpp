// Generated file : do not edit manually 


#include "component/gameplay/timespawner.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void TimeSpawner::Clone(Entity* _entity, natU32 _type) const
{
	TimeSpawner* component;
	natU32 base_type = TimeSpawner::GetType();
	if(_type == 0)
	{
		component = _entity->AddComponent<TimeSpawner>();
	}
	else
	{
		component = static_cast<TimeSpawner*>(_entity->GetComponentByType(_type));
		base_type = _type;
	}

	Spawner::Clone(_entity, base_type);
	component->m_interval = m_interval;
}


void TimeSpawner::WriteData(Serializer& _ser)
{
	Spawner::WriteData(_ser);
	_ser << m_interval;
}


void TimeSpawner::ReadData(Serializer& _ser)
{
	Spawner::ReadData(_ser);
	_ser >> m_interval;
}



}
