// Generated file : do not edit manually 


#include "component/material/bumpmapping.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void BumpMapping::Clone(Entity* _entity, ref_t _type) const
{
	BumpMapping* component;
	ref_t base_type = BumpMapping::GetType();
	if(_type == 0)
	{
		component = _entity->AddComponent<BumpMapping>();
	}
	else
	{
		component = static_cast<BumpMapping*>(_entity->GetComponentByType(_type));
		base_type = _type;
	}

	Material::Clone(_entity, base_type);
}


void BumpMapping::WriteData(Serializer& _ser)
{
	Material::WriteData(_ser);
}


void BumpMapping::ReadData(Serializer& _ser)
{
	Material::ReadData(_ser);
}



}
