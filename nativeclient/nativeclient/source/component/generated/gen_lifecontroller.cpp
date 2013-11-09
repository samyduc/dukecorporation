// Generated file : do not edit manually 


#include "component/gameplay/lifecontroller.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void LifeController::Clone(Entity* _entity, ref_t _type) const
{
	LifeController* component;
	ref_t base_type = LifeController::GetType();
	if(_type == 0)
	{
		component = _entity->AddComponent<LifeController>();
	}
	else
	{
		component = static_cast<LifeController*>(_entity->GetComponentByType(_type));
		base_type = _type;
	}

	component->m_life = m_life;
	component->m_smallDamageTexture = m_smallDamageTexture;
	component->m_BigDamageTexture = m_BigDamageTexture;
}


void LifeController::WriteData(Serializer& _ser)
{
	_ser << m_life;
	_ser << m_smallDamageTexture;
	_ser << m_BigDamageTexture;
}


void LifeController::ReadData(Serializer& _ser)
{
	_ser >> m_life;
	_ser >> m_smallDamageTexture;
	_ser >> m_BigDamageTexture;
}



}
