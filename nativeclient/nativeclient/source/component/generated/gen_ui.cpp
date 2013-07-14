// Generated file : do not edit manually 


#include "component/ui.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void UI::Clone(Entity* _entity, natU32 _type) const
{
	UI* component;
	if(_type == 0)
	{
		component = _entity->AddComponent<UI>();
	}
	else
	{
		component = static_cast<UI*>(_entity->GetComponentByType(_type));
	}

	component->m_pos = m_pos;
	component->m_rad = m_rad;
	component->m_scale = m_scale;
}


void UI::WriteData(Serializer& _ser)
{
	_ser << m_pos;
	_ser << m_rad;
	_ser << m_scale;
}


void UI::ReadData(Serializer& _ser)
{
	_ser >> m_pos;
	_ser >> m_rad;
	_ser >> m_scale;
}



}
