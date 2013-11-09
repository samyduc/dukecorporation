// Generated file : do not edit manually 


#include "component/sdlrender.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void SDLRender::Clone(Entity* _entity, ref_t _type) const
{
	SDLRender* component;
	ref_t base_type = SDLRender::GetType();
	if(_type == 0)
	{
		component = _entity->AddComponent<SDLRender>();
	}
	else
	{
		component = static_cast<SDLRender*>(_entity->GetComponentByType(_type));
		base_type = _type;
	}

}


void SDLRender::WriteData(Serializer& _ser)
{
}


void SDLRender::ReadData(Serializer& _ser)
{
}



}
