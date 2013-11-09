// Generated file : do not edit manually 


#include "component/material/monotexture.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void MonoTexture::Clone(Entity* _entity, ref_t _type) const
{
	MonoTexture* component;
	ref_t base_type = MonoTexture::GetType();
	if(_type == 0)
	{
		component = _entity->AddComponent<MonoTexture>();
	}
	else
	{
		component = static_cast<MonoTexture*>(_entity->GetComponentByType(_type));
		base_type = _type;
	}

	Material::Clone(_entity, base_type);
	component->m_textureRef = m_textureRef;
	component->m_color = m_color;
}


void MonoTexture::WriteData(Serializer& _ser)
{
	Material::WriteData(_ser);
	_ser << m_textureRef;
	_ser << m_color;
}


void MonoTexture::ReadData(Serializer& _ser)
{
	Material::ReadData(_ser);
	_ser >> m_textureRef;
	_ser >> m_color;
}



}
