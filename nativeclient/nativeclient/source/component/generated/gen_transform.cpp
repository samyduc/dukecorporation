// Generated file : do not edit manually 


#include "component/transform.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void Transform::Clone(Entity* _entity, natU32 _type) const
{
	Transform* component;
	natU32 base_type = Transform::GetType();
	if(_type == 0)
	{
		component = _entity->AddComponent<Transform>();
	}
	else
	{
		component = static_cast<Transform*>(_entity->GetComponentByType(_type));
		base_type = _type;
	}

	component->m_pos = m_pos;
	component->m_rad = m_rad;
	component->m_scale = m_scale;
	component->m_forward = m_forward;
}


void Transform::WriteData(Serializer& _ser)
{
	_ser << m_pos;
	_ser << m_rad;
	_ser << m_scale;
	_ser << m_forward;
}


void Transform::ReadData(Serializer& _ser)
{
	_ser >> m_pos;
	_ser >> m_rad;
	_ser >> m_scale;
	_ser >> m_forward;
}



}
