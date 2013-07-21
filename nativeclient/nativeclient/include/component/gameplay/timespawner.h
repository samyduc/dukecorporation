#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#include "component/gameplay/spawner.h"

#include <glm/glm.hpp>

namespace Natorium
{

static natU32 s_TimeSpawner = Hash::Compute("TimeSpawner");

class TimeSpawner : public Spawner
{
public:
	friend class AiController;

					TimeSpawner();
	virtual			~TimeSpawner();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);

	virtual void	Clone(Entity* _entity, natU32 _type) const;
	void			WriteData(Serializer& _ser);
	void			ReadData(Serializer& _ser);

	static natU32	GetType() { return s_TimeSpawner; }

public:
	natU64			m_interval;

private:
	natU64			m_currentInterval;

};




}