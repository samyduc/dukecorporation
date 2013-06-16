#include "component/gameplay/bulletcontroller.h"

#include "base/entity.h"
#include "base/component.h"
#include "component/transform.h"

#include "entity/bullet.h"

#include <assert.h>

namespace Natorium
{

BulletController::BulletController()
	: m_weapon(nullptr)
	, m_damage(10)
{
}

BulletController::~BulletController()
{
}

void BulletController::OnInit()
{

}

void BulletController::Clone(Entity* _entity) const
{
	BulletController* component = _entity->AddComponent<BulletController>();
	component->m_damage = m_damage;
}

void BulletController::OnDeInit()
{

}

void BulletController::OnTick(const natU64 _dt)
{
	//Transform* transform = GetEntity()->GetComponent<Transform>();
	//transform->m_pos += static_cast<natF32>(_dt) * transform->m_forward;

	// apply force
	RigidBody* rigidbody = GetEntity()->GetComponent<RigidBody>();
	Transform* transform = GetEntity()->GetComponent<Transform>();
	glm::vec3 impulse = transform->m_forward*400.f;
	rigidbody->ApplyLinearImpulse(impulse);
}

void BulletController::OnEnterCollide(Contact* _contact)
{
	assert(m_weapon);

	m_weapon->OnHit(_contact);
}

}