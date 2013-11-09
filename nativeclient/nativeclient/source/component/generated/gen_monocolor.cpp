// Generated file : do not edit manually 


#include "component/material/monocolor.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void MonoColor::Clone(Entity* _entity, ref_t _type) const
{
	MonoColor* component;
	ref_t base_type = MonoColor::GetType();
	if(_type == 0)
	{
		component = _entity->AddComponent<MonoColor>();
	}
	else
	{
		component = static_cast<MonoColor*>(_entity->GetComponentByType(_type));
		base_type = _type;
	}

	Material::Clone(_entity, base_type);
	component->m_color = m_color;
}


void MonoColor::WriteData(Serializer& _ser)
{
	Material::WriteData(_ser);
	_ser << m_color;
}


void MonoColor::ReadData(Serializer& _ser)
{
	Material::ReadData(_ser);
	_ser >> m_color;
}



}
