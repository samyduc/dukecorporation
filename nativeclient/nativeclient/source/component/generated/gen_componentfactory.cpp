// Generated file : do not edit manually 


#include "component/componentfactory.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void ComponentFactory::Clone(Entity* _entity, natU32 _type) const
{
	ComponentFactory* component;
	if(_type == 0)
	{
		component = _entity->AddComponent<ComponentFactory>();
	}
	else
	{
		component = static_cast<ComponentFactory*>(_entity->GetComponentByType(_type));
	}

}


void ComponentFactory::WriteData(Serializer& _ser)
{
}


void ComponentFactory::ReadData(Serializer& _ser)
{
}



}
