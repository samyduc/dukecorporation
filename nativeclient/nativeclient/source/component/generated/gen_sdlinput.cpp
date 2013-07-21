// Generated file : do not edit manually 


#include "component/sdlinput.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void SDLInput::Clone(Entity* _entity, natU32 _type) const
{
	SDLInput* component;
	natU32 base_type = SDLInput::GetType();
	if(_type == 0)
	{
		component = _entity->AddComponent<SDLInput>();
	}
	else
	{
		component = static_cast<SDLInput*>(_entity->GetComponentByType(_type));
		base_type = _type;
	}

}


void SDLInput::WriteData(Serializer& _ser)
{
}


void SDLInput::ReadData(Serializer& _ser)
{
}



}
