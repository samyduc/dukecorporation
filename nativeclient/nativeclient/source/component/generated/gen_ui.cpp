// Generated file : do not edit manually 


#include "component/ui.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void UI::Clone(Entity* _entity, ref_t _type) const
{
	UI* component;
	ref_t base_type = UI::GetType();
	if(_type == 0)
	{
		component = _entity->AddComponent<UI>();
	}
	else
	{
		component = static_cast<UI*>(_entity->GetComponentByType(_type));
		base_type = _type;
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
