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
	, m_rateStep(1.f/60.f)
	, m_acc(0.f)
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
}

void PhysicsManager::OnTick(const natU64 _dt)
{
	m_acc += _dt;

	if(m_acc >= m_rateStep)
	{
		m_acc -= m_rateStep;
		m_b2World->Step(m_rateStep, m_velocityIterations, m_positionIterations);
		m_b2World->ClearForces();
	}
}

void PhysicsManager::OnDeInit()
{
	delete m_b2World;
}


void PhysicsManager::BeginContact(b2Contact* _contact)
{
	Entity *A = static_cast<Entity*>(_contact->GetFixtureA()->GetBody()->GetUserData());
	Entity *B = static_cast<Entity*>(_contact->GetFixtureB()->GetBody()->GetUserData());

	A->OnEnterCollide(_contact);
	B->OnEnterCollide(_contact);
}

void PhysicsManager::EndContact(b2Contact* _contact)
{
	Entity *A = static_cast<Entity*>(_contact->GetFixtureA()->GetBody()->GetUserData());
	Entity *B = static_cast<Entity*>(_contact->GetFixtureB()->GetBody()->GetUserData());

	A->OnExitCollide(_contact);
	B->OnExitCollide(_contact);
}







}