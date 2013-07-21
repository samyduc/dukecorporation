#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"


namespace Natorium
{

class Spawner;

static natU32 s_Spawned = Hash::Compute("Spawned");

class Spawned : public Component
{
public:

	friend class Spawner;

					Spawned();
	virtual			~Spawned();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	virtual void	Clone(Entity* _entity, natU32 _type) const;
	void			WriteData(Serializer& _ser);
	void			ReadData(Serializer& _ser);

	static natU32	GetType() { return s_Spawned; }

	void			Kill();
	Spawner*		GetSpawner() { return m_spawner; }

public:

private:
	Spawner*		m_spawner;


};








}