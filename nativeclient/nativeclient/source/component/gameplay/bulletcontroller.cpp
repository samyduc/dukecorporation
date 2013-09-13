#include "component/gameplay/bulletcontroller.h"

#include "base/entity.h"
#include "base/component.h"

#include "component/transform.h"
#include "component/gameplay/spawned.h"
#include "component/gameplay/spawner.h"
#include "component/gameplay/baseweapon.h"

#include "entity/bullet.h"

#include <assert.h>

namespace Natorium
{

BulletController::BulletController()
	: m_damage(10)
	, m_lifetime(2000)
{
}

BulletController::~BulletController()
{
}

void BulletController::OnInit()
{
	m_time = 0;
}

void BulletController::OnDeInit()
{

}

void BulletController::OnTick(const natU64 _dt)
{
	// apply force
	RigidBody* rigidbody = GetEntity()->GetComponent<RigidBody>();
	Transform* transform = GetEntity()->GetComponent<Transform>();

	//glm::vec3 impulse = transform->m_forward * 100.f * static_cast<natF32>(_dt);
	glm::mat4 matrix(1.f);
	matrix *= glm::mat4_cast(transform->m_rot);
	glm::vec3 impulse(matrix[2].x, matrix[2].y, matrix[2].z);
	impulse *= 100.f * static_cast<natF32>(_dt);

	rigidbody->ApplyLinearImpulse(impulse);

	m_time += _dt;

	if(m_time >= m_lifetime)
	{
		Spawned* spawned = GetEntity()->GetComponent<Spawned>();
		spawned->Kill();
	}
}

void BulletController::OnEnterCollide(Contact* _contact)
{
	Spawned* spawned = GetEntity()->GetComponent<Spawned>();

	assert(spawned);

	//if(spawned)
	//{
		BaseWeapon* weapon = static_cast<BaseWeapon*>(spawned->GetSpawner());
		weapon->OnHit(_contact);
	//}
}

}