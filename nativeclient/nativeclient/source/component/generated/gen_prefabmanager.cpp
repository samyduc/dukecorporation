// Generated file : do not edit manually 


#include "component/prefabmanager.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void PrefabManager::Clone(Entity* _entity, natU32 _type) const
{
	PrefabManager* component;
	if(_type == 0)
	{
		component = _entity->AddComponent<PrefabManager>();
	}
	else
	{
		component = static_cast<PrefabManager*>(_entity->GetComponentByType(_type));
	}

}


void PrefabManager::WriteData(Serializer& _ser)
{
}


void PrefabManager::ReadData(Serializer& _ser)
{
}



}
