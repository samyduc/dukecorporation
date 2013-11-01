#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#include "glm/glm.hpp"

#include <vector>
#include <map>
#include <string>

namespace tinyxml2
{
	class XMLElement;
}

namespace Natorium
{

static natU32 s_TiledMapManager = Hash::Compute("TiledMapManager");

struct TiledMap
{
	glm::vec2	m_size;
	glm::vec2	m_tileSize;
	glm::vec4	m_backgroundColor;
};

struct TiledTiles
{
	size_t		m_GID;
	ref_t		m_refTexture;
	std::string m_pathTexture;
	glm::vec2	m_size;
	natBool		m_isTile;
};

typedef std::vector<struct TiledTiles> tiledTiles_t;
typedef std::map<size_t, Entity*> cacheEntities_t;

struct TiledSet
{
	size_t			m_firstGID;
	tiledTiles_t	m_tiles;
};

typedef std::vector<struct TiledSet> tiledSets_t;

class TiledMapManager : public Component
{
public:
					TiledMapManager();
	virtual			~TiledMapManager();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_TiledMapManager; }

	virtual void	Clone(Entity* _entity, natU32 _type) const;
	void			WriteData(Serializer& _ser);
	void			ReadData(Serializer& _ser);

	void			Load(const natChar* _path);

protected:
	void			Load(const natU8* _bytes, size_t _size);

	void			LoadMap(struct TiledMap& _tiledMap, tinyxml2::XMLElement* _element);
	void			LoadTileSets(tiledSets_t& _tileSets, tinyxml2::XMLElement* _element);
	void			LoadImage(struct TiledSet& _tileSet, natBool _isTile, tinyxml2::XMLElement* _element);
	void			LoadRessources(tiledSets_t& _tileSets);
	void			LoadLayers(struct TiledMap& _tiledMap, tiledSets_t& _tileSets, tinyxml2::XMLElement* _element);
	void			LoadObjectGroup(struct TiledMap& _tiledMap, tinyxml2::XMLElement* _element);
	Entity*			LoadTile(struct TiledMap& _tiledMap, tiledSets_t& _tileSets, size_t _gid, size_t _cellNumber);
	
	TiledTiles		GetTile(tiledSets_t& _tileSets, size_t _gid);
	Entity*			GetCacheEntity(size_t _gid);
	void			ClearCacheEntities();

private:
	cacheEntities_t	m_cacheEntities;

};




}