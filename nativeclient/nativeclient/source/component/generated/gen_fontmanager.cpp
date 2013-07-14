// Generated file : do not edit manually 


#include "component/fontmanager.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void FontManager::Clone(Entity* _entity, natU32 _type) const
{
	FontManager* component;
	if(_type == 0)
	{
		component = _entity->AddComponent<FontManager>();
	}
	else
	{
		component = static_cast<FontManager*>(_entity->GetComponentByType(_type));
	}

}


void FontManager::WriteData(Serializer& _ser)
{
}


void FontManager::ReadData(Serializer& _ser)
{
}



}
