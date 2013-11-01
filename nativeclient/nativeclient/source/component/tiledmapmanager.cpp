#include "component/tiledmapmanager.h"

#include "base/entity.h"
#include "base/kernel.h"
#include "base/layer.h"
#include "base/component.h"
#include "base/hash.h"

#include "component/transform.h"
#include "component/glrender.h"
#include "component/squareshape.h"

#include "component/filemanager.h"
#include "component/texturemanager.h"
#include "component/prefabmanager.h"
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
	FileManager* filemanager = GetEntity()->GetKernel()->GetLayer(Layer::s_LayerManager)->GetRootEntity()->GetComponent<FileManager>();
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

	// load tiledsheet
	tiledSets_t sheets;
	LoadTileSets(sheets, element);

	// load ressources
	LoadRessources(sheets);

	// start loading maps (tiles)
	LoadLayers(tileMap, sheets, element);

	//load objects now
	LoadObjectGroup(tileMap, element);

	// clean
	ClearCacheEntities();
}


void TiledMapManager::LoadMap(struct TiledMap& _tiledMap, tinyxml2::XMLElement* _element)
{
	_tiledMap.m_size.x = static_cast<natF32>(_element->IntAttribute("width"));
	_tiledMap.m_size.y = static_cast<natF32>(_element->IntAttribute("height"));
	_tiledMap.m_tileSize.x = static_cast<natF32>(_element->IntAttribute("tilewidth"));
	_tiledMap.m_tileSize.y = static_cast<natF32>(_element->IntAttribute("tileheight"));

	// HEX to RGB convertion
	const natChar* color = _element->Attribute("backgroundcolor");
	if(color)
	{
		std::string hexColor = color;
		assert(hexColor[0] == '#');

		natChar *end;

		std::string R = hexColor.substr(1, 2);
		_tiledMap.m_backgroundColor.r = static_cast<natF32>(strtol(R.c_str(), &end, 16)) / 255.f;

		std::string G = hexColor.substr(3, 2);
		_tiledMap.m_backgroundColor.g = static_cast<natF32>(strtol(G.c_str(), &end, 16)) / 255.f;

		std::string B = hexColor.substr(5, 2);
		_tiledMap.m_backgroundColor.b = static_cast<natF32>(strtol(B.c_str(), &end, 16)) / 255.f;

		_tiledMap.m_backgroundColor.a = 1.0f;

		// override clear color
		GLManager* glmanager = GetEntity()->GetKernel()->GetLayer(Layer::s_LayerManager)->GetRootEntity()->GetComponent<GLManager>();
		assert(glmanager);
		glmanager->SetClearColor(_tiledMap.m_backgroundColor);
	}
}

void TiledMapManager::LoadTileSets(tiledSets_t& _tileSets, tinyxml2::XMLElement* _element)
{
	tinyxml2::XMLElement* element_tileset = _element->FirstChildElement("tileset");
	while(element_tileset)
	{
		TiledSet tileset;
		tileset.m_firstGID = element_tileset->IntAttribute("firstgid");

		// iterate over image (one or many in tile)
		tinyxml2::XMLElement* element_tile = element_tileset->FirstChildElement("tile");
		while(element_tile)
		{
			tinyxml2::XMLElement* element_image = element_tile->FirstChildElement("image");
			LoadImage(tileset, true, element_image);
			element_tile = element_tile->NextSiblingElement("tile");
		}

		tinyxml2::XMLElement* element_image = element_tileset->FirstChildElement("image");
		if(element_image)
		{
			LoadImage(tileset, false, element_image);
		}

		_tileSets.push_back(tileset);
		element_tileset = element_tileset->NextSiblingElement("tileset");
	}

}

void TiledMapManager::LoadImage(struct TiledSet& _tileSet, natBool _isTile, tinyxml2::XMLElement* _element)
{
	TiledTiles tiles;

	// parse texture name (with correction)
	std::string source = _element->Attribute("source");
	std::string formatedSource = source.substr(2, source.size());
	tiles.m_pathTexture = "/data";
	tiles.m_pathTexture += formatedSource;
	tiles.m_refTexture = Hash::Compute(tiles.m_pathTexture.c_str());

	tiles.m_size.x = static_cast<natF32>(_element->IntAttribute("width"));
	tiles.m_size.y = static_cast<natF32>(_element->IntAttribute("height"));

	tiles.m_isTile = _isTile;

	tiles.m_GID = _tileSet.m_tiles.size() + _tileSet.m_firstGID;

	_tileSet.m_tiles.push_back(tiles);
}

void TiledMapManager::LoadRessources(tiledSets_t& _tileSets)
{
	TextureManager* texturemanager = GetEntity()->GetKernel()->GetLayer(Layer::s_LayerManager)->GetRootEntity()->GetComponent<TextureManager>();

	for(tiledSets_t::iterator it_sets = _tileSets.begin(); it_sets != _tileSets.end(); ++it_sets)
	{
		TiledSet& set = (*it_sets);

		for(tiledTiles_t::iterator it_tiles = set.m_tiles.begin(); it_tiles != set.m_tiles.end(); ++it_tiles)
		{
			TiledTiles& tiles =  (*it_tiles);
			texturemanager->Load(tiles.m_pathTexture.c_str(), FLAG_MIPMAPS |  FLAG_COMPRESS_TO_DXT | FLAG_TEXTURE_REPEATS);

			if(tiles.m_size.x == 0.0f || tiles.m_size.y == 0.0f)
			{
				tiles.m_size = texturemanager->GetTextureSize(tiles.m_pathTexture.c_str());
			}
		}
	}
}

void TiledMapManager::LoadLayers(struct TiledMap& _tiledMap, tiledSets_t& _tileSets, tinyxml2::XMLElement* _element)
{
	tinyxml2::XMLElement* element_layer = _element->FirstChildElement("layer");
	while(element_layer)
	{
		// allocate layer
		Layer* layer = GetEntity()->GetKernel()->AppendLayer();

		size_t tileNumber = 0;
		tinyxml2::XMLElement* element_data = element_layer->FirstChildElement("data");

		tinyxml2::XMLElement* element_tile = element_data->FirstChildElement("tile");
		while(element_tile)
		{
			size_t gid = element_tile->UnsignedAttribute("gid");

			// load here the good tile
			if(gid != 0)
			{
				Entity* entity = LoadTile(_tiledMap, _tileSets, gid, tileNumber);
				GetEntity()->GetKernel()->AddEntity(layer->GetLayerID(), entity);
			}

			++tileNumber;
			element_tile = element_tile->NextSiblingElement("tile");
		}

		element_layer = element_layer->NextSiblingElement("layer");
	}
}

void TiledMapManager::LoadObjectGroup(struct TiledMap& _tiledMap, tinyxml2::XMLElement* _element)
{
	PrefabManager* prefabmanager = GetEntity()->GetKernel()->GetLayer(Layer::s_LayerManager)->GetRootEntity()->GetComponent<PrefabManager>();
	assert(prefabmanager);

	tinyxml2::XMLElement* element_objectgroup = _element->FirstChildElement("objectgroup");
	while(element_objectgroup)
	{
		// allocate layer
		Layer* layer = GetEntity()->GetKernel()->AppendLayer();

		tinyxml2::XMLElement* element_object = element_objectgroup->FirstChildElement("object");
		while(element_object)
		{
			//
			glm::vec3 spawn_pos(0.f);
			spawn_pos.x = static_cast<natF32>(element_object->IntAttribute("x"));
			spawn_pos.y = static_cast<natF32>(element_object->IntAttribute("y"));

			const natChar* type_str = element_object->Attribute("type");
			ref_t type = Hash::Compute(type_str);

			Entity* entity = prefabmanager->CreateFromType(type);

			Transform* transform = entity->GetComponent<Transform>();
			if(transform)
			{
				transform->m_pos = spawn_pos;
			}

			layer->AddEntity(entity);
			//

			element_object = element_object->NextSiblingElement("object");
		}

		element_objectgroup = element_objectgroup->NextSiblingElement("objectgroup");
	}

}

Entity* TiledMapManager::LoadTile(struct TiledMap& _tiledMap, tiledSets_t& _tileSets, size_t _gid, size_t _cellNumber)
{
	Entity* blueprint = GetCacheEntity(_gid);

	if(blueprint == nullptr)
	{
		// build manually entity
		blueprint = new Entity();
		blueprint->AddComponent<Transform>();
		SquareShape* squareshape = blueprint->AddComponent<SquareShape>();
		GLRender* glrender = blueprint->AddComponent<GLRender>();

		// build blueprint
		TiledTiles tile =  GetTile(_tileSets, _gid);
		
		if(tile.m_isTile)
		{
			// raw picture
			squareshape->m_size = tile.m_size;
			squareshape->m_textureRef = tile.m_refTexture;
			squareshape->m_color = glm::vec4(1.f, 1.f, 1.f, 1.f);
			squareshape->m_repeat = 1.f;
			squareshape->m_uv = glm::mat4x2(0.f);

			glrender->m_shapeType = Hash::Compute("SquareShape");
			glrender->m_type = Hash::Compute("monotexture");
		}
		else
		{
			// cut the picture and compute uv
			glm::mat4x2 uv;

			size_t relative_gid = _gid - tile.m_GID;
			size_t line = (relative_gid) / static_cast<natU32>(tile.m_size.x / _tiledMap.m_tileSize.x);
			size_t column = (relative_gid) % static_cast<natU32>( tile.m_size.x / _tiledMap.m_tileSize.x);

			glm::vec2 pixel_pos;
			pixel_pos.x = column * _tiledMap.m_tileSize.x;
			pixel_pos.y = line * _tiledMap.m_tileSize.y;

			uv[0].x = (pixel_pos.x) / tile.m_size.x;
			uv[0].y = 1.f - (pixel_pos.y) / tile.m_size.y;

			uv[1].x = (pixel_pos.x + _tiledMap.m_tileSize.x) / tile.m_size.x;
			uv[1].y = 1.f - (pixel_pos.y) / tile.m_size.y;

			uv[2].x = (pixel_pos.x) / tile.m_size.x;
			uv[2].y = 1.f - (pixel_pos.y + _tiledMap.m_tileSize.y) / tile.m_size.y;

			uv[3].x = (pixel_pos.x + _tiledMap.m_tileSize.x) / tile.m_size.x;
			uv[3].y = 1.f - (pixel_pos.y + _tiledMap.m_tileSize.y) / tile.m_size.y;


			squareshape->m_size = _tiledMap.m_tileSize;
			squareshape->m_textureRef = tile.m_refTexture;
			squareshape->m_color = glm::vec4(1.f, 1.f, 1.f, 1.f);
			squareshape->m_repeat = 0.f;
			squareshape->m_uv = uv;

			glrender->m_shapeType = Hash::Compute("SquareShape");
			glrender->m_type = Hash::Compute("monotexture");
		}

		// update cache
		m_cacheEntities[_gid] = blueprint;
	}

	Entity* entity = new Entity();
	blueprint->Clone(entity);

	size_t line = _cellNumber / static_cast<natU32>(_tiledMap.m_size.x);
	size_t column = _cellNumber % static_cast<natU32>(_tiledMap.m_size.x);

	Transform* transform = entity->GetComponent<Transform>();
	SquareShape* squareshape = entity->GetComponent<SquareShape>();

	transform->m_pos.x = column * _tiledMap.m_tileSize.x + squareshape->m_size.x / 2.f;
	transform->m_pos.y = line * _tiledMap.m_tileSize.y - squareshape->m_size.y / 2.f;
	//transform->m_rot = glm::quat(glm::vec3(0.f, 0.f, s_PI));

	return entity;
}

Entity* TiledMapManager::GetCacheEntity(size_t _gid)
{
	Entity* ret = nullptr;
	cacheEntities_t::iterator it = m_cacheEntities.find(_gid);

	if(it != m_cacheEntities.end())
	{
		ret = it->second;
	}

	return ret;
}

void TiledMapManager::ClearCacheEntities()
{
	for(cacheEntities_t::iterator it = m_cacheEntities.begin(); it != m_cacheEntities.end(); ++it)
	{
		Entity* entity = it->second;
		delete entity;
	}
	m_cacheEntities.clear();
}

TiledTiles TiledMapManager::GetTile(tiledSets_t& _tileSets, size_t _gid)
{
	TiledTiles ret;

	for(tiledSets_t::iterator it_sets = _tileSets.begin(); it_sets != _tileSets.end(); ++it_sets)
	{
		natBool goodTile = false;
		TiledSet& set = (*it_sets);
		tiledSets_t::iterator it_sets_next = it_sets + 1;
		
		if(it_sets_next != _tileSets.end())
		{
			TiledSet& set_next = (*it_sets_next);

			if(_gid >= set.m_firstGID && _gid < set_next.m_firstGID)
			{
				goodTile = true;
			}
		}
		else
		{
			goodTile = true;
		}

		if(goodTile)
		{
			for(tiledTiles_t::iterator it_tiles = set.m_tiles.begin(); it_tiles != set.m_tiles.end(); ++it_tiles)
			{
				TiledTiles& tiles =  (*it_tiles);
				
				if(tiles.m_GID == _gid || !tiles.m_isTile)
				{
					ret = tiles;
					break;
				}
			}
			break;
		}
	}
	
	return ret;
}

}