// Generated file : do not edit manually 


#include "component/textshape.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void TextShape::Clone(Entity* _entity, natU32 _type) const
{
	TextShape* component;
	natU32 base_type = TextShape::GetType();
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
	component->m_color = m_color;
}


void TextShape::WriteData(Serializer& _ser)
{
	_ser << m_text;
	_ser << m_fontType;
	_ser << m_color;
}


void TextShape::ReadData(Serializer& _ser)
{
	_ser >> m_text;
	_ser >> m_fontType;
	_ser >> m_color;
}



}
