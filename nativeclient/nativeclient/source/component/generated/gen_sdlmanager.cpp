// Generated file : do not edit manually 


#include "component/sdlmanager.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void SDLManager::Clone(Entity* _entity, natU32 _type) const
{
	SDLManager* component;
	natU32 base_type = SDLManager::GetType();
	if(_type == 0)
	{
		component = _entity->AddComponent<SDLManager>();
	}
	else
	{
		component = static_cast<SDLManager*>(_entity->GetComponentByType(_type));
		base_type = _type;
	}

	component->m_resolution = m_resolution;
	component->m_isFullScreen = m_isFullScreen;
}


void SDLManager::WriteData(Serializer& _ser)
{
	_ser << m_resolution;
	_ser << m_isFullScreen;
}


void SDLManager::ReadData(Serializer& _ser)
{
	_ser >> m_resolution;
	_ser >> m_isFullScreen;
}



}
