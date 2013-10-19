#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#include "glm/glm.hpp"

namespace tinyxml2
{
	class XMLElement;
}

namespace Natorium
{

static natU32 s_TiledMapManager = Hash::Compute("TiledMapManager");

struct TiledMap
{
	natU32		m_width;
	natU32		m_height;
	natU32		m_tileWidth;
	natU32		m_tileHeight;
	glm::vec4	m_backgroundColor;
};

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

private:

};




}