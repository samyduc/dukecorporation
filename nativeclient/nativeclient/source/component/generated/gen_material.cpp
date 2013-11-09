// Generated file : do not edit manually 


#include "component/material/material.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void Material::Clone(Entity* _entity, ref_t _type) const
{
	Material* component;
	ref_t base_type = Material::GetType();
	if(_type == 0)
	{
		component = _entity->AddComponent<Material>();
	}
	else
	{
		component = static_cast<Material*>(_entity->GetComponentByType(_type));
		base_type = _type;
	}

}


void Material::WriteData(Serializer& _ser)
{
}


void Material::ReadData(Serializer& _ser)
{
}



}
