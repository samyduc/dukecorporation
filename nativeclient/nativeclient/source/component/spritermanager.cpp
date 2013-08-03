#include "component/spritermanager.h"


#include "base/entity.h"
#include "base/kernel.h"
#include "base/layer.h"
#include "base/component.h"
#include "base/hash.h"

#include "component/filemanager.h"
#include "component/glmanager.h"

#include "component/texturemanager.h"

#include "tinyxml/tinyxml2.h"

#include <cassert>
#include <sstream>

namespace Natorium
{

SpriterManager::SpriterManager()
{

}

SpriterManager::~SpriterManager()
{

}

void SpriterManager::OnInit()
{
	InitFromDirectory("/data/spriter");
}

void SpriterManager::OnTick(const natU64 _dt)
{

}

void SpriterManager::OnDeInit()
{
	m_sprites.clear();
}

void SpriterManager::InitFromDirectory(const natChar* _path)
{
	FileManager* filemanager = GetEntity()->GetKernel()->GetLayer(Layer::Layer_0)->GetRootEntity()->GetComponent<FileManager>();
	assert(filemanager);

	// load all prefab
	std::vector<std::string> directory_listing;
	filemanager->EnumerateFiles(_path, directory_listing);

	for(std::vector<std::string>::iterator directory_it = directory_listing.begin(); directory_it != directory_listing.end(); ++directory_it)
	{
		const natChar* directory_path = (*directory_it).c_str();
		
		std::vector<std::string> files;
		filemanager->EnumerateFiles(directory_path, files);
		for(std::vector<std::string>::iterator it = files.begin(); it != files.end(); ++it)
		{
			// check if scml file
			const natChar* path = (*it).c_str();
			std::string extension;

			filemanager->GetFileExtension(path, extension);
			if(strcmp(extension.c_str(), "scml") == 0)
			{
				Load(path, directory_path);
			}
		}
	}
}

ref_t SpriterManager::Compute(const natChar* _path, natU32 _index) const
{
	std::ostringstream oss;
	oss << _path << ':' << _index;
	return Hash::Compute(oss.str().c_str());
}

const scml_sprite_t* SpriterManager::Get(const natChar* _path, natU32 _index) const
{
	ref_t id = Compute(_path, _index);
	return Get(id);
}

const scml_sprite_t* SpriterManager::Get(ref_t _id) const
{
	const scml_sprite_t* ret = nullptr;
	spriter_scml_t::const_iterator it = m_sprites.find(_id);

	if(it != m_sprites.end())
	{
		ret = &(it->second);
	}

	return ret;
}

void SpriterManager::Load(const natChar* _path, const natChar* _baseDir)
{
	FileManager* filemanager = GetEntity()->GetKernel()->GetLayer(Layer::Layer_0)->GetRootEntity()->GetComponent<FileManager>();
	assert(filemanager);

	TextureManager* texturemanager = GetEntity()->GetKernel()->GetLayer(Layer::Layer_0)->GetRootEntity()->GetComponent<TextureManager>();
	assert(texturemanager);

	size_t size;
	natU8* buffer = filemanager->Read(_path, &size);

	tinyxml2::XMLDocument doc;

	doc.Parse(reinterpret_cast<natChar*>(buffer), size);

	tinyxml2::XMLElement* element = doc.FirstChildElement("spriter_data");
	assert(element);

	// loading ressources used by the sprite
	spriter_ressources_t ressources;
	LoadRessources(ressources, _baseDir, element);

	element = element->FirstChildElement("entity");

	while(element)
	{
		struct scml_sprite_t scml;
		scml.m_path = _path;
		LoadAnimations(scml, ressources, element);

		// store resulting scml file
		scml.m_entityId = static_cast<natU32>(element->IntAttribute("id"));
		scml.m_id = Compute(_path, scml.m_entityId);

		// copy
		m_sprites[scml.m_id] = scml;
		element = element->NextSiblingElement("entity");
	}

	delete buffer;
}

void SpriterManager::LoadRessources(spriter_ressources_t& _ressources, const natChar* _baseDir, tinyxml2::XMLElement* _element)
{
	FileManager* filemanager = GetEntity()->GetKernel()->GetLayer(Layer::Layer_0)->GetRootEntity()->GetComponent<FileManager>();
	assert(filemanager);

	TextureManager* texturemanager = GetEntity()->GetKernel()->GetLayer(Layer::Layer_0)->GetRootEntity()->GetComponent<TextureManager>();
	assert(texturemanager);

	tinyxml2::XMLElement* element = _element;
	element = element->FirstChildElement("folder");

	while(element)
	{
		natU32 folder_id = static_cast<natU32>(element->IntAttribute("id"));
		_ressources[folder_id];
		// iterate in file
		tinyxml2::XMLElement* element_file = element->FirstChildElement("file");

		while(element_file)
		{
			natU32 file_id = static_cast<natU32>(element_file->IntAttribute("id"));
			const natChar* file_relativePath = element_file->Attribute("name");

			std::string file_path;
			filemanager->ConcatenatePath(_baseDir, file_relativePath, file_path);
			texturemanager->Preload(file_path.c_str());

			struct ressource_sprite_t ressourceinfo;
			ressourceinfo.m_ref = Hash::Compute(file_path.c_str());
			ressourceinfo.m_size.x = static_cast<natF32>(element_file->FloatAttribute("width"));
			ressourceinfo.m_size.y = static_cast<natF32>(element_file->FloatAttribute("height"));

			_ressources[folder_id][file_id] = ressourceinfo;
			element_file = element_file->NextSiblingElement("file");
		}
		element = element->NextSiblingElement("folder");
	}
}

void SpriterManager::LoadAnimations(struct scml_sprite_t& _scml, spriter_ressources_t& _ressources, tinyxml2::XMLElement* _element)
{
	tinyxml2::XMLElement* element = _element;
	element = element->FirstChildElement("animation");

	while(element)
	{
		struct animation_sprite_t animation;
		animation.m_name = element->Attribute("name");
		animation.m_duration = static_cast<natU64>(element->IntAttribute("length"));
		animation.m_isLoop = element->BoolAttribute("looping");

		LoadMainline(animation, element);
		LoadTimelines(animation, _ressources, element);

		ref_t animation_id = Hash::Compute(animation.m_name.c_str());
		_scml.m_animations[animation_id] = animation;
		element = element->NextSiblingElement("animation");
	}
}

void SpriterManager::LoadMainline(struct animation_sprite_t& _animation, tinyxml2::XMLElement* _element)
{
	// mainLine allocate all timeline and keys
	tinyxml2::XMLElement* element = _element;
	element = element->FirstChildElement("mainline");
	element = element->FirstChildElement("key");

	while(element)
	{
		natU32 key_id = static_cast<natU32>(element->IntAttribute("id"));
		natU64 key_time = static_cast<natU64>(element->IntAttribute("time"));
		tinyxml2::XMLElement* object_ref_element = element->FirstChildElement("object_ref");

		while(object_ref_element)
		{
			natU32 timeline_id = static_cast<natU32>(object_ref_element->IntAttribute("timeline"));
			// insertion must be ordered !
			if(timeline_id >= _animation.m_timelines.size())
			{
				for(size_t i = _animation.m_timelines.size(); i <= timeline_id; ++i)
				{
					struct timeline_sprite_t timeline;
					timeline.m_id = static_cast<natU32>(i);
					_animation.m_timelines.push_back(timeline);
				}
			}

			// add missing timeline
			struct timeline_sprite_t& timeline = _animation.m_timelines[timeline_id];

			// insert key
			if(key_id >= timeline.m_keys.size())
			{
				assert(key_id == timeline.m_keys.size());

				struct key_sprite_t key;
				key.m_id = key_id;
				key.m_z_index = static_cast<natU32>(object_ref_element->IntAttribute("z_index"));
				key.m_time = key_time;

				timeline.m_keys.push_back(key);
			}
			else
			{
				// must happen at each iteration
				assert(false);
			}

			object_ref_element = object_ref_element->NextSiblingElement("object_ref");
		}

		element = element->NextSiblingElement("key");
	}
}

void SpriterManager::LoadTimelines(struct animation_sprite_t& _animation, spriter_ressources_t& _ressources, tinyxml2::XMLElement* _element)
{
	// just fill the hole now
	tinyxml2::XMLElement* element = _element;
	element = element->FirstChildElement("timeline");

	while(element)
	{
		natU32 timeline_id = static_cast<natU32>(element->IntAttribute("id"));
		const natChar* timeline_name = element->Attribute("name");

		struct timeline_sprite_t& timeline = _animation.m_timelines[timeline_id];
		timeline.m_name = timeline_name;

		tinyxml2::XMLElement* key_element = element->FirstChildElement("key");

		while(key_element)
		{
			natU32 key_id = key_element->IntAttribute("id");
			tinyxml2::XMLElement* object_element = key_element->FirstChildElement("object");

			struct key_sprite_t& key = timeline.m_keys[key_id];
			key.m_pivot.x = static_cast<natF32>(object_element->FloatAttribute("pivot_x"));
			key.m_pivot.y = static_cast<natF32>(object_element->FloatAttribute("pivot_y"));
			key.m_pivot.z = 0.0f;

			key.m_position.x = static_cast<natF32>(object_element->FloatAttribute("x"));
			key.m_position.y = static_cast<natF32>(object_element->FloatAttribute("y"));
			key.m_position.z = 0.0f;

			key.m_scale.x = static_cast<natF32>(object_element->FloatAttribute("scale_x"));
			key.m_scale.y = static_cast<natF32>(object_element->FloatAttribute("scale_y"));
			key.m_scale.z = 0.0f;

			key.m_rotation = static_cast<natF32>(object_element->FloatAttribute("angle"));

			const natChar* alpha = object_element->Attribute("a");

			if(alpha != nullptr)
			{
				key.m_alpha = static_cast<natF32>(object_element->FloatAttribute("a"));
			}
			else
			{
				key.m_alpha = 1.0f;
			}

			natU32 folder_id = static_cast<natU32>(object_element->IntAttribute("folder"));
			natU32 file_id = static_cast<natU32>(object_element->IntAttribute("file"));
			key.m_ressource = _ressources[folder_id][file_id];

			key_element = key_element->NextSiblingElement("key");
		}

		element = element->NextSiblingElement("timeline");
	}
}



}