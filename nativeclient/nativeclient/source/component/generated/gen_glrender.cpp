// Generated file : do not edit manually 


#include "component/glrender.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void GLRender::Clone(Entity* _entity, ref_t _type) const
{
	GLRender* component;
	ref_t base_type = GLRender::GetType();
	if(_type == 0)
	{
		component = _entity->AddComponent<GLRender>();
	}
	else
	{
		component = static_cast<GLRender*>(_entity->GetComponentByType(_type));
		base_type = _type;
	}

	component->m_materialType = m_materialType;
	component->m_shapeType = m_shapeType;
}


void GLRender::WriteData(Serializer& _ser)
{
	_ser << m_materialType;
	_ser << m_shapeType;
}


void GLRender::ReadData(Serializer& _ser)
{
	_ser >> m_materialType;
	_ser >> m_shapeType;
}



}
