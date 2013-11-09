// Generated file : do not edit manually 


#include "component/scenemanager.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void SceneManager::Clone(Entity* _entity, ref_t _type) const
{
	SceneManager* component;
	ref_t base_type = SceneManager::GetType();
	if(_type == 0)
	{
		component = _entity->AddComponent<SceneManager>();
	}
	else
	{
		component = static_cast<SceneManager*>(_entity->GetComponentByType(_type));
		base_type = _type;
	}

	component->m_bootScene = m_bootScene;
}


void SceneManager::WriteData(Serializer& _ser)
{
	_ser << m_bootScene;
}


void SceneManager::ReadData(Serializer& _ser)
{
	_ser >> m_bootScene;
}



}
