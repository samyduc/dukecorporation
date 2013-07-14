// Generated file : do not edit manually 


#include "component/sdlrender.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void SDLRender::Clone(Entity* _entity, natU32 _type) const
{
	SDLRender* component;
	if(_type == 0)
	{
		component = _entity->AddComponent<SDLRender>();
	}
	else
	{
		component = static_cast<SDLRender*>(_entity->GetComponentByType(_type));
	}

}


void SDLRender::WriteData(Serializer& _ser)
{
}


void SDLRender::ReadData(Serializer& _ser)
{
}



}
