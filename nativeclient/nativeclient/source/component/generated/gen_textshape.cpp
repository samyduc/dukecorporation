// Generated file : do not edit manually 


#include "component/textshape.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void TextShape::Clone(Entity* _entity, ref_t _type) const
{
	TextShape* component;
	ref_t base_type = TextShape::GetType();
	if(_type == 0)
	{
		component = _entity->AddComponent<TextShape>();
	}
	else
	{
		component = static_cast<TextShape*>(_entity->GetComponentByType(_type));
		base_type = _type;
	}

	component->m_text = m_text;
	component->m_fontType = m_fontType;
}


void TextShape::WriteData(Serializer& _ser)
{
	_ser << m_text;
	_ser << m_fontType;
}


void TextShape::ReadData(Serializer& _ser)
{
	_ser >> m_text;
	_ser >> m_fontType;
}



}
