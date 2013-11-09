// Generated file : do not edit manually 


#include "component/tiledmapmanager.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void TiledMapManager::Clone(Entity* _entity, ref_t _type) const
{
	TiledMapManager* component;
	ref_t base_type = TiledMapManager::GetType();
	if(_type == 0)
	{
		component = _entity->AddComponent<TiledMapManager>();
	}
	else
	{
		component = static_cast<TiledMapManager*>(_entity->GetComponentByType(_type));
		base_type = _type;
	}

}


void TiledMapManager::WriteData(Serializer& _ser)
{
}


void TiledMapManager::ReadData(Serializer& _ser)
{
}



}
