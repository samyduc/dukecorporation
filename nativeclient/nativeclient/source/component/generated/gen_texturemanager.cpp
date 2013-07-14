// Generated file : do not edit manually 


#include "component/texturemanager.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void TextureManager::Clone(Entity* _entity, natU32 _type) const
{
	TextureManager* component;
	if(_type == 0)
	{
		component = _entity->AddComponent<TextureManager>();
	}
	else
	{
		component = static_cast<TextureManager*>(_entity->GetComponentByType(_type));
	}

}


void TextureManager::WriteData(Serializer& _ser)
{
}


void TextureManager::ReadData(Serializer& _ser)
{
}



}
