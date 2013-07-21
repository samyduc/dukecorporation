// Generated file : do not edit manually 


#include "component/playersmanager.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void PlayersManager::Clone(Entity* _entity, natU32 _type) const
{
	PlayersManager* component;
	natU32 base_type = PlayersManager::GetType();
	if(_type == 0)
	{
		component = _entity->AddComponent<PlayersManager>();
	}
	else
	{
		component = static_cast<PlayersManager*>(_entity->GetComponentByType(_type));
		base_type = _type;
	}

}


void PlayersManager::WriteData(Serializer& _ser)
{
}


void PlayersManager::ReadData(Serializer& _ser)
{
}



}
