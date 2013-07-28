#include "component/prefabmanager.h"


#include "base/entity.h"
#include "base/kernel.h"
#include "base/layer.h"

#include "component/filemanager.h"
#include "component/componentfactory.h"

#include <vector>
#include <string>

#include "tinyxml/tinyxml2.h"

namespace Natorium
{

PrefabManager::PrefabManager()
{

}

PrefabManager::~PrefabManager()
{

}

void PrefabManager::OnInit()
{
	InitFromDirectory("/data/prefab");
}


void PrefabManager::OnTick(const natU64 _dt)
{

}

void PrefabManager::OnDeInit()
{
	for(prefabs_t::iterator it = m_prefabs.begin(); it != m_prefabs.end(); ++it)
	{
		Entity* entity = it->second;
		delete entity;
	}

	m_prefabs.clear();
}

void PrefabManager::Load(const natChar* _path)
{
	FileManager* filemanager = GetEntity()->GetKernel()->GetLayer(Layer::Layer_0)->GetRootEntity()->GetComponent<FileManager>();
	assert(filemanager);

	ComponentFactory* componentFactory = GetEntity()->GetKernel()->GetLayer(Layer::Layer_0)->GetRootEntity()->GetComponent<ComponentFactory>();
	assert(filemanager);

	size_t size;
	natU8* buffer = filemanager->Read(_path, &size);

	tinyxml2::XMLDocument doc;

	doc.Parse(reinterpret_cast<natChar*>(buffer), size);

	tinyxml2::XMLElement* element = doc.FirstChildElement("prefab");
	assert(element);

	Entity* entity = new Entity();
	natU32 hash = Hash::Compute(_path);
	Entity* is_exist = Get(hash);
	assert(is_exist == nullptr);

	element = element->FirstChildElement();

	while(element)
	{
		componentFactory->ParseComponent(entity, element);

		element = element->NextSiblingElement();
	}

	delete buffer;

	// store the result
	m_prefabs[hash] = entity;
}


Entity* PrefabManager::Get(const natChar* _path)
{
	ref_t hash = Hash::Compute(_path);
	return Get(hash);
}

Entity*	PrefabManager::Get(ref_t _id)
{
	Entity* ret = nullptr;
	prefabs_t::iterator it = m_prefabs.find(_id);
	
	if(it != m_prefabs.end())
	{
		ret = it->second;
	}

	return ret;
}

Entity* PrefabManager::CreateFromType(const natChar* _path)
{
	natU32 hash = Hash::Compute(_path);
	return CreateFromType(hash);
}

Entity* PrefabManager::CreateFromType(natU32 _id)
{
	Entity* orig = Get(_id);
	assert(orig);

	Entity* entity = new Entity();
	orig->Clone(entity);

	return entity;
}

void PrefabManager::InitFromDirectory(const natChar* _path)
{
	FileManager* filemanager = GetEntity()->GetKernel()->GetLayer(Layer::Layer_0)->GetRootEntity()->GetComponent<FileManager>();
	assert(filemanager);

	// load all prefab
	std::vector<std::string> files;
	filemanager->EnumerateFiles(_path, files);

	for(std::vector<std::string>::iterator it = files.begin(); it != files.end(); ++it)
	{
		const natChar* path = (*it).c_str();
		Load(path);
	}
}







}