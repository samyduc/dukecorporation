#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"
#include "base/contact.h"

#include <glm/glm.hpp>

#include <Box2d/Box2d.h>

#include <vector>

namespace Natorium
{

static natU32 s_PhysicsManager = Hash::Compute("s_PhysicsManager");

class Shape;

class PhysicsManager : public Component, public b2ContactListener
{
public:
					PhysicsManager();
	virtual			~PhysicsManager();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_PhysicsManager; }

	virtual void	Clone(Entity* _entity, natU32 _type) const;
	void			WriteData(Serializer& _ser);
	void			ReadData(Serializer& _ser);

	b2World*		GetWorld() { return m_b2World; }

	// contact listener
	void			BeginContact(b2Contact* _contact);
	void			EndContact(b2Contact* _contact);

protected:

	void			_BeginContact(Contact* _contact);
	void			_EndContact(Contact* _contact);

	void			ResolveContact();

private:
	b2World*		m_b2World;
	natU64			m_acc;
	natU64			m_rateStep;
	natF32			m_rateStepFloat;
	natU32			m_velocityIterations;
	natU32			m_positionIterations;

	typedef std::vector<Contact> contacts_t;
	contacts_t		m_beginContacts;
	contacts_t		m_endContacts;

};




}