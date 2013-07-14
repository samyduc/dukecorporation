// Generated file : do not edit manually 


#include "component/filemanager.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void FileManager::Clone(Entity* _entity, natU32 _type) const
{
	FileManager* component;
	if(_type == 0)
	{
		component = _entity->AddComponent<FileManager>();
	}
	else
	{
		component = static_cast<FileManager*>(_entity->GetComponentByType(_type));
	}

}


void FileManager::WriteData(Serializer& _ser)
{
}


void FileManager::ReadData(Serializer& _ser)
{
}



}
