// Generated file : do not edit manually 


#include "component/physicsmanager.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void PhysicsManager::Clone(Entity* _entity, ref_t _type) const
{
	PhysicsManager* component;
	ref_t base_type = PhysicsManager::GetType();
	if(_type == 0)
	{
		component = _entity->AddComponent<PhysicsManager>();
	}
	else
	{
		component = static_cast<PhysicsManager*>(_entity->GetComponentByType(_type));
		base_type = _type;
	}

}


void PhysicsManager::WriteData(Serializer& _ser)
{
}


void PhysicsManager::ReadData(Serializer& _ser)
{
}



}
