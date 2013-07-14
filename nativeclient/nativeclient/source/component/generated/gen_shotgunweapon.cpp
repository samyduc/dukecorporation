// Generated file : do not edit manually 


#include "component/gameplay/shotgunweapon.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void ShotgunWeapon::Clone(Entity* _entity, natU32 _type) const
{
	ShotgunWeapon* component;
	if(_type == 0)
	{
		component = _entity->AddComponent<ShotgunWeapon>();
	}
	else
	{
		component = static_cast<ShotgunWeapon*>(_entity->GetComponentByType(_type));
	}

	BaseWeapon::Clone(_entity, ShotgunWeapon::GetType());
	component->m_radius = m_radius;
	component->m_bullets = m_bullets;
}


void ShotgunWeapon::WriteData(Serializer& _ser)
{
	BaseWeapon::WriteData(_ser);
	_ser << m_radius;
	_ser << m_bullets;
}


void ShotgunWeapon::ReadData(Serializer& _ser)
{
	BaseWeapon::ReadData(_ser);
	_ser >> m_radius;
	_ser >> m_bullets;
}



}
