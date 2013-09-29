// Generated file : do not edit manually 


#include "component/rigidbody.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void RigidBody::Clone(Entity* _entity, natU32 _type) const
{
	RigidBody* component;
	natU32 base_type = RigidBody::GetType();
	if(_type == 0)
	{
		component = _entity->AddComponent<RigidBody>();
	}
	else
	{
		component = static_cast<RigidBody*>(_entity->GetComponentByType(_type));
		base_type = _type;
	}

	component->m_forceCircle = m_forceCircle;
	component->m_isDynamic = m_isDynamic;
	component->m_isBullet = m_isBullet;
	component->m_maxSpeed = m_maxSpeed;
	component->m_density = m_density;
	component->m_friction = m_friction;
	component->m_restitution = m_restitution;
	component->m_linearDampling = m_linearDampling;
	component->m_shapeType = m_shapeType;
}


void RigidBody::WriteData(Serializer& _ser)
{
	_ser << m_forceCircle;
	_ser << m_isDynamic;
	_ser << m_isBullet;
	_ser << m_maxSpeed;
	_ser << m_density;
	_ser << m_friction;
	_ser << m_restitution;
	_ser << m_linearDampling;
	_ser << m_shapeType;
}


void RigidBody::ReadData(Serializer& _ser)
{
	_ser >> m_forceCircle;
	_ser >> m_isDynamic;
	_ser >> m_isBullet;
	_ser >> m_maxSpeed;
	_ser >> m_density;
	_ser >> m_friction;
	_ser >> m_restitution;
	_ser >> m_linearDampling;
	_ser >> m_shapeType;
}



}
