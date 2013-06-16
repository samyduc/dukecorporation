#include "component/physicsmanager.h"
#include "base/kernel.h"
#include "base/layer.h"

#include "entity/player.h"
#include "entity/civilian.h"
#include "entity/spawnercivilian.h"

namespace Natorium
{

PhysicsManager::PhysicsManager()
	: m_velocityIterations(6)
	, m_positionIterations(2)
	, m_rateStepFloat(1/60.f)
	, m_acc(0)
	, m_b2World(nullptr)
{
}

PhysicsManager::~PhysicsManager()
{
}

void PhysicsManager::OnInit()
{
	b2Vec2 gravity(0.f, 0.f);
	m_b2World = new b2World(gravity);
	m_b2World->SetContactListener(this);

	m_rateStep = static_cast<natU64>(m_rateStepFloat*1000);
}

void PhysicsManager::OnTick(const natU64 _dt)
{
	m_acc += _dt;

	while(m_acc >= m_rateStep)
	{
		m_acc -= m_rateStep;
		m_b2World->Step(m_rateStepFloat, m_velocityIterations, m_positionIterations);
		m_b2World->ClearForces();
	}

	ResolveContact();
}

void PhysicsManager::ResolveContact()
{
	for(contacts_t::iterator it = m_beginContacts.begin(); it != m_beginContacts.end(); ++it)
	{
		Contact* contact = &(*it);
		_BeginContact(contact);
	}
	m_beginContacts.clear();

	for(contacts_t::iterator it = m_endContacts.begin(); it != m_endContacts.end(); ++it)
	{
		Contact* contact = &(*it);
		_EndContact(contact);
	}
	m_endContacts.clear();
}

void PhysicsManager::OnDeInit()
{
	delete m_b2World;
}


void PhysicsManager::BeginContact(b2Contact* _contact)
{
	Contact contact;
	contact.A = _contact->GetFixtureA();
	contact.B = _contact->GetFixtureB();

	m_beginContacts.push_back(contact);
}

void PhysicsManager::EndContact(b2Contact* _contact)
{
	Contact contact;
	contact.A = _contact->GetFixtureA();
	contact.B = _contact->GetFixtureB();

	m_endContacts.push_back(contact);
}

void PhysicsManager::_BeginContact(Contact* _contact)
{
	Entity *A = static_cast<Entity*>(_contact->A->GetBody()->GetUserData());
	Entity *B = static_cast<Entity*>(_contact->B->GetBody()->GetUserData());

	A->OnEnterCollide(_contact);
	B->OnEnterCollide(_contact);
}

void PhysicsManager::_EndContact(Contact* _contact)
{
	Entity *A = static_cast<Entity*>(_contact->A->GetBody()->GetUserData());
	Entity *B = static_cast<Entity*>(_contact->B->GetBody()->GetUserData());

	A->OnExitCollide(_contact);
	B->OnExitCollide(_contact);
}







}