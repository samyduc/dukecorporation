// Generated file : do not edit manually 


#include "component/gameplay/lifecontroller.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void LifeController::Clone(Entity* _entity, natU32 _type) const
{
	LifeController* component;
	if(_type == 0)
	{
		component = _entity->AddComponent<LifeController>();
	}
	else
	{
		component = static_cast<LifeController*>(_entity->GetComponentByType(_type));
	}

	component->m_life = m_life;
}


void LifeController::WriteData(Serializer& _ser)
{
	_ser << m_life;
}


void LifeController::ReadData(Serializer& _ser)
{
	_ser >> m_life;
}



}
