// Generated file : do not edit manually 


#include "component/gameplay/clickcontroller.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void ClickController::Clone(Entity* _entity, natU32 _type) const
{
	ClickController* component;
	natU32 base_type = ClickController::GetType();
	if(_type == 0)
	{
		component = _entity->AddComponent<ClickController>();
	}
	else
	{
		component = static_cast<ClickController*>(_entity->GetComponentByType(_type));
		base_type = _type;
	}

	component->m_speed = m_speed;
}


void ClickController::WriteData(Serializer& _ser)
{
	_ser << m_speed;
}


void ClickController::ReadData(Serializer& _ser)
{
	_ser >> m_speed;
}



}
