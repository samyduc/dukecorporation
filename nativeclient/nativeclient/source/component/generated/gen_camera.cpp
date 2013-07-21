// Generated file : do not edit manually 


#include "component/camera.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void Camera::Clone(Entity* _entity, natU32 _type) const
{
	Camera* component;
	natU32 base_type = Camera::GetType();
	if(_type == 0)
	{
		component = _entity->AddComponent<Camera>();
	}
	else
	{
		component = static_cast<Camera*>(_entity->GetComponentByType(_type));
		base_type = _type;
	}

	component->m_effect_followMouse = m_effect_followMouse;
	component->m_efect_followMouseSmooth = m_efect_followMouseSmooth;
	component->m_viewMatrix = m_viewMatrix;
	component->m_projectionMatrix = m_projectionMatrix;
	component->m_resolution = m_resolution;
}


void Camera::WriteData(Serializer& _ser)
{
	_ser << m_effect_followMouse;
	_ser << m_efect_followMouseSmooth;
	_ser << m_viewMatrix;
	_ser << m_projectionMatrix;
	_ser << m_resolution;
}


void Camera::ReadData(Serializer& _ser)
{
	_ser >> m_effect_followMouse;
	_ser >> m_efect_followMouseSmooth;
	_ser >> m_viewMatrix;
	_ser >> m_projectionMatrix;
	_ser >> m_resolution;
}



}
