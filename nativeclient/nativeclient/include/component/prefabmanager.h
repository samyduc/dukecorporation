#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#include <map>

namespace Natorium
{

class Entity;

static natU32 s_PrefabManager = Hash::Compute("PrefabManager");

class PrefabManager : public Component
{
public:
					PrefabManager();
	virtual			~PrefabManager();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_PrefabManager; }

	virtual void	Clone(Entity* _entity, natU32 _type) const;
	void			WriteData(Serializer& _ser);
	void			ReadData(Serializer& _ser);

	void			InitFromDirectory(const natChar* _path);

	Entity*			Get(const natChar* _path);
	Entity*			Get(natU32 _id);

	Entity*			CreateFromType(const natChar* _path);
	Entity*			CreateFromType(ref_t _id);

	void			Load(const natChar* _path);
	
public:


private:

	typedef std::map<ref_t, Entity*> prefabs_t;
	prefabs_t m_prefabs;

};




}