// Generated file : do not edit manually 


#include "component/glrender.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void GLRender::Clone(Entity* _entity, natU32 _type) const
{
	GLRender* component;
	if(_type == 0)
	{
		component = _entity->AddComponent<GLRender>();
	}
	else
	{
		component = static_cast<GLRender*>(_entity->GetComponentByType(_type));
	}

	component->m_type = m_type;
}


void GLRender::WriteData(Serializer& _ser)
{
	_ser << m_type;
}


void GLRender::ReadData(Serializer& _ser)
{
	_ser >> m_type;
}



}
