// Generated file : do not edit manually 


#include "component/componentfactory.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void ComponentFactory::Clone(Entity* _entity, ref_t _type) const
{
	ComponentFactory* component;
	ref_t base_type = ComponentFactory::GetType();
	if(_type == 0)
	{
		component = _entity->AddComponent<ComponentFactory>();
	}
	else
	{
		component = static_cast<ComponentFactory*>(_entity->GetComponentByType(_type));
		base_type = _type;
	}

}


void ComponentFactory::WriteData(Serializer& _ser)
{
}


void ComponentFactory::ReadData(Serializer& _ser)
{
}



}
