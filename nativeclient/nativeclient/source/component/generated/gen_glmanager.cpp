// Generated file : do not edit manually 


#include "component/glmanager.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void GLManager::Clone(Entity* _entity, natU32 _type) const
{
	GLManager* component;
	natU32 base_type = GLManager::GetType();
	if(_type == 0)
	{
		component = _entity->AddComponent<GLManager>();
	}
	else
	{
		component = static_cast<GLManager*>(_entity->GetComponentByType(_type));
		base_type = _type;
	}

}


void GLManager::WriteData(Serializer& _ser)
{
}


void GLManager::ReadData(Serializer& _ser)
{
}



}
