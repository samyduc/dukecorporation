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
	, m_restitution(0.0f)
	, m_linearDampling(0.0f)
	, m_shape(nullptr)
	, m_b2Shape(nullptr)
{

}

RigidBody::~RigidBody()
{

}


void RigidBody::OnInit()
{
	m_transform = GetEntity()->GetComponent<Transform>();
	m_b2World = GetEntity()->GetKernel()->GetLayer(Layer::s_LayerManager)->GetRootEntity()->GetComponent<PhysicsManager>()->GetWorld();

	m_shape = static_cast<Shape*>(GetEntity()->GetComponentByType(m_shapeType));

	assert(m_transform);
	assert(m_shape);
	assert(m_b2World);

	glm::vec2 size = m_shape->GetSize();

	glm::vec3 pos = m_transform->GetPos();
	glm::quat angle = m_transform->GetRot();
	m_b2BodyDef.position.Set(pos.x / s_B2RatioPos, pos.y / s_B2RatioPos);
	glm::vec3 rad = glm::eulerAngles(angle);
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
	size /= 2.f;
	m_b2Body = m_b2World->CreateBody(&m_b2BodyDef);
	m_b2Body->SetLinearDamping(m_linearDampling);

	// shape allocation
	if(m_forceCircle)
	{
		b2CircleShape* circleShape = new b2CircleShape();
		m_b2Shape = circleShape;

		circleShape->m_radius = size.x / s_B2RatioPos;
	}
	else
	{
		b2PolygonShape* polygonShape = new b2PolygonShape();
		m_b2Shape = polygonShape;

		polygonShape->SetAsBox(size.x / s_B2RatioPos, size.y / s_B2RatioPos);
	}
	
	m_b2Fixture = m_b2Body->CreateFixture(m_b2Shape, m_density);
	m_b2Fixture->SetFriction(m_friction);
	m_b2Fixture->SetUserData(static_cast<void*>(GetEntity()));
	m_b2Fixture->SetRestitution(m_restitution);
}


void RigidBody::OnTick(const natU64 _dt)
{
	if(m_b2BodyDef.type != b2_staticBody)
	{
		// warning global coordinates (not local !)
		b2Vec2 b2_pos = m_b2Body->GetPosition();
		m_transform->m_pos.x = b2_pos.x * s_B2RatioPos;
		m_transform->m_pos.y = b2_pos.y * s_B2RatioPos;

		glm::vec3 angle(0.f, 0.f, m_b2Body->GetAngle());
		m_transform->m_rot = glm::quat(angle);
	}
}

void RigidBody::OnDeInit()
{
	assert(m_b2World != nullptr);
	assert(m_b2Body != nullptr);
	m_b2World->DestroyBody(m_b2Body);

	delete m_b2Shape;
	m_b2Shape = nullptr;
}

void RigidBody::OnEnable()
{
	assert(m_b2Body != nullptr);

	if(m_b2Fixture == nullptr)
	{
		m_b2Fixture = m_b2Body->CreateFixture(m_b2Shape, m_density);
		m_b2Fixture->SetFriction(0.2f);
		m_b2Body->SetLinearDamping(10.f);
	}

	glm::vec3 pos = m_transform->GetPos();
	m_b2Body->SetTransform(b2Vec2(pos.x/s_B2RatioPos, pos.y/s_B2RatioPos), 0.f);

	m_b2Body->SetActive(true);
}

void RigidBody::OnDisable()
{
	assert(m_b2Body != NULL);
	m_b2Body->SetActive(false);
}

void RigidBody::SetAngle(glm::quat& _angle) 
{ 
	assert(m_b2Body); 
	glm::vec3 euler = glm::eulerAngles(_angle);
	m_b2Body->SetTransform(m_b2Body->GetPosition(), euler.z);
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