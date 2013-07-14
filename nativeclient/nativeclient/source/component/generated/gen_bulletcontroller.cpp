// Generated file : do not edit manually 


#include "component/gameplay/bulletcontroller.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void BulletController::Clone(Entity* _entity, natU32 _type) const
{
	BulletController* component;
	if(_type == 0)
	{
		component = _entity->AddComponent<BulletController>();
	}
	else
	{
		component = static_cast<BulletController*>(_entity->GetComponentByType(_type));
	}

	component->m_damage = m_damage;
	component->m_lifetime = m_lifetime;
}


void BulletController::WriteData(Serializer& _ser)
{
	_ser << m_damage;
	_ser << m_lifetime;
}


void BulletController::ReadData(Serializer& _ser)
{
	_ser >> m_damage;
	_ser >> m_lifetime;
}



}
