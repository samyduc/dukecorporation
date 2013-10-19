#include "component/tiledmapmanager.h"

#include "base/entity.h"
#include "base/kernel.h"
#include "base/layer.h"
#include "base/component.h"
#include "base/hash.h"

#include "component/filemanager.h"
#include "component/glmanager.h"
#include "component/componentfactory.h"

#include <vector>
#include <string>

#include "tinyxml/tinyxml2.h"


namespace Natorium
{

TiledMapManager::TiledMapManager()
{

}

TiledMapManager::~TiledMapManager()
{

}

void TiledMapManager::OnInit()
{

}

void TiledMapManager::OnTick(const natU64 _dt)
{

}

void TiledMapManager::OnDeInit()
{

}

void TiledMapManager::Load(const natChar* _path)
{
	FileManager* filemanager = GetEntity()->GetKernel()->GetLayer(Layer::Layer_0)->GetRootEntity()->GetComponent<FileManager>();
	assert(filemanager);

	size_t size;
	natU8 *buffer = filemanager->Read(_path, &size);
	Load(buffer, size);

	delete buffer;
}

void TiledMapManager::Load(const natU8* _bytes, size_t _size)
{
	tinyxml2::XMLDocument doc;
	doc.Parse(reinterpret_cast<const natChar*>(_bytes), _size);

	tinyxml2::XMLElement* element = doc.FirstChildElement("map");
	assert(element);

	struct TiledMap tileMap;
	LoadMap(tileMap, element);

	// override clear color
	GLManager* glmanager = GetEntity()->GetKernel()->GetLayer(Layer::Layer_0)->GetRootEntity()->GetComponent<GLManager>();
	assert(glmanager);
	glmanager->SetClearColor(tileMap.m_backgroundColor);

}

void TiledMapManager::LoadMap(struct TiledMap& _tiledMap, tinyxml2::XMLElement* _element)
{
	_tiledMap.m_height = static_cast<natU32>(_element->IntAttribute("width"));
	_tiledMap.m_height = static_cast<natU32>(_element->IntAttribute("height"));
	_tiledMap.m_height = static_cast<natU32>(_element->IntAttribute("tilewidth"));
	_tiledMap.m_height = static_cast<natU32>(_element->IntAttribute("tileheight"));

	// HEX to RGB convertion
	std::string hexColor = _element->Attribute("backgroundcolor");
	assert(hexColor[0] == '#');

	natChar *end;

	std::string R = hexColor.substr(1, 2);
	_tiledMap.m_backgroundColor.r = static_cast<natF32>(strtol(R.c_str(), &end, 16)) / 255.f;

	std::string G = hexColor.substr(3, 2);
	_tiledMap.m_backgroundColor.g = static_cast<natF32>(strtol(G.c_str(), &end, 16)) / 255.f;

	std::string B = hexColor.substr(5, 2);
	_tiledMap.m_backgroundColor.b = static_cast<natF32>(strtol(B.c_str(), &end, 16)) / 255.f;

	_tiledMap.m_backgroundColor.a = 1.0f;

}















}