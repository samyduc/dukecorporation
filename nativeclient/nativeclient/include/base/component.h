#pragma once

#include "base/natdef.h"

namespace Natorium
{

class Entity;

class Component
{
public:

	friend class Entity;

						Component();
	virtual				~Component();

	virtual void		OnInit();
	virtual void		OnTick(natU64 _dt);
	virtual void		OnDeInit();

			natBool		IsInit() { return m_isInit; }		
			Entity*		GetEntity() const { return m_entity; }

	static	natU32		GetType() { return 0; }

private:

	void				_Init(Entity& _entity);
	void				_Tick(natU64 _dt);
	void				_DeInit();

private:
	Entity*				m_entity;
	natBool				m_isInit;

};




}