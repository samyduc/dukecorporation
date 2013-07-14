// Generated file : do not edit manually 


#include "component/physicsmanager.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void PhysicsManager::Clone(Entity* _entity, natU32 _type) const
{
	PhysicsManager* component;
	if(_type == 0)
	{
		component = _entity->AddComponent<PhysicsManager>();
	}
	else
	{
		component = static_cast<PhysicsManager*>(_entity->GetComponentByType(_type));
	}

}


void PhysicsManager::WriteData(Serializer& _ser)
{
}


void PhysicsManager::ReadData(Serializer& _ser)
{
}



}
