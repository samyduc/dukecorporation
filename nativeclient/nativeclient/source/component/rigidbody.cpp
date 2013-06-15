#include "component/rigidbody.h"

#include "base/entity.h"
#include "base/kernel.h"
#include "base/layer.h"

#include "component/physicsmanager.h"
#include "component/transform.h"
#include "component/shape.h"

#include <assert.h>

namespace Natorium
{


RigidBody::RigidBody()
	: m_isDynamic(true)
	, m_isBullet(false)
	, m_maxSpeed(1.0f)
	, m_density(1.0f)
{

}

RigidBody::~RigidBody()
{

}


void RigidBody::OnInit()
{
	m_transform = GetEntity()->GetComponent<Transform>();
	m_shape = GetEntity()->GetComponent<Shape>();
	m_b2World = GetEntity()->GetKernel()->GetLayer(Layer::Layer_0)->GetRootEntity()->GetComponent<PhysicsManager>()->GetWorld();

	assert(m_transform);
	assert(m_shape);
	assert(m_b2World);

	glm::vec2 size = m_shape->GetSize();

	glm::vec3 pos = m_transform->GetPos();
	glm::vec3 rad = m_transform->GetRad();
	m_b2BodyDef.position.Set(pos.x / s_B2RatioPos, pos.y / s_B2RatioPos);
	m_b2BodyDef.angle = rad.z;
	m_b2BodyDef.userData = static_cast<void*>(GetEntity());
	
	if(m_isDynamic /*&& !m_isBullet*/)
	{
		m_b2BodyDef.type = b2_dynamicBody;
	}
	else if(m_isDynamic && m_isBullet)
	{
		m_b2BodyDef.type = b2_kinematicBody;
	}
	else
	{
		m_b2BodyDef.type = b2_staticBody;
	}
	m_b2BodyDef.bullet = m_isBullet;

	m_b2Body = m_b2World->CreateBody(&m_b2BodyDef);
	m_b2Shape.SetAsBox(size.x / s_B2RatioPos, size.y / s_B2RatioPos);
	m_b2Fixture = m_b2Body->CreateFixture(&m_b2Shape, m_density);
	m_b2Fixture->SetFriction(0.2f);
	m_b2Body->SetLinearDamping(10.f);
}

void RigidBody::OnTick(const natU64 _dt)
{
	// warning global coordinates (not local !)
	b2Vec2 b2_pos = m_b2Body->GetPosition();
	m_transform->m_pos.x = b2_pos.x * s_B2RatioPos;
	m_transform->m_pos.y = b2_pos.y * s_B2RatioPos;

}

void RigidBody::OnDeInit()
{
	assert(m_b2World != NULL);
	assert(m_b2Body != NULL);
	m_b2World->DestroyBody(m_b2Body);
}

void RigidBody::OnEnable()
{
	assert(m_b2Body != NULL);

	glm::vec3 pos = m_transform->GetPos();
	m_b2Body->SetTransform(b2Vec2(pos.x/s_B2RatioPos, pos.y/s_B2RatioPos), 0.f);

	m_b2Body->SetActive(true);
}

void RigidBody::OnDisable()
{
	assert(m_b2Body != NULL);
	m_b2Body->SetActive(false);
}

void RigidBody::ApplyLinearImpulse(glm::vec3& _impulse)
{
	b2Vec2 target_impulse = m_b2Body->GetLinearVelocity();
	target_impulse.x = _impulse.x - target_impulse.x;
	target_impulse.y = _impulse.y - target_impulse.y;

	if(!m_isBullet)
	{
		target_impulse *= m_b2Body->GetMass();
	}

	m_b2Body->ApplyLinearImpulse(target_impulse, m_b2Body->GetWorldCenter());

}

}