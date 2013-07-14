// Generated file : do not edit manually 


#include "component/scenemanager.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void SceneManager::Clone(Entity* _entity, natU32 _type) const
{
	SceneManager* component;
	if(_type == 0)
	{
		component = _entity->AddComponent<SceneManager>();
	}
	else
	{
		component = static_cast<SceneManager*>(_entity->GetComponentByType(_type));
	}

}


void SceneManager::WriteData(Serializer& _ser)
{
}


void SceneManager::ReadData(Serializer& _ser)
{
}



}
