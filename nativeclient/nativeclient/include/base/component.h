#pragma once

#include "base/natdef.h"
#include "base/contact.h"

#include <cassert>

namespace Natorium
{

class Entity;
class Contact;
class Serializer;

class Component
{
public:

	friend class Entity;

						Component();
	virtual				~Component();

	virtual void		OnInit();
	virtual void		OnTick(const natU64 _dt);
	virtual void		OnDeInit();

	virtual void		OnEnable() {}
	virtual void		OnDisable() {}

	virtual void		OnEnterCollide(Contact *_contact) {}
	virtual void		OnExitCollide(Contact *_contact) {}

			natBool		IsInit() { return m_isInit; }		
			Entity*		GetEntity() { return m_entity; }

	static	natU32		GetType() { return 0; }

	// generated code
	virtual void		Clone(Entity* _entity, natU32 _type) const = 0; 
	virtual void		WriteData(Serializer& _ser) = 0;
	virtual void		ReadData(Serializer& _ser) = 0;

private:

	void				_Init(Entity& _entity);
	void				_Tick(natU64 _dt);
	void				_DeInit();

private:
	Entity*				m_entity;
	natBool				m_isInit;

};




}