// Generated file : do not edit manually 


#include "component/gameplay/baseweapon.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void BaseWeapon::Clone(Entity* _entity, natU32 _type) const
{
	BaseWeapon* component;
	natU32 base_type = BaseWeapon::GetType();
	if(_type == 0)
	{
		component = _entity->AddComponent<BaseWeapon>();
	}
	else
	{
		component = static_cast<BaseWeapon*>(_entity->GetComponentByType(_type));
		base_type = _type;
	}

	Spawner::Clone(_entity, base_type);
	component->m_rateShot = m_rateShot;
}


void BaseWeapon::WriteData(Serializer& _ser)
{
	Spawner::WriteData(_ser);
	_ser << m_rateShot;
}


void BaseWeapon::ReadData(Serializer& _ser)
{
	Spawner::ReadData(_ser);
	_ser >> m_rateShot;
}



}
