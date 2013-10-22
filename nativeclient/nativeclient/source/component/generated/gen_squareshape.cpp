// Generated file : do not edit manually 


#include "component/squareshape.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void SquareShape::Clone(Entity* _entity, natU32 _type) const
{
	SquareShape* component;
	natU32 base_type = SquareShape::GetType();
	if(_type == 0)
	{
		component = _entity->AddComponent<SquareShape>();
	}
	else
	{
		component = static_cast<SquareShape*>(_entity->GetComponentByType(_type));
		base_type = _type;
	}

	component->m_textureRef = m_textureRef;
	component->m_size = m_size;
	component->m_color = m_color;
	component->m_repeat = m_repeat;
	component->m_uv = m_uv;
}


void SquareShape::WriteData(Serializer& _ser)
{
	_ser << m_textureRef;
	_ser << m_size;
	_ser << m_color;
	_ser << m_repeat;
	_ser << m_uv;
}


void SquareShape::ReadData(Serializer& _ser)
{
	_ser >> m_textureRef;
	_ser >> m_size;
	_ser >> m_color;
	_ser >> m_repeat;
	_ser >> m_uv;
}



}
