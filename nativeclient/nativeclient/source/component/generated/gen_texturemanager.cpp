// Generated file : do not edit manually 


#include "component/texturemanager.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void TextureManager::Clone(Entity* _entity, ref_t _type) const
{
	TextureManager* component;
	ref_t base_type = TextureManager::GetType();
	if(_type == 0)
	{
		component = _entity->AddComponent<TextureManager>();
	}
	else
	{
		component = static_cast<TextureManager*>(_entity->GetComponentByType(_type));
		base_type = _type;
	}

}


void TextureManager::WriteData(Serializer& _ser)
{
}


void TextureManager::ReadData(Serializer& _ser)
{
}



}
