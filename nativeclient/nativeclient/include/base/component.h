#pragma once

#include "base/natdef.h"

#include <map>

namespace Natorium
{

class Entity;
class Component;

typedef std::map<natU32, Component*> components_t;

class Component
{
public:

	friend class Entity;

					Component();
	virtual			~Component();

	virtual void	OnInit();
	virtual void	OnTick(natU64 _dt);
	virtual void	OnDeInit();

	Entity*			GetEntity() const { return m_entity; }

	static natU32	GetType() { return 0; }

private:

	void			_Init(Entity& _entity);
	void			_Tick(natU64 _dt);
	void			_DeInit();

private:
	Entity*			m_entity;

};




}