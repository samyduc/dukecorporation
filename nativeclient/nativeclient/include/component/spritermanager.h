#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#include <glm/glm.hpp>

#include <map>
#include <vector>

namespace tinyxml2
{
	class XMLElement;
}


namespace Natorium
{


struct ressource_sprite_t
{
	glm::vec2	m_size;
	ref_t		m_ref;
};

struct key_sprite_t
{
	natU32						m_id;
	natU64						m_time;
	struct ressource_sprite_t	m_ressource;
	glm::vec3					m_position;
	glm::vec3					m_pivot;
	glm::vec3					m_scale;
	natF32						m_rotation;
	natU32						m_z_index;
	natF32						m_alpha;
};

typedef std::vector<struct key_sprite_t> keyVector_t;

struct timeline_sprite_t
{
	std::string		m_name;
	natU32			m_id;
	keyVector_t		m_keys;
};

typedef std::vector<struct timeline_sprite_t> timelineVector_t;

struct animation_sprite_t
{
	std::string			m_name;
	natU64				m_duration;
	natBool				m_isLoop;
	timelineVector_t	m_timelines;
};

typedef std::map<ref_t, struct animation_sprite_t> animationMap_t;

struct scml_sprite_t
{
	std::string			m_path;
	ref_t				m_id;
	natU32				m_entityId;
	animationMap_t		m_animations;
};

static natU32 s_SpriterManager = Hash::Compute("SpriterManager");

class SpriterManager : public Component
{
public:
					SpriterManager();
	virtual			~SpriterManager();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_SpriterManager; }

	virtual void	Clone(Entity* _entity, natU32 _type) const;
	void			WriteData(Serializer& _ser);
	void			ReadData(Serializer& _ser);

	ref_t			Compute(const natChar* _path, natU32 _index) const;
	void			InitFromDirectory(const natChar* _path);

	void			Load(const natChar* _path, const natChar* _baseDir);

	const scml_sprite_t*	Get(const natChar* _path, natU32 _index) const;
	const scml_sprite_t*	Get(ref_t _id) const;

public:
	

public:

protected:
	// type helper, do not use as permanent storage
	typedef			std::map<natU32, std::map<natU32, struct ressource_sprite_t>> spriter_ressources_t;

	typedef			std::map<ref_t, scml_sprite_t> spriter_scml_t;
	spriter_scml_t	m_sprites;

protected:
	void			LoadRessources(spriter_ressources_t& _ressources, const natChar* _baseDir, tinyxml2::XMLElement* _element);
	void			LoadAnimations(struct scml_sprite_t& _scml, spriter_ressources_t& _ressources, tinyxml2::XMLElement* _element);
	void			LoadMainline(struct animation_sprite_t& _animation, tinyxml2::XMLElement* _element);
	void			LoadTimelines(struct animation_sprite_t& _animation, spriter_ressources_t& _ressources, tinyxml2::XMLElement* _element);
	



};




}