// Generated file : do not edit manually 


#include "component/spritermanager.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void SpriterManager::Clone(Entity* _entity, ref_t _type) const
{
	SpriterManager* component;
	ref_t base_type = SpriterManager::GetType();
	if(_type == 0)
	{
		component = _entity->AddComponent<SpriterManager>();
	}
	else
	{
		component = static_cast<SpriterManager*>(_entity->GetComponentByType(_type));
		base_type = _type;
	}

}


void SpriterManager::WriteData(Serializer& _ser)
{
}


void SpriterManager::ReadData(Serializer& _ser)
{
}



}
