#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#include <assert.h>
#include <list>

namespace Natorium
{

class Entity;

static natU32 s_SceneManager = Hash::Compute("SceneManager");

class SceneManager : public Component
{
public:
					SceneManager();
	virtual			~SceneManager();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_SceneManager; }

	virtual void	Clone(Entity* _entity, natU32 _type) const;
	void			WriteData(Serializer& _ser);
	void			ReadData(Serializer& _ser);

private:


};




}